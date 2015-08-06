#ifndef PVRMANAGER_H
#define PVRMANAGER_H

#include <QObject>

namespace yasem
{
class MagProfile;

namespace SDK {
class WebPage;
}

class PvrManager : public QObject
{
    Q_OBJECT
public:
    explicit PvrManager(MagProfile *m_profile, SDK::WebPage* page);
    MagProfile *m_profile;
    QString GetTaskByID(const QString &id);
signals:

public slots:
    void SetMaxRecordingCnt(int count);
    QString GetAllTasks();

protected:
    SDK::WebPage* m_page;

};
}
#endif // PVRMANAGER_H
