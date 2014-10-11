#include "magapi.h"
#include "pluginmanager.h"
#include "customkeyevent.h"
#include "datasourceplugin.h"
#include "browserplugin.h"
#include "mediaplayerplugin.h"
#include "guiplugin.h"
#include "core.h"
#include "profilemanager.h"
#include "magprofile.h"
#include "stbevent.h"
#include "stbstorage.h"

#include <QFileInfoList>
#include <QDir>
#include <QJsonDocument>

using namespace yasem;

MagApi::MagApi()
{
    QFile res(QString(":/mag/fixes/fontfix.js"));
    res.open(QIODevice::ReadOnly|QIODevice::Text);
    fontFix = res.readAll();

    webServerHost = "http://127.0.0.1";
    webServerPort = Core::instance()->settings()->value("web-server/port", 9999).toInt();
}

PLUGIN_ERROR_CODES MagApi::initialize()
{
   player(dynamic_cast<MediaPlayerPlugin*>(PluginManager::instance()->getByRole(ROLE_MEDIA)));
   gui(dynamic_cast<GuiPlugin*>(PluginManager::instance()->getByRole(ROLE_GUI)));
   browser(dynamic_cast<BrowserPlugin*>(PluginManager::instance()->getByRole(ROLE_BROWSER)));

    return PLUGIN_ERROR_NO_ERROR;
}

PLUGIN_ERROR_CODES MagApi::deinitialize()
{
    STUB();
    return PLUGIN_ERROR_NO_ERROR;
}

QString MagApi::getStorageInfo()
{
    QList<DiskInfo*> disks = Core::instance()->disks();
    QJsonArray result = QJsonArray();

    int partitionNum = 1;
    foreach (DiskInfo* disk, disks) {

        QString sn = QString("00000000%1").arg(partitionNum);

        QJsonObject obj = QJsonObject();
        obj.insert("sn", sn);
        obj.insert("partitionNum", partitionNum);
        obj.insert("vendor", QString());
        obj.insert("model", disk->blockDevice.replace("/dev/", "").append(" "));
        obj.insert("label", disk->mountPoint);
        obj.insert("mountPath", /*drive.absoluteFilePath()*/ QString("USB-%1-%2").arg(sn).arg(partitionNum));
        obj.insert("size", QString::number(disk->size));
        obj.insert("freeSize", QString::number(disk->available));
        partitionNum++;

        qDebug() << "partition" << obj;

        result.append(QJsonValue(obj));
    }
    return QString(QJsonDocument(result).toJson(QJsonDocument::Compact));
}

QString MagApi::getIcon(const QSize &size = QSize())
{
    return "qrc:/mag/icons/aurahd/aura-hd-256.png";
}

Profile* MagApi::createProfile(const QString &id = "")
{
    return new MagProfile(this, id);
}

QString MagApi::getProfileClassId()
{
    return "mag";
}

void MagApi::resetObjects()
{
    QHash<QString, QObject*>& api = getApi();
    api.clear();

    MagProfile* profile = dynamic_cast<MagProfile*>(ProfileManager::instance()->getActiveProfile());

    api.insert("screen", new StbScreen(profile));

    GStb* stb = new GStb(profile);
    api.insert("stb", stb);
    api.insert("gSTB", stb);
    api.insert("stbDownloadManager", new StbDownloadManager(profile));
    api.insert("stbWindowMgr", new StbWindowMgr(profile));
    api.insert("pvrManager", new PvrManager(profile));
    api.insert("stbUpdate", new StbUpdate(profile));
    api.insert("stbWebWindow", new StbWebWindow(profile));
    api.insert("timeShift", new TimeShift(profile));
    api.insert("netscape", new Netscape(profile));
    api.insert("stbEvent", new StbEvent(profile));
    api.insert("stbStorage", new StbStorage(profile));

    /*
    connect(mediaPlayer, &QtAV::AVPlayer::paused,               &this->mediaSignalSender, &MediaSignalSender::paused);
    connect(mediaPlayer, &QtAV::AVPlayer::started,              &this->mediaSignalSender, &MediaSignalSender::started);
    connect(mediaPlayer, &QtAV::AVPlayer::stopped,              &this->mediaSignalSender, &MediaSignalSender::stopped);
    connect(mediaPlayer, &QtAV::AVPlayer::speedChanged,         &this->mediaSignalSender, &MediaSignalSender::speedChanged);
    connect(mediaPlayer, &QtAV::AVPlayer::repeatChanged,        &this->mediaSignalSender, &MediaSignalSender::repeatChanged);
    connect(mediaPlayer, &QtAV::AVPlayer::currentRepeatChanged, &this->mediaSignalSender, &MediaSignalSender::currentRepeatChanged);
    connect(mediaPlayer, &QtAV::AVPlayer::startPositionChanged, &this->mediaSignalSender, &MediaSignalSender::startPositionChanged);
    connect(mediaPlayer, &QtAV::AVPlayer::stopPositionChanged,  &this->mediaSignalSender, &MediaSignalSender::stopPositionChanged);
    connect(mediaPlayer, &QtAV::AVPlayer::positionChanged,      &this->mediaSignalSender, &MediaSignalSender::positionChanged);
    connect(mediaPlayer, &QtAV::AVPlayer::brightnessChanged,    &this->mediaSignalSender, &MediaSignalSender::brightnessChanged);
    connect(mediaPlayer, &QtAV::AVPlayer::contrastChanged,      &this->mediaSignalSender, &MediaSignalSender::contrastChanged);
    connect(mediaPlayer, &QtAV::AVPlayer::saturationChanged,    &this->mediaSignalSender, &MediaSignalSender::saturationChanged);
    */
}

void MagApi::applyFixes()
{
    //browser()->evalJs(fontFix);
}

void MagApi::init()
{
    resetObjects();
}

QUrl MagApi::handleUrl(QUrl &url) {
    QString urlString = url.toString();

    if(urlString.startsWith("http://home/web"))
        urlString.replace(QString("http://home/web"), QString("%1:%2").arg(webServerHost).arg(webServerPort));
    else if(urlString.startsWith("file:///home/web"))
        urlString.replace(QString("file:///home/web"), QString("%1:%2").arg(webServerHost).arg(webServerPort));
    else if(urlString.startsWith("/home/web"))
        urlString.replace(QString("/home/web"), QString("%1:%2").arg(webServerHost).arg(webServerPort));


    STUB() << urlString;

    return QUrl(urlString);
}

void yasem::MagApi::register_dependencies()
{
    add_dependency(ROLE_DATASOURCE);
    add_dependency(ROLE_BROWSER);
    add_dependency(ROLE_MEDIA);
}

void yasem::MagApi::register_roles()
{
    register_role(ROLE_STB_API);
}
