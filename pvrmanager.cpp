#include "pvrmanager.h"
#include "macros.h"
#include "magprofile.h"

using namespace yasem;

PvrManager::PvrManager(MagProfile *profile)
{
    this->profile = profile;
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
