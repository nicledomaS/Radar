#pragma once
#include <QObject>

struct Object;

class RealTimeObjectModel: public QObject
{
    Q_OBJECT
public:
    RealTimeObjectModel(QObject *parent = nullptr);

public slots:
    void add(const Object* object);
    void update(Object* object);
    void remove(const Object* object);

signals:
    void addSeries(const Object* object);
    void updateSeries(const Object* object);
    void removeSeries(const Object* object);
};