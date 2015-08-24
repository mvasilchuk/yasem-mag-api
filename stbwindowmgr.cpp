#include "macros.h"
#include "stbwindowmgr.h"
#include "pluginmanager.h"
#include "browser.h"
#include "stbpluginobject.h"
#include "mag_macros.h"
#include "magprofile.h"
#include "profilemanager.h"
#include "webpage.h"
#include "datasource.h"

using namespace yasem;

StbWindowMgr::StbWindowMgr(MagProfile *profile, SDK::WebPage* page)
{
    this->m_profile = profile;
    this->m_page = page;

    SDK::Datasource* datasource = profile->datasource();
    localPortalUrl = datasource->get(SDK::DB_TAG_PROFILE, CONFIG_INNER_PORTAL_URL, "");
    //gui = dynamic_cast<GuiPlugin*>(PluginManager::instance()->getByRole("gui"));
}

StbWindowMgr::~StbWindowMgr()
{
    STUB();
}

/**
 * @brief StbWindowMgr::addBrowserBookmark
 * Open "bookmark manager" web application and pass currently opened URL of "wild web browser" to application as parameter.
 *
 * @since: 0.2.16 (MAG API version)
 * @deprecated: 0.2.18 (MAG API version)
 */
void StbWindowMgr::addBrowserBookmark()
{
    STUB();
}

/**
 * @brief StbWindowMgr::closeWebWindow
 * Close "Wild Web" window.
 *
 * @deprecated: 0.2.18 (MAG API version)
 */
void StbWindowMgr::closeWebWindow()
{
    STUB();
}

/**
 * @brief StbWindowMgr::closeWindow
 * Close window "windowId".
 *
 * @param windowId ID of window to close
 * @return true	executed correctly
 * false	failed to execute
 */
bool StbWindowMgr::closeWindow(int windowId)
{
    STUB();
    return true;
}

/**
 * @brief StbWindowMgr::getCurrentTitle
 * Get title of currently opened "Wild Web" window.
 * If there is no "Wild Web" window opened then return empty string.
 *
 * @since: 0.2.16 (MAG API version)
 *
 */
QString StbWindowMgr::getCurrentTitle() const
{
    STUB();
    return page()->getTitle();
}

/**
 * @brief StbWindowMgr::getCurrWebUrl
 * Get currently loaded URL of "Wild Web" window.
 * If there is no "Wild Web" window opened then returns empty string.

 * @return URL
 *
 * @since: 0.2.18 (MAG API version)
 */
QString StbWindowMgr::getCurrWebUrl() const
{
    STUB();
    return page()->getURL().toString();
}

/**
 * @brief StbWindowMgr::GetFocusedInputInfo
 * Get information for currently focused user interface element (HTML inputs etc...).
 *
 * @see UiElementInfo
 * @return attributes of element
 *
 * @since: 0.2.18 (MAG API version)
 */
QString StbWindowMgr::GetFocusedInputInfo() const
{
    STUB();
    return UiElementInfo().toString();
}

/**
 * @brief StbWindowMgr::hideWindow
 * Make specified window invisible.
 * If there other windows exist on window stack then most upper window will became active (be visible and has input focus).
 *
 * @param windowId
 *
 * @since: 0.2.18 (MAG API version)
 */
void StbWindowMgr::hideWindow(int windowId)
{
    STUB() << windowId;
}

/**
 * @brief StbWindowMgr::initWebWindow
 * Create and initialize the "Wild Web" window using URL "url". Created window will be invisible by default.
 *
 * @param url URL to load into newly created window
 *
 * @since: 0.2.18 (MAG API version)
 */
void StbWindowMgr::initWebWindow(const QString &url)
{
    STUB() << url;
}

/**
 * @brief StbWindowMgr::InitWebWindow
 *
 * @deprecated: 0.2.18 (MAG API version)
 */
void StbWindowMgr::InitWebWindow()
{
    STUB();
}

/**
 * @brief StbWindowMgr::IsScreenSaverWindowExist
 * Get status for "screen saver" window.
 *
 * @return true	window exist
 * false	window not found
 *
 * @since: 0.2.18 (MAG API version)
 */
bool StbWindowMgr::IsScreenSaverWindowExist() const
{
    STUB();
    return false;
}

/**
 * @brief StbWindowMgr::IsWebVkWindowExist
 * Check if "Virtual Keyboard" dedicated window exists.
 *
 * @return true	window existed
 * false	window not found
 *
 * @since: 0.2.18 (MAG API version)
 */
bool StbWindowMgr::IsWebVkWindowExist() const
{
    STUB();
    return false;
}

/**
 * @brief StbWindowMgr::IsWebWindowExist
 * Check if "Wild Web" dedicated window exists.
 *
 * @return true	window existed
 * false	window not found
 *
 * @since: 0.2.16 (MAG API version)
 */
