#include "magapiplugin.h"
#include "magapistbobject.h"

using namespace yasem;

MagApiPlugin::MagApiPlugin(QObject* parent):
    SDK::Plugin(parent)
{

}

MagApiPlugin::~MagApiPlugin()
{
    STUB();
}

void yasem::MagApiPlugin::register_dependencies()
{
    add_dependency(SDK::ROLE_DATASOURCE);
    add_dependency(SDK::ROLE_BROWSER);
    add_dependency({SDK::ROLE_MEDIA, true, true});
}

void yasem::MagApiPlugin::register_roles()
{
    register_role(SDK::ROLE_STB_API, new MagApiStbObject(this));
}
