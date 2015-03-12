#ifndef MAGPROFILE_H
#define MAGPROFILE_H

#include "stbprofile.h"


#include <QObject>

namespace yasem
{
class StbPluginObject;
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
};

}

#endif // MAGPROFILE_H
