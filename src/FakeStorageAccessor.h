#pragma once

#include <QObject>
#include <QMap>

#include "Object.h"

class FakeStorageAccessor: public QObject
{
    Q_OBJECT
public:
    QMap<QString, QList<Object*>> getTraks(const QString& startDate, const QString& endDate) const;
    
    void updateRealtimeTrack(Object* object);

signals:
    void addedObject(Object* object) const;
    void updatedObject(Object* object) const;
    void removedObject(Object* object) const;


private:
    QMap<QString, QList<Object*>> m_tracks;
};