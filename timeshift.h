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
signals:

public slots:
    void SetSlidingMode(bool enable);

    void SetTimeShiftFolder(const QString &folderName);
    void SetMaxDuration(qint64 maxDuration);
protected:
    MagProfile *profile;
    SDK::WebPage* m_page;
};

}

#endif // TIMESHIFT_H
