#ifndef MAGAPI_H
#define MAGAPI_H

#include "plugin.h"
#include "stbplugin.h"

#include "customkeyevent.h"
#include "gstb.h"
#include "pvrmanager.h"
#include "stbscreen.h"
#include "stbwindowmgr.h"
#include "stbupdate.h"
#include "stbwebwindow.h"
#include "timeshift.h"
#include "netscape.h"
#include "stbdownloadmanager.h"
#include "magapi_global.h"

namespace yasem
{
class BrowserPlugin;
class GuiPlugin;
class MediaPlayerPlugin;
class DatasourcePlugin;

class MAGAPISHARED_EXPORT MagApi: public QObject, public StbPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.mvas.yasem.MagApiPlugin/1.0" FILE "resources/metadata.json")
    Q_INTERFACES(yasem::Plugin yasem::StbPlugin)

    Q_CLASSINFO("author", "Maxim Vasilchuk")
    Q_CLASSINFO("description", "MAG API implementation for YASEM")
public:
    MagApi();

    virtual PLUGIN_ERROR_CODES initialize();
    virtual PLUGIN_ERROR_CODES deinitialize();

    virtual QString getStorageInfo();
    QString getIcon(const QSize &size);

protected:


    StbScreen *screen;
    StbDownloadManager *stbDownloadManager;
    GStb *gStb;
    GStb *stb;
    StbWindowMgr* stbWindowMgr;
    PvrManager* pvrManager;
    StbUpdate* stbUpdate;
    StbWebWindow* stbWebWindow;
    TimeShift* timeShift;
    Netscape* netscape;
    QString fontFix;

    // StbPlugin interface
public slots:
    Profile* createProfile(const QString& id);
    QString getProfileClassId();

    // StbPlugin interface
protected:
    void resetObjects();
    void applyFixes();

    // StbProfilePlugin interface
public:
    void init();
    QUrl handleUrl(QUrl &url);

    QString webServerHost;
    int webServerPort;

    // StbPlugin interface

    // Plugin interface
public:
    void register_dependencies();
    void register_roles();
};
}


#endif // MAGAPI_H
