#include "stbdownloadmanager.h"
#include "macros.h"
#include "magprofile.h"

#include <QJsonArray>
#include <QJsonObject>

using namespace yasem;

StbDownloadManager::StbDownloadManager(MagProfile *profile)
{
    this->profile = profile;
}

bool StbDownloadManager::AddJob(const QString &urlToDownload, const QString &filePath)
{
    STUB() << urlToDownload << filePath;
    return false;
}

bool StbDownloadManager::AddMeasureJob(const QString &urlToDownload)
{
    STUB() << urlToDownload;
    return false;
}

void StbDownloadManager::AdjustJobPriority(long id, bool rise)
{
    STUB() << id << rise;
}

bool StbDownloadManager::DeleteJob(const QString &id, bool deleteFile)
{
    STUB() << id << deleteFile;
    return false;
}

/**
 * Similar to GetQueueInfo.
 * Get information about special (test) job. If test job does not exist then return nothing.
 * @return See GetQueueInfo
 */
QString StbDownloadManager::GetMeasureInfo()
{
    STUB();
    return GetQueueInfo("[-1]");
}

/**
 * Get info about queue of jobs.
 * @param [idList] If list is not empty information for given jobs will be returned. Whole queue will be returned in other case.
 *   @example "1.0, 2.0, 3.0"
 * @return {String} Contain JavaScript array of objects. Size of the array depends on operation’s result.
 * Each object should have these fields:
 *   id - numeric (0-4294967295) ID of the job
 *   state - state number (0 – Stopped, 1 – WaitingQueue, 2 – Running, 3 – Completed, 4 – TemporaryError, 5 - PermanentError)
 *   stateStr - state string (localization is supported for this string resource)
 *   url - URL of remote file
 *   filePath - path to local storage
 *   progressPct - progress of downloading process (expressed in percents: 0-100)
 *   sizeDone - size of already downloaded data
 *   sizeTotal - total file size (value -1 if undefined)
 *   prio - priority of the job
 *   attempt - number of the download attempt
 */
QString StbDownloadManager::GetQueueInfo(const QString &idList)
{
    STUB() << idList;

    QJsonArray arr = QJsonDocument::fromJson(QByteArray(idList.toUtf8())).array();

    QJsonArray result;

    for(int index=0; index < arr.size(); index++)
    {
        QJsonObject info;
        info.insert("id", arr.at(index));
        info.insert("state", 3);
        info.insert("stateStr", QString("Completed"));
        info.insert("url", QString());
        info.insert("filePath", QString());
        info.insert("progressPct", 100);
        info.insert("sizeDone", 1024);
        info.insert("sizeTotal", 1024);
        info.insert("prio", 0);
        info.insert("attempt", 1);

        result.append(arr);
    }

    return QString(QJsonDocument(result).toJson(QJsonDocument::Compact));
}

/**
 * Get info about queue of jobs.
 * @param [idList] If list is not empty information for given jobs will be returned. Whole queue will be returned in other case.
 *   @example "1.0, 2.0, 3.0"
 * @return {String} Contain JavaScript array of objects. Size of the array depends on operation’s result.
 * Each object should have these fields:
 *   id - numeric (0-4294967295) ID of the job
 *   state - state number (0 – Stopped, 1 – WaitingQueue, 2 – Running, 3 – Completed, 4 – TemporaryError, 5 - PermanentError)
 *   stateStr - state string (localization is supported for this string resource)
 *   url - URL of remote file
 *   filePath - path to local storage
 *   progressPct - progress of downloading process (expressed in percents: 0-100)
 *   sizeDone - size of already downloaded data
 *   sizeTotal - total file size (value -1 if undefined)
 *   prio - priority of the job
 *   attempt - number of the download attempt
 */
QString StbDownloadManager::GetQueueInfo()
{
    STUB();
    return "[]";
}

void StbDownloadManager::InvalidateCatalog(const QString &strVal)
{
    STUB() << strVal;
}

void StbDownloadManager::PlayDownloadedMedia(long id)
{
    STUB() << id;
}

void StbDownloadManager::RestoreJobs(const QString &val)
{
    STUB() << val;
}

bool StbDownloadManager::StartJob(long id)
{
    STUB() << id;
    return false;
}

bool StbDownloadManager::StopJob(long id)
{
    STUB() << id;
    return false;
}
