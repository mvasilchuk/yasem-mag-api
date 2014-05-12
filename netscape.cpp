#include "netscape.h"
#include "stbplugin.h"
#include "magprofile.h"

using namespace yasem;

Netscape::Netscape(MagProfile *profile)
{
    security = new Security();

    this->profile = profile;
}
