#include "speedprovider.h"

SpeedProvider::SpeedProvider(QObject *parent)
    : QObject(parent), m_speed(0), m_isSpeedingUp(true)
{
    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SpeedProvider::updateSpeed);
    timer->start(50);
}

int SpeedProvider::speed() const
{
    return m_speed;
}

void SpeedProvider::updateSpeed()
{
    if (m_isSpeedingUp) {
        m_speed += 2;
        if (m_speed >= 220) {
            m_speed = 220;
            m_isSpeedingUp = false;
        }
    } else {
        m_speed -= 2;
        if (m_speed <= 0) {
            m_speed = 0;
            m_isSpeedingUp = true;
        }
    }
    emit speedChanged();
}