bool StbWindowMgr::IsWebWindowExist() const
{
    STUB();
    return false;
}

/**
 * @brief StbWindowMgr::LoadUrl
 * Load URL "url" to "Wild Web" dedicated window.
 *
 * @param url URL to load (if string is empty then load file:///home/pages/blank/index.html)
 *
 * @since: 0.2.16 (MAG API version)
 */
void StbWindowMgr::LoadUrl(const QString &url)
{
    STUB() << url;
}

/**
 * @brief StbWindowMgr::openDownloadManager
 * Open "download manager" dedicated web window using "url".
 *
 * @param url URL to open
 *
 * @deprecated: 0.2.18 (MAG API version)
 */
void StbWindowMgr::openDownloadManager(const QString &url)
{
    STUB() << url;
    openNewWindow(url, "", "DownloadManager");
}

/**
 * @brief StbWindowMgr::openMediaPlayer
 *
 * @since: 0.2.16 (MAG API version)
 * @deprecated: 0.2.18 (MAG API version)
 */
void StbWindowMgr::openMediaPlayer()
{
    STUB();
}

/**
 * @brief StbWindowMgr::openWebCfgPortal
 * Open "Configuration Portal" window and run specified web application.
 *
 * @param windowAttributes
 *
 * @since: 0.2.18 (MAG API version)
 *
 * @see WindowAttributes
 */
void StbWindowMgr::openWebCfgPortal(const QString& windowAttributes)
{
    WindowAttributes attributes = WindowAttributes::fromJson(windowAttributes);
    Q_UNUSED(attributes);
    STUB() << windowAttributes;
}

/**
 * @brief StbWindowMgr::openWebFace
 * Create "Web Face" dedicated window and load address "url".
 *
 * @param url
 * @return ID of the created window
 *
 * @since: 0.2.18 (MAG API version)
 */
int StbWindowMgr::openWebFace(const QString &url)
{
    STUB() << url;
    return 0;
}

/**
 * @brief StbWindowMgr::openWebFavorites
 * @param url
 * @param params
 *
 * @since: 0.2.16 (MAG API version)
 * @deprecated: 0.2.18 (MAG API version)
 */
void StbWindowMgr::openWebFavorites(const QString &url, const QString &params = "")
{
    openNewWindow(url, params, "WebFavorites");
}

/**
 * @brief StbWindowMgr::openWebFavorites
 * @param url
 * @param params
 *
 * @since: 0.2.16 (MAG API version)
 * @deprecated: 0.2.18 (MAG API version)
 */
void StbWindowMgr::openWebFavorites(const QString &url, int params)
{
    openWebFavorites(url, QString(""));
}

/**
 * @brief StbWindowMgr::openWebWindow
 *
 * @since: 0.2.16 (MAG API version)
 * @deprecated: 0.2.18 (MAG API version)
 */
void StbWindowMgr::openWebWindow()
{
    STUB();
}

/**
 * @brief StbWindowMgr::raiseWebFaceWindow
 * Make "Web Face" window active. Do nothing if window does not exist.
 *
 * @since: 0.2.18 (MAG API version)
 */
void StbWindowMgr::raiseWebFaceWindow()
{
   STUB();
}

/**
 * @brief StbWindowMgr::raiseWebWindow
 * Make "Wild Web" window active. Do nothing if window does not exist.
 *
 * @since: 0.2.18 (MAG API version)
 */
void StbWindowMgr::raiseWebWindow()
{
    STUB();
}

/**
 * @brief StbWindowMgr::resizeWebWindow
 * Resize "Wild Web" window using given coordinates. "x","y" - top left corner, "w","h" - width and height of the new window.
 *
 * @param x
 * @param y
 * @param width
 * @param height
 *
 * @since: 0.2.18 (MAG API version)
 */
void StbWindowMgr::resizeWebWindow(int x, int y, int width, int height)
{
    STUB() << x << y << width << height;
}

/**
 * @brief StbWindowMgr::setBookmarkImplUrl
 * Set URL "url" for "web favorites" web application.
 *
 * @param url
 *
 * @deprecated: 0.2.18 (MAG API version)
 */
void StbWindowMgr::setBookmarkImplUrl(const QString &url)
{
    STUB() << url;
}

/**
 * @brief StbWindowMgr::SetFocusedInputText
 * Set text "text" for currently focused HTML element.
 *
 * @param text
 *
 * @since: 0.2.18 (MAG API version)
 */
void StbWindowMgr::SetFocusedInputText(const QString &text)
{
    STUB() << text;
}

