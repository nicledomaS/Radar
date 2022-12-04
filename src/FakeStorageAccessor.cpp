#include "FakeStorageAccessor.h"

QMap<QString, QList<Object*>> FakeStorageAccessor::getTraks(const QString& startDate, const QString& endDate) const
{
    return m_tracks;
}

void FakeStorageAccessor::updateRealtimeTrack(Object* object)
{

    auto it = m_tracks.find(object->id);
    if(it == m_tracks.end() && (object->state == State::Found || object->state == State::Leading))
    {
        it = m_tracks.insert(object->id, { object });
        emit addedObject(object);
    }
    else if(object->state == State::Leading)
    {
        (*it).push_back(object);
        emit updatedObject(object);
    }
    else if(object->state == State::Lost)
    {
        emit removedObject(object);
    }
    else
    {
        //log error
    }
}