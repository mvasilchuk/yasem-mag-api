#include "macros.h"
#include "stbwindowmgr.h"
#include "pluginmanager.h"
#include "browserplugin.h"
#include "datasource.h"
#include "stbplugin.h"
#include "mag_macros.h"
#include "magprofile.h"
#include "profilemanager.h"

using namespace yasem;

StbWindowMgr::StbWindowMgr(MagProfile *profile)
{
    this->profile = profile;

    Datasource* datasource = profile->datasource();
    localPortalUrl = datasource->get(DB_TAG_PROFILE, CONFIG_INNER_PORTAL_URL, "");
    //gui = dynamic_cast<GuiPlugin*>(PluginManager::instance()->getByRole("gui"));
}

void StbWindowMgr::openWebFavorites(const QString &url, const QString &params = "")
{
    Q_ASSERT(profile->getProfilePlugin()->browser());
    openNewWindow(url, params, "WebFavorites");
}

void StbWindowMgr::openWebFavorites(const QString &url, int params)
{
    openWebFavorites(url, QString(""));

}

void StbWindowMgr::openDownloadManager(const QString &url)
{
    Q_ASSERT(profile->getProfilePlugin()->browser());
    openNewWindow(url, "", "DownloadManager");
}

QString StbWindowMgr::transformInnerPortalPathToLocal(QString innerPortalPath)
{
    STUB();
    bool isInternalPortal = static_cast<MagProfile*>(ProfileManager::instance()->getActiveProfile())->isInternalPortal();
    QString result;

    if(innerPortalPath.startsWith("/home/web/"))
    {
        if(isInternalPortal)
            result = innerPortalPath.replace("/home/web/", profile->getProfilePlugin()->browser()->browserRootDir()) ;
        else
            result = innerPortalPath.replace("/home/web/", "file://" + localPortalUrl) ;
    }
    else result = innerPortalPath;

    qDebug() << result;

    return result;
}

QString StbWindowMgr::openNewWindow(const QString &url, const QString &params, const QString &name)
{
    profile->getProfilePlugin()->browser()->evalJs(QString("window.open('%1', '%2', '%3')")
                .arg(transformInnerPortalPathToLocal(url))
                .arg(name)
                .arg(params));

    return "";
}

void StbWindowMgr::setBookmarkImplUrl(const QString &url)
{
    STUB_WITH_PARAMS(url);
}

void StbWindowMgr::showBrowserBookmarks()
{
    STUB();
}

void StbWindowMgr::SetVirtualKeyboardCoord(const QString &coord)
{
   STUB_WITH_PARAMS(coord);
}

void StbWindowMgr::windowInit(const QString &params)
{
    STUB_WITH_PARAMS(params);
}

/**
 * Set VK window init parameters
 * @param options parameters from windowInit function
 */
void StbWindowMgr::setVirtualKeyboardInitAttr(const QString &options)
{
    STUB_WITH_PARAMS(options);
}

/**
 * Set internet browser main window init parameters
 * @param options parameters from windowInit function
 */
void StbWindowMgr::setWebFaceInitAttr(const QString &options)
{
   STUB_WITH_PARAMS(options);
}

QString StbWindowMgr::getCurrWebUrl()
{
    STUB();
    return "http://google.com";
}

void StbWindowMgr::initWebWindow(const QString &url)
{
    STUB_WITH_PARAMS(url);
}

/**
 * @brief StbWindowMgr::resizeWebWindow
 * @param x
 * @param y
 * @param width
 * @param height
 */
void StbWindowMgr::resizeWebWindow(int x, int y, int width, int height)
{
    STUB_WITH_LIST(QStringList() << QString::number(x) << QString::number(y) << QString::number(width) <<QString::number(height));
}

void StbWindowMgr::raiseWebWindow()
{
    STUB();
}

void StbWindowMgr::raiseWebFaceWindow()
{
   STUB();
}

void StbWindowMgr::openWebFace(const QString &url)
{
    STUB_WITH_PARAMS(url);
}
