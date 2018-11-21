#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <cppgpio.hpp>
#include <Valve.hpp>

int main(int argc, char *argv[])
{
    GPIO::GPIOBase::simulation(true);
    Valve normalValve(6);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
