#ifndef PVRMANAGER_H
#define PVRMANAGER_H

#include <QObject>

namespace yasem
{
class MagProfile;

class PvrManager : public QObject
{
    Q_OBJECT
public:
    explicit PvrManager(MagProfile *profile);
    MagProfile *profile;
    QString GetTaskByID(const QString &id);
signals:

public slots:
    void SetMaxRecordingCnt(int count);
    QString GetAllTasks();

};
}
#endif // PVRMANAGER_H
