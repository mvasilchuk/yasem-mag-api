#include "stbscreen.h"
#include "magprofile.h"

using namespace yasem;

StbScreen::StbScreen(MagProfile *profile)
{
    width = 1280;
    height = 720;
    innerWidth = 1280;
    innerHeight = 720;

    this->profile = profile;
}


