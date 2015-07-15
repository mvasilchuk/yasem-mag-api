#include "stbwebwindow.h"
#include "macros.h"
#include "magprofile.h"
#include "browser.h"
#include "webpage.h"

using namespace yasem;

StbWebWindow::StbWebWindow(MagProfile *profile, SDK::WebPage* page)
{
    this->profile = profile;
    this->m_page = page;
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
