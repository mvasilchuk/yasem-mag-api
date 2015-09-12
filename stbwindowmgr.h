#ifndef STBWINDOWMGR_H
#define STBWINDOWMGR_H

#include <QObject>

namespace yasem {

namespace SDK {
class GUI;
class WebPage;
}

class UiElementInfo {
public:
    QString m_x;
    QString m_y;
    QString m_w;
    QString m_h;
    QString m_isTextInput;
    QString m_text;
    QString m_positionHint;

    QJsonObject toJson() const;
    QString toString() const;

};

class WindowAttributes {
public:
    QString m_url;              ///< Web document (application) address to load
    int m_x;                    ///< X-coordinate of the window (relative to screen)
    int m_y;                    ///< Y-coordinate of the window (relative to screen)
    int m_width;                ///< width of the window
    int m_height;               ///< height of the window
    bool m_visible;             ///< visibility
    QString m_backgroundColor;  ///< background color

    static WindowAttributes fromJson(const QString& json);
    QJsonObject toJson();
    QString toString();
};

class WindowList {
public:
    int m_errCode = 0;
    int m_errMsg;
    QList<int> m_ids;

    QJsonObject toJson() const;
    QString toString() const;
};

class MagProfile;

/**
 * @brief The StbWindowMgr class
 *
 * Main object stbWindowMgr methods declaration.
 * Some methods require windowId field which can be achieved either from stbWindowMgr.windowInit or from stbWebWindow.windowId.
 */
class StbWindowMgr : public QObject
{
    Q_OBJECT
public:
    explicit StbWindowMgr(MagProfile *m_profile, SDK::WebPage* page);
    virtual ~StbWindowMgr();
signals:

public slots:
    void addBrowserBookmark();
    void closeWebWindow();
    bool closeWindow(int windowId);
    QString getCurrentTitle() const;
    QString getCurrWebUrl() const;
    QString GetFocusedInputInfo() const;
    void hideWindow(int windowId);
    void initWebWindow(const QString &url);
    void InitWebWindow();
    bool IsScreenSaverWindowExist() const;
    bool IsWebVkWindowExist() const;
    bool IsWebWindowExist() const;
    void LoadUrl(const QString& url);
    void openDownloadManager(const QString &url);
    void openMediaPlayer();
    void openWebCfgPortal(const QString& windowAttributes);
    int openWebFace(const QString &url);

    void openWebFavorites(const QString &url, const QString &params);
    void openWebFavorites(const QString &url, int params);

    void openWebWindow();
    void raiseWebFaceWindow();
    void raiseWebWindow();
    void resizeWebWindow(int x, int y, int width, int height);
    void setBookmarkImplUrl(const QString &url);
    void SetFocusedInputText(const QString& text);
    void SetVirtualKeyboardCoord (const QString& hint,int  xPos, int yPos);
    void SetVirtualKeyboardCoord ();
    void setVirtualKeyboardInitAttr(const QString &windowAttributes);
    void setVirtualMouseMode(bool mode);
    void setWebFaceInitAttr(const QString &windowAttributes);
    void showBrowserBookmarks();
    void showPortalWindow();
    void VkSetFocus(bool mode);
    int windowActive() const;
    bool windowAttr(int windowId, const QString& windowAttributes) ;
    bool windowClose(int windowId);
    bool windowHide(int windowId);
    QString windowInfo (int windowId) const;
    int windowInit(const QString &windowAttributes);
    QString windowList() const;
    bool windowLoad(int windowId,const QString& url);
    bool windowShow(int windowId) ;

protected:
    SDK::GUI* gui;
    MagProfile *m_profile;
    QString m_inner_portal_url;
    SDK::WebPage* m_page;
    SDK::WebPage* m_wild_page;

    SDK::WebPage* page() const;

    QString transformInnerPortalPathToLocal(QString innerPortalPath);
    QString openNewWindow(const QString &url, const QString &params, const QString &name);


};
}
#endif // STBWINDOWMGR_H
