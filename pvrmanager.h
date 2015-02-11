#ifndef PVRMANAGER_H
#define PVRMANAGER_H

#include <QObject>

namespace yasem
{
class MagProfile;
class AbstractWebPage;

class PvrManager : public QObject
{
    Q_OBJECT
public:
    explicit PvrManager(MagProfile *profile, AbstractWebPage* page);
    MagProfile *profile;
    QString GetTaskByID(const QString &id);
signals:

public slots:
    void SetMaxRecordingCnt(int count);
    QString GetAllTasks();

protected:
    AbstractWebPage* m_page;

};
}
#endif // PVRMANAGER_H
