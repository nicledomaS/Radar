#pragma once

#include <QObject>
#include <QString>

enum class State
{
    Found,
    Leading,
    Lost
};

struct Object: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id MEMBER id)
    Q_PROPERTY(int x MEMBER x)
    Q_PROPERTY(int y MEMBER y)
    // Q_PROPERTY(State state MEMBER state)
public:

    Object(QString id, int x, int y, State state, QObject *parent = nullptr)
        : QObject(parent),
        id(id),
        x(x),
        y(y),
        state(state)
    {
    }

    QString id;
    int x;
    int y;
    State state;
};