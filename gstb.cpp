#include "gstb.h"
#include "stbpluginobject.h"
#include "datasourceplugin.h"
#include "browserpluginobject.h"
#include "mediaplayerpluginobject.h"
#include "guipluginobject.h"
#include "enums.h"
#include "mag_enums.h"
#include "mag_macros.h"
#include "core.h"
#include "datasourcepluginobject.h"
#include "magprofile.h"
#include "stbevent.h"
#include "mediaplayerpluginobject.h"
#include "NetworkThread.h"
#include "magapistbobject.h"
#include "core-network.h"
#include "samba.h"
#include "sambanode.h"
#include "abstractwebpage.h"

#ifdef CONFIG_QCA
#include "remotecontrolhandler.h"
#endif //CONFIG_QCA

#include <QStringList>
#include <QDebug>
#include <QSysInfo>
#include <QDir>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QRect>
#include <QRegExp>
#include <QRegularExpression>
#include <QCryptographicHash>
#include <QHostInfo>

using namespace yasem;

GStb::GStb(MagProfile *profile, AbstractWebPage* page):
    m_profile(profile),
    m_page(page)
{
    //qDebug() << "logger: " << parent->getLogger();
    this->setObjectName("gSTB");
}

QString GStb::listLocalFiles(const QString &dir)
{
    QDir* directory = new QDir(dir);
    QJsonArray files;
    QJsonArray dirs;

    DEBUG() << directory->absolutePath();
    foreach (QFileInfo file, directory->entryInfoList(QDir::Files | QDir::Dirs, QDir::Name))
    {
        if(file.isDir())
        {
            if(file.fileName() == "." || file.fileName() == "..") continue;
            dirs.append(file.fileName() + "/");
        }
        else if(file.isFile())
        {
            QStringList fileParts = file.fileName().split(".");
            if(fileParts.length() > 0 && !listFileExt.contains(QString(".") + fileParts.at(fileParts.length()-1)))
            {
                INFO() << "Skipping file " << file.fileName();
                continue;
            }

            QJsonObject obj;
            obj.insert("name", file.fileName() );
            obj.insert("size", QString::number(file.size()));
            files.append(QJsonValue::fromVariant(QJsonDocument(obj).toVariant()));
        }
    }

    dirs.append(QString(""));
    files.append(QJsonValue::fromVariant(QJsonDocument(QJsonObject()).toVariant()));

    QString result =  QString("var dirs = %1; var files = %2;").arg(QString(QJsonDocument(dirs).toJson(QJsonDocument::Compact))).arg(QString(QJsonDocument(files).toJson(QJsonDocument::Compact)));
    //DEBUG(result);
    return result;
}

MediaPlayerPluginObject *GStb::player()
{
    return profile()->getProfilePlugin()->player();
}

BrowserPluginObject *GStb::browser()
{
    return profile()->getProfilePlugin()->browser();
}

DatasourcePluginObject *GStb::datasource()
{
    return profile()->datasource();
}

void GStb::CloseWebWindow()
{
    STUB();
}

/**
 * @brief GStb::Continue
 */
void GStb::Continue()
{
    CHECK_OR_RETURN_VOID(player());
    player()->mediaContinue();
}

void GStb::Debug(const QString &str)
{
    DEBUG() << str;
}

void GStb::DeinitPlayer()
{
    STUB();
}

void GStb::DeleteAllCookies()
{
    STUB();
}

void GStb::EnableAppButton(bool enable)
{
    STUB() << enable;
}

void GStb::EnableCustomNavigation(bool enable)
{
    STUB() << enable;
}

void GStb::EnableJavaScriptInterrupt(bool enable)
{
    STUB() << enable;
}

void GStb::EnableMulticastProxy(bool enable)
{
    STUB() << enable;
}

void GStb::EnableServiceButton(bool enable)
{
    STUB() << enable;
}

void GStb::EnableSetCookieFrom(const QString &domain, bool enable)
{
    STUB() << domain << enable;
}

void GStb::EnableSpatialNavigation(bool enable)
{
    STUB() << QString("EnableSpatialNavigation(%1)").arg(enable);
}

void GStb::EnableVKButton(bool enable)
{
    STUB() << enable;
}

void GStb::ExecAction(const QString &str)
{
    STUB() << str;
}

void GStb::ExtProtocolCommand(const QString &val1, const QString &val2, const QString &val3)
{
    STUB() << val1 << val2 << val3;
}

/**
 * @brief GStb::ForceHDMItoDVI
 * @param forceDVI
 * 0	auto detect HDMI mode
 * 1	force HDMI to DVI mode
 */
void GStb::ForceHDMItoDVI(int forceDVI)
{
    STUB() << forceDVI;
}

int GStb::Get3DConversionMode()
{
    STUB();
    return 0;
}

int GStb::GetAlphaLevel()
{
    STUB();
    return 0;
}

/**
 * @brief GStb::GetAspect
 * @return
 * 0	as it is (video is stretched for the whole screen)
 * 1	Letter box mode (video is proportionally enlarged to the size of the screen along the larger edge)
 * 2	Pan&Scan mode (video is proportionally enlarged to the screen size along the lesser edge)
 * 3	combined mode (intermediate between Letter Box Box and Pan&Scan)
 * 4	enlarged mode
 * 5	optimal mode
 */
int GStb::GetAspect()
{
    STUB();
    CHECK_OR_RETURN(player(), ASPECT_RATIO_AUTO);
    AspectRatio ratio = player()->getAspectRatio();

    switch(ratio)
    {
        case ASPECT_RATIO_AUTO: {
            return 0;
        }
        case ASPECT_RATIO_20_9: {
            return 1;
        }
        case ASPECT_RATIO_16_9: {
            return 2;
        }
        case ASPECT_RATIO_4_3: {
            return 3;
        }
        default: {
            return ASPECT_RATIO_16_9;
        }
    }
}

int GStb::GetAudioPID()
{
    CHECK_OR_RETURN(player(), 0);
    return player()->getAudioPID();
}

QString GStb::GetAudioPIDs()
{
    QJsonArray resultArray;
    CHECK_OR_RETURN(player(), "[]");
    QList<AudioLangInfo> languages = player()->getAudioLanguages();
    for(AudioLangInfo info: languages)
    {
        QJsonObject obj;
        obj.insert("pid", info.pid);

        QJsonArray names;
        names.append(info.code2);
        names.append(info.code3);

        obj.insert("lang", names);
        resultArray.append(obj);
    }
    QString res = QJsonDocument(resultArray).toJson();
    return res;
}

/**
 * @brief GStb::GetAudioPIDsEx
 * @return
list of the audio tracks found in the following format:
[{pid:<PID1>, lang:[<lang1_1>, <lang2_1>], type:<type_1>}, ... , {pid:<PIDn>, lang:[<lang1_n>, <lang2_n>], type:<type_n>}]
where:
PIDn                PID of audio track with the number n
lang1_n, lang2_n	first two descriptions of languages in audio track
number n            3-symbol tags according to ISO 639
type_n is audio codec type:

Value	Description
    0	Unknown
    1	mp2a
    2	mp3
    3	AC3
    4	AAC
    5	PCM
    6	OGG
    7	DTS
 *
 */
