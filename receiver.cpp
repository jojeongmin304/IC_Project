#include "receiver.h"

// DataUnion은 더 이상 필요 없으므로 삭제합니다.

Receiver::Receiver(QObject *parent)
    : QThread(parent), m_socket(-1), m_isRunning(true)
{
}

Receiver::~Receiver()
{
    m_isRunning = false; // 스레드 루프를 종료시킵니다.
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
        qWarning() << "CAN 소켓 생성 실패!";
        return false;
    }

    // 2. 사용할 CAN 인터페이스 지정 (예: "can0")
    ifreq ifr;
    std::strcpy(ifr.ifr_name, "can1");
    if (ioctl(m_socket, SIOCGIFINDEX, &ifr) < 0) {
        qWarning() << "CAN 인터페이스 'can1'를 찾을 수 없습니다!";
        close(m_socket);
        return false;
    }

    // 3. 소켓을 CAN 인터페이스에 바인드
    sockaddr_can addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(m_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        qWarning() << "CAN 소켓 바인드 실패!";
        close(m_socket);
        return false;
    }

    return true;
}

void Receiver::run()
{
    can_frame frame;

    while (m_isRunning) {
        // CAN 프레임이 들어올 때까지 대기합니다.
        int nbytes = read(m_socket, &frame, sizeof(struct can_frame));

        if (nbytes < 0) {
            qWarning() << "CAN 프레임 읽기 오류!";
            continue; // 오류가 발생해도 루프를 계속합니다.
        }

        if (nbytes < sizeof(struct can_frame)) {
            qWarning() << "불완전한 CAN 프레임 수신";
            continue;
        }

        // --- 여기서 데이터를 해석합니다 (아두이노 코드에 맞게 수정) ---

        // 아두이노에서 보낸 CAN ID가 0x10인지 확인합니다.
        if (frame.can_id == 0x10) {
            // 수신된 데이터의 길이가 2바이트 이상인지 확인합니다.
            if (frame.can_dlc >= 2) {
                // 2개의 바이트(data[0], data[1])를 다시 하나의 int로 합칩니다.
                // data[0]이 상위 바이트(highByte), data[1]이 하위 바이트(lowByte)입니다.
                int receivedSpeed = (frame.data[0] << 8) | frame.data[1];

                // 새로운 속도 값을 받았다고 신호를 보냅니다.
                emit newSpeedReceived(receivedSpeed);
            }
        }
    }
}
