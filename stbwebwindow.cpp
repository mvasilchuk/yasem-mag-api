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

void StbWebWindow::close()
{
    STUB();
    m_page->close();
}

QString StbWebWindow::windowId()
{
    STUB();
    return "---- < TODO: WINDOW ID > -----";
}

/**
 * @brief StbWebWindow::messageSend
 * @param windowId
 * @param message
 * @param data
 * Send message "message" with data "data" to window ID "windowId".
 * Message can be handled using callback stbEvent.onMessage(data) which should be defined in target window.
 */
void StbWebWindow::messageSend(int windowId, const QString &message, const QString &data)
{
    STUB() << windowId << message << data;
}
