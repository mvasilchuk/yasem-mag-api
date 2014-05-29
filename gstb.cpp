#include "gstb.h"
#include "stbplugin.h"
#include "datasourceplugin.h"
#include "browserplugin.h"
#include "mediaplayerplugin.h"
#include "guiplugin.h"
#include "enums.h"
#include "mag_macros.h"
#include "core.h"
#include "stbplugin.h"
#include "magapi.h"
#include "datasource.h"
#include "magprofile.h"
#include "stbevent.h"
#include "mediaplayerplugin.h"
#include "NetworkThread.h"

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

using namespace yasem;

GStb::GStb(MagProfile *profile)
{
    //qDebug() << "logger: " << parent->getLogger();
    this->setObjectName("gSTB");

    this->profile = profile;
}

QString GStb::listLocalFiles(const QString &dir)
{
    QDir* directory = new QDir(dir);
    QJsonArray files;
    QJsonArray dirs;

    DEBUG(directory->absolutePath());
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
                //INFO(QString("Skipping file ").append(file.fileName()));
                continue;
            }

            QJsonObject obj;
            obj.insert("name", file.fileName() );
            obj.insert("size", file.size());
            files.append(QJsonValue::fromVariant(QJsonDocument(obj).toVariant()));
        }
    }

    dirs.append(QString(""));
    files.append(QJsonValue::fromVariant(QJsonDocument(QJsonObject()).toVariant()));

    QString result =  QString("var dirs = %1; var files = %2;").arg(QString(QJsonDocument(dirs).toJson(QJsonDocument::Compact))).arg(QString(QJsonDocument(files).toJson(QJsonDocument::Compact)));
    //DEBUG(result);
    return result;
}

MediaPlayerPlugin *GStb::player()
{
    return profile->getProfilePlugin()->player();
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
    STUB();
}

void GStb::Debug(const QString &str)
{
    STUB_WITH_PARAMS(str);
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
    STUB_WITH_PARAMS(enable);
}

void GStb::EnableCustomNavigation(bool enable)
{
    STUB_WITH_PARAMS(enable);
}

void GStb::EnableJavaScriptInterrupt(bool enable)
{
    STUB_WITH_PARAMS(enable);
}

void GStb::EnableMulticastProxy(bool enable)
{
    STUB_WITH_PARAMS(enable);
}

void GStb::EnableServiceButton(bool enable)
{
    STUB_WITH_PARAMS(enable);
}

void GStb::EnableSetCookieFrom(const QString &domain, bool enable)
{
    STUB_WITH_LIST(QStringList() << domain << QVariant::fromValue(enable).toString());
}

void GStb::EnableSpatialNavigation(bool enable)
{
    STUB_WITH_PARAMS(QString("EnableSpatialNavigation(%1)").arg(enable));
}

void GStb::EnableVKButton(bool enable)
{
    STUB_WITH_PARAMS(enable);
}

void GStb::ExecAction(const QString &str)
{
    STUB_WITH_PARAMS(str);
}

void GStb::ExtProtocolCommand(const QString &val1, const QString &val2, const QString &val3)
{
    STUB_WITH_LIST(QStringList() << val1 << val2 << val3);
}

