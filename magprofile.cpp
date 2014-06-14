#include "stbplugin.h"
#include "browserplugin.h"
#include "magprofile.h"
#include "datasource.h"
#include "pluginmanager.h"
#include "profilemanager.h"
#include "mag_macros.h"
#include "mediaplayerplugin.h"
#include "stbevent.h"

#include <QDir>

static const QString CONFIG_INTERNAL_PORTAL = "internal_portal";

using namespace yasem;

MagProfile::MagProfile(StbPlugin *profilePlugin, const QString &id = "") :
    Profile(profilePlugin, id)
{
    Q_ASSERT(profilePlugin);

    submodelNames.insert(MAG_100, "MAG100");
    submodelNames.insert(MAG_200, "MAG200");
    submodelNames.insert(MAG_245, "MAG245");
    submodelNames.insert(MAG_250, "MAG250");
    submodelNames.insert(MAG_254, "MAG254");
    submodelNames.insert(MAG_255, "MAG255");
    submodelNames.insert(MAG_260, "MAG260");
    submodelNames.insert(MAG_270, "MAG270");
    submodelNames.insert(MAG_275, "MAG275");

    userAgents.insert("MAG250", "Mozilla/5.0 (QtEmbedded; U; Linux; C) AppleWebKit/533.3 (KHTML, like Gecko) MAG200 stbapp ver: 2 rev: 234 Safari/533.3");

    portalResolutions.insert("720", QSize(720, 576));
    portalResolutions.insert("1280", QSize(1280, 720));
    portalResolutions.insert("1920", QSize(1920, 1080));

    videoResolutions.insert("720p", QSize(1280, 720));
    videoResolutions.insert("1080p", QSize(1920, 1080));

    //MAG specific options
    profileConfig.add(ProfileConfig::Option(DB_TAG_RDIR, "MACAddress", "00:1A:79:00:00:00", "MAC address"));
    profileConfig.add(ProfileConfig::Option(DB_TAG_ENV, "portal1", "", "Portal URL"));
}

void MagProfile::start()
{
    STUB();

    MediaPlayerPlugin* player = profilePlugin->player();
    MediaSignalSender& signalHandler = player->getSignalSender();

    StbEvent* event = static_cast<StbEvent*>(profilePlugin->getStbApiList().find("stbEvent").value());

    connect(&signalHandler, &MediaSignalSender::paused,               this, [=](bool)
    {
        event->sendEvent(StbEvent::STB_EVENT_NO_ERROR);
    });
    connect(&signalHandler, &MediaSignalSender::started,              this, [=]()
    {
        event->sendEvent(StbEvent::STB_EVENT_GOT_VIDEO_INFO);
        event->sendEvent(StbEvent::STB_EVENT_PLAY_START);
    });
    connect(&signalHandler, &MediaSignalSender::stopped,              this, [=]()
    {
        event->sendEvent(StbEvent::STB_EVENT_EOF);
    });
    connect(&signalHandler, &MediaSignalSender::speedChanged,         this, [=](qreal speed)
    {
        DEBUG() << "speedChanged" << speed;
    });
    connect(&signalHandler, &MediaSignalSender::repeatChanged,        this, [=](int repeat)
    {
        DEBUG() << "repeatChanged" << repeat;
    });
    connect(&signalHandler, &MediaSignalSender::currentRepeatChanged, this, [=](int repeat)
    {
        DEBUG() << "currentRepeatChanged" << repeat;
    });
    connect(&signalHandler, &MediaSignalSender::startPositionChanged, this, [=](qint64 pos)
    {
        DEBUG() << "startPositionChanged" << pos;
    });
    connect(&signalHandler, &MediaSignalSender::stopPositionChanged,  this, [=](qint64 pos)
    {
        DEBUG() << "stopPositionChanged" << pos;
    });
    connect(&signalHandler, &MediaSignalSender::positionChanged,      this, [=](qint64 pos)
    {
        DEBUG() << "stopPositionChanged" << pos;
    });
    connect(&signalHandler, &MediaSignalSender::brightnessChanged,    this, [=](bool)
    {

    });
    connect(&signalHandler, &MediaSignalSender::contrastChanged,      this, [=](bool)
    {
    });
    connect(&signalHandler, &MediaSignalSender::saturationChanged,    this, [=](bool)
    {
    });

    //QString defaultUrl = "http://dmichael.org.ua/mag250";
    //QString defaultUrl = "http://tvportal1.global.net.ba";
    //QString defaultUrl = "http://stalker.local/stalker_portal/c/";
    //QString defaultUrl = "http://192.168.0.71:8087/portal-dev/";
    //QString defaultUrl = "http://tv.ipnet.ua/mag200/";
    //QString defaultUrl = "http://iptv.bluepointtv.com";
    //QString defaultUrl = datasource()->get("profile", "portal", "http://tv.tenet.ua/iptv/all22");
    //QString urlString = "file:///home/max/www/test.html";

    internalPortal = get(CONFIG_INTERNAL_PORTAL, "").toLower() == "true";

    configureKeyMap();

    QString userAgent = get(CONFIG_SUBMODEL, "MAG250");
    if(userAgent == "CUSTOM")
        userAgent = get("user_agent", userAgents.value("MAG250"));
    else
        userAgent = userAgents.value(userAgent);

    profilePlugin->browser()->setUserAgent(userAgent);

    profilePlugin->browser()->stb(profilePlugin);

    QSize portalSize = portalResolutions.value(datasource()->get(DB_TAG_RDIR, "gmode", "1280"));
    profilePlugin->browser()->setInnerSize(portalSize);

    QString urlString = portal();
    qDebug() << "Loading" << urlString;
    QUrl portalUrl = QUrl(urlString.replace("~", QDir::homePath()));
    profilePlugin->browser()->load(portalUrl);

}

