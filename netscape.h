#ifndef NETSCAPE_H
#define NETSCAPE_H

#include "macros.h"

#include <QObject>

namespace yasem
{
class MagProfile;

class CPrivilegeManager: public QObject
{
    Q_OBJECT
public:
    CPrivilegeManager(){}
public slots:

    void enablePrivilege(const QString &name)
    {
        DEBUG() << QString("netscape.security.privilegeManager.enablePrivilege(%1)").arg(name);
    }
};

class Security: public QObject {
    Q_OBJECT

public:
    CPrivilegeManager* PrivilegeManager;
    Q_PROPERTY(CPrivilegeManager* PrivilegeManager READ getPrivilegeManager)
    Security(){
        PrivilegeManager = new CPrivilegeManager();
    }

    CPrivilegeManager* getPrivilegeManager()
    {
        return PrivilegeManager;
    }

};

class Netscape : public QObject
{
    Q_OBJECT
public:

protected:
    Security* security;
    MagProfile *profile;
public:
    explicit Netscape(MagProfile *profile);
    Q_PROPERTY(Security* security READ getSecurity)

signals:

public slots:

    Security* getSecurity()
    {
        return security;
    }
};

}
#endif // NETSCAPE_H
