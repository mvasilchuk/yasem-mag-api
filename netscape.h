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
    CPrivilegeManager* m_privilege_manager;
    Q_PROPERTY(CPrivilegeManager* PrivilegeManager READ getPrivilegeManager)
    Security();

    virtual ~Security();

    CPrivilegeManager* getPrivilegeManager();

};

class Netscape : public QObject
{
    Q_OBJECT
public:

protected:
    Security* m_security;
    MagProfile *m_profile;
public:
    explicit Netscape(MagProfile *m_profile);
    virtual ~Netscape();
    Q_PROPERTY(Security* security READ getSecurity)

signals:

public slots:

    Security* getSecurity();
};

}
#endif // NETSCAPE_H