void MagProfile::configureKeyMap()
{
    BrowserPlugin* browser = profilePlugin->browser();

    browser->clearKeyEvents();

    browser->registerKeyEvent(RC_KEY_OK, 13, 13);
    browser->registerKeyEvent(RC_KEY_LEFT, 37, 37);
    browser->registerKeyEvent(RC_KEY_RIGHT, 39, 39);
    browser->registerKeyEvent(RC_KEY_UP, 38, 38);
    browser->registerKeyEvent(RC_KEY_DOWN, 40, 40);

    browser->registerKeyEvent(RC_KEY_BACK, 8, 8);
    browser->registerKeyEvent(RC_KEY_PAGE_UP, 33, 33);
    browser->registerKeyEvent(RC_KEY_PAGE_DOWN, 34, 34);

    browser->registerKeyEvent(RC_KEY_FAST_FORWARD, 70, 102, true);
    browser->registerKeyEvent(RC_KEY_REWIND, 66, 98, true);
    browser->registerKeyEvent(RC_KEY_STOP, 83, 83, true);
    browser->registerKeyEvent(RC_KEY_PLAY_PAUSE, 82, 82, true);

    browser->registerKeyEvent(RC_KEY_EXIT, 27, 27);
    browser->registerKeyEvent(RC_KEY_MENU, 122, 122, false, true);
    browser->registerKeyEvent(RC_KEY_REFRESH, 116, 116, false, true);

    browser->registerKeyEvent(RC_KEY_RED, 112, 112, false, true);
    browser->registerKeyEvent(RC_KEY_GREEN, 113, 113, false, true);
    browser->registerKeyEvent(RC_KEY_YELLOW, 114, 114, false, true);
    browser->registerKeyEvent(RC_KEY_BLUE, 115, 115, false, true);
}

QString MagProfile::portal()
{
    return datasource()->get(DB_TAG_ENV, "portal1", "--");
}

void MagProfile::stop()
{

}

