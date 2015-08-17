#include "stbstorage.h"
#include "webpage.h"
#include "datasource.h"

using namespace yasem;

#define STB_STORAGE_GROUP "stb-storage"

StbStorage::StbStorage(MagProfile *profile, SDK::WebPage* page)
{
    //qDebug() << "logger: " << parent->getLogger();
    this->setObjectName("gSTB");

    this->m_profile = profile;
    this->m_page = page;
}

StbStorage::~StbStorage()
{
    STUB();
}

void StbStorage::setItem(const QString &name, const QString &value)
{
    STUB() << name << value;
    m_profile->datasource()->set(STB_STORAGE_GROUP, name, value);
}

void StbStorage::removeItem(const QString &name)
{
    STUB() << name;
    m_profile->datasource()->set(STB_STORAGE_GROUP, name, "");
}

QString StbStorage::getItem(const QString &name)
{
    STUB() << name;
    return m_profile->datasource()->get(STB_STORAGE_GROUP, name);
}