QString GStb::GetAudioPIDsEx()
{
    QJsonArray resultArray;
    CHECK_OR_RETURN(player(), "[]");
    QList<AudioLangInfo> languages = player()->getAudioLanguages();
    for(AudioLangInfo info: languages)
    {
        QJsonObject obj;
        obj.insert("pid", info.pid);

        QJsonArray names;
        names.append(info.code2);
        names.append(info.code3);

        obj.insert("lang", names);

        obj.insert("type", "Unknown");
        resultArray.append(obj);
    }
    QString res = QJsonDocument(resultArray).toJson();

    return res;
}

int GStb::GetBrightness()
{
    CHECK_OR_RETURN(player(), 0);
    return player()->getBrightness();
}

int GStb::GetBufferLoad()
{
    CHECK_OR_RETURN(player(), 100);
    return player()->bufferLoad();
}

int GStb::GetContrast()
{
    CHECK_OR_RETURN(player(), 0);
    return player()->getContrast();
}

QString GStb::GetDeviceActiveBank()
{
    STUB();
    return profile()->datasource()->get(DB_TAG_ENV, "DeviceActiveBank", "0");
}

QString GStb::GetDeviceImageDesc()
{
    QString description = profile()->datasource()->get(DB_TAG_RDIR, "ImageDescription");
    LOG() << description;
    return description;
}

QString GStb::GetDeviceImageVersion()
{
    QString version = profile()->datasource()->get(DB_TAG_RDIR, "ImageVersion");
    LOG() << QString("GetDeviceImageVersion(): %1").arg(version);
    return version;
}

QString GStb::GetDeviceImageVersionCurrent()
{
    QString version = profile()->datasource()->get(DB_TAG_RDIR, "DeviceImageVersionCurrent", "0.2.16-250 Tue Apr 9 18:10:19 EEST 2013");
    LOG() << QString("GetDeviceImageVersionCurrent(): %1").arg(version);
    return version;
}

QString GStb::GetDeviceMacAddress()
{
    if(!profile()->datasource())
        return "";

    QString mac = profile()->datasource()->get(DB_TAG_RDIR, "MACAddress");
    LOG() << QString("GetDeviceMacAddress(): %1").arg(mac);
    return mac;
}

QString GStb::GetDeviceModel()
{
    QString model = "MAG250";
    STUB() << QString("GetDeviceModel(): %1").arg(model);
    return model;
}

QString GStb::GetDeviceModelExt()
{
    STUB();
    return "MAG250";
}

QString GStb::GetDeviceSerialNumber()
{
    if(!profile()->datasource())
        return "";

    QString serial = profile()->datasource()->get(DB_TAG_RDIR, "SerialNumber");
    LOG() << QString("GetDeviceSerialNumber(): %1").arg(serial);
    return serial;
}

QString GStb::GetDeviceVendor()
{
    QString vendor = profile()->datasource()->get(DB_TAG_RDIR, "HardwareVersion", "TeleTec");
    STUB() << QString("GetDeviceVendor(): %1").arg(vendor);
    return vendor;
}

QString GStb::GetDeviceVersionHardware()
{
    QString device_hardware =  profile()->datasource()->get(DB_TAG_RDIR, "HardwareVersion", "1.7-BD-00");
    STUB() << QString("GetDeviceVersionHardware(): %1").arg(device_hardware);
    return device_hardware;
}

QString GStb::GetEnv(const QString &data)
{
    if(!profile()->datasource())
        return "";

    QJsonObject obj = QJsonDocument::fromJson(QByteArray(data.toUtf8())).object();
    QJsonObject elements;
    QJsonArray varList = obj.value("varList").toArray();

    for(int index = 0; index < varList.size(); index++)
    {
        QString name = varList.at(index).toString();

        QString value = profile()->datasource()->get(DB_TAG_ENV, name);
        if(name == "portal1" && value.startsWith("file:///"))
        {
             elements.insert(name, "");
        }// Fix for internal portals
        else
            elements.insert(name, value);
    }

    //QString result = parent->getDataSource()->getValue(DB_TAG_ENV, name);
    QJsonObject result;
    result.insert("result", elements);
    result.insert("errMsg", "");
    result.insert("errCode", 0);

    QString strResult  = QString(QJsonDocument(result).toJson(QJsonDocument::Compact));
    DEBUG() << QString("GetEnv(%1): %2").arg(data, strResult);
    return strResult;
}

QString GStb::GetExtProtocolList()
{
    STUB();
    return "[]";
}

bool GStb::GetLanLinkStatus()
{
    STUB();
    return Core::instance()->network()->isLanConnected();
}

int GStb::GetMediaLen()
{
    STUB();
    CHECK_OR_RETURN(player(), 0);
    int len = (int)(player()->getDuration() / 1000);
    DEBUG() << "media length:" << len;
    return len;

}

int GStb::GetMediaLenEx()
{
    STUB();
    CHECK_OR_RETURN(player(), 0);
    //TODO: fixme
    return (int)(player()->getDuration() / 1000);
}

QString GStb::GetMetadataInfo()
{
    STUB();
    CHECK_OR_RETURN(player(), "{}");
    MediaMetadata metadata = player()->getMediaMetadata();

    QJsonObject data;
    data.insert("album",            metadata.album);
    data.insert("album_artist",     metadata.album_artist);
    data.insert("artist",           metadata.artist);
    data.insert("comment",          metadata.comment);
    data.insert("composer",         metadata.composer);
    data.insert("copyright",        metadata.copyright);
    data.insert("date",             metadata.date);
    data.insert("disk",             metadata.disk);
    data.insert("encoder",          metadata.encoder);
    data.insert("encoded_by",       metadata.encoded_by);
    data.insert("filename",         metadata.filename);
    data.insert("genre",            metadata.genre);
    data.insert("language",         metadata.language);
    data.insert("performer",        metadata.performer);
    data.insert("publisher",        metadata.publisher);
    data.insert("title",            metadata.title);
    data.insert("track",            metadata.track);

    return QJsonDocument(data).toJson();
}

/**
 * @brief GStb::GetMicVolume
 *
 * MAG 100 Only
 * @return
 */
int GStb::GetMicVolume()
{
    STUB();
    CHECK_OR_RETURN(player(), 100);
    return 100;
}

bool GStb::GetMute()
{
    STUB();
    CHECK_OR_RETURN(player(), false);
    return player()->isMute();
}

QString GStb::GetNetworkGateways()
{
    STUB();
    return "";
}

QString GStb::GetNetworkNameServers()
{
    STUB();
    return "8.8.8.8\n8.8.4.4";
}

QString GStb::GetNetworkWifiMac()
{
    STUB();
    return "";
}

bool GStb::GetPIG()
{
    STUB();
    CHECK_OR_RETURN(player(), false);
    return !(player()->isFullscreen());
}

int GStb::GetPosPercent()
{
    STUB();
    CHECK_OR_RETURN(player(), 0);
    int pos = 0;
    qint64 duration = player()->getDuration();
    if(duration > 0)
        pos = int((float)player()->getPosition() * 100 / duration);
    return pos;
}

int GStb::GetPosPercentEx()
{
    STUB();
    CHECK_OR_RETURN(player(), 0);
    int pos = 0;
    qint64 duration = player()->getDuration();
    if(duration > 0)
        pos = int(player()->getPosition() * 10000 / duration);
    DEBUG() << "GetPosPercentEx:" << pos;
    return pos;
}

int GStb::GetPosTime()
{
    STUB();
    CHECK_PLAYER(0)
    int pos = player()->getPosition() / 1000;
    DEBUG() << "position:" << pos;
    return pos;
}

int GStb::GetPosTimeEx()
{
    STUB();
    CHECK_PLAYER(0)
    int pos = player()->getPosition();
    qDebug() << "position:" << pos;
    return pos;
}

QString GStb::GetPppoeIp()
{
    STUB();
    return "";
}

bool GStb::GetPppoeLinkStatus()
{
    STUB();
    return false;
}

int GStb::GetSaturation()
{
    STUB();
    return 0;
}

QString GStb::GetSmbGroups()
{
    STUB();
    QJsonObject result;
    QJsonArray resultArray;
    QString errorMsg;
    QList<SambaNode*> domains = Core::instance()->network()->samba()->domains();

    for(SambaNode* node: domains)
    {
        resultArray.append(node->name);
    }

    result.insert("result", resultArray);
    result.insert("errMsg", errorMsg);
    result.insert("errCode", 0);

    return QJsonDocument(result).toJson(QJsonDocument::Compact);
}

QString GStb::GetSmbServers(const QString &args)
{
    STUB() << args;

    QJsonObject data = QJsonDocument::fromJson(args.toUtf8()).object();

    QJsonObject result;
    QJsonArray resultArray;
    QString errorMsg;

    QList<SambaNode*> hosts = Core::instance()->network()->samba()->hosts(data.value("group").toString());
    for(SambaNode* host: hosts)
        resultArray.append(host->name);

    result.insert("result", resultArray);
    result.insert("errMsg", errorMsg);
    result.insert("errCode", 0);

    QString res = QJsonDocument(result).toJson(QJsonDocument::Compact);
    DEBUG() << res;
    return res;
}

QString GStb::GetSmbShares(const QString &args)
{
    STUB() << args;
    QJsonObject data = QJsonDocument::fromJson(args.toUtf8()).object();

    QJsonObject result;
    QJsonObject resultData;
    QString errorMsg;

    QJsonArray sharesArray;

    QString hostName = data.value("server").toString();
    QList<SambaNode*> shares = Core::instance()->network()->samba()->shares(hostName);


    for(SambaNode* share: shares)
        sharesArray.append(share->name);

    resultData.insert("shares",sharesArray);
    resultData.insert("serverIP", hostName);
    result.insert("result", resultData);
    result.insert("errMsg", errorMsg);
    result.insert("errCode", 0);

    return QJsonDocument(result).toJson(QJsonDocument::Compact);
}

/**
 * @brief GStb::GetSpeed
 * @return
 *
1	normal
2	2x
3	4x
4	8x
5	16x
6	1/2
7	1/4
8	12x
-1	reverse
-2	reverse 2x
-3	reverse 4x
-4	reverse 8x
-5	reverse 16x
-8	reverse 12x
 */
qint32 GStb::GetSpeed()
{
    STUB();
    return 1;
}

/**
 * Get all mount point info
 * @param param
 * @return
result	holds result of operation
errMsg	empty string in case of success or non-localized string that representing error condition otherwise
errCode	0 in case of success or -1 in case of general error
 */
QString GStb::GetStorageInfo(const QString &param)
{
    STUB() << param;

    QJsonObject result;
    QString info = ((MagApiStbObject*)profile()->getProfilePlugin())->getStorageInfo();
    QJsonArray storages( QJsonDocument::fromJson(info.toUtf8()).array());

    result.insert("result", storages);
    result.insert("errCode", 0);
    result.insert("errMsg", "");

    return QString(QJsonDocument(result).toJson(QJsonDocument::Compact));
}

qint16 GStb::GetSubtitlePID()
{
    STUB();
    CHECK_PLAYER(0);
    //return plugin->player()->subtitlePID();
    return 0;
}

QString GStb::GetSubtitlePIDs()
{
    STUB();
    return "[]";
}

QString GStb::GetTeletextPID()
{
    STUB();
    return "";
}

QString GStb::GetTeletextPIDs()
{
    STUB();
    return "[]";
}

qint64 GStb::GetTransparentColor()
{
    STUB();
    return m_page->getChromaKey().rgb();
}

QString GStb::GetVideoInfo()
{
    STUB();
    return "{}";
}

qint32 GStb::GetVolume()
{
    STUB();
    CHECK_PLAYER(0);
    return player()->getVolume();
}

QString GStb::GetWepKey128ByPassPhrase(const QString &passPhrase)
{
    STUB() << passPhrase;
    return "";
}

QString GStb::GetWepKey64ByPassPhrase(const QString &passPhrase)
{
    STUB() << passPhrase;
    return "";
}

QString GStb::GetWifiGroups()
{
    STUB();
    return "";
}

bool GStb::GetWifiLinkStatus()
{
    STUB();
    return Core::instance()->network()->isWifiConnected();
}

qint32 GStb::GetWinAlphaLevel(int winNum)
{
    STUB();
    if(winNum == WINDOW_BROWSER)
        return 255.0 * m_page->getOpacity();
    else if(winNum == WINDOW_BROWSER)
        return 255.0 * player()->getOpacity();
    return 255;
}

void GStb::HideVirtualKeyboard()
{
    STUB();
}

void GStb::HideVirtualKeyboardEx()
{
    STUB();
}

void GStb::IgnoreUpdates(bool ignore)
{
    STUB() << ignore;
}

void GStb::InitPlayer()
{
    STUB();
}

bool GStb::IsFileExist(QString fileName)
{
    STUB() << fileName;

    //Font fix
    //fixme: should be really checked
    if(fileName.startsWith("/usr/lib"))
    {
        return true;
        //fileName = "qrc://" + fileName;
    }
    return QFile(fileName).exists();
}

bool GStb::IsFolderExist(const QString &folderName)
{
    DEBUG() << "IsFolderExist:" <<  folderName;
    return QDir(folderName).exists();
}

bool GStb::IsInternalPortalActive()
{
    STUB();
    return false;
}

bool GStb::IsPlaying()
{
    CHECK_PLAYER(StoppedState);
    bool state = player()->state() == PlayingState;
    LOG() << "IsPlaying(): " << state;
    return state;
}

bool GStb::IsVirtualKeyboardActive()
{
    STUB();
    return false;
}

bool GStb::IsVirtualKeyboardActiveEx()
{
    STUB();
    return false;
}

/**
 * @brief GStb::ListDir
 * @param dir Directory to get files and folders from
 *
 * Method should return string like:
 * @example var dir = ["dir1/","dir2/",""]; var files = [{"name": filename, "size": filesize}, {}];
 *
 * For some reasons MAG requires to add empty values to the end of these lists (i.e. "" for dirs and {} for files).
 *
 * Directory usually starts with /media/ (root dir) and if it's equals root dir this method should return (possibly without spaces):
 * var dir = [
 *      "SAMBA/",
 *      "UPnP",
 *      "USB-<SN>-<INDEX>",
 *      ""
 * ]; var files = [{}];
 * where <SN> ia a drive serial number and <INDEX> is a drive index starting from 1 (for each drive should be one row),
 * as it returned by RDir("get_storage_info").
 *
 * \see @RDir
 * @return
 */
