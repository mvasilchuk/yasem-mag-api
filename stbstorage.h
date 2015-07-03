#ifndef STBSTORAGE_H
#define STBSTORAGE_H

#include "enums.h"
#include "macros.h"
#include "magprofile.h"

#include <QObject>
#include <QHash>

namespace yasem
{

namespace SDK {
class MediaPlayerPluginObject;
class AbstractWebPage;

}

class StbStorage : public QObject
{
    Q_OBJECT
public:
    explicit StbStorage(MagProfile *profile, SDK::AbstractWebPage* page);

signals:

public slots:

    void removeItem(const QString &name);
    void setItem(const QString &name, const QString &value);
    QString getItem(const QString &name);
protected:
    MagProfile *profile;
    SDK::AbstractWebPage* m_page;
};

}

#endif // STBSTORAGE_H
