#include "stbplugin.h"
#include "browserplugin.h"
#include "magprofile.h"
#include "datasource.h"
#include "pluginmanager.h"
#include "profilemanager.h"
#include "mag_macros.h"
#include "mediaplayerplugin.h"
#include "stbevent.h"
#include "mag_enums.h"
#include "profileconfigparserimpl.h"

#include <QDir>

static const QString CONFIG_INTERNAL_PORTAL = "internal_portal";

using namespace yasem;

MagProfile::MagProfile(StbPlugin *profilePlugin, const QString &id = "") :
    Profile(profilePlugin, id)
{
    Q_ASSERT(profilePlugin);

    userAgents.insert("MAG250", "Mozilla/5.0 (QtEmbedded; U; Linux; C) AppleWebKit/533.3 (KHTML, like Gecko) MAG200 stbapp ver: 2 rev: 234 Safari/533.3");

    portalResolutions.insert("720", QSize(720, 576));
    portalResolutions.insert("1280", QSize(1280, 720));
    portalResolutions.insert("1920", QSize(1920, 1080));

    videoResolutions.insert("720p", QSize(1280, 720));
    videoResolutions.insert("1080p", QSize(1920, 1080));

    loadConfigOptions();
}

void MagProfile::loadConfigOptions()
{
    ProfileConfigGroup &main_group = profileConfiguration.groups.first(); //Main group is created by default in profile
    main_group.options.append(ConfigOption(DB_TAG_ENV, "portal1", tr("Portal URL"), "http://", "string"));

    QHash<QString, QString> models;
    models.insert("MAG100", "MAG 100");
    models.insert("MAG200", "MAG 200");
    models.insert("MAG245", "MAG 245");
    models.insert("MAG250", "MAG 250");
    models.insert("MAG254", "MAG 254");
    models.insert("MAG255", "MAG 255");
    models.insert("MAG260", "MAG 260");
    models.insert("MAG270", "MAG 270");
    models.insert("MAG275", "MAG 275");
    models.insert("AuraHD", "AuraHD");
    main_group.options.append(ConfigOption(DB_TAG_PROFILE, "Model",         tr("STB Model"),          "MAG250",       "options", "", models));

    QHash<QString, QString> gmodes;
    gmodes.insert("720", "720x576");
    gmodes.insert("1280", "1280x720");
    gmodes.insert("1920", "1920x1080");
    main_group.options.append(ConfigOption(DB_TAG_RDIR, "gmode",         tr("Graphical mode"),     "1280",         "options", "", gmodes));

    QHash<QString, QString> vmodes;
    vmodes.insert("720p", "720p (HD)");
    vmodes.insert("1080p", "1080p (FullHD)");
    main_group.options.append(ConfigOption(DB_TAG_RDIR, "vmode",         tr("Video mode"),         "720p",         "options", "", vmodes));
    main_group.options.append(ConfigOption(DB_TAG_ENV,  "subtitles_on",  tr("Subtitles enabled"),  "true",         "bool",   ""));
    main_group.options.append(ConfigOption(DB_TAG_ENV,  "timezone_conf", tr("Timezone"),           "Europe/Kiev",  "string", ""));

    ProfileConfigGroup network(tr("Network"));
    network.options.append(ConfigOption(DB_TAG_RDIR,  "MACAddress",   tr("MAC address"),     "00:1A:79:00:00:00",  "string"));
    network.options.append(ConfigOption(DB_TAG_RDIR,  "SerialNumber", tr("Serial number"),   "012012N01212",       "string"));
    network.options.append(ConfigOption(DB_TAG_RDIR,  "LAN_link",     tr("LAN enabled"),     "true",               "bool"));
    network.options.append(ConfigOption(DB_TAG_ENV,   "ethaddr",      tr("LAN MAC Address"), "00:1A:79:00:00:01",  "string"));
    network.options.append(ConfigOption(DB_TAG_RDIR,  "WiFi_link",    tr("Wi-Fi enabled"),   "false",              "bool"));
    network.options.append(ConfigOption(DB_TAG_RDIR,  "IPAddress",    tr("Wi-Fi address"),   "192.168.0.100",      "string"));

    network.options.append(ConfigOption(DB_TAG_ENV,  "mc_proxy_enabled",    tr("Multicast proxy enabled"),      "false",                    "bool"));
    network.options.append(ConfigOption(DB_TAG_ENV,  "mc_proxy_url",        tr("Multicast proxy URL"),          "http://0.0.0.0:1234",      "string"));
    profileConfiguration.groups.append(network);

    ProfileConfigGroup hardware(tr("Hardware"));
    hardware.options.append(ConfigOption(DB_TAG_RDIR, "HardwareVersion", tr("Hardware version"), "1.7-BD-00", "string"));
    profileConfiguration.groups.append(hardware);

    ProfileConfigGroup firmware_description(tr("Firmware"));
    firmware_description.options.append(ConfigOption(DB_TAG_RDIR, "ImageDate",        tr("Image date"),         "Fri Oct 25 17:28:41 EEST 2013", "string"));
    firmware_description.options.append(ConfigOption(DB_TAG_RDIR, "ImageDescription", tr("Image description"),  "0.2.16-r2",                     "string"));
    firmware_description.options.append(ConfigOption(DB_TAG_RDIR, "ImageVersion",     tr("Image version"),      "216",                           "string"));
    profileConfiguration.groups.append(firmware_description);
}