QString GStb::ListDir(const QString &dir)
{
    //TODO: Add UPnP, LAN & Favourites support

    QString directoryPath;

    if(dir.startsWith("/ram/"))
    {
        directoryPath = QString("/tmp/yasem").append(dir);
    }
    else
    {
        directoryPath = dir;
    }

    STUB() << directoryPath;

    QJsonArray files;
    QJsonArray dirs;
    QString result;

    // for some reasons Stalker in some cases puts two slashes in path instead of one (as it possibly should).
    QRegularExpression rootMatch("^(/){1,2}media(/){1,2}$");
    QRegularExpression diskRegex("[/{0,2}]USB-\\d+-(\\d+)");
    QRegularExpressionMatch diskRegexMatch = diskRegex.match(directoryPath);
    QList<StorageInfo*> disks = Core::instance()->storages();

    // root dir
    if(rootMatch.match(directoryPath).hasMatch())
    {
        qDebug() << "match root";
        dirs.append(QString("SAMBA/"));
        dirs.append(QString("UPnP/"));

        for(int index = 1; index <= disks.length(); index++)
        {
            dirs.append(QString("USB-00000000%1-%2/").arg(index).arg(index));
        }
    }
    // USB-X-Y dir (actually, it should be HDD)
    else
    {
        QString newPath = translateStbPathToLocal(directoryPath);
        if(!newPath.isEmpty())
        {
            return listLocalFiles(newPath);
        }
        else
        {
            STUB();
        }
    }


    dirs.append(QString(""));
    files.append(QJsonValue::fromVariant(QJsonDocument(QJsonObject()).toVariant()));

    DEBUG() << result;
    return QString("var dirs = %1; var files = %2;").arg(QString(QJsonDocument(dirs).toJson(QJsonDocument::Compact))).arg(QString(QJsonDocument(files).toJson(QJsonDocument::Compact)));
}

QString GStb::translateStbPathToLocal(const QString& path)
{
    STUB() << path;
    QRegularExpression diskRegex("[/{0,2}]USB-\\d+-(\\d+)(/)?");
    QRegularExpressionMatch diskRegexMatch = diskRegex.match(path);
    QList<StorageInfo*> disks = Core::instance()->storages();

    QString newPath = path;

    if(diskRegexMatch.hasMatch())
    {
        qDebug() << "match disk";
        int diskIndex = diskRegexMatch.captured(1).toInt() - 1; // Disk index starts from 1
        QString mountPoint = disks.at(diskIndex)->mountPoint;
        if(!mountPoint.endsWith("/"))
            mountPoint = mountPoint.append("/");

        newPath = newPath.replace(diskRegex, mountPoint);
    }

    qDebug() << "New path is " << newPath;
    return newPath;
}

MagProfile *GStb::profile()
{
    return m_profile;
}

void GStb::LoadCASIniFile(const QString &iniFileName)
{
    STUB() << iniFileName;
}

void GStb::LoadExternalSubtitles(const QString &url)
{
    STUB() << url;
}

void GStb::LoadURL(const QString &str)
{
    STUB() << str;
}

/**
 * Load file from mnt/Userfs/data
 * @param {String} strVal file name
 * @returns {String} file content
 */
QString GStb::LoadUserData(const QString &str)
{
    QString data = profile()->datasource()->get(DB_TAG_USER, str);
    DEBUG() << str << data;
    return data;
}

void GStb::Pause()
{
    CHECK_PLAYER_VOID;
    player()->mediaPause();
}

/**
 * @brief GStb::Play
 * @param playStr
    format: solution URL [position:pnum] [atrack:anum] [vtrack:vnum] [strack:snum] [subURL:subtitleUrl]
    Option	Description
    solution	Media content type. Depends on the IPTV-device type (see Appendix 2 for the table of supported formats and the description of media content types).
    URL	Address of the content to be started for playing. Depends on the type (see more detailed information in Appendix 2).
    atrack:anum	Sets the number(PID) of audio track (optional parameter).
    vtrack:vnum	Sets the number(PID) of audio track (optional parameter).
    strack:snum	Sets the number(PID) of subtitle track (optional parameter).
    subURL:subtitleURL	Sets the URL of external subtitles file. See gSTB.LoadExternalSubtitles (optional parameter).
 * @param proxyParams
    format: http://[username[:password]@]proxy_addr:proxy_port
    Proxy server settings are affect only HTTP playback and valid till the next call of gSTB.Play.
 */
void GStb::Play(const QString &playStr, const QString &proxyParams)
{
    DEBUG() << "GStb::Play" << playStr << proxyParams;
    CHECK_PLAYER_VOID

    QString urlString = playStr.trimmed();

    QRegularExpression urlRegex("^((?<proto>auto|rtp|rtsp_ac3|rtsp|rtpac3|rtpmpeg4_aac|ptpmpeg4|mpegts|mpegps|file|mp4_mpa|mp4|fm|ffmpeg|ffrt4|ffrt3|ffrt2|ffrt)\\s+)?\
(?<url>.*?)$");
    QRegularExpressionMatch urlMatch = urlRegex.match(urlString);


    if(!urlMatch.hasMatch())
    {
        qDebug() << "Unknown URL type!";
        return;
    }

    QString protocol = !urlMatch.captured("proto").isEmpty() ? urlMatch.captured("proto"): "auto";
    QString url = urlMatch.captured("url");

    qDebug() << "matched proto:" << protocol << ", url:" << url;


    if(url.startsWith("//"))
    {
        url = url.replace("//", "/");

        url = translateStbPathToLocal(url);
    }

    //Transform multicast address
    if((url.startsWith("udp://") || url.startsWith("rtp://")))
    {
        bool use_multicast = profile()->isUsingMulticastProxy();
        DEBUG() << "use_multicast" << use_multicast;
        if(use_multicast)
        {
            QStringList url_data = url.split("://");
            if(url_data.size() == 2)
            {
                QString proto = url_data.at(0);
                QString tmp_url = url_data.at(1);
                if(tmp_url.startsWith("@"))
                        tmp_url = tmp_url.right(tmp_url.length() - 1);

                QString proxy_url = profile()->getMulticastProxy();
                url = proxy_url.append("/").append(proto).append("/").append(tmp_url);
            }
            else
                WARN() << "Incorrect multicast url" << url_data;
        }

    }


    player()->mediaPlay(url);
}

/**
 * @brief GStb::PlaySolution
 * @param solution corresponds to the parameter solution from the function gSTB.Play
 * @param url
    address of the content to be started for playing
    depends on the type
 */
void GStb::PlaySolution(const QString &solution, const QString &url)
{
    STUB() << solution << url;
}

