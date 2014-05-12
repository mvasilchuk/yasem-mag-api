#ifndef STBDOWNLOADMANAGER_H
#define STBDOWNLOADMANAGER_H


#include <QObject>


namespace yasem
{
class MagProfile;

class StbDownloadManager : public QObject
{
    Q_OBJECT
public:
    explicit StbDownloadManager(MagProfile *profile);

signals:

public slots:
    bool AddJob(const QString &urlToDownload, const QString &filePath);
    bool AddMeasureJob(const QString &urlToDownload);
    void AdjustJobPriority(long id, bool rise);
    bool DeleteJob(const QString &id, bool deleteFile);
    QString GetMeasureInfo();
    QString GetQueueInfo(const QString &idList);
    void InvalidateCatalog(const QString &strVal);
    void PlayDownloadedMedia(long id);
    void RestoreJobs(const QString &val);
    bool StartJob(long id);
    bool StopJob(long id);

    QString GetQueueInfo();
protected:
    MagProfile *profile;
};

}

#endif // STBDOWNLOADMANAGER_H
