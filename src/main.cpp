#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

// #include <gsl/gsl>

#include <iostream>

int main (int argc, char** argv)
{
    std::cout << "Start program" << std::endl;
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
