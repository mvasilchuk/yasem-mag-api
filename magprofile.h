#ifndef MAGPROFILE_H
#define MAGPROFILE_H

#include "stbprofile.h"


#include <QObject>

namespace yasem {

namespace SDK {
class StbPluginObject;
}

class RemoteControlHandler;
class MagProfile : public QObject, public SDK::Profile
{
    Q_OBJECT
public:
    explicit MagProfile(SDK::StbPluginObject* profilePlugin, const QString &id);
    virtual ~MagProfile();

signals:

public slots:
    void loadConfigOptions();
public:
    void start();
    void stop();
    void initDefaults();

    bool isInternalPortal();

protected:
    bool internalPortal;
public:
    QString portal();
    void configureKeyMap();

    bool isUsingMulticastProxy();
    QString getMulticastProxy();

    static QString translateStbPathToLocal(const QString &path);

#ifdef CONFIG_QCA
public:
    RemoteControlHandler* getRemoteControl() { return m_remote_control_handler; }
protected:
    RemoteControlHandler* m_remote_control_handler;
#endif //#ifdef CONFIG_QCA
};

}

#endif // MAGPROFILE_H