QString GStb::RDir(const QString &name)
{
    Q_ASSERT(profile()->datasource());

    if(name == "SerialNumber")
    {
        return GetDeviceSerialNumber();
    }
    if(name == "MACAddress")
    {
        return GetDeviceMacAddress();
    }
    if(name == "IPAddress")
    {
        return datasource()->get(DB_TAG_RDIR, "IPAddress", "192.168.0.100");
    }
    if(name == "WiFi_ip")
    {
        //TODO: Should get Wi-Fi MAC
        return datasource()->get(DB_TAG_RDIR, "IPAddress", "192.168.0.100");
    }
    if(name == "HardwareVersion")
    {
        return GetDeviceVersionHardware();
    }
    if(name == "Vendor")
    {
        return GetDeviceVendor();
    }
    if(name == "Model")
    {
        return GetDeviceModel();
    }
    if(name == "ImageVersion")
    {
        return GetDeviceImageVersion();
    }
    if(name == "ImageDescription")
    {
        return GetDeviceImageDesc();
    }
    if(name == "ImageDate")
    {
        return datasource()->get(DB_TAG_RDIR, "ImageDate", "Fri Oct 25 17:28:41 EEST 2013");
    }
    if(name == "get_storage_info")
    {
        return ((MagApiStbObject*)profile()->getProfilePlugin())->getStorageInfo();
    }
    if(name.startsWith("ResolveIP"))
    {
        QStringList data = name.split(" ");
        if(data.length() == 2)
        {
            QHostInfo info = QHostInfo::fromName(data.at(1));
            return info.addresses().isEmpty()? "": info.addresses().first().toString();
        }
        return "";
    }
    if(name.startsWith("SHA1"))
    {
        QStringList data = name.split(" ");
        if(data.length() == 2)
        {
            return QCryptographicHash::hash(data.at(1).toUtf8(), QCryptographicHash::Sha1);
        }
        return "";
    }

    QString result;
    if(name.startsWith("getenv ") || name.startsWith("setenv "))
    {
       QStringList params = name.split(" ");
       if(params.at(0) == "getenv")
            result = datasource()->get(DB_TAG_ENV, params[1]);
       else if(params.at(0) == "setenv")
           result = QVariant(datasource()->set(DB_TAG_ENV, params.at(1), params.at(2))).toString();
    }
    else if(name.startsWith("tempfile"))
    {
        QStringList params = name.split(" ");

        if(params.length() != 3)
           qWarning() << "Wrong length:", params.length();
        else
        {
            if(params[1] == "read")
            {
                QString fileName = QString(":/mag/files/").append(params[2]);
                QFile file(fileName);
                file.open(QIODevice::ReadOnly|QIODevice::Text);
                result = file.readAll();
            }
        }
    }
    else if(name == "get_hdd_info")
    {
        result = ((MagApiStbObject*)profile()->getProfilePlugin())->getStorageInfo();
    }
    else if(name.startsWith("mount"))
    {
        //mount cifs //IRONMAN/IPC$ /ram/mnt/smb username=guest,password=,iocharset=utf8

        QStringList data = name.split(" ");
        if(data.length() == 5)
        {
            QString path = data.at(2);
            path = path.replace("\\", "/");
            QString mount_point = QString("/tmp/yasem").append(data.at(3));
            QString params;
            result = QVariant(Core::instance()->network()->samba()->mount(path, mount_point, params)).toString();
        }
    }
    else
    {
        result = profile()->datasource()->get(DB_TAG_RDIR, name);
    }

    DEBUG() << "RDir:" << QString("[\"%1\"] -> \"%2\"").arg(name, result);
    return result;
}

QString GStb::ReadCFG()
{
    STUB();
    return "";
}

void GStb::ResetUserFs()
{
    STUB();
}

void GStb::Rotate(qint16 angle)
{
    STUB() << angle;
}

void GStb::SaveUserData(const QString &fileName, const QString &data)
{
    DEBUG() << "SaveUserData:" << fileName << data;
    datasource()->set(DB_TAG_USER, fileName, data);
}

void GStb::SendEventToPortal(const QString &args)
{
    STUB() << args;
}

void GStb::ServiceControl(const QString &serviceName, const QString &action)
{
    STUB() << serviceName << action;
}

void GStb::Set3DConversionMode(int mode)
{
    STUB() << mode;
}

void GStb::SetAdditionalCasParam(const QString &name, const QString &value)
{
    STUB() << name << value;
}

void GStb::SetAlphaLevel(qint32 alpha)
{
    STUB() << alpha;
}

/**
 * @brief GStb::SetAspect
 * @param aspect
    0	as it is (video is stretched for the whole screen)
    1	Letter box mode (video is proportionally enlarged to the size of the screen along the larger edge)
    2	Pan&Scan mode (video is proportionally enlarged to the screen size along the lesser edge)
    3	combined mode (intermediate between Letter Box Box and Pan&Scan)
    4	enlarged mode
    5	optimal mode
 */
void GStb::SetAspect(int aspect)
{
    STUB() << aspect;
    CHECK_PLAYER_VOID;

    AspectRatio ratio;
    switch(aspect)
    {
        case 0: {
            ratio = ASPECT_RATIO_16_9 /*ASPECT_RATIO_AUTO*/ ; break;
        }
        case 1: {
            ratio = ASPECT_RATIO_20_9; break;
        }
        case 2: {
            ratio = ASPECT_RATIO_16_9; break;
        }
        case 3: {
            ratio = ASPECT_RATIO_4_3; break;
        }
        default: {
            ratio = ASPECT_RATIO_16_9; break;
        }
    }

    player()->setAspectRatio(ratio);
}

void GStb::SetAudioLangs(const QString &priLang, const QString &secLang)
{
    STUB() << priLang << secLang;
}

void GStb::SetAudioOperationalMode(int mode)
{
    STUB() << mode;
}

void GStb::SetAudioPID(int pid)
{
    DEBUG() << "SetAudioPID:" << pid;
    CHECK_PLAYER_VOID
    player()->setAudioPID(pid);
}

void GStb::SetAutoFrameRate(int mode)
{
    STUB() << mode;
}

void GStb::SetBrightness(qint32 bri)
{
    STUB() << bri;
}

void GStb::SetBufferSize(qint32 sizeInMs, qint32 maxSizeInBytes)
{
    STUB() << sizeInMs << maxSizeInBytes;
}

void GStb::SetCASDescrambling(int isSoftware)
{
    STUB() << isSoftware;
}

void GStb::SetCASParam(const QString &serverAddr, qint32 port, const QString &companyName, qint32 opID, qint32 errorLevel)
{
    STUB() << serverAddr << port << companyName << opID <<  errorLevel;
}

void GStb::SetCASType(qint32 type)
{
    STUB() << type;
}

void GStb::SetCheckSSLCertificate(int val)
{
    STUB() << val;
}

void GStb::SetChromaKey(qint64 key, qint64 mask)
{
    STUB() << key << mask;
    QColor chromakey = QColor::fromRgb(key);
    chromakey.setAlpha(0);
    m_page->setChromaKey(chromakey);
    m_page->setChromaMask(QColor::fromRgb(mask));
}

void GStb::SetComponentMode(int mode)
{
    STUB() << mode;
}

void GStb::SetContrast(qint16 contrast)
{
    STUB() << contrast;
}

void GStb::SetCustomHeader(const QString &header)
{
    STUB() << header;
}

void GStb::SetDefaultFlicker(int state)
{
    STUB() << state;
}

void GStb::SetDRC(int high, int low)
{
    STUB() << high << low;
}

