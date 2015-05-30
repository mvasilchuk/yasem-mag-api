#ifndef MAGPROFILE_H
#define MAGPROFILE_H

#include "stbprofile.h"


#include <QObject>

namespace yasem
{
class StbPluginObject;
class RemoteControlHandler;
class MagProfile : public QObject, public Profile
{
    Q_OBJECT
public:
    explicit MagProfile(StbPluginObject *profilePlugin, const QString &id);

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

#ifdef CONFIG_QCA
public:
    RemoteControlHandler* getRemoteControl() { return m_remote_control_handler; }
protected:
    RemoteControlHandler* m_remote_control_handler;
#endif //#ifdef CONFIG_QCA
};

}

#endif // MAGPROFILE_H