void GStb::ForceHDMItoDVI(int forceDVI)
{
    STUB_WITH_PARAMS(forceDVI);
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

int GStb::GetAspect()
{
    STUB();
    CHECK_PLAYER(ASPECT_RATIO_AUTO);
    return player()->aspectRatio();
}

int GStb::GetAudioPID()
{
    CHECK_PLAYER(0);
    return player()->audioPID();
}

QString GStb::GetAudioPIDs()
{
    STUB();
    //if(player())
    //    return player()->audioPIDs();
    return "";
}

QString GStb::GetAudioPIDsEx()
{
    STUB();
    //CHECK_PLAYER("");
    return "";
}

int GStb::GetBrightness()
{
    STUB();
    //CHECK_PLAYER(100);
    return 100;
}

int GStb::GetBufferLoad()
{
    STUB();
    CHECK_PLAYER(100);
    return player()->bufferLoad();
}

int GStb::GetContrast()
{
    STUB();
    //CHECK_PLAYER(100);
    return 100;
}

QString GStb::GetDeviceActiveBank()
{
    STUB();
    //CHECK_PLAYER("");
    return "";
}

QString GStb::GetDeviceImageDesc()
{
    QString description = profile->datasource()->get(DB_TAG_RDIR, "ImageDescription");
    LOG(description);
    return description;
}

QString GStb::GetDeviceImageVersion()
{
    QString version = profile->datasource()->get(DB_TAG_RDIR, "ImageVersion");
    LOG(QString("GetDeviceImageVersion(): %1").arg(version));
    return version;
}

QString GStb::GetDeviceImageVersionCurrent()
{
    STUB();
    return "";
}

QString GStb::GetDeviceMacAddress()
{
    if(!profile->datasource())
        return "";

    QString mac = profile->datasource()->get(DB_TAG_RDIR, "MACAddress");
    LOG(QString("GetDeviceMacAddress(): %1").arg(mac));
    return mac;
}

QString GStb::GetDeviceModel()
{
    QString model = "MAG250";
    STUB_WITH_PARAMS(QString("GetDeviceModel(): ").arg(model));
    return model;
}

QString GStb::GetDeviceModelExt()
{
    STUB();
    return "MAG250";
}

QString GStb::GetDeviceSerialNumber()
{
    if(!profile->datasource())
        return "";

    QString serial = profile->datasource()->get(DB_TAG_RDIR, "SerialNumber");
    LOG(QString("GetDeviceSerialNumber(): %1").arg(serial));
    return serial;
}

QString GStb::GetDeviceVendor()
{
    QString vendor = "TeleTec";
    STUB_WITH_PARAMS(QString("GetDeviceVendor(): %1").arg(vendor));
    return vendor;
}

QString GStb::GetDeviceVersionHardware()
{
    STUB();
    return "";
}

QString GStb::GetEnv(const QString &data)
{
    if(!profile->datasource())
        return "";

    QJsonObject obj = QJsonDocument::fromJson(QByteArray(data.toUtf8())).object();
    QJsonObject elements;
    QJsonArray varList = obj.value("varList").toArray();

    for(int index = 0; index < varList.size(); index++)
    {
        QString name = varList.at(index).toString();

        QString value = profile->datasource()->get(DB_TAG_ENV, name);
        elements.insert(name, value);
    }

    //QString result = parent->getDataSource()->getValue(DB_TAG_ENV, name);
    QJsonObject result;
    result.insert("result", elements);
    QString strResult  = QString(QJsonDocument(result).toJson(QJsonDocument::Compact));
    STUB_WITH_PARAMS(QString("GetEnv(%1): %2").arg(data, strResult));
    return strResult;
}

QString GStb::GetExtProtocolList()
{
    STUB();
    return "";
}

bool GStb::GetLanLinkStatus()
{
    STUB();
    return Core::instance()->network()->isLanConnected();
}

int GStb::GetMediaLen()
{
    STUB();
    CHECK_PLAYER(0);
    return (int)(player()->mediaLength() / 1000);

}

int GStb::GetMediaLenEx()
{
    STUB();
    CHECK_PLAYER(0);
    //TODO: fixme
    return (int)(player()->mediaLength() / 1000);
}

QString GStb::GetMetadataInfo()
{
    STUB();
    //CHECK_PLAYER("");
    return "";
}

int GStb::GetMicVolume()
{
    STUB();
    //CHECK_PLAYER(0);
    return 100;
}

bool GStb::GetMute()
{
    STUB();
    CHECK_PLAYER(false);
    return player()->mute();
}

QString GStb::GetNetworkGateways()
{
    STUB();
    return "";
}

QString GStb::GetNetworkNameServers()
{
    STUB();
    return "";
}

QString GStb::GetNetworkWifiMac()
{
    STUB();
    return "";
}

bool GStb::GetPIG()
{
    STUB();
    return false;
}

int GStb::GetPosPercent()
{
    STUB();
    CHECK_PLAYER(0);
    return (int)(((float)player()->position() * 100) / player()->duration());
}

int GStb::GetPosPercentEx()
{
    STUB();
    //CHECK_PLAYER(0);
    return 0;
}

int GStb::GetPosTime()
{
    STUB();
    int pos = player()->position() / 1000;
    qDebug() << "position:" << pos;
    return pos;
}

int GStb::GetPosTimeEx()
{
    STUB();
    int pos = player()->position();
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
    //FIXME: Fix SAMBA sheres.
    //Next code doesn't work because QFile/QDir only supports local files
    STUB();

    QString smbPath;

    #ifdef Q_OS_LINUX
        smbPath = "smb:///";
    #endif
    #ifdef Q_OS_WIN32
        smbPath = "";
    #endif

    QJsonObject result;
    QJsonArray resultArray;
    QString errorMsg;

    NetworkThread thread;
    thread.setCallback([&](){
        QDir sambaDir(smbPath);
        qDebug() << "Looking for SAMBA groups in " << sambaDir;
        foreach(QString file, sambaDir.entryList(QDir::Files | QDir::Readable))
        {
            resultArray.append(file);
        }
        qDebug() << "Lookup finished. Found: " << resultArray;
    });

    thread.start();
    thread.wait(5000);
    thread.terminate();
    thread.wait(100);

    result.insert("result", resultArray);
    result.insert("errMsg", errorMsg);

    return QJsonDocument(result).toJson(QJsonDocument::Compact);
}

QString GStb::GetSmbServers(const QString &args)
{
    STUB_WITH_PARAMS(args);

    QJsonObject result;
    QJsonArray resultArray;
    QString errorMsg;

    result.insert("result", resultArray);
    result.insert("errMsg", errorMsg);

    return QJsonDocument(result).toJson(QJsonDocument::Compact);
}

QString GStb::GetSmbShares(const QString &args)
{
    STUB_WITH_PARAMS(args);

    QJsonObject result;
    QJsonObject resultData;
    QString errorMsg;

    QJsonArray sharesArray;

    resultData.insert("shares",sharesArray);
    result.insert("result", resultData);
    result.insert("serverIP", QString("127.0.0.1"));
    result.insert("errMsg", errorMsg);

    return QJsonDocument(result).toJson(QJsonDocument::Compact);
}

qint32 GStb::GetSpeed()
{
    STUB();
    return 0;
}

/**
 * Get all mount point info
 * @param param
 * @return
 */
QString GStb::GetStorageInfo(const QString &param)
{
    STUB_WITH_PARAMS(param);
    return "{}";
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
    return 0;
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
    return player()->volume();
}

QString GStb::GetWepKey128ByPassPhrase(const QString &passPhrase)
{
    STUB_WITH_PARAMS(passPhrase);
    return "";
}

QString GStb::GetWepKey64ByPassPhrase(const QString &passPhrase)
{
    STUB_WITH_PARAMS(passPhrase);
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

qint32 GStb::GetWinAlphaLevel()
{
    STUB();
    return 0;
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
    STUB_WITH_PARAMS(ignore);
}

void GStb::InitPlayer()
{
    STUB();
    //if(plugin->player())
    //    plugin->player()->mediaReset();
    //else
    //    WARN(QString("Cannot init player - not found!"));
}

bool GStb::IsFileExist(QString fileName)
{
    STUB_WITH_PARAMS(fileName);

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
    STUB_WITH_PARAMS(folderName);
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
    LOG("IsPlaying(): " + QVariant(state).toString());
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
 * where <SN> - drive serial number and <INDEX> - drive index starting from 1 (for each drive should be one row),
 * as it returned by RDir("get_storage_info").
 *
 * \see @RDir
 * @return
 */
QString GStb::ListDir(const QString &dir)
{
    //TODO: Add UPnP, LAN & Favourites support
    STUB_WITH_PARAMS(dir);
    QString directoryPath = dir;

    QJsonArray files;
    QJsonArray dirs;
    QString result;

    // for some reasons Stalker in some cases puts two slashes in path instead of one (as it possibly should).
    QRegularExpression rootMatch("^(/){1,2}media(/){1,2}$");
    QRegularExpression diskRegex("[/{0,2}]USB-\\d+-(\\d+)");
    QRegularExpressionMatch diskRegexMatch = diskRegex.match(directoryPath);
    QList<DiskInfo*> disks = Core::instance()->disks();

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
            DEBUG(QString("FIXME: ").append(dir));
        }
    }


    dirs.append(QString(""));
    files.append(QJsonValue::fromVariant(QJsonDocument(QJsonObject()).toVariant()));

    DEBUG(result);
    return QString("var dirs = %1; var files = %2;").arg(QString(QJsonDocument(dirs).toJson(QJsonDocument::Compact))).arg(QString(QJsonDocument(files).toJson(QJsonDocument::Compact)));
}

QString GStb::translateStbPathToLocal(const QString& path)
{
    QRegularExpression diskRegex("[/{0,2}]USB-\\d+-(\\d+)");
    QRegularExpressionMatch diskRegexMatch = diskRegex.match(path);
    QList<DiskInfo*> disks = Core::instance()->disks();

    if(diskRegexMatch.hasMatch())
    {
        qDebug() << "match disk";
        int diskIndex = diskRegexMatch.captured(1).toInt() - 1; // Disk index starts from 1
        QString newPath = path;
        newPath = newPath.replace(diskRegex, disks.at(diskIndex)->mountPoint);
        return newPath;
    }
    else
    {
        return "";
    }

}

void GStb::LoadCASIniFile(const QString &iniFileName)
{
    STUB_WITH_PARAMS(iniFileName);
}

void GStb::LoadExternalSubtitles(const QString &url)
{
    STUB_WITH_PARAMS(url);
}

void GStb::LoadURL(const QString &str)
{
    STUB_WITH_PARAMS(str);
}

/**
 * Load file from mnt/Userfs/data
 * @param {String} strVal file name
 * @returns {String} file content
 */
QString GStb::LoadUserData(const QString &str)
{
    QString data = profile->datasource()->get(DB_TAG_USER, str);
    STUB_WITH_LIST(QStringList() << str << data);
    return data;
}

void GStb::Pause()
{
    STUB();
    CHECK_PLAYER_VOID;
    player()->mediaPause();
}

void GStb::Play(const QString &playStr, const QString &proxyParmas)
{
    STUB_WITH_LIST(QStringList() << playStr << proxyParmas);

    QString urlString = playStr.trimmed();

    QRegularExpression urlRegex("^(?<proto>auto|rtsp)?\\s+(?<url>.*?)$");
    QRegularExpressionMatch urlMatch = urlRegex.match(urlString);


    if(!urlMatch.hasMatch())
    {
        qDebug() << "Unknown URL type!";
        return;
    }

    QString protocol = !urlMatch.captured("proto").isEmpty() ? urlMatch.captured("proto"): "auto";
    QString url = urlMatch.captured("url");

    qDebug() << "matched proto:" << protocol << ", url:" << url;


    CHECK_PLAYER_VOID;

    if(url.startsWith("//"))
    {
        url = url.replace("//", "/");

        url = translateStbPathToLocal(url);
    }


    player()->mediaPlay(url);
}

void GStb::PlaySolution(const QString &solution, const QString &url)
{
    STUB_WITH_LIST(QStringList() << solution << url);
}

QString GStb::RDir(const QString &name)
{
    Q_ASSERT(profile->datasource());

    if(name == "get_storage_info")
    {
        return ((MagApi*)profile->getProfilePlugin())->getStorageInfo();
    }

    QString result;
    if(name.startsWith("getenv ") || name.startsWith("setenv "))
    {
       QStringList params = name.split(" ");
       if(params.at(0) == "getenv")
            result = profile->datasource()->get(DB_TAG_ENV, params[1]);
       else if(params.at(0) == "setenv")
           result = QVariant(profile->datasource()->set(DB_TAG_ENV, params.at(1), params.at(2))).toString();
    }
    else if(name.startsWith("tempfile"))
    {
        QStringList params = name.split(" ");

        if(params.length() != 3)
            WARN(QString("Wrong length:").append(params.length()));
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
        result = ((MagApi*)profile->getProfilePlugin())->getStorageInfo();
    }
    else
    {
        result = profile->datasource()->get(DB_TAG_RDIR, name);
    }

    LOG(QString("[\"%1\"] -> \"%2\"").arg(name, result));
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
    STUB_WITH_PARAMS(angle);
}

void GStb::SaveUserData(const QString &fileName, const QString &data)
{
    STUB_WITH_LIST(QStringList() << fileName << data);
    profile->datasource()->set(DB_TAG_USER, fileName, data);
}

void GStb::SendEventToPortal(const QString &args)
{
    STUB_WITH_PARAMS(args);
}

void GStb::ServiceControl(const QString &serviceName, const QString &action)
{
    STUB_WITH_LIST(QStringList() << serviceName << action);
}

void GStb::Set3DConversionMode(int mode)
{
    STUB_WITH_PARAMS(mode);
}

void GStb::SetAdditionalCasParam(const QString &name, const QString &value)
{
    STUB_WITH_LIST(QStringList() << name << value);
}

void GStb::SetAlphaLevel(qint32 alpha)
{
    STUB_WITH_PARAMS(alpha);
}

void GStb::SetAspect(int aspect)
{
    STUB_WITH_PARAMS(aspect);
    //fixme
    ASPECT_RATIO aspectRatio = ASPECT_RATIO_AUTO; // (int) aspect;
    CHECK_PLAYER_VOID;
    player()->aspectRatio(aspectRatio);
}

void GStb::SetAudioLangs(const QString &priLang, const QString &secLang)
{
    STUB_WITH_LIST(QStringList() << priLang << secLang);
}

void GStb::SetAudioOperationalMode(int mode)
{
    STUB_WITH_PARAMS(mode);
}

void GStb::SetAudioPID(int pid)
{
    STUB_WITH_PARAMS(pid);
    CHECK_PLAYER_VOID;
    player()->audioPID(pid);
}

void GStb::SetAutoFrameRate(int mode)
{
    STUB_WITH_PARAMS(mode);
}

void GStb::SetBrightness(qint32 bri)
{
    STUB_WITH_PARAMS(bri);
}

void GStb::SetBufferSize(qint32 sizeInMs, qint32 maxSizeInBytes)
{
    STUB_WITH_LIST(QStringList() << QString::number(sizeInMs) << QString::number(maxSizeInBytes));
}

void GStb::SetCASDescrambling(int isSoftware)
{
    STUB_WITH_PARAMS(isSoftware);
}

void GStb::SetCASParam(const QString &serverAddr, qint32 port, const QString &companyName, qint32 opID, qint32 errorLevel)
{
    STUB_WITH_LIST(QStringList() << serverAddr << QString().number(port) << companyName << QString().number(opID) <<  QString().number(errorLevel));
}

void GStb::SetCASType(qint32 type)
{
    STUB_WITH_PARAMS(type);
}

void GStb::SetCheckSSLCertificate(int val)
{
    STUB_WITH_PARAMS(val);
}

void GStb::SetChromaKey(qint64 key, qint64 mask)
{
    STUB_WITH_LIST(QStringList() << QString::number(key) << QString::number(mask));
}

void GStb::SetComponentMode(int mode)
{
    STUB_WITH_PARAMS(mode);
}

void GStb::SetContrast(qint16 contrast)
{
    STUB_WITH_PARAMS(contrast);
}

void GStb::SetCustomHeader(const QString &header)
{
    STUB_WITH_PARAMS(header);
}

void GStb::SetDefaultFlicker(int state)
{
    STUB_WITH_PARAMS(state);
}

void GStb::SetDRC(int high, int low)
{
    STUB_WITH_LIST(QStringList() << QString::number(high) << QString::number(low));
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
    if(!profile->datasource())
        return false;

    LOG(QString("SetEnv(%1 = %2)").arg(data).arg(value));
    bool result = true;
    if(value == 0)
    {
        QJsonObject obj = QJsonDocument::fromJson(QByteArray(data.toUtf8())).object();
        foreach(QString key, obj.keys())
        {
            result = result && profile->datasource()->set(DB_TAG_ENV, key, obj.take(key).toString());
        }
    }
    else
    {
        result = profile->datasource()->set(DB_TAG_ENV, data, value);
    }

    return result;
}

void GStb::SetFlicker(int state, int flk, int shp)
{
    STUB_WITH_LIST(QStringList() << QString::number(state) << QString::number(flk) << QString::number(shp));
}

void GStb::SetHDMIAudioOut(int type)
{
    STUB_WITH_PARAMS(type);
}

void GStb::SetInternalPortalActive(bool active)
{
    STUB_WITH_PARAMS(active);
}

void GStb::SetListFilesExt(const QString &exts)
{
    STUB_WITH_PARAMS(exts);
    listFileExt = exts.split(" ");
}

void GStb::SetLoop(int loop)
{
    STUB_WITH_PARAMS(loop);
    CHECK_PLAYER_VOID;
    player()->loop(loop);
}

void GStb::SetMicVolume(int volume)
{
    STUB_WITH_PARAMS(volume);
}

/**
 * Switch on (mode=1) or switch off (mode=0) the mode ChromaKey for the video window.
 * @param mode ChromaKey mode for the video window: 0 – off; 1 – on.
 * The parameters set by stb.SetChromaKey {@link #SetTransparentColor} shall be valid if the on-mode is used.
 */
int GStb::SetMode(int mode)
{
    STUB_WITH_PARAMS(mode);
    return 0;
}

int GStb::SetMulticastProxyURL(const QString &val)
{
    STUB_WITH_PARAMS(val);
    return 0;
}

void GStb::SetMute(int mute)
{
    STUB_WITH_PARAMS(mute);
    CHECK_PLAYER_VOID;
    player()->mute(mute == 1);
}

void GStb::SetObjectCacheCapacities(int val1, int val2, int val3)
{
    STUB_WITH_LIST(QStringList() << QString::number(val1) << QString::number(val2) << QString::number(val3));
}

void GStb::SetPCRModeEnabled(bool val)
{
    STUB_WITH_PARAMS(val);
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
    STUB_WITH_LIST(QStringList() << QString::number(state) << QString::number(scale) << QString::number(x) << QString::number(y));

    if(state == 1)
    {
        player()->fullscreen(true);
    }
    else
    {
        player()->fullscreen(true);
        if(x >= 0 && y >= 0)
            player()->move(x, y);
    }
    player()->resize();
}

void GStb::SetPixmapCacheSize(int val)
{
    STUB_WITH_PARAMS(val);
}

void GStb::SetPosPercent(int prc)
{
    STUB_WITH_PARAMS(prc);
}

void GStb::SetPosPercentEx(int prc)
{
    STUB_WITH_PARAMS(prc);
}

void GStb::SetPosTime(int time)
{
    STUB_WITH_PARAMS(time);
    CHECK_PLAYER_VOID;
    player()->position(time * 1000);
}

void GStb::SetPosTimeEx(int time)
{
    STUB_WITH_PARAMS(time);
}

void GStb::SetSaturation(int sat)
{
    STUB_WITH_PARAMS(sat);
}

void GStb::SetSpeed(int speed)
{
    STUB_WITH_PARAMS(speed);
}

void GStb::SetStereoMode(int mode)
{
    STUB_WITH_PARAMS(mode);
}

void GStb::SetSubtitleLangs(const QString &priLang, const QString &secLang)
{
    STUB_WITH_LIST(QStringList() << priLang << secLang);
}

void GStb::SetSubtitlePID(int pid)
{
    STUB_WITH_PARAMS(pid);
}

void GStb::SetSubtitles(bool enable)
{
    STUB_WITH_PARAMS(enable);
}

void GStb::SetSubtitlesColor(int val)
{
    STUB_WITH_PARAMS(val);
}

void GStb::SetSubtitlesEncoding(const QString &encoding)
{
    STUB_WITH_PARAMS(encoding);
}

void GStb::SetSubtitlesFont(const QString &font)
{
    STUB_WITH_PARAMS(font);
}

void GStb::SetSubtitlesOffs(int offset)
{
    STUB_WITH_PARAMS(offset);
}

void GStb::SetSubtitlesSize(int size)
{
    STUB_WITH_PARAMS(size);
}

void GStb::SetSyncCorrection(int val1, int val2)
{
    STUB_WITH_LIST(QStringList() << QString::number(val1) << QString::number(val2));
}

void GStb::SetSyncOffsetCorrection(int val)
{
    STUB_WITH_PARAMS(val);
}

void GStb::SetTeletext(bool val)
{
    STUB_WITH_PARAMS(val);
}

void GStb::SetTeletextPID(unsigned int val)
{
    STUB_WITH_PARAMS(val);
}

/**
 * Sets the preset window over others
 * @param winNum number of the window for which this function is used: 0 - graphic window; 1 - video window
 */
void GStb::SetTopWin(int winNum)
{

    STUB_WITH_PARAMS(winNum);
    //return;
    if(winNum == WINDOW_BROWSER)
        profile->getProfilePlugin()->browser()->raise();
    else
        player()->raise();
}

void GStb::SetTransparentColor(int color)
{
    STUB_WITH_PARAMS(color);
}

void GStb::SetupRTSP(int type, int flags)
{
    STUB_WITH_LIST(QStringList() << QString::number(type) << QString::number(flags));
}

void GStb::SetupSPdif(int flags)
{
    STUB_WITH_PARAMS(flags);
}

void GStb::SetUserFlickerControl(int mode)
{
    STUB_WITH_PARAMS(mode);
}

void GStb::SetVideoControl(int mode)
{
    STUB_WITH_PARAMS(mode);
}

void GStb::SetVideoState(int state)
{
    STUB_WITH_PARAMS(state);
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
    CHECK_PLAYER_VOID;
    STUB_WITH_LIST(QStringList() << QString::number(xsize) << QString::number(ysize) << QString::number(x) << QString::number(y));

    StbPlugin* plugin = profile->getProfilePlugin();

    plugin->player()->fullscreen(false);
    plugin->player()->setViewport(plugin->browser()->rect(), plugin->browser()->scale(), QRect(x, y, xsize, ysize));
}

void GStb::SetVolume(int volume)
{
    STUB_WITH_PARAMS(volume);
    CHECK_PLAYER_VOID;
    player()->volume(volume);
}

void GStb::SetWebMode(bool val, const QString &str)
{
    STUB_WITH_LIST(QStringList() << QVariant::fromValue(val).toString() << str);
}

void GStb::SetWebProxy(const QString &host, int port, const QString &user, const QString &password, const QString &exclude)
{
    STUB_WITH_LIST(QStringList() << host << QString::number(port) << user << password << exclude);
}

void GStb::SetWinAlphaLevel(int winNum, int alpha)
{
    STUB_WITH_LIST(QStringList() << QString::number(winNum) << QString::number(alpha));
}

void GStb::SetWinMode(int winNum, int mode)
{
    STUB_WITH_LIST(QStringList() << QString::number(winNum) << QString::number(mode));
}

void GStb::ShowSubtitle(int start, int end, const QString &text)
{
     STUB_WITH_LIST(QStringList() << QString::number(start) << QString::number(end) << text);
}

void GStb::ShowVideoImmediately(bool val)
{
     STUB_WITH_PARAMS(val);
}

void GStb::ShowVirtualKeyboard()
{
    ShowVirtualKeyboard(true);
}

void GStb::ShowVirtualKeyboard(bool show)
{
    STUB_WITH_PARAMS(show);
}

void GStb::StandBy(bool standBy)
{
    STUB_WITH_PARAMS(standBy);
}

void GStb::StartLocalCfg()
{
    STUB();
}

void GStb::Step()
{
    STUB();
}

void GStb::Stop()
{
    STUB();
    CHECK_PLAYER_VOID;
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
    STUB_WITH_PARAMS(cfg);
}

/**
 * Save the string as the browser set up (prefs.js).
 * This function is not browser specific and it is used to set the right of access to the portal.
 * This is performed in starting portal saved at /home/web of the root file system and it is recommended to avoid using it anywhere else.
 * @param {String} prefs Data to be saved in the file of browser settings
 */
void GStb::WritePrefs(const QString &prefs)
{
    STUB_WITH_PARAMS(prefs);
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
* @seed48 http://mahonen.tumblr.com/post/8637914737/hmac-hash-for-qt
*/
QString GStb::GetHashVersion1(QString secret, QString key)
{
    STUB_WITH_LIST(QStringList() << secret << key);

   //Length of the text, that will be hashed
   int   text_length;

   //For secret word.
   QByteArray K;
   //Lenght of secret word
   int   K_lenght;

   K_lenght = secret.size();
   text_length = key.size();

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
    STUB_WITH_PARAMS(enable);
}

/**
 * True to apply new native string handling without utf8/utf16 encoding/decoding
 * @param {Boolean} boolVal true - all string manipulations are with utf16 strings
 */
void GStb::SetNativeStringMode(bool native)
{
    STUB_WITH_PARAMS(native);
}

void GStb::SetScreenSaverTime(int time)
{
   STUB_WITH_PARAMS(time);
}

/**
 * Set new input language
 * @param langId Language id to be set as input language
 */
void GStb::SetInputLang(const QString &lang)
{
    STUB_WITH_PARAMS(lang);
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
    STUB_WITH_PARAMS(lang);
}

/**
 * Set system settings init parameters
 * @param options parameters from windowInit function
 */
void GStb::SetSettingsInitAttr(const QString &options)
{
    STUB_WITH_PARAMS(options);
}

/**
 * Set screensaver window init parameters
 * @param options parameters from windowInit function
 */
void GStb::SetScreenSaverInitAttr(const QString &options)
{
    STUB_WITH_PARAMS(options);
}