void MagProfile::start()
{
    STUB();

    MediaPlayerPlugin* player = profilePlugin->player();
    MediaSignalSender& signalHandler = player->getSignalSender();

    StbEvent* event = static_cast<StbEvent*>(profilePlugin->getStbApiList().find("stbEvent").value());

    Q_ASSERT(event);

    connect(&signalHandler, &MediaSignalSender::paused,               this, [=](bool)
    {
        DEBUG() << "[MEDIA]: paused";
        event->sendEvent(StbEvent::STB_EVENT_NO_ERROR);
    });
    connect(&signalHandler, &MediaSignalSender::started,              this, [=]()
    {
        DEBUG() << "[MEDIA]: started";
        event->sendEvent(StbEvent::STB_EVENT_GOT_VIDEO_INFO);
        event->sendEvent(StbEvent::STB_EVENT_PLAY_START);
    });

    connect(&signalHandler, &MediaSignalSender::speedChanged,         this, [=](qreal speed)
    {
        DEBUG() << "[MEDIA]: speedChanged" << speed;
    });
    connect(&signalHandler, &MediaSignalSender::repeatChanged,        this, [=](int repeat)
    {
        DEBUG() << "[MEDIA]: repeatChanged" << repeat;
    });
    connect(&signalHandler, &MediaSignalSender::currentRepeatChanged, this, [=](int repeat)
    {
        DEBUG() << "[MEDIA]: currentRepeatChanged" << repeat;
    });
    connect(&signalHandler, &MediaSignalSender::startPositionChanged, this, [=](qint64 pos)
    {
        DEBUG() << "[MEDIA]: startPositionChanged" << pos;
    });
    connect(&signalHandler, &MediaSignalSender::stopPositionChanged,  this, [=](qint64 pos)
    {
        DEBUG() << "[MEDIA]: stopPositionChanged" << pos;
    });
    connect(&signalHandler, &MediaSignalSender::positionChanged,      this, [=](qint64 pos)
    {
        //DEBUG() << "[MEDIA]: positionChanged" << pos;
    });
    connect(&signalHandler, &MediaSignalSender::brightnessChanged,    this, [=](bool)
    {
        DEBUG() << "[MEDIA]: brightnessChanged";
    });
    connect(&signalHandler, &MediaSignalSender::contrastChanged,      this, [=](bool)
    {
        DEBUG() << "[MEDIA]: contrastChanged";
    });
    connect(&signalHandler, &MediaSignalSender::saturationChanged,    this, [=](bool)
    {
        DEBUG() << "[MEDIA]: saturationChanged";
    });

    connect(&signalHandler, &MediaSignalSender::statusChanged,              this, [=](MediaStatus status)
    {
        DEBUG() << "[MEDIA]: status changed:" << status;
        switch(status)
        {
            case MediaStatus::EndOfMedia: {
                event->sendEvent(StbEvent::STB_EVENT_EOF);
                break;
            }
            default: {
                WARN() << "status ignored";
                break;
            }
        }
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

    QString submodel = get("Model", "MAG250");

    qDebug() << "submodel" << submodel;

    QString userAgent;

    if(submodel == "CUSTOM")
        submodel = get("user_agent", userAgents.value(submodel));
    else
        userAgent = userAgents.value(submodel);

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

}

bool MagProfile::isUsingMulticastProxy()
{
    return datasource()->get(DB_TAG_ENV, "mc_proxy_enabled", "false") == "true";
}

QString MagProfile::getMulticastProxy()
{
    return datasource()->get(DB_TAG_ENV, "mc_proxy_url", "");
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
    ds->set(DB_TAG_RDIR, "ModelExt", "MAG250");
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

