#include "stbwebwindow.h"
#include "macros.h"
#include "magprofile.h"
#include "browserplugin.h"

using namespace yasem;

StbWebWindow::StbWebWindow(MagProfile *profile)
{
    this->profile = profile;
}

void StbWebWindow::close()
{
    STUB();

    profile->getProfilePlugin()->browser()->evalJs("debugger; window.close();");

    //parent->page()->close();
}

QString StbWebWindow::windowId()
{
    STUB();
    return "---------";
}
