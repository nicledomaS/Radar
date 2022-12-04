#include "RealTimeObjectModel.h"
#include "Object.h"

RealTimeObjectModel::RealTimeObjectModel(QObject *parent)
    : QObject(parent)
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