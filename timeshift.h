#ifndef TIMESHIFT_H
#define TIMESHIFT_H


#include <QObject>

namespace yasem
{
class MagProfile;

class TimeShift : public QObject
{
    Q_OBJECT
public:
    TimeShift(MagProfile *profile);
signals:

public slots:
    void SetSlidingMode(bool enable);

    void SetTimeShiftFolder(const QString &folderName);
    void SetMaxDuration(qint64 maxDuration);
protected:
    MagProfile *profile;
};

}

#endif // TIMESHIFT_H
