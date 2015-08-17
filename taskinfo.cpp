#include "taskinfo.h"
#include "macros.h"
#include "magprofile.h"

#include <QNetworkRequest>
#include <QNetworkReply>

using namespace yasem;

TaskInfo::TaskInfo(int id, const QString &url, const QString &fileName,
                   const QDateTime &startTime, const QDateTime &endTime,
                   QObject* parent):
    QObject(parent),
    m_id(id),
    m_url(url),
    m_file_name(fileName),
    m_start_time(startTime),
    m_end_time(endTime),
    m_state(STATE_COMPLETED),
    m_error_code(ERROR_SUCCESSFUL),
    m_manager(NULL),
    m_reply(NULL),
    m_file(NULL),
    m_request_aborted(false)

{
    m_task_timer.setSingleShot(true);
    connect(this, &TaskInfo::errorHappened, this, &TaskInfo::onError);
}

TaskInfo::~TaskInfo()
{
    STUB();
    if(m_reply)
    {
        m_reply->deleteLater();
        m_reply = 0;
    }
}

QJsonObject TaskInfo::toJson() const
{
    QJsonObject result;
    result.insert("id", m_id);
    result.insert("state", m_state);
    result.insert("errorCode", m_error_code);
    result.insert("fileName", m_file_name);
    result.insert("url", m_url);
    result.insert("startTime", m_start_time.toMSecsSinceEpoch() / 1000);
    result.insert("endTime", m_end_time.toMSecsSinceEpoch() / 1000);
    return result;
}

TaskInfo *TaskInfo::fromJson(const QJsonObject& json, QObject* parent)
{
    STUB() << json;
    if(json.contains("id")
            && json.contains("state")
            && json.contains("errorCode")
            && json.contains("fileName")
            && json.contains("url")
            && json.contains("startTime")
            && json.contains("endTime"))
    {
        TaskInfo* task = new TaskInfo(json.value("id").toInt(),
                                      json.value("url").toString(),
                                      json.value("fileName").toString(),
                                      QDateTime::fromMSecsSinceEpoch(json.value("startTime").toVariant().toLongLong()),
                                      QDateTime::fromMSecsSinceEpoch(json.value("endTime").toVariant().toLongLong()),
                                      parent);

        task->m_state = (TaskState)json.value("state").toInt();
        task->m_error_code = (ErrorCode)json.value("errorCode").toInt();

        if(task->m_end_time > QDateTime::currentDateTime())
        {
            DEBUG() << "Task was already finished";
            return NULL;
        }

        DEBUG() << "Task loaded";
        return task;
    }
    else
    {
        WARN() << "Incorrect json data" << QString(QJsonDocument(json).toJson(QJsonDocument::Compact));
        return NULL;
    }
}

TaskInfo::ErrorCode TaskInfo::scheduleStart()
{
    m_state = STATE_WAITING_FOR_START;
    qint64 timeout = m_start_time.toMSecsSinceEpoch() - QDateTime::currentMSecsSinceEpoch();
    STUB() << "Scheduling task start in" << timeout / 1000 << "sec";

    if(timeout <= 0)
    {
        return startRecord();
    }
    else
    {
        disconnect(&m_task_timer);
        connect(&m_task_timer, &QTimer::timeout, this, &TaskInfo::startRecord);
        m_task_timer.start(timeout);
    }
    return ERROR_SUCCESSFUL;
}

TaskInfo::ErrorCode TaskInfo::scheduleStop()
{
    qint64 timeout = m_end_time.toMSecsSinceEpoch() - QDateTime::currentMSecsSinceEpoch();
    STUB() << "Scheduling task stop in" << timeout / 1000 << "sec";

    disconnect(&m_task_timer);
    connect(&m_task_timer, &QTimer::timeout, this, &TaskInfo::stopRecord);
    if(timeout > 0)
        m_task_timer.start(timeout);
    else
        stopRecord();
    return ERROR_SUCCESSFUL;
}

TaskInfo::ErrorCode TaskInfo::startRecord()
{
    STUB();
    m_state = STATE_RECORDING;
    scheduleStop();

    const QString real_file_name = MagProfile::translateStbPathToLocal(m_file_name);
    DEBUG() << "Writing video to" << real_file_name;

    m_file = new QFile(real_file_name, this);
    if(!m_file->open(QIODevice::WriteOnly /* | QIODevice::Append */))
    {
        emit errorHappened(ERROR_CANNOT_OPEN_OUTPUT_FILE);
        return ERROR_CANNOT_OPEN_OUTPUT_FILE;
    }

    m_manager = new QNetworkAccessManager(this);    
    m_reply = m_manager->get(QNetworkRequest(m_url));

    connect(m_reply, &QNetworkReply::readyRead, this, &TaskInfo::httpReadyRead);
    connect(m_reply, &QNetworkReply::downloadProgress, [=](qint64 bytesReceived, qint64 bytesTotal){
        /*DEBUG() << qPrintable(
                       QString("Recording task %1: downloaded %2 bytes of %3")
                            .arg(m_id)
                            .arg(bytesReceived)
                            .arg(bytesTotal)
                       );
                       */
    });
    connect(m_reply,
            static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),
            this, &TaskInfo::onNetworkError);

    return ERROR_SUCCESSFUL;

}

TaskInfo::ErrorCode TaskInfo::stopRecord()
{
    STUB();
    stopDownloading();
    m_state = STATE_COMPLETED;
    return ERROR_SUCCESSFUL;
}

void TaskInfo::httpReadyRead()
{
    // this slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply
    if (m_file)
    {
        qint64 len = m_file->write(m_reply->readAll());
        if(len < 0)
            emit errorHappened(ERROR_CANNOT_WRITE_FILE);
    }
}

void TaskInfo::onNetworkError(QNetworkReply::NetworkError error)
{
    WARN() << error;
    if(error != QNetworkReply::OperationCanceledError)
        emit errorHappened(ERROR_STREAM_OPENING_ERROR);
}

void TaskInfo::onError(TaskInfo::ErrorCode code)
{
    STUB() << code;
    m_state = STATE_ERROR;
    m_error_code = code;
    stopDownloading();
}

void TaskInfo::stopDownloading()
{
    STUB();

    if(m_reply && m_reply->isOpen())
        m_reply->abort();
    if(m_file && m_file->isOpen())
    {
        m_file->flush();
        m_file->close();
    }
}


