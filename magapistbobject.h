#ifndef MAGAPISTBOBJECT_H
#define MAGAPISTBOBJECT_H

#include "stbpluginobject.h"

namespace yasem
{
class Plugin;
class StbScreen;
class StbDownloadManager;
class GStb;
class StbWindowMgr;
class PvrManager;
class StbUpdate;
class StbUpdate;
class StbWebWindow;
class TimeShift;
class Netscape;

class MagApiStbObject: public StbPluginObject
{
public:
    enum DeviceModel {
        MAG_100,
        MAG_200,
        MAG_245,
        MAG_250,
        AURA_HD,
        MAG_254,
        MAG_255,
        MAG_260,
        MAG_270,
        MAG_275
    };

    MagApiStbObject(Plugin* plugin);
    virtual ~MagApiStbObject();

    // StbPluginObject interface
public slots:
    QString getProfileClassId();
    Profile *createProfile(const QString &id);
    void initObject(AbstractWebPage *page);
    QString getIcon(const QSize &size);
    QString getStorageInfo();
    void resetObjects(AbstractWebPage* page);
    void applyFixes();
    QUrl handleUrl(QUrl &url);

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

    QString webServerHost;
    int webServerPort;

    // AbstractPluginObject interface
public:
    PluginObjectResult init();
    PluginObjectResult deinit();
};

}

#endif // MAGAPISTBOBJECT_H
