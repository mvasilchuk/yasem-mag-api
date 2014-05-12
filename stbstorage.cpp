#include "stbstorage.h"

using namespace yasem;

StbStorage::StbStorage(MagProfile *profile)
{
    //qDebug() << "logger: " << parent->getLogger();
    this->setObjectName("gSTB");

    this->profile = profile;
}

void StbStorage::setItem(const QString &name, const QString &value)
{
    STUB_WITH_LIST(QStringList() << name << value);
    items.insert(name, value);
}

void StbStorage::removeItem(const QString &name)
{
    STUB_WITH_PARAMS(name);
    items.remove(name);
}

QString StbStorage::getItem(const QString &name)
{
    STUB_WITH_PARAMS(name);
    return items.value(name);
}
