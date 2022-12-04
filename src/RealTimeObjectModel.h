#pragma once

#include "ChartViewController.h"

#include <QString>
#include <QMap>

class RealTimeObjectModel: public ChartViewController
{
public slots:
    RealTimeObjectModel(QObject *parent = nullptr);

    void add(const Object* object);
    void update(Object* object);
    void remove(const Object* object);

private:
    QMap<QString, QAbstractSeries*> points;
};