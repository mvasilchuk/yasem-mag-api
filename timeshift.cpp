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
    STUB_WITH_PARAMS(enable);
}

void TimeShift::SetTimeShiftFolder(const QString &folderName)
{

}

void TimeShift::SetMaxDuration(qint64 maxDuration)
{

}
