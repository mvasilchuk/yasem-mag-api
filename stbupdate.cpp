#include "stbupdate.h"
#include "macros.h"
#include "magprofile.h"
#include "webpage.h"

using namespace yasem;

StbUpdate::StbUpdate(MagProfile *profile, SDK::WebPage* page)
{
    this->m_profile = profile;
    this->m_page = page;
}

StbUpdate::~StbUpdate()
{
    STUB();
}

int StbUpdate::GetFlashBankCount()
{
    STUB();
    return 2;
}

int StbUpdate::getStatus()
{
    STUB();
    return UpdateStatus::WRONG_STB_MODEL;
}

/**
 * Returns memory bank number, which was used for current software loading.
 * @return 0 – first memory bank; 1 – second memory bank; -1 – memory bank is undefined
 * (it could be possible if device was booted from network storage. For examples, NFS)
 */
int StbUpdate::getActiveBank()
{
    return 0;
}

void StbUpdate::startCheck(const QString &data)
{
    STUB();
}

int StbUpdate::getPercents()
{
    STUB();
    return 100;
}

QString StbUpdate::getImageDateStr()
{
    QString stub_str = "Tue Apr 9 18:14:45 EEST 2013";
    STUB() << stub_str;
    return stub_str;
}

QString StbUpdate::getImageDescStr()
{
    QString stub_str = "0.2.16-pub-250";
    STUB() << stub_str;
    return stub_str;
}

QString StbUpdate::getImageVersionStr()
{
    QString stub_str = "216";
    STUB() << stub_str;
    return stub_str;
}
