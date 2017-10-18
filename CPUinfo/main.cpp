#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <procfs.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext*context = engine.rootContext();
    procfs myprocfs;
    context->setContextProperty("procfs",&myprocfs);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