void MagProfile::initDefaults()
{
    STUB();

    Datasource* ds = datasource();

    /*
        STB Model:MAG250
        Date:Thu Feb 20 11:29:26 EET 2014
        Image Version:218
        Image Description:0.2.18-250
        VerUpdateAPI:2
        Kernel size:3316779
        Image  size:57222199
     */

    ds->set(DB_TAG_RDIR, "IPAddress", "192.168.0.100");
    ds->set(DB_TAG_RDIR, "ImageVersion", "216");
    ds->set(DB_TAG_RDIR, "Img_Ver", "ImageVersion: 216");
    ds->set(DB_TAG_RDIR, "ImageDescription", "0.2.16-r2");
    ds->set(DB_TAG_RDIR, "ImageDate", "Fri Oct 25 17:28:41 EEST 2013");
    ds->set(DB_TAG_RDIR, "vmode", "720p");
    ds->set(DB_TAG_RDIR, "gmode", "1280");
    //ds->set(DB_TAG_RDIR, "get_storage_info", getStorageInfo());
    ds->set(DB_TAG_RDIR, "HardwareVersion", "1.7-BD-00");
    ds->set(DB_TAG_RDIR, "MACAddress", "00:1A:79:00:00:00");
    //ds->set(DB_TAG_RDIR, "MACAddress", "00:1A:79:10:EF:13");
    ds->set(DB_TAG_RDIR, "SerialNumber", "012012N01212");
    ds->set(DB_TAG_RDIR, "Model", "MAG250");
    ds->set(DB_TAG_RDIR, "WiFi_link", "Off");
    ds->set(DB_TAG_RDIR, "LAN_link", "On");


    ds->set(DB_TAG_ENV, "portal1", "");
    ds->set(DB_TAG_ENV, "ntpurl", "pool.ntp.org");
    ds->set(DB_TAG_ENV, "timezone_conf", "Europe/Kiev");
    ds->set(DB_TAG_ENV, "timezone", "Europe/Kyiv");
    ds->set(DB_TAG_ENV, "language", "en");
    ds->set(DB_TAG_ENV, "playlist_url", "");
    ds->set(DB_TAG_ENV, "playlist_charset", "UTF-8");

    //Codes in MAG language table
    ds->set(DB_TAG_ENV, "lang_subtitles", "0");
    ds->set(DB_TAG_ENV, "lang_audiotracks", "0");
    ds->set(DB_TAG_ENV, "subtitles_on", "true");
    ds->set(DB_TAG_ENV, "mtdparts", "");

    ds->set(DB_TAG_ENV, "update_url", "");
    ds->set(DB_TAG_ENV, "ntpurl", "");
    ds->set(DB_TAG_ENV, "graphicres", "720");
    ds->set(DB_TAG_ENV, "tvsystem", "1080p-60");
    ds->set(DB_TAG_ENV, "ethaddr", "00:1A:79:00:00:01");
    ds->set(DB_TAG_ENV, "volume", "50");
    ds->set(DB_TAG_ENV, "autoupdate_cond", "2");
    ds->set(DB_TAG_ENV, "betaupdate_cond", "");
    ds->set(DB_TAG_ENV, "front_panel", "");
    ds->set(DB_TAG_ENV, "screen_clock", "");

    ds->set(DB_TAG_ENV, "ts_endType", "");
    ds->set(DB_TAG_ENV, "ts_exitType", "");
    ds->set(DB_TAG_ENV, "ts_icon", "");
    ds->set(DB_TAG_ENV, "ts_lag", "");
    ds->set(DB_TAG_ENV, "ts_on", "");
    ds->set(DB_TAG_ENV, "ts_path", "");
    ds->set(DB_TAG_ENV, "ts_time", "");

    ds->set(DB_TAG_ENV, "video_clock", "0");
    ds->set(DB_TAG_ENV, "upnp_conf", "lan");

    ds->set(DB_TAG_ENV, "audio_operational_mode", "");
    ds->set(DB_TAG_ENV, "audio_hdmi_audio_mode", "");
    ds->set(DB_TAG_ENV, "audio_stereo_out_mode", "");
    ds->set(DB_TAG_ENV, "audio_spdif_mode", "");
    ds->set(DB_TAG_ENV, "audio_dyn_range_comp", "");
    ds->set(DB_TAG_ENV, "audio_initial_volume", "50");
    ds->set(DB_TAG_ENV, "input_buffer_size", "");
}

bool MagProfile::isInternalPortal()
{
    return internalPortal;
}
