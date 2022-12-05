#include "ArchiveTrackModel.h"
#include "FakeStorageAccessor.h"
#include "Object.h"

ArchiveTrackModel::ArchiveTrackModel(std::shared_ptr<FakeStorageAccessor> storage, QObject *parent)
    : QObject(parent),
    m_storage(storage)
{
    connect(this, &ArchiveTrackModel::update, this, &ArchiveTrackModel::updateView);
}

void ArchiveTrackModel::updateView(const QString& startDate, const QString& endDate)
{
    auto tracks = m_storage->getTraks(startDate, endDate);
    for(const auto track: tracks)
    {
        emit addArchiveSeries(track);
    }
}