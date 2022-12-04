#include "RealTimeObjectModel.h"

#include <QScatterSeries>

RealTimeObjectModel::RealTimeObjectModel(QObject *parent)
    : ChartViewController(parent)
{
}

void RealTimeObjectModel::add(const Object* object)
{
    emit addSeries(object);
}

void RealTimeObjectModel::update(Object* object)
{
    emit updateSeries(object);
}

void RealTimeObjectModel::remove(const Object* object)
{
    emit removeSeries(object);
}