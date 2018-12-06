#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <wiringPi.h>
#include <Valve.hpp>


int main(int argc, char *argv[])
{
    wiringPiSetupGpio();
    Valve normalValve(5);
    Valve secretValve(6);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
