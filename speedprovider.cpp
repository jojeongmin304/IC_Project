#include "speedprovider.h"

SpeedProvider::SpeedProvider(QObject *parent)
    : QObject(parent), m_speed(0)//, m_isSpeedingUp(true)
{
    //---가짜 속도값 만들기위한 타이머---
    // auto timer = new QTimer(this);
    // connect(timer, &QTimer::timeout, this, &SpeedProvider::updateSpeed);
    // timer->start(50);
}

int SpeedProvider::speed() const
{
    return m_speed;
}

void SpeedProvider::setSpeed(int newSpeed) {
    // 새로운 속도 값이 현재 속도와 다를 때만 업데이트하고 신호를 보냅니다.
    // 이렇게 하면 불필요한 신호 발생을 막아 성능에 도움이 됩니다.
    if (m_speed != newSpeed) {
        m_speed = newSpeed;
        emit speedChanged(); // QML에 값이 변경되었음을 알립니다.
    }
}

// void SpeedProvider::updateSpeed()
// {
//     if (m_isSpeedingUp) {
//         m_speed += 2;
//         if (m_speed >= 220) {
//             m_speed = 220;
//             m_isSpeedingUp = false;
//         }
//     } else {
//         m_speed -= 2;
//         if (m_speed <= 0) {
//             m_speed = 0;
//             m_isSpeedingUp = true;
//         }
//     }
//     emit speedChanged();
// }
