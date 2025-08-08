#ifndef RECEIVER_H
#define RECEIVER_H

#include <QThread>
#include <QDebug>

// C++ 시스템 헤더
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <cstring>

// CAN 통신을 백그라운드에서 처리하기 위해 QThread를 상속받습니다.
class Receiver : public QThread
{
    Q_OBJECT

public:
    explicit Receiver(QObject *parent = nullptr);
    ~Receiver();

    // CAN 소켓을 초기화하는 함수
    bool initializeCanSocket();

signals:
    // 새로운 속도 값을 받았을 때 보낼 C++ 내부용 신호
    void newSpeedReceived(int speed);

protected:
    // QThread가 시작될 때 이 함수가 별도의 스레드에서 실행됩니다.
    void run() override;

private:
    int m_socket; // CAN 소켓 파일 디스크립터
    bool m_isRunning; // 스레드 실행 상태를 제어하는 플래그
};

#endif // RECEIVER_H
