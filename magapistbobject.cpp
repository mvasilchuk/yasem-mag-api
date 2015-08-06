#include "magapistbobject.h"
#include "customkeyevent.h"
#include "gstb.h"
#include "pvrmanager.h"
#include "stbscreen.h"
#include "stbwindowmgr.h"
#include "stbupdate.h"
#include "stbwebwindow.h"
#include "timeshift.h"
#include "netscape.h"
#include "stbdownloadmanager.h"
#include "magprofile.h"
#include "pluginmanager.h"
#include "profilemanager.h"
#include "stbevent.h"
#include "stbstorage.h"
#include "mediaplayer.h"
#include "gui.h"
#include "browser.h"

#include <QFile>
#include <QFileInfoList>
#include <QDir>
#include <QJsonDocument>

using namespace yasem;

MagApiStbObject::MagApiStbObject(SDK::Plugin* plugin):
    SDK::StbPluginObject(plugin)
{

}

MagApiStbObject::~MagApiStbObject()
{
    STUB();
}

QString yasem::MagApiStbObject::getProfileClassId()
{
    return "mag";
}

SDK::Profile* yasem::MagApiStbObject::createProfile(const QString &id)
{
    return new MagProfile(this, id);
}

void yasem::MagApiStbObject::initObject(SDK::WebPage *page)
{
     resetObjects(page);
}

QString yasem::MagApiStbObject::getIcon(const QSize &size)
{
    return "qrc:/mag/icons/aurahd/aura-hd-256.png";
}

QString MagApiStbObject::getStorageInfo()
{
    QList<SDK::StorageInfo*> disks = SDK::Core::instance()->storages();
    QJsonArray result = QJsonArray();

    int partitionNum = 1;
    foreach (SDK::StorageInfo* disk, disks) {

        QString sn = QString("00000000%1").arg(partitionNum);

        QJsonObject obj = QJsonObject();
        obj.insert("sn", sn);
        obj.insert("partitionNum", partitionNum);

        // To make it looks better in Stalker I swapped  label and vendor+model
        // If you want to revert just comment this code
        //*
        obj.insert("vendor", disk->mountPoint + " ");
        obj.insert("model", QString(""));
        obj.insert("label", disk->vendor + " " + disk->model);
        /*/
        obj.insert("vendor", disk->vendor);
        obj.insert("model", disk->model != "" ? disk->model : disk->blockDevice.replace("/dev/", "").append(" "));
        obj.insert("label", disk->mountPoint);
        //*/
        obj.insert("mountPath", /*drive.absoluteFilePath()*/ QString("USB-%1-%2").arg(sn).arg(partitionNum));
        obj.insert("size", QString::number(disk->size));
        obj.insert("freeSize", QString::number(disk->available));
        obj.insert("isReadOnly", disk->writable ? 0 : 1);
        partitionNum++;

        qDebug() << "partition" << obj;

        result.append(QJsonValue(obj));
    }
    return QString(QJsonDocument(result).toJson(QJsonDocument::Compact));
}

void MagApiStbObject::resetObjects(SDK::WebPage *page)
{
    QHash<QString, QObject*>& api = getApi();

    const QSharedPointer<MagProfile>& profile = qSharedPointerCast<MagProfile>(SDK::ProfileManager::instance()->getActiveProfile());

    cleanApi();
    api.insert("screen", QPointer<QObject>(new StbScreen(profile.data())));

    Q_ASSERT(page);

    // TODO: Move to smart pointer
    GStb* stb = new GStb(profile.data(), page);
    api.insert("stb", stb);
    api.insert("gSTB", stb);
    api.insert("stbDownloadManager", new StbDownloadManager(profile.data(), page));
    api.insert("stbWindowMgr", new StbWindowMgr(profile.data(), page));
    api.insert("pvrManager", new PvrManager(profile.data(), page));
    api.insert("stbUpdate", new StbUpdate(profile.data(), page));
    api.insert("stbWebWindow", new StbWebWindow(profile.data(), page));
    api.insert("timeShift", new TimeShift(profile.data(), page));
    api.insert("netscape", new Netscape(profile.data()));
    api.insert("stbEvent", new StbEvent(profile.data(), page));
    api.insert("stbStorage", new StbStorage(profile.data(), page));

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

void MagApiStbObject::applyFixes()
{
    //browser()->evalJs(fontFix);
}

QUrl MagApiStbObject::handleUrl(QUrl &url)
{
    QString urlString = url.toString();

    if(urlString.startsWith("http://home/web"))
        urlString.replace(QString("http://home/web"), QString("%1:%2").arg(webServerHost).arg(webServerPort));
    else if(urlString.startsWith("file:///home/web"))
        urlString.replace(QString("file:///home/web"), QString("%1:%2").arg(webServerHost).arg(webServerPort));
    else if(urlString.startsWith("/home/web"))
        urlString.replace(QString("/home/web"), QString("%1:%2").arg(webServerHost).arg(webServerPort));

    return QUrl(urlString);
}


SDK::PluginObjectResult MagApiStbObject::init()
{
    StbPluginObject::init();// It's reqired to register profile class id

    QFile res(QString(":/mag/fixes/fontfix.js"));
    res.open(QIODevice::ReadOnly|QIODevice::Text);
    fontFix = res.readAll();

    webServerHost = "http://127.0.0.1";
    webServerPort = SDK::Core::instance()->settings()->value("web-server/port", 9999).toInt();

    QList<SDK::StbSubmodel>& submodels = getSubmodels();

    setSubmodelDatasourceField("RDIR", "STB Model");

    submodels.append(SDK::StbSubmodel(QString::number(MAG_100), "MAG100"));
    submodels.append(SDK::StbSubmodel(QString::number(MAG_200), "MAG200"));
    submodels.append(SDK::StbSubmodel(QString::number(MAG_245), "MAG245"));
    submodels.append(SDK::StbSubmodel(QString::number(MAG_250), "MAG250"));
    submodels.append(SDK::StbSubmodel(QString::number(MAG_254), "MAG254"));
    submodels.append(SDK::StbSubmodel(QString::number(MAG_255), "MAG255"));
    submodels.append(SDK::StbSubmodel(QString::number(MAG_260), "MAG260"));
    submodels.append(SDK::StbSubmodel(QString::number(MAG_270), "MAG270"));
    submodels.append(SDK::StbSubmodel(QString::number(MAG_275), "MAG275"));
    submodels.append(SDK::StbSubmodel(QString::number(AURA_HD), "AuraHD"));

    return SDK::PLUGIN_OBJECT_RESULT_OK;
}

SDK::PluginObjectResult MagApiStbObject::deinit()
{
    return SDK::PLUGIN_OBJECT_RESULT_OK;
}

