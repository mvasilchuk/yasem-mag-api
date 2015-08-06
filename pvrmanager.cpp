#include "pvrmanager.h"
#include "macros.h"
#include "magprofile.h"
#include "webpage.h"

using namespace yasem;

PvrManager::PvrManager(MagProfile *profile, SDK::WebPage* page)
{
    this->m_profile = profile;
    this->m_page = page;
}

void PvrManager::SetMaxRecordingCnt(int count)
{
    STUB() << count;
}

QString PvrManager::GetAllTasks()
{
    STUB();
    return "[]";
}

QString PvrManager::GetTaskByID(const QString &id)
{
    STUB() << id;
    return "{}";
}