/**
 * Setting up values of specified boot loader’s variables.
 * @param args Each pair's name is referencing name of variable. And pair value will be used as new value of variable.
 * If referencing variable does not exist it will be created. If new value is empty string then value will be deleted.<br/>
 *   Format: JSON object, which holding only pairs. Each pair has string value. Each pair name is referencing variable name. And pair value will set new value.<br/>
 *   Example: {"a34":"b34", "c34":"", "c34":"d34"}
 * @return Result of operation
 */
bool GStb::SetEnv(const QString &data, const QString &value)
{
    if(!profile()->datasource())
        return false;

    LOG() << QString("SetEnv(%1 = %2)").arg(data).arg(value);
    bool result = true;
    if(value == 0)
    {
        QJsonObject obj = QJsonDocument::fromJson(QByteArray(data.toUtf8())).object();
        foreach(QString key, obj.keys())
        {
            result = result && profile()->datasource()->set(DB_TAG_ENV, key, obj.take(key).toString());
        }
    }
    else
    {
        result = profile()->datasource()->set(DB_TAG_ENV, data, value);
    }

    return result;
}

void GStb::SetFlicker(int state, int flk, int shp)
{
    STUB() << state << flk << shp;
}

void GStb::SetHDMIAudioOut(int type)
{
    STUB() << type;
}

void GStb::SetInternalPortalActive(bool active)
{
    STUB() << active;
}

void GStb::SetListFilesExt(const QString &exts)
{
    STUB() << exts;
    listFileExt = exts.split(" ");
}

void GStb::SetLoop(int loop)
{
    DEBUG() << "SetLoop:" << loop;
    CHECK_PLAYER_VOID
    player()->setLoop(loop);
}

void GStb::SetMicVolume(int volume)
{
    STUB() << volume;
}

/**
 * Switch on (mode=1) or switch off (mode=0) the mode ChromaKey for the video window.
 * @param mode ChromaKey mode for the video window: 0 – off; 1 – on.
 * The parameters set by stb.SetChromaKey {@link #SetTransparentColor} shall be valid if the on-mode is used.
 */
int GStb::SetMode(int mode)
{
    STUB() << mode;
    // API says it should be a video window, not browser. It's possible a mistake
    m_page->setChromaKeyEnabled(mode == 1);
    return 0;
}

int GStb::SetMulticastProxyURL(const QString &val)
{
    STUB() << val;
    return 0;
}

void GStb::SetMute(int mute)
{
    STUB() << mute;
    CHECK_PLAYER_VOID
    player()->setMute(mute == 1);
}

/**
 * @brief GStb::SetObjectCacheCapacities
 * Test only!
 * @param cacheMinDeadCapacity
 * @param cacheMaxDead
 * @param totalCapacity
*/
void GStb::SetObjectCacheCapacities(int cacheMinDeadCapacity, int cacheMaxDead, int totalCapacity)
{
    STUB() << cacheMinDeadCapacity << cacheMaxDead << totalCapacity;
}

void GStb::SetPCRModeEnabled(bool enable)
{
    STUB() << enable;
}

/**
 * Sets position and mode of video window
 * @param state If state=1 show the video on full screen. If state=0 show the video in the specified rectangle.
 * @param scale The scale of the video window. The present multiplier of the video window size equals to scale/256.
 * @param x Horizontal offset of the upper left corner of the video window from the screen edge.
 * @param y Vertical offset of the upper left corner of the video window from the screen edge.
 */
void GStb::SetPIG(int state, float scale, int x, int y)
{
    STUB() << state << scale << x << y;

    CHECK_PLAYER_VOID

    if(state == 1)
    {
        player()->setFullscreen(true);
    }
    else
    {
        player()->setFullscreen(false);
        if(x >= 0 && y >= 0)
            player()->move(x, y);
    }
    player()->resize();
}

void GStb::SetPixmapCacheSize(int sizeKb)
{
    STUB() << sizeKb;
}

void GStb::SetPosPercent(int prc)
{
    STUB() << prc;
}

void GStb::SetPosPercentEx(int prc)
{
    STUB() << prc;
}

void GStb::SetPosTime(int time)
{
    STUB() << time;
    CHECK_PLAYER_VOID;
    player()->setPosition(time * 1000);
}

void GStb::SetPosTimeEx(int time)
{
    STUB() << time;
}

void GStb::SetSaturation(int sat)
{
    STUB() << sat;
}

void GStb::SetSpeed(int speed)
{
    STUB() << speed;
}

void GStb::SetStereoMode(int mode)
{
    STUB() << mode;
}

void GStb::SetSubtitleLangs(const QString &priLang, const QString &secLang)
{
    STUB() << priLang << secLang;
}

void GStb::SetSubtitlePID(int pid)
{
    STUB() << pid;
}

void GStb::SetSubtitles(bool enable)
{
    STUB() << enable;
}

void GStb::SetSubtitlesColor(int val)
{
    STUB() << val;
}

void GStb::SetSubtitlesEncoding(const QString &encoding)
{
    STUB() << encoding;
}

void GStb::SetSubtitlesFont(const QString &font)
{
    STUB() << font;
}

void GStb::SetSubtitlesOffs(int offset)
{
    STUB() << offset;
}

void GStb::SetSubtitlesSize(int size)
{
    STUB() << size;
}

void GStb::SetSyncCorrection(int val1, int val2)
{
    STUB() << val1 << val2;
}

void GStb::SetSyncOffsetCorrection(int val)
{
    STUB() << val;
}

void GStb::SetTeletext(bool val)
{
    STUB() << val;
}

void GStb::SetTeletextPID(unsigned int val)
{
    STUB() << val;
}


//TODO: Move top widget switching to a new manager class
/**
 * Sets the preset window over others
 * @param winNum number of the window for which this function is used: 0 - graphic window; 1 - video window
 */
void GStb::SetTopWin(int winNum)
{
    STUB() << "GStb::SetTopWin" << winNum;
    CHECK_PLAYER_VOID
    if(winNum == WINDOW_BROWSER)
    {
        browser()->setTopWidget(BrowserPluginObject::TOP_WIDGET_BROWSER);
    }
    else
    {
        browser()->setTopWidget(BrowserPluginObject::TOP_WIDGET_PLAYER);
    }
}

void GStb::SetTransparentColor(int color)
{
    STUB() << color;
    QColor chromakey = QColor::fromRgb(color);
    chromakey.setAlpha(0);
    m_page->setChromaKey(chromakey);
}

void GStb::SetupRTSP(int type, int flags)
{
    STUB() << type << flags;
}

void GStb::SetupSPdif(int flags)
{
    STUB() << flags;
}

void GStb::SetUserFlickerControl(int mode)
{
    STUB() << mode;
}

void GStb::SetVideoControl(int mode)
{
    STUB() << mode;
}

void GStb::SetVideoState(int state)
{
    STUB() << state;
}

/**
* Set the location and size of the video window.
* Parameters xsize and ysize depends on the screen resolution.
* @param xsize Horizontal size of the video window (width).
* @param ysize Vertical size of the video window (height).
* @param x Left upper corner of the video window horizontal offset from the screen edge. Must not exceed the screen width in sum with xsize.
* @param y Left upper cornet of the video window vertical offset from the screen edge. Must not exceed the screen width in sum with ysize.
*/
void GStb::SetViewport(int xsize, int ysize, int x, int y)
{
    DEBUG() << "GStb::SetViewport" << xsize << ysize << x << y;
    CHECK_PLAYER_VOID

    player()->setFullscreen(false);
    player()->setViewport(QRect(x, y, xsize, ysize));
}

