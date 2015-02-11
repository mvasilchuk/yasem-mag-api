#include "stbstorage.h"
#include "abstractwebpage.h"

using namespace yasem;

#define STB_STORAGE_GROUP "stb-storage"

StbStorage::StbStorage(MagProfile *profile, AbstractWebPage* page)
{
    //qDebug() << "logger: " << parent->getLogger();
    this->setObjectName("gSTB");

    this->profile = profile;
    this->m_page = page;
}

void StbStorage::setItem(const QString &name, const QString &value)
{
    STUB() << name << value;
    profile->datasource()->set(STB_STORAGE_GROUP, name, value);
}

void StbStorage::removeItem(const QString &name)
{
    STUB() << name;
    profile->datasource()->set(STB_STORAGE_GROUP, name, "");
}

QString StbStorage::getItem(const QString &name)
{
    STUB() << name;
    return profile->datasource()->get(STB_STORAGE_GROUP, name);
}
