#include "magapiplugin.h"
#include "magapistbobject.h"

using namespace yasem;

MagApiPlugin::MagApiPlugin(QObject* parent):
    Plugin(parent)
{

}

MagApiPlugin::~MagApiPlugin()
{

}

void yasem::MagApiPlugin::register_dependencies()
{
    add_dependency(ROLE_DATASOURCE);
    add_dependency(ROLE_BROWSER);
    add_dependency({ROLE_MEDIA, true, true});
}

void yasem::MagApiPlugin::register_roles()
{
    register_role(ROLE_STB_API, new MagApiStbObject(this));
}
