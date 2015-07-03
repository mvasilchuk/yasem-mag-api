#include "stbevent.h"
#include "macros.h"
#include "magprofile.h"
#include "browserpluginobject.h"
#include "abstractwebpage.h"

using namespace yasem;

StbEvent::StbEvent(MagProfile *profile, SDK::AbstractWebPage* page)
{
    this->setObjectName("StbEvent");
    this->m_page = page;
    this->profile = profile;
}

void StbEvent::sendEvent(int eventCode)
{
    m_page->evalJs(QString("javascript: stbEvent.onEvent(%1)").arg(eventCode));

    this->eventCode = eventCode;
}

void StbEvent::onEvent(int eventCode)
{
    STUB() << eventCode;
}

void StbEvent::initEvents()
{

}

int StbEvent::getEventCode()
{
    return eventCode;
}