/**
 * @brief StbWindowMgr::SetVirtualKeyboardCoord
 * Set manual position for "Virtual keyboard" window.
 * This effectively override default behavior of stbWindowMgr.GetFocusedInputInfo.
 *
 * @param hint defines the hint for positioning hint value depends on "Virtual keyboard" implementation
(value is defined for web application level) recommended values:
"none"	position hind is undefined
"topleft"	window should be positioned close to top-left corner
"topright"	window should be positioned close to top-right corner
"top"	window should be positioned close to top edge
"bottomright"	window should be positioned close to bottom-right corner
"bottomleft"	window should be positioned close to bottom-left corner
"bottom"	window should be positioned close to bottom edge

 * @param xPos set manual "X" coordinate of top-left corner for "Virtual keyboard" window
-1 value cancel manual coordinates (stbWindowMgr.GetFocusedInputInfo will return coordinates of the active element)

 * @param yPos set manual "Y" coordinate of top-left corner for "Virtual keyboard" window
-1 value cancel manual coordinates (stbWindowMgr.GetFocusedInputInfo will return coordinates of the active element)

 * @since: 0.2.18 (MAG API version)
 */
void StbWindowMgr::SetVirtualKeyboardCoord(const QString &hint, int xPos, int yPos)
{
    STUB() << hint << xPos << yPos;
}

/**
 * Set VK window init parameters
 * Set window init attributes for "Virtual keyboard" window.
 *
 * @param options @see WindowAttributes
 *
 * @since: 0.2.18 (MAG API version)
 */
void StbWindowMgr::setVirtualKeyboardInitAttr(const QString &windowAttributes)
{
    STUB() << windowAttributes;
}

/**
 * @brief StbWindowMgr::setVirtualMouseMode
 * Set virtual mouse mode.
 *
 * @param mode true	turn virtual mouse on
 * false	turn virtual mouse off
 *
 * @since: 0.2.16 (MAG API version)
 */
void StbWindowMgr::setVirtualMouseMode(bool mode)
{
    STUB() << mode;
}

/**
 * @brief StbWindowMgr::setWebFaceInitAttr
 * Set init window attributes for "Web Face" window.
 *
 * @param windowAttributes @see WindowAttributes
 *
 * @since: 0.2.18 (MAG API version)
 */
void StbWindowMgr::setWebFaceInitAttr(const QString &windowAttributes)
{
    STUB() << windowAttributes;
}

/**
 * @brief StbWindowMgr::showBrowserBookmarks
 * Open "Web Favorites" window.
 *
 * @since: 0.2.16 (MAG API version)
 * @deprecated: 0.2.18 (MAG API version)
 */
void StbWindowMgr::showBrowserBookmarks()
{
    STUB();
}

/**
 * @brief StbWindowMgr::showPortalWindow
 * Make the "Internal Portal" window active.
 *
 * @since: 0.2.16 (MAG API version)
 */
void StbWindowMgr::showPortalWindow()
{
    STUB();
}

/**
 * @brief StbWindowMgr::VkSetFocus
 * Set focus mode for "Virtual keyboard" window.
 *
 * @param mode true	focus VK window
 * false	focus previously focused window
 *
 * @since: 0.2.18 (MAG API version)
 * @deprecated: 0.2.18 (MAG API version)
 */
void StbWindowMgr::VkSetFocus(bool mode)
{
    STUB() << mode;
}

/**
 * @brief StbWindowMgr::windowActive
 * Get ID of currently active window.
 *
 * @return ID of the window. May return -1 if there is no proper candidates
 *
 * @since: 0.2.18 (MAG API version)
 */
int StbWindowMgr::windowActive() const
{
    STUB();
    return -1;
}

/**
 * @brief StbWindowMgr::windowAttr
 * Set window attributes.
 *
 * @param windowId ID of target window
 * @param windowAttributes parameters to set @see WindowAttributes
 * @return  true	executed correctly
 * false	failed to execute
 *
 * @since: 0.2.18 (MAG API version)
 */
bool StbWindowMgr::windowAttr(int windowId, const QString &windowAttributes)
{
    STUB() << windowId << windowAttributes;
    return true;
}

/**
 * @brief StbWindowMgr::windowClose
 * Close given window.
 *
 * @param windowId ID of target window
 * @since: 0.2.18 (MAG API version)
 * @return true	executed correctly
 * false	failed to execute
 */
bool StbWindowMgr::windowClose(int windowId)
{
    STUB() << windowId;
    return true;
}

/**
 * @brief StbWindowMgr::windowHide
 * Make given window invisible.
 * Operation have the same effect as stbWindowMgr.windowAttr(id, '{"visible":false}').
 *
 * @param windowId ID of target window
 * @since: 0.2.18 (MAG API version)
 * @return true	executed correctly
 * false	failed to execute
 */
bool StbWindowMgr::windowHide(int windowId)
{
    STUB() << windowId;
    return true;
}

/**
 * @brief StbWindowMgr::windowInfo
 * Get attributes for given window.
 *
 * @param windowId ID of target window
 * @return  parameters of the window @see WindowAttributes
 * @since: 0.2.18 (MAG API version)
 */
