#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
#include <QObject>
#include <QDebug>
#include <QThread>
#include "speedprovider.h"
#include "receiver.h"

// --- 메인 함수 ---
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    //1.---객체 생성---
    SpeedProvider speedProvider; //QML과 데이터를 주고받을 sppedProvider객체
    Receiver canReceiver; //CAN 버스에서 데이터를 수신할 Receiver 객체

    //2.---CAN 수신기 초기화 및 스레드 시작---
    if (!canReceiver.initializeCanSocket()) {
        qCritical() << "CAN 수신기 초기화 실패! 프로그램을 종료합니다.";
        return -1;
    }

    //3.---Receiver와 SpeedProvider 연결 (가장 중요) ---
    // canReceiver가 newSpeedReceived signals 신호를 보내면(emit),
    // speedProvider의 세터함수가 그 신호를 받아 실행됩니다.
    QObject::connect(&canReceiver, &Receiver::newSpeedReceived,
                     &speedProvider, &SpeedProvider::setSpeed);

    //4.---QML에 C++객체 노출--- ****중요!!!!!!!!!!
    engine.rootContext()->setContextProperty("speedController", &speedProvider);

    //5.---CAN수신 thread 백그라운드에서 시작---
    canReceiver.start();

    // Main.qml 파일을 로드합니다.
    const QUrl url(QStringLiteral("qrc:/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();

    // --- 7. 프로그램 종료 처리 ---

    // 애플리케이션이 종료되기 전에 CAN 수신 스레드를 안전하게 중지시킵니다.
    canReceiver.quit();
    canReceiver.wait();
}

#include "main.moc"







