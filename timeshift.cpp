#include "timeshift.h"
#include "macros.h"
#include "magprofile.h"
#include "abstractwebpage.h"

using namespace yasem;

TimeShift::TimeShift(MagProfile *profile, AbstractWebPage* page)
{
    this->profile = profile;
    this->m_page = page;
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