QString StbWindowMgr::windowInfo(int windowId) const
{
    STUB() << windowId;
    return WindowAttributes().toString();
}

/**
 * @brief StbWindowMgr::windowInit
 * Create new window with specified attributes.
 *
 * @param windowAttributes parameters of created window @see WindowAttributes
 * @return window ID for created window (-1 if window was not created)
 * @since: 0.2.18 (MAG API version)
 */
int StbWindowMgr::windowInit(const QString &windowAttributes)
{
    STUB() << windowAttributes;
    return 0;
}

/**
 * @brief StbWindowMgr::windowList
 * Get list of ID of currently existing windows.
 *
 * @return list of ID
 * @since: 0.2.18 (MAG API version)
 * @see WindowList
 */
QString StbWindowMgr::windowList() const
{
    STUB();
    return WindowList().toString();
}

/**
 * @brief StbWindowMgr::windowLoad
 * Load new web document into given window "windowId" using URL "url".
 *
 * @param windowId ID of target window
 * @param url address to load
 * @return
true	executed correctly
false	failed to execute
 *
 * @since: 0.2.16 (MAG API version)
 */
bool StbWindowMgr::windowLoad(int windowId, const QString &url)
{
    STUB() << windowId << url;
    return true;
}

/**
 * @brief StbWindowMgr::windowShow
 * Make given window visible.
Operation have the same effect as stbWindowMgr.windowAttr(id, '{"visible":true}').

 * @param windowId ID of target window
 * @since 0.2.18
 * @return  true	executed correctly
false	failed to execute
 */
bool StbWindowMgr::windowShow(int windowId)
{
    STUB() << windowId;
    return true;
}



QString StbWindowMgr::transformInnerPortalPathToLocal(QString innerPortalPath)
{
    STUB();
    bool isInternalPortal = static_cast<MagProfile*>(SDK::ProfileManager::instance()->getActiveProfile())->isInternalPortal();
    QString result;

    if(innerPortalPath.startsWith("/home/web/"))
    {
        if(isInternalPortal)
            result = innerPortalPath.replace("/home/web/", SDK::Browser::instance()->browserRootDir()) ;
        else
            result = innerPortalPath.replace("/home/web/", "file://" + localPortalUrl) ;
    }
    else result = innerPortalPath;

    qDebug() << result;

    return result;
}

QString StbWindowMgr::openNewWindow(const QString &url, const QString &params, const QString &name)
{
    m_page->openWindow(transformInnerPortalPathToLocal(url), params, name);
    return "";
}



SDK::WebPage *StbWindowMgr::page() const
{
    return m_page;
}

QJsonObject UiElementInfo::toJson() const
{
    QJsonObject result;
    result.insert("x", m_x);
    result.insert("y", m_y);
    result.insert("w", m_w);
    result.insert("h", m_h);
    result.insert("isTextInput", m_isTextInput);
    result.insert("text", m_text);
    result.insert("positionHint", m_positionHint);
    return result;
}

/**
 * @brief UiElementInfo::toString
 *
 * @example
{
    h: "100",
    isTextInput: "0",
    positionHint: "top",
    text: "some text",
    w: "100",
    x: "100",
    y: "100"
}

 * @return JSON string
 */
QString UiElementInfo::toString() const
{
    return QString(QJsonDocument(toJson()).toJson(QJsonDocument::Compact));
}


WindowAttributes WindowAttributes::fromJson(const QString &json)
{
    QJsonObject obj = QJsonDocument::fromJson(json.toUtf8()).object();
    WindowAttributes result;
    result.m_x = obj.value("x").toInt();
    result.m_y = obj.value("y").toInt();
    result.m_width = obj.value("width").toInt();
    result.m_height = obj.value("height").toInt();
    result.m_url = obj.value("url").toString();
    result.m_backgroundColor = obj.value("backgroundColor").toString();
    result.m_visible = obj.value("visible").toBool();
    return result;

}

QJsonObject WindowAttributes::toJson()
{
    QJsonObject result;
    result.insert("x", m_x);
    result.insert("y", m_y);
    result.insert("width", m_width);
    result.insert("height", m_height);
    result.insert("url", m_url);
    result.insert("backgroundColor", m_backgroundColor);
    result.insert("visible", m_visible);
    return result;
}

QString WindowAttributes::toString()
{
    return QString(QJsonDocument(toJson()).toJson(QJsonDocument::Compact));
}


QJsonObject WindowList::toJson() const
{
    QJsonObject result;
    QJsonArray list;
    result.insert("errCode", m_errCode);
    result.insert("errMsg", m_errMsg);
    result.insert("result", list);
    return result;
}

QString WindowList::toString() const
{
    return QString(QJsonDocument(toJson()).toJson(QJsonDocument::Compact));
}
