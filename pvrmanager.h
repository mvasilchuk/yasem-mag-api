#ifndef PVRMANAGER_H
#define PVRMANAGER_H

#include "taskinfo.h"

#include <QObject>
#include <QJsonObject>
#include <QDateTime>

namespace yasem
{
class MagProfile;
class TaskInfo;

namespace SDK {
class WebPage;
}


class PvrManager : public QObject
{
    Q_OBJECT
public:

    enum RemoveType {
        DO_NO_REMOVE = 0, /// do not remove any files
        RENAME_TEMPORARY_FILE = 1, /// if temporary file exists, rename it into resulting file
        REMOVE_TEMPORARY_FILE_IF_EXISTS = 2, /// remove only temporary file, if it exists
        REMOVE_BOTH = 3, /// remove both temporary and resulting files
    };

    explicit PvrManager(MagProfile *m_profile, SDK::WebPage* page);
    virtual ~PvrManager();

signals:

public slots:
    int ChangeEndTime(int id, const QString& endTime);
    QString CreateTask(const QString& url, const QString& fileName, const QString& startTime, const QString& endTime);
    QString GetAllTasks();

    QString GetTaskByID(const QString &id);
    QString GetTasksByIDs(const QString& ids);
    void RemoveTask(const QString& id, int removeType);
    void SetMaxRecordingCnt(int count);

protected slots:
    void onTaskError(TaskInfo::ErrorCode error);

protected:
    void loadTasks();
    void saveTasks();

protected:
    MagProfile *m_profile;
    SDK::WebPage* m_page;
    int m_max_record_count;
    int m_last_task_index;
    QHash<QString, TaskInfo*> m_tasks;
};


}
#endif // PVRMANAGER_H
