#ifndef MAGAPI_H
#define MAGAPI_H

#include "plugin.h"
#include "stbpluginobject.h"

#include "magapi_global.h"

namespace yasem
{

class MAGAPISHARED_EXPORT MagApiPlugin: public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.mvas.yasem.MagApiPlugin/1.0" FILE "resources/metadata.json")
    Q_INTERFACES(yasem::Plugin)

    Q_CLASSINFO("author", "Maxim Vasilchuk")
    Q_CLASSINFO("description", "MAG API")
    Q_CLASSINFO("version", MODULE_VERSION)
    Q_CLASSINFO("revision", GIT_VERSION)
public:
    explicit MagApiPlugin(QObject* parent = 0);
    virtual ~MagApiPlugin();
    void register_dependencies();
    void register_roles();
};
}


#endif // MAGAPI_H
