#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTimer>
#include <QObject>
#include "speedprovider.h"

// --- 메인 함수 ---
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // 1. SpeedProvider 객체를 생성합니다.
    SpeedProvider speedProvider;
    // 2. "speedController"라는 이름으로 QML 환경에 노출시킵니다. ****중요!!!!!!!!!!
    engine.rootContext()->setContextProperty("speedController", &speedProvider);

    // Main.qml 파일을 로드합니다.
    const QUrl url(QStringLiteral("qrc:/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

#include "main.moc"







