#include "receiver.h"
#include <QDebug>
#include <QByteArray>

Receiver::Receiver(QObject *parent)
    : QThread(parent), m_socket(-1), m_isRunning(true)
{
}

Receiver::~Receiver()
{
    m_isRunning = false;
    if (m_socket >= 0) {
        close(m_socket);
    }
    wait();
}

bool Receiver::initializeCanSocket()
{
    m_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (m_socket < 0) {
        qWarning() << "[Receiver] CAN socket creation failed!";
        return false;
    }

    ifreq ifr;
    std::strcpy(ifr.ifr_name, "can1");
    if (ioctl(m_socket, SIOCGIFINDEX, &ifr) < 0) {
        qWarning() << "[Receiver] Could not find CAN interface 'can1'!";
        close(m_socket);
        return false;
    }

    sockaddr_can addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(m_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        qWarning() << "[Receiver] Failed to bind CAN socket!";
        close(m_socket);
        return false;
    }
    qDebug() << "[Receiver] CAN socket initialized on can1.";
    return true;
}

void Receiver::run()
{
    can_frame frame;
    qDebug() << "[Receiver] Thread started, listening for messages...";

    while (m_isRunning) {
        int nbytes = read(m_socket, &frame, sizeof(struct can_frame));

        if (nbytes > 0) {
            // 수신된 모든 프레임 정보 출력
            qDebug() << "[Receiver] Frame Received - ID:" << Qt::hex << frame.can_id
                     << "DLC:" << frame.can_dlc
                     << "Data:" << QByteArray(reinterpret_cast<const char*>(frame.data), frame.can_dlc).toHex(' ');

            // 아두이노에서 보낸 속도 데이터 처리
            if (frame.can_id == 0x10 && frame.can_dlc >= 2) {
                int receivedRPM = (frame.data[0] << 8) | frame.data[1]; //rpm값 으로 2 바이트 합치기
                //실수를 사용 하여 정밀하게 계산
                double speed_ms = (receivedRPM * 3.141592 * 0.068) / 60.0;
                int speed_kmh = speed_ms * 3.6;

                //최종 결과만 정수로 변환하여 시그널 전송 by 명시적 형변환
                emit newSpeedReceived(static_cast<int>(speed_kmh));
            }
        } else {
            msleep(20); // CPU 과부하 방지
        }
    }
}
