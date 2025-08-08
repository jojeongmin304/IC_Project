#ifndef SPEEDPROVIDER_H
#define SPEEDPROVIDER_H

#include <QObject>
#include <QTimer>

class SpeedProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speed READ speed NOTIFY speedChanged)

public:
    explicit SpeedProvider(QObject *parent = nullptr);

    int speed() const;
    //---외부에서 실제 속도값을 받아오는 setter함수---
    void setSpeed(int newSpeed);

signals:
    void speedChanged();

// private slots:
//     void updateSpeed();

private:
    int m_speed;
    //bool m_isSpeedingUp;
};

#endif // SPEEDPROVIDER_H
