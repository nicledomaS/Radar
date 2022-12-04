#pragma once

#include <QObject>
#include <QList>

#include "Object.h"

class FakeStorageAccessor;

class ArchiveTrackModel: public QObject
{
    Q_OBJECT
public:
    ArchiveTrackModel(std::shared_ptr<FakeStorageAccessor> storage, QObject *parent = nullptr);

public slots:
    void updateView(const QString& startDate, const QString& endDate);

signals:
    void addArchiveSeries(const QList<Object*>& series);
    void update(const QString& startDate, const QString& endDate);

private:
    std::shared_ptr<FakeStorageAccessor> m_storage;
};
