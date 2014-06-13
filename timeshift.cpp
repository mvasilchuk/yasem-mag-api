#include "timeshift.h"
#include "macros.h"
#include "magprofile.h"

using namespace yasem;

TimeShift::TimeShift(MagProfile *profile)
{
    this->profile = profile;
}

void TimeShift::SetSlidingMode(bool enable)
{
    STUB() << enable;
}

void TimeShift::SetTimeShiftFolder(const QString &folderName)
{
    STUB() << folderName;
}

void TimeShift::SetMaxDuration(qint64 maxDuration)
{
    STUB() << maxDuration;
}
