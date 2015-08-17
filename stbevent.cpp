#include "stbevent.h"
#include "macros.h"
#include "magprofile.h"
#include "browser.h"
#include "webpage.h"

using namespace yasem;

StbEvent::StbEvent(MagProfile *profile, SDK::WebPage* page):\
    m_profile(profile),
    m_event_code(STB_EVENT_NO_ERROR),
    m_page(page)
{
    this->setObjectName("StbEvent");
    Q_ASSERT(page);
}

StbEvent::~StbEvent()
{
    STUB();
}

/**
 * @brief StbEvent::sendEvent
 * @param eventCode @see Events
 */
void StbEvent::sendEvent(int eventCode)
{
    STUB() << eventCode << ", name:" << getEventName((Events)eventCode);
    if(m_page)
    {
        Q_ASSERT(m_page);
        m_page->evalJs(QString("javascript: stbEvent.onEvent(%1)").arg(eventCode));
    }
    else {
        FIXME() << "WebPage is missing! This is a bug!";
    }

    this->m_event_code = eventCode;
}

/**
 * @brief StbEvent::onEvent
 * @param eventCode Type of event
 * @param data Associated data in JSON format
 *
 * The function to be called when getting the player event.
 * It is used for processing the events in the portal with the event code as the parameter.
 */
void StbEvent::onEvent(int eventCode, const QString& data = "")
{
    STUB() << eventCode << data;
}

void StbEvent::initEvents()
{
    STUB();
}

/**
 * @brief StbEvent::onBroadcastMessage
 * @param windowId
 * @param message
 * @param data
 *
 * Receive a broadcast message from a window.
 */
void StbEvent::onBroadcastMessage(int windowId, const QString &message, const QString &data)
{
    STUB() << windowId << message << data;
}

/**
 * @brief StbEvent::onInternetStateChange
 * @param status New network state
 *
 * Callback fired on lost/restore internet connection.
 */
void StbEvent::onInternetStateChange(bool status)
{
    STUB() << status;
}

void StbEvent::onLanguageChange()
{
    STUB();
}

/**
 * @brief StbEvent::onMediaAvailable
 *
 * Callback on internet browser link clicked to ask user what to do with link: play or download.
 * It is also used to start playing a downloaded item.
 */
void StbEvent::onMediaAvailable()
{
    STUB();
}

/**
 * @brief StbEvent::onMessage
 * @param windowId
 * @param message
 * @param data
 *
 * Receive a message from a window.
 */
void StbEvent::onMessage(int windowId, const QString &message, const QString &data)
{
    STUB() << windowId << message << data;
}

/**
 * @brief StbEvent::onNetworkStateChange
 * @param status
 *
 * USB device mount/unmount.
 */
void StbEvent::onMount(int state)
{
    STUB() << state;
}

/**
 * @brief StbEvent::onNetworkStateChange
 * @param status
 *
 * Callback fired on lost/restore local network connection.
 */
void StbEvent::onNetworkStateChange(bool status)
{
    STUB() << status;
}

/**
 * @brief StbEvent::onScreenSaverActivation
 * @param mode
 *
 * Callback on screensaver activation/deactivation.
 */
void StbEvent::onScreenSaverActivation(bool mode)
{
    STUB() << mode;
}

/**
 * @brief StbEvent::onScreenSaverOverride
 *
 * Callback on screensaver activation/deactivation.
 */
void StbEvent::onScreenSaverOverride()
{
    STUB();
}

/**
 * @brief StbEvent::onWebBrowserProgress
 * @param progress
 *
 * Callback on current web document loading.
 * Triggers every time the document loading progress changes.
 */
void StbEvent::onWebBrowserProgress(int progress)
{
    STUB() << progress;
}

/**
 * @brief StbEvent::onWindowActivated
 *
 * Callback on browser web window activation.
 */
void StbEvent::onWindowActivated()
{
    STUB();
}

int StbEvent::getEventCode()
{
    return m_event_code;
}

QString StbEvent::getEventName(StbEvent::Events event)
{
    int keyEnumIndex = staticMetaObject.indexOfEnumerator("Events");
    return staticMetaObject.enumerator(keyEnumIndex).valueToKey(event);
}
