#pragma once

#include <QObject>
#include <QAbstractSeries>
#include <QtQml/qqml.h>

struct Object: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id MEMBER id)
    Q_PROPERTY(int x MEMBER x)
    Q_PROPERTY(int y MEMBER y)
public:
    Object(QString id, int x, int y, QObject *parent = nullptr)
        : QObject(parent),
        id(id),
        x(x),
        y(y)
    {
    }

    QString id;
    int x;
    int y;
};


class ChartViewController: public QObject
{
    Q_OBJECT
public:
    ChartViewController(QObject *parent = nullptr)
        : QObject(parent)
    {}

signals:
    void addSeries(const Object* series);
    void updateSeries(const Object* series);
    void removeSeries(const Object* series);
    void removeAllSeries(const Object* series);
};