#include "pvrmanager.h"
#include "macros.h"
#include "magprofile.h"
#include "webpage.h"
#include "taskinfo.h"
#include "datasource.h"

using namespace yasem;

static const QString DATE_TIME_FORMAT = "YYYYMMDDThhmmss";

PvrManager::PvrManager(MagProfile *profile, SDK::WebPage* page):
    m_profile(profile),
    m_page(page),
    m_max_record_count(0),
    m_last_task_index(0)
{
    setObjectName("pvrManager");
    loadTasks();
}

PvrManager::~PvrManager()
{
    STUB();
    saveTasks();
    qDeleteAll(m_tasks);
}

/**
 * @brief PvrManager::ChangeEndTime
 * Change recording end time.
 *
 * @param id task identifier
 * @param end Time new recording end time.
 * UTC time in "YYYYMMDDThhmmss" format or number of seconds since Epoch (1970/01/01 UTC)
 *
 * @return see error codes table
 */
int PvrManager::ChangeEndTime(int id, const QString &endTime)
{
    STUB() << id << endTime;
    return TaskInfo::ERROR_SUCCESSFUL;
}

/**
 * @brief PvrManager::CreateTask
 * Schedule channel recording task.
 *
 * @param url address of the stream that will be recorded (http://..., rtp://..., udp://...)
 * @param fileName full file name of recording (/media/USB-... or /ram/media/USB-...)
 * @param startTime recording start time
 * UTC time in "YYYYMMDDThhmmss" format or number of seconds since Epoch (1970/01/01 UTC)
 *
 * @param endTime recording end time
 * UTC time in "YYYYMMDDThhmmss" format or number of seconds since Epoch (1970/01/01 UTC)
 *
 * @return unique task identifier if operation was successful, otherwise return value is a string representing error code (<0) from error codes table
 *
 * @example
 * // number of seconds since Epoch can be obtained via Date object
 * var date = new Date();
 * var startTime = date.getTime()/1000;
 */
QString PvrManager::CreateTask(const QString &url, const QString &fileName, const QString &startTime, const QString &endTime)
{
    STUB() << url << fileName << startTime << endTime;

    if(m_tasks.size() >= m_max_record_count - 1)
    {
        DEBUG() << "Reached maximum of simultaneous records!" << m_tasks.size();
        return QString::number(TaskInfo::ERROR_MAX_SIMULTANEOUS_RECORDS);
    }

    QDateTime start_time = QDateTime::fromString(startTime, DATE_TIME_FORMAT);;
    if(!start_time.isValid())
        start_time = QDateTime::fromMSecsSinceEpoch(startTime.toLongLong() * 1000);

    QDateTime end_time = QDateTime::fromString(endTime, DATE_TIME_FORMAT);
    if(!end_time.isValid())
        end_time = QDateTime::fromMSecsSinceEpoch(endTime.toLongLong() * 1000);

    if(!start_time.isValid() || !end_time.isValid())
    {
        DEBUG() << "Start or end time is incorrect" << start_time << end_time;
        return QString::number(TaskInfo::ERROR_BAD_ARGUMENT);
    }

    if( (start_time > end_time)
        || ((end_time.currentMSecsSinceEpoch() - start_time.currentMSecsSinceEpoch()) > 24*60*60*1000) // 24 hours
        )
    {
        DEBUG() << "Incorrect time range!" << start_time << end_time;
        return QString::number(TaskInfo::ERROR_WRONG_RANGE);
    }

    if(!fileName.startsWith("/media/USB-")
            && !fileName.startsWith("/ram/media/USB-")
            && !fileName.startsWith("USB-")
            )
    {
        DEBUG() << "Wrong file name" << fileName;
        return QString::number(TaskInfo::ERROR_WRONG_FILE_NAME);
    }

    for(const TaskInfo* item: m_tasks)
    {
        if(item->m_file_name == fileName)
        {
            DEBUG() << "File" << fileName << "already exists";
            return QString::number(TaskInfo::ERROR_DUPLICATE_TASKS);
        }
    }

    TaskInfo* task = new TaskInfo(m_profile, ++m_last_task_index, url, fileName, start_time, end_time, this);

    connect(task, &TaskInfo::errorHappened, this, &PvrManager::onTaskError);

    m_tasks.insert(QString::number(task->m_id), task);

    DEBUG() << task->m_url << task->m_file_name << task->m_start_time << task->m_end_time;

    TaskInfo::ErrorCode result = task->scheduleStart();
    if(result != TaskInfo::ERROR_SUCCESSFUL)
        return QString::number(result);

    return QString::number(task->m_id);
}

/**
 * @brief PvrManager::GetAllTasks
 * Get the list of all tasks.
 * See pvrManager.TaskInfo, pvrManager.CreateTask.
 * @return list of all recording tasks in JSON format
 */
QString PvrManager::GetAllTasks()
{
    STUB();
    QJsonArray result;

    for(const TaskInfo* task: m_tasks)
        result.append(task->toJson());

    const QString str = QString(QJsonDocument(result).toJson(QJsonDocument::Compact));
    DEBUG() << "result:" << str;

    return str;
}

/**
 * @brief PvrManager::GetTaskByID
 * Get recording task by its identifier.
 * See pvrManager.GetTasksByIDs.
 * @param id task identifier
 * @return task data
 */
QString PvrManager::GetTaskByID(const QString &id)
{
    STUB() << id;

    QString str;
    if(m_tasks.contains(id))
        str = QString(QJsonDocument(m_tasks.value(id)->toJson()).toJson(QJsonDocument::Compact));
    else
        str = "{}";
    DEBUG() << "result:" << str;
    return str;
}

/**
 * @brief PvrManager::GetTasksByIDs
 * Get task list by identifier list.
 * See pvrManager.TaskInfo, pvrManager.CreateTask, pvrManager.GetTaskByID.
 * @param ids list of task identifiers in JSON format
 * signature: number[]
 *
 * @return list of all matched recording tasks in JSON format
 */
QString PvrManager::GetTasksByIDs(const QString &ids)
{
    STUB() << ids;
    QJsonArray items = QJsonDocument::fromJson(ids.toUtf8()).array();

    QJsonArray result;

    for(const QVariant& item: items.toVariantList())
    {
        const QString id = item.toString();
        if(m_tasks.contains(id))
            result.append(m_tasks.value(id)->toJson());
        else
            WARN() << "Task" << id << "not found! Skipping...";
    }

    const QString str = QString(QJsonDocument(result).toJson(QJsonDocument::Compact));
    DEBUG() << "result:" << str;

    return str;
}

/**
 * @brief PvrManager::RemoveTask
 * Remove recording task by its identifier.
 * @param id task identifier
 * @param removeType @see #RemoveType
 */
void PvrManager::RemoveTask(const QString &id, int removeType)
{
    STUB() << id << removeType;
    TaskInfo* task = m_tasks.value(id);
    if(task)
    {
        if(task->m_state == TaskInfo::STATE_RECORDING)
            task->stopRecord();
        delete task;
    }
    else
        WARN() << "Task not found!";

    m_tasks.remove(id);
}

/**
 * @brief PvrManager::SetMaxRecordingCnt
 * Set maximum number of simultaneous recording.
 * @param count maximum number of simultaneous recording
 */
void PvrManager::SetMaxRecordingCnt(int count)
{
    STUB() << count;
    m_max_record_count = count;
}

void PvrManager::onTaskError(TaskInfo::ErrorCode error)
{
    STUB();
    TaskInfo* task = static_cast<TaskInfo*>(sender());
    DEBUG() << "Task" << task->toJson();
    DEBUG() << "Error code" << error;
}

void PvrManager::loadTasks()
{
    STUB();
    m_tasks.clear();
    const QString str = m_profile->datasource()->get("PVR", "tasks");
    const QJsonArray arr = QJsonDocument::fromJson(str.toUtf8()).array();
    for(size_t index = 0; index< arr.size(); index++)
    {
        TaskInfo* task = TaskInfo::fromJson(m_profile, arr.at(index).toObject(), this);
        if(task)
        {
            m_tasks.insert(QString::number(task->m_id), task);
            task->scheduleStart();
        }
    }
    DEBUG() << "Tasks loaded:" << m_tasks.size();
}

void PvrManager::saveTasks()
{
    STUB();
    m_profile->datasource()->set("PVR", "tasks", GetAllTasks());
    DEBUG() << "Tasks saved: " << m_tasks.size();
    for(TaskInfo* task: m_tasks)
        task->stopRecord();
}