/**
 * @brief GStb::SetViewportEx
    Set video plane position and size in pixels and clipping rectangle for input video. More flexible version of gSTB.SetViewport.
    Clip rectangle specifies which sub-rectangle will be shown in specified video window rectangle (stretched to fill whole video window). If clip_xsize==0 or clip_ysize==0 then clip will be ignored.
    If clip rectangle is ignored or has size equal to encoded video size then aspect ratio conversion will be performed inside specified video window rectangle according to the current aspect for fullscreen mode. This does not depend on specified video window size. At the same time gSTB.SetViewport function does aspect ratio conversion only in fullscreen mode.
    Clip rectangle size and position should be in pixels of the encoded video. Width and height of encoded video can be retrieved via gSTB.GetVideoInfo. See pictureWidth and pictureHeight.
 *
 * @param xSize horizontal size of the video window (width)
 * @param ySize vertical size of the video window (height)
 * @param xPos left upper corner of the video window horizontal offset from the screen edge must not exceed the screen width in sum with xSize
 * @param yPos left upper cornet of the video window vertical offset from the screen edge must not exceed the screen width in sum with ySize
 * @param clipXSize clip rectangle horizontal size
 * @param clipYSize clip rectangle vertical size
 * @param clipXPos clip rectangle horizontal offset related to encoded video
 * @param clipYPos clip rectangle vertical offset related to encoded video
 * @param saveClip whether player should save clip region over the sequential playbacks:
    true	use this clip only for current playback
    false	use this clip till next call of STB_SetViewportEx, STB_SetViewport, STB_SetPIG
 */
void GStb::SetViewportEx(int xSize, int ySize, int xPos, int yPos, int clipXSize, int clipYSize, int clipXPos, int clipYPos, bool saveClip)
{
    STUB() << xSize << ySize << xPos << yPos << clipXSize << clipYSize << clipXPos << clipYPos << saveClip;
}

void GStb::SetVolume(int volume)
{
    DEBUG() << "SetVolume:" << volume;
    CHECK_PLAYER_VOID
    player()->setVolume(volume);
}

void GStb::SetWebMode(bool val, const QString &str)
{
    STUB() << val << str;
}

void GStb::SetWebProxy(const QString &host, int port, const QString &user, const QString &password, const QString &exclude)
{
    STUB() << host << port << user << password << exclude;
}

void GStb::SetWinAlphaLevel(int winNum, int alpha)
{
    STUB() << winNum <<alpha;
    CHECK_PLAYER_VOID
    if(winNum == WINDOW_BROWSER)
        m_page->setOpacity((float)alpha / 255.0);
    else if(winNum == WINDOW_VIDEO)
        player()->setOpacity((float)alpha / 255.0);
}

void GStb::SetWinMode(int winNum, int mode)
{
    STUB() << winNum << mode;
    if(winNum == WINDOW_BROWSER)
    {
        m_page->setChromaKeyEnabled(mode == 1);
    }
}

void GStb::ShowSubtitle(int start, int end, const QString &text)
{
     STUB() << start << end << text;
}

void GStb::ShowVideoImmediately(bool val)
{
     STUB() << val;
}

void GStb::ShowVirtualKeyboard()
{
    ShowVirtualKeyboard(true);
}

void GStb::ShowVirtualKeyboard(bool show)
{
    STUB() << show;
}

void GStb::StandBy(bool standBy)
{
    STUB() << "GStb::StartLocalCfg" << standBy;
}

void GStb::StartLocalCfg()
{
    STUB() << "GStb::StartLocalCfg";
    if(!m_system_settings.url.isEmpty())
        m_page->openWindow(translateStbPathToLocal(m_system_settings.url), "", "LocalCfg");
}

void GStb::Step()
{
    STUB();
}

void GStb::Stop()
{
    DEBUG() << "GStb::Stop";
    CHECK_PLAYER_VOID
    player()->mediaStop();
}

/**
 * Receive API version
 * @return The string in the form of:
 * "JS API version: <JS_API version>; STB API version: <STB_API version>; Player Engine version: <Player version>"
 *   <p>JS_API version – this API version number</p>
 *   <p>STB_API version – player API version</p>
 *   <p>Player version – version of the player used in API in HEX code form</p>
 * @example
 *   JS API version: 301; STB API version: 104; Player Engine version: 0x23
 */
QString GStb::Version()
{
    STUB();
    return "";
}

/**
 * Write the file of portal settings /etc/stb_params.
 * It must be kept in mind that the values PORTAL_IP, PORTAL_1, PORTAL_2 are used in the starting portal stored in /home/web of the root file system,
 * therefore it is desirable to receive source values of these parameters via gSTB.ReadCFG before making the call and add them to the string cfg.
 * @param {String} Cfg The data to be stored in the file
 */
void GStb::WriteCFG(const QString &cfg)
{
    STUB() << cfg;
}

/**
 * Save the string as the browser set up (prefs.js).
 * This function is not browser specific and it is used to set the right of access to the portal.
 * This is performed in starting portal saved at /home/web of the root file system and it is recommended to avoid using it anywhere else.
 * @param {String} prefs Data to be saved in the file of browser settings
 */
void GStb::WritePrefs(const QString &prefs)
{
    STUB() << prefs;
}

/**
*
* FIXME: Possibly this method is incorrect. Should be another hashing method.
*
* Hashes the given string using the HMAC-SHA1 algorithm.
*
* \param key The string to be hashed
* \param secret The string that contains secret word
* \return The hashed string
*
* @see http://mahonen.tumblr.com/post/8637914737/hmac-hash-for-qt
*/
QString GStb::GetHashVersion1(QString secret, QString key)
{
    STUB() << secret << key;

   //Length of the text, that will be hashed
   //int   text_length;

   //For secret word.
   QByteArray K;
   //Lenght of secret word
   int   K_lenght;

   K_lenght = secret.size();
   //text_length = key.size();

   //Need to do for XOR operation. Transforms QString to
   //unsigned char
   K = secret.toLatin1();

   //Inner padding
   QByteArray ipad;
   //Outer pad
   QByteArray opad;

   //if secret key > 64 bytes use this to obtain sha1 key
   if(K_lenght > 64)
   {
      QByteArray tempSecret;
      tempSecret.append(secret);
      K = QCryptographicHash::hash(tempSecret,QCryptographicHash::Sha1);
      K_lenght = 20;
   }

   //Fills ipad and opad with zeros
   //bzero( ipad, sizeof ipad);
   //bzero( opad, sizeof opad);

   ipad.fill( 0, 64);
   opad.fill(0, 64);

   //Copies Secret to ipad and opad
   //bcopy( K, ipad, K_lenght);
   //bcopy( K, opad, K_lenght);

   ipad.replace(0, K_lenght, K);
   opad.replace(0, K_lenght, K);

   //XOR operation for inner and outer pad
   for (int i=0; i<64; i++)
   {
      ipad[i] = ipad[i] ^ 0x36;
      opad[i] = opad[i] ^ 0x5c;
   }

   //Stores hashed content
   QByteArray context;

   //Appends XOR:ed ipad to context
   context.append(ipad,64);
   //Appends key to context
   context.append(key);

   //Hashes Inner pad
   QByteArray Sha1   = QCryptographicHash::hash(context, QCryptographicHash::Sha1);

   context.clear();
   //Appends opad to context
   context.append(opad,64);
   //Appends hashed inner pad to context
   context.append(Sha1);

   Sha1.clear();

   // Hashes outerpad
   Sha1 = QCryptographicHash::hash(context, QCryptographicHash::Sha1);

   // String to return hashed stuff in Base64 format
   QByteArray str(Sha1.toBase64());

   return str;
}

