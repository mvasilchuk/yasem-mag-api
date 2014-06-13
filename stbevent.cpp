#include "stbevent.h"
#include "macros.h"
#include "magprofile.h"
#include "browserplugin.h"

using namespace yasem;

StbEvent::StbEvent(MagProfile *profile)
{
    this->setObjectName("StbEvent");

    this->profile = profile;
}

void StbEvent::sendEvent(int eventCode)
{
    profile->getProfilePlugin()->browser()->evalJs(QString("javascript: stbEvent.onEvent(%1)").arg(eventCode));
}

void StbEvent::onEvent(int eventCode)
{
    STUB() << eventCode;
}
