#include "stbwebwindow.h"
#include "macros.h"
#include "magprofile.h"
#include "browser.h"
#include "webpage.h"

using namespace yasem;

StbWebWindow::StbWebWindow(MagProfile *profile, SDK::WebPage* page)
{
    this->m_profile = profile;
    this->m_page = page;
}

StbWebWindow::~StbWebWindow()
{
    STUB();
}

/**
 * @brief StbWebWindow::close
 * Close window
 */
void StbWebWindow::close()
{
    STUB();
    m_page->close();
}

/**
 * @brief StbWebWindow::FocusMiddleWindow
 * Give the focus to the main web browser frame.
 */
void StbWebWindow::FocusMiddleWindow()
{
    STUB();
}

/**
 * @brief StbWebWindow::FocusTopWindow
 * Give the focus to the top web browser frame.
 */
void StbWebWindow::FocusTopWindow()
{
    STUB();
}

/**
 * @brief StbWebWindow::getCurrentUrl
 * Get currently opened URL.
 *
 * @return
 */
QString StbWebWindow::getCurrentUrl()
{
    STUB();
    return m_page->getURL().toString();
}

/**
 * @brief StbWebWindow::messageBroadcast
 * Send message "message" with data "data" to all existed windows. Message can be handled using callback stbEvent.onBroadcastMessage(data)
 *
 * @param message
 * @param data
 */
void StbWebWindow::messageBroadcast(const QString &message, const QString &data)
{
    STUB() << message << data;
}

/**
 * @brief StbWebWindow::messageSend
 * Send message "message" with data "data" to window ID "windowId".
 * Message can be handled using callback stbEvent.onMessage(data) which should be defined in target window.
 *
 * @param windowId
 * @param message
 * @param data
 */
void StbWebWindow::messageSend(int windowId, const QString &message, const QString &data)
{
    STUB() << windowId << message << data;
}

/**
 * @brief StbWebWindow::NavigateBack
 * Go back in the navigation history. Defined only for dedicated "Wild Web" window.
 */
void StbWebWindow::NavigateBack()
{
    STUB();
}

/**
 * @brief StbWebWindow::NavigateForward
 * Go forward in the navigation history. Defined only for dedicated "Wild Web" window.
 */
void StbWebWindow::NavigateForward()
{
    STUB();
}

/**
 * @brief StbWebWindow::ReloadDocument
 * Reload current web document.
 */
void StbWebWindow::ReloadDocument()
{
    STUB();
}

/**
 * @brief StbWebWindow::SendVirtualKeypress
 * Generate virtual key event using Unicode text "unicodeText" and QT key code "key"
 *
 * @param unicodeText
 * @param key
 */
void StbWebWindow::SendVirtualKeypress(const QString &unicodeText, const int key)
{
    STUB() << unicodeText << key;
}

/**
 * @brief StbWebWindow::SetFullScreenMode
 * Set full screen mode for dedicated "Wild Web" window.
 *
 * @param mode
 */
void StbWebWindow::SetFullScreenMode(bool mode)
{
    STUB() << mode;
}

/**
 * @brief StbWebWindow::SetZoomFactor
 * Set zoom ratio for embedded web browser.
 *
 * @param ratio
 */
void StbWebWindow::SetZoomFactor(int ratio)
{
    STUB() << ratio;
}


/**
 * @brief StbWebWindow::StopLoading
 * Cancel loading web document.
 */
void StbWebWindow::StopLoading()
{
    STUB();
}


/**
 * @brief StbWebWindow::windowId
 * Get window ID.
 * @return
 */
int StbWebWindow::windowId()
{
    STUB() << m_page->getId();
    return m_page->getId();
}

