#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "RealTimeObjectModel.h"

// #include <gsl/gsl>

#include <iostream>
#include <memory>
#include <thread>

int main (int argc, char** argv)
{
    std::cout << "Start program" << std::endl;
    QApplication app(argc, argv);

    auto realtimeViewController = std::make_shared<RealTimeObjectModel>();

    QQmlApplicationEngine engine;

    auto context = engine.rootContext();
    context->setContextProperty("realtimeViewController", realtimeViewController.get());

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    std::thread([realtimeViewController](){
        static int id = 0;
        static int x = 0;
        static int y = 0;
        auto obj = new Object(std::to_string(id++).data(), x, y);
        realtimeViewController->add(obj);
        while(true)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            obj->x += 5;
            obj->y += 5;
            realtimeViewController->update(obj);
            if(obj->x > 100)
            {
                realtimeViewController->remove(obj);
                break;
            }
        }
    }).detach();


    return app.exec();
}
