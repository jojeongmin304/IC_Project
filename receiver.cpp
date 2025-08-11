#include "receiver.h"

Receiver::Receiver(QObject *parent)
    : QThread(parent), m_socket(-1), m_isRunning(true)
{
}

Receiver::~Receiver()
{
    m_isRunning = false; // 스레드 루프를 안전하게 종료시킵니다.
    if (m_socket >= 0) {
        close(m_socket); // 소켓을 닫습니다.
    }
    wait(); // 스레드가 완전히 종료될 때까지 기다립니다.
}

bool Receiver::initializeCanSocket()
{
    // 1. CAN raw 소켓 생성
    m_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (m_socket < 0) {
        qDebug() << "CAN socket creation failed!";
        return false;
    }

    // 2. 사용할 CAN 인터페이스 지정 (can1)
    ifreq ifr;
    std::strcpy(ifr.ifr_name, "can1");
    if (ioctl(m_socket, SIOCGIFINDEX, &ifr) < 0) {
        qWarning() << "Could not find CAN interface 'can1'!";
        close(m_socket);
        return false;
    }

    // 3. 소켓을 CAN 인터페이스에 바인드
    sockaddr_can addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(m_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        qDebug() << "Failed to bind CAN socket!";
        close(m_socket);
        return false;
    }

    return true;
}

void Receiver::run()
{
    can_frame frame;

    qDebug() << "listening for CAN messages on can1...\n";

    while (m_isRunning) {
        // CAN 프레임이 들어올 때까지 대기합니다.
        int nbytes = read(m_socket, &frame, sizeof(struct can_frame));

        if (nbytes < 0) {
            // 데이터가 없을 때 계속 오류를 출력하지 않도록 잠시 대기합니다.
            qDebug() << "Error reading CAN frame!\n";
            msleep(10);
            continue;
        }

        // --- 여기서 데이터를 해석합니다 (사용자님의 아두이노 코드에 맞춤) ---

        // 아두이노에서 보낸 CAN ID가 0x10인지 확인합니다.
        if (frame.can_id == 0x10) {
            // 수신된 데이터의 길이가 2바이트 이상인지 확인합니다.
            if (frame.can_dlc >= 2) {
                // 2개의 바이트(data[0], data[1])를 다시 하나의 int로 합칩니다.
                // data[0]이 상위 바이트(highByte), data[1]이 하위 바이트(lowByte)입니다.
                int receivedSpeed = (frame.data[0] << 8) | frame.data[1];

                // 디버깅을 위해 터미널에 수신된 속도 값을 출력합니다.
                qDebug() << "CAN data received:" << receivedSpeed;

                // 새로운 속도 값을 받았다고 신호를 보냅니다.
                emit newSpeedReceived(receivedSpeed);

                qDebug() << "Received CAN ID: " << frame.can_id << '\n';
            }
        }
    }
}
