#include "netscape.h"
#include "magprofile.h"

using namespace yasem;

Netscape::Netscape(MagProfile *profile):
    m_security(new Security())
{
    this->profile = profile;
}

Netscape::~Netscape()
{
    delete m_security;
}

Security *Netscape::getSecurity()
{
    return m_security;
}


Security::Security():
    m_privilege_manager(new CPrivilegeManager())
{

}

Security::~Security()
{
    delete m_privilege_manager;
}

CPrivilegeManager *Security::getPrivilegeManager()
{
    return m_privilege_manager;
}
