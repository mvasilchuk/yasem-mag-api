#include "stbupdate.h"
#include "macros.h"
#include "magprofile.h"

using namespace yasem;

StbUpdate::StbUpdate(MagProfile *profile)
{
    this->profile = profile;
}

int StbUpdate::GetFlashBankCount()
{
    STUB();
    return 2;
}

int StbUpdate::getStatus()
{
    STUB();
    return -1;
}

/**
 * Returns memory bank number, which was used for current software loading.
 * @return 0 – first memory bank; 1 – second memory bank; -1 – memory bank is undefined (it could be possible if device was booted from network storage. For examples, NFS)
 */
int StbUpdate::getActiveBank()
{
    return 0;
}
