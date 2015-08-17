#ifndef GSTB_H
#define GSTB_H

#include "macros.h"

#include <QObject>

namespace yasem
{
class MagProfile;

namespace SDK {
class MediaPlayer;
class WebPage;
class Browser;
class Datasource;
}

class GStb : public QObject
{
    Q_OBJECT

public:
    explicit GStb(MagProfile *profile, SDK::WebPage* page);
    virtual ~GStb();


protected:
    enum WINDOW_TYPE {
        WINDOW_BROWSER = 0,
        WINDOW_VIDEO = 1
    };

    QStringList listFileExt;
    MagProfile *m_profile;
    SDK::WebPage* m_page;
    QString listLocalFiles(const QString &dir);
    SDK::MediaPlayer* player();
    SDK::Browser* browser();
    SDK::Datasource* datasource();

    struct SystemSettingsCfg {
        QString url;
        QString backgroundColor;
    } m_system_settings;

signals:

public:
    MagProfile* profile();

public slots:

    void CloseWebWindow();
    void Continue();
    void Debug(const QString &str);
    void DeinitPlayer();
    void DeleteAllCookies();
    void EnableAppButton(bool enable);
    void EnableCustomNavigation(bool enable);
    void EnableJavaScriptInterrupt(bool enable);
    void EnableMulticastProxy(bool enable);
    void EnableServiceButton(bool enable);
    void EnableSetCookieFrom(const QString &domain, bool enable);
    void EnableSpatialNavigation(bool enable);
    void EnableVKButton(bool enable);
    void ExecAction(const QString &str);
    void ExtProtocolCommand(const QString &val1, const QString &val2, const QString &val3);
    void ForceHDMItoDVI(int forceDVI);
    int Get3DConversionMode();
    int GetAlphaLevel();
    int GetAspect();
    int GetAudioPID();
    QString GetAudioPIDs();
    QString GetAudioPIDsEx();
    int GetBrightness();
    int GetBufferLoad();
    int GetContrast();
    QString GetDeviceActiveBank();
    QString GetDeviceImageDesc();
    QString GetDeviceImageVersion();
    QString GetDeviceImageVersionCurrent();
    QString GetDeviceMacAddress();
    QString GetDeviceModel();
    QString GetDeviceModelExt();
    QString GetDeviceSerialNumber();
    QString GetDeviceVendor();
    QString GetDeviceVersionHardware();
    QString GetEnv(const QString &name);
    QString GetExtProtocolList();
    bool GetLanLinkStatus();
    int GetMediaLen();
    int GetMediaLenEx();
    QString GetMetadataInfo();
    int GetMicVolume(); //MAG 100
    bool GetMute();
    QString GetNetworkGateways();
    QString GetNetworkNameServers();
    QString GetNetworkWifiMac();
    bool GetPIG();
    int GetPosPercent();
    int GetPosPercentEx();
    int GetPosTime();
    int GetPosTimeEx();
    QString GetPppoeIp();
    bool GetPppoeLinkStatus();
    int GetSaturation();
    QString GetSmbGroups();
    QString GetSmbServers(const QString &args);
    QString GetSmbShares(const QString &args);
    qint32 GetSpeed();
    QString GetStorageInfo(const QString &args);
    qint16 GetSubtitlePID();
    QString GetSubtitlePIDs();
    QString GetTeletextPID();
    QString GetTeletextPIDs();
    qint64 GetTransparentColor();
    QString GetVideoInfo();
    qint32 GetVolume();
    QString GetWepKey128ByPassPhrase(const QString &passPhrase);
    QString GetWepKey64ByPassPhrase(const QString &passPhrase);
    QString GetWifiGroups();
    bool GetWifiLinkStatus();
    qint32 GetWinAlphaLevel(int winNum);
    void HideVirtualKeyboard();
    void HideVirtualKeyboardEx();
    void IgnoreUpdates(bool ignore);
    void InitPlayer();
    bool IsFileExist(QString fileName);
    bool IsFolderExist(const QString &folderName);
    bool IsInternalPortalActive();
    bool IsPlaying();
    bool IsVirtualKeyboardActive();
    bool IsVirtualKeyboardActiveEx();
    QString ListDir(const QString &dir);
    void LoadCASIniFile(const QString &iniFileName);
    void LoadExternalSubtitles(const QString &url);
    void LoadURL(const QString &str);
    QString LoadUserData(const QString &str);
    void Pause();
    void Play(const QString &playStr, const QString &proxyParams = "");
    void PlaySolution(const QString &solution, const QString &url);
    QString RDir(const QString &name);
    QString ReadCFG();
    void ResetUserFs();
    void Rotate(qint16 angle);
    void SaveUserData(const QString &fileName, const QString &data);
    void SendEventToPortal(const QString &args);
    void ServiceControl(const QString &serviceName, const QString &action);
    void Set3DConversionMode(int mode);
    void SetAdditionalCasParam(const QString &name, const QString &value);
    void SetAlphaLevel(qint32 alpha);
    void SetAspect(int aspect);
    void SetAudioLangs(const QString &priLang, const QString &secLang);
    void SetAudioOperationalMode(int mode);
    void SetAudioPID(int pid);
    void SetAutoFrameRate(int mode);
    void SetBrightness(qint32 bri);
    void SetBufferSize(qint32 sizeInMs, qint32 maxSizeInBytes);
    void SetCASDescrambling(int isSoftware);
    void SetCASParam(const QString &serverAddr, qint32 port, const QString &companyName, qint32 opID, qint32 errorLevel);
    void SetCASType(qint32 type);
    void SetCheckSSLCertificate(int val);
    void SetChromaKey(qint64 key, qint64 mask);
    void SetComponentMode(int mode);
    void SetContrast(qint16 contrast);
    void SetCustomHeader(const QString &header);
    void SetDefaultFlicker(int state);
    void SetDRC(int high, int low);
    bool SetEnv(const QString &data, const QString &value=0);
    void SetFlicker(int state, int flk, int shp);
    void SetHDMIAudioOut(int type);
    void SetInternalPortalActive(bool active);
    void SetListFilesExt(const QString &exts);
    void SetLoop(int loop);
    void SetMicVolume(int volume);
    int SetMode(int mode);
    int SetMulticastProxyURL(const QString &val);
    void SetMute(int mute);
    void SetObjectCacheCapacities(int cacheMinDeadCapacity, int cacheMaxDead, int totalCapacity);
    void SetPCRModeEnabled(bool enable);
    void SetPIG(int state, float scale, int x, int y);
    void SetPixmapCacheSize(int sizeKb);
    void SetPosPercent(int prc);
    void SetPosPercentEx(int prc);
    void SetPosTime(int time);
    void SetPosTimeEx(int time);
    void SetSaturation(int sat);
    void SetSpeed(int speed);
    void SetStereoMode(int mode);
    void SetSubtitleLangs(const QString &priLang, const QString &secLang);
    void SetSubtitlePID(int pid);
    void SetSubtitles(bool enable);
    void SetSubtitlesColor(int val);
    void SetSubtitlesEncoding(const QString &encoding);
    void SetSubtitlesFont(const QString &font);
    void SetSubtitlesOffs(int offset);
    void SetSubtitlesSize(int size);
    void SetSyncCorrection(int val1, int val2);
    void SetSyncOffsetCorrection(int val);
    void SetTeletext(bool val);
    void SetTeletextPID(unsigned int val);
    void SetTopWin(int winNum);
    void SetTransparentColor(int color);
    void SetupRTSP(int type, int flags);
    void SetupSPdif(int flags);
    void SetUserFlickerControl(int mode);
    void SetVideoControl(int mode);
    void SetVideoState(int state);
    void SetViewport(int xsize, int ysize, int x, int y);
    void SetViewportEx( int xSize, int ySize, int xPos, int yPos, int clipXSize, int clipYSize, int clipXPos, int clipYPos, bool saveClip );
    void SetVolume(int volume);
    void SetWebMode(bool val, const QString &str);
    void SetWebProxy(const QString &host, int port = 3128, const QString &user = "", const QString &password = "", const QString &exclude = "");
    void SetWinAlphaLevel(int winNum, int alpha);
    void SetWinMode(int winNum, int mode);
    void ShowSubtitle(int start, int end, const QString &text);
    void ShowVideoImmediately(bool val);
    void ShowVirtualKeyboard();
    void ShowVirtualKeyboard(bool show);
    void StandBy(bool standBy);
    void StartLocalCfg();
    void Step(); //MAG 100
    void Stop();
    QString Version();
    void WriteCFG(const QString &cfg);
    void WritePrefs(const QString &prefs);
    QString GetHashVersion1(QString secret, QString key);

    void EnableTvButton(bool enable);
    void SetNativeStringMode(bool native);
    void SetScreenSaverTime(int time);
    void SetInputLang(const QString &lang);
    QString GetDefaultUpdateUrl();
    void SetUiLang(const QString &lang);
    QString GetInputLang();
    void SetSettingsInitAttr(const QString &options);
    void SetScreenSaverInitAttr(const QString &options);
    void ClearStatistics();
    int GetHDMIConnectionState();
    QString GetHLSInfo();
    void SetLedIndicatorMode(int mode);
    void SetLedIndicatorLevels(int baseLevel, int blinkLevel);
    QString GetLedIndicatorState();
    bool GetStandByStatus();
    QString GetStatistics();
    int GetTopWin();
    QString GetWifiLinkStatusEx();
    bool IsFileUTF8Encoded(const QString &fileName);
    void ResetWebProxy();
    void SetSyslogLevel(int level);

    void ConfigNetRc(const QString &deviceName, const QString &password);
    void SetNetRcStatus(bool enable);
};

}



#endif // GSTB_H
