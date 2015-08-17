#ifndef TIMESHIFT_H
#define TIMESHIFT_H


#include <QObject>

namespace yasem
{
class MagProfile;

namespace SDK {
class WebPage;
}

class TimeShift : public QObject
{
    Q_OBJECT
public:
    TimeShift(MagProfile *profile, SDK::WebPage* page);
    virtual ~TimeShift();
signals:

public slots:
    void SetSlidingMode(bool enabled);
    void SetTimeShiftFolder(const QString &folderName);
    void SetMaxDuration(qint64 maxDuration);
    void EnterTimeShift();
    void ExitTimeShift();
    void ExitTimeShiftAndSave (const QString& path, const QString& name);
    void ExitTimeShiftAndSaveDuration (const QString& path, const QString& name, qint64 duration );
protected:
    MagProfile *m_profile;
    SDK::WebPage* m_page;
    bool m_sliding_mode;
    QString m_timeshift_folder;
    qint64 m_max_duration;
    bool m_entered_timeshift;
};

}

#endif // TIMESHIFT_H