void GStb::EnableTvButton(bool enable)
{
    STUB() << enable;
}

/**
 * True to apply new native string handling without utf8/utf16 encoding/decoding
 * @param {Boolean} boolVal true - all string manipulations are with utf16 strings
 */
void GStb::SetNativeStringMode(bool native)
{
    STUB() << native;
}

void GStb::SetScreenSaverTime(int time)
{
   STUB() << time;
}

/**
 * Set new input language
 * @param langId Language id to be set as input language
 */
void GStb::SetInputLang(const QString &lang)
{
    STUB() << lang;
}

/**
 * Get current input language
 */
QString GStb::GetInputLang()
{
    STUB();
    return "en";
}

QString GStb::GetDefaultUpdateUrl()
{
    STUB();
    return "";
}

/**
 * Set the user interface language
 * @param {String} langId Attention! This function also causes SetInputLang()
 */
void GStb::SetUiLang(const QString &lang)
{
    STUB() << lang;
}

/**
 * Set system settings init parameters
 * @param options parameters from windowInit function
 */
void GStb::SetSettingsInitAttr(const QString &options)
{
    STUB() << options;
    QJsonObject obj = QJsonDocument::fromJson(options.toUtf8()).object();
    if(obj.isEmpty())
    {
        WARN() << "Emptry JSON";
        return;
    }

    if(obj.keys().contains("url") && obj.keys().contains("backgroundColor"))
    {
        m_system_settings.url = obj.value("url").toString();
        m_system_settings.backgroundColor = obj.value("backgroundColor").toString();
    }
    else
        WARN() << "Incorrect data";
}

/**
 * Set screensaver window init parameters
 * @param options parameters from windowInit function
 */
void GStb::SetScreenSaverInitAttr(const QString &options)
{
    STUB() << options;
}

void GStb::ClearStatistics()
{
    STUB();
}

/**
 * @brief GStb::GetHDMIConnectionState
 * @return
    0	HDMI disconnected from TV.
    1	HDMI connected to TV, but not in active state e.i. standby mode, TV is off
    2	HDMI connected to TV in active state.
 */
int GStb::GetHDMIConnectionState()
{
    STUB() << 2;
    return 2;
}

/**
 * @brief GStb::GetHLSInfo
 * @return
    currentVariant	the number of currently active variant in variants array
    variants	a list of bitrates for all variants and can be empty (available only for Apple HLS streams)
*/
QString GStb::GetHLSInfo()
{
    STUB();
    QJsonObject result;
    result.insert("currentVariant", 0);
    result.insert("variants", QJsonArray());
    return QString(QJsonDocument(result).toJson(QJsonDocument::Compact));
}

/**
 * @brief GStb::SetLedIndicatorMode
 * @param mode
    0	off
    1	normal
    2	standby
*/
void GStb::SetLedIndicatorMode(int mode)
{
    STUB() << mode;
}

/**
 * @brief GStb::SetLedIndicatorLevels
 * @param baseLevel
 * @param blinkLevel
 */
void GStb::SetLedIndicatorLevels(int baseLevel, int blinkLevel)
{
    STUB() << baseLevel << blinkLevel;
}

/**
 * @brief GStb::GetLedIndicatorState
 * @return
    mode	current mode
    levelBase	base LED level
    levelBlink	level for blinking
 */
QString GStb::GetLedIndicatorState()
{
    QJsonObject result;
    result.insert("mode", 0);
    result.insert("levelBase", 0);
    result.insert("levelBlink", 0);
    return QString(QJsonDocument(result).toJson(QJsonDocument::Compact));
}

/**
 * @brief GStb::GetStandByStatus
 * Get the current working mode.
 * @return
    true - in standby mode
 */
bool GStb::GetStandByStatus()
{
    return false;
}

/**
 * @brief GStb::GetStatistics
 * @return
    CCErrorCnt	continuity counter error count
    RTPErrorCnt	RTP error count
    VideoDecodingErrorCnt	video decoding error count
*/
QString GStb::GetStatistics()
{
    STUB();
    QJsonObject result;
    result.insert("CCErrorCnt", 0);
    result.insert("RTPErrorCnt", 0);
    result.insert("VideoDecodingErrorCnt", 0);
    return QString(QJsonDocument(result).toJson(QJsonDocument::Compact));
}

/**
 * @brief GStb::GetTopWin
 * number of window which is in top position now
 * @return
    0	graphic window
    1	video window
 */
int GStb::GetTopWin()
{
    STUB();
    BrowserPluginObject::TopWidget top = browser()->getTopWidget();
    if(top == BrowserPluginObject::TOP_WIDGET_BROWSER)
        return 0;
    else
        return 1;
}

/**
 * @brief GStb::GetWifiLinkStatusEx
 * Return attributes for current WiFi connection if available.
 * @return
 */
QString GStb::GetWifiLinkStatusEx()
{
    STUB();
    QJsonObject result;
    result.insert("Bit Rate", 0); // in Mb/s
    result.insert("Frequency", 0.000000000000000); // in GHz
    result.insert("Noise level", 0);
    result.insert("Signal level", 0);
    return QString(QJsonDocument(result).toJson(QJsonDocument::Compact));
}

bool GStb::IsFileUTF8Encoded(const QString &fileName)
{
    STUB() << fileName;
    return true;
}

void GStb::ResetWebProxy()
{
    STUB();
}

/**
 * @brief GStb::SetSyslogLevel
 * Setup logging level via JS API.
    This function just enables logging to syslog but does not start/configure syslogd.
    syslogd should be configured (if needed) by operator who creates custom software images.
 * @param level logging level which should be OR-ed value of the following levels
    0	quiet level, logging disabled (default)
    1	error level, e.i. "RTP counter error", "TS Continuity Counter error", "Video decoding error"
    2	warning level
    4	info level, e.i. "Starting playback", "External subtitles opening error", "Content opening error", "End of Stream"
    8	debug level, e.i.: gSTB.Debug from JS API do not filter frequent error events.
    By default logging is set to quiet mode.
 */
void GStb::SetSyslogLevel(int level)
{
    STUB() << level;
}

void GStb::ConfigNetRc(const QString &deviceName, const QString &password)
{
    STUB() << deviceName << password;
#ifdef CONFIG_QCA
    profile()->getRemoteControl()->setParams(deviceName, password);
#else
    WARN() << "QCA library is missing. Remote control features disabled!";
#endif //CONFIG_QCA

}

void GStb::SetNetRcStatus(bool enable)
{
    STUB() << enable;
#ifdef CONFIG_QCA
    if(enable)
        profile()->getRemoteControl()->start();
    else
        profile()->getRemoteControl()->stop();
#else
    WARN() << "QCA library is missing. Remote control features disabled!";
#endif //CONFIG_QCA
}

