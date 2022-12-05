#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "RealTimeObjectModel.h"
#include "ArchiveTrackModel.h"
#include "FakeStorageAccessor.h"
#include "Object.h"

// #include <gsl/gsl>

#include <iostream>
#include <memory>
#include <thread>

int main (int argc, char** argv)
{
    std::cout << "Start program" << std::endl;
    QApplication app(argc, argv);

    auto realtimeViewController = std::make_shared<RealTimeObjectModel>();
    auto storage = std::make_shared<FakeStorageAccessor>();
    auto archiveTrackModel = std::make_shared<ArchiveTrackModel>(storage);

    QObject::connect(
        storage.get(), &FakeStorageAccessor::addedObject,
        realtimeViewController.get(), &RealTimeObjectModel::addSeries);
    QObject::connect(
        storage.get(), &FakeStorageAccessor::updatedObject,
        realtimeViewController.get(), &RealTimeObjectModel::updateSeries);
    QObject::connect(
        storage.get(), &FakeStorageAccessor::removedObject,
        realtimeViewController.get(), &RealTimeObjectModel::removeSeries);

    QQmlApplicationEngine engine;

    auto context = engine.rootContext();
    context->setContextProperty("realtimeViewController", realtimeViewController.get());
    context->setContextProperty("archiveTrackModel", archiveTrackModel.get());

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    std::thread([realtimeViewController, storage](){
        static int id1 = 0;
        static int x1 = 0;
        static int y1 = 0;
        auto obj1 = new Object(std::to_string(id1).data(), x1, y1, State::Found);
        storage->updateRealtimeTrack(obj1);
        static int id2 = 1;
        static int x2 = 0;
        static int y2 = 100;
        auto obj2 = new Object(std::to_string(id2).data(), x2, y2, State::Found);
        storage->updateRealtimeTrack(obj2);
        while(true)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));

            if(x1 > 100 && y2 < 0)
            {
                break;
            }
            x1 += 5;
            y1 += 5;

            x2 += 5;
            y2 -= 5;

            if(x1 > 100)
            {
                auto obj1 = new Object(std::to_string(id1).data(), x1, y1, State::Lost);
                storage->updateRealtimeTrack(obj1);
            }
            else
            {
                auto obj1 = new Object(std::to_string(id1).data(), x1, y1, State::Leading);
                storage->updateRealtimeTrack(obj1);
            }

            if(y2 < 0)
            {
                auto obj2 = new Object(std::to_string(id2).data(), x2, y2, State::Lost);
                storage->updateRealtimeTrack(obj2);
                break;
            }
            else
            {
                auto obj2 = new Object(std::to_string(id2).data(), x2, y2, State::Leading);
                storage->updateRealtimeTrack(obj2);
            }
        }
    }).detach();


    return app.exec();
}
