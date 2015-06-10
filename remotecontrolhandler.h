#ifndef REMOTECONTROLHANDLER_H
#define REMOTECONTROLHANDLER_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QJsonObject>
#include <QtCrypto/QtCrypto>

namespace yasem {

class MagProfile;

class Device: public QObject
{
    Q_OBJECT
public:
    Device(QObject* parent);
    virtual ~Device();

    void setName(const QString& name);

    void fromJson(QJsonObject json);
    QJsonObject toJson();
protected:
    QString m_name;
    QString m_type;
    int m_port;
    QString m_serial_number;
    int m_screen_width;
    int m_screen_height;
    QString m_device_family;
    QString m_modes = "TOUCHSCREEN,MOUSE,KEYBOARD";
    QString m_protocol_version;
};

class RemoteControlHandler : public QObject
{
    Q_OBJECT
public:
    explicit RemoteControlHandler(MagProfile *profile);
    virtual ~RemoteControlHandler();

signals:

public slots:
    void setParams(const QString& deviceName, const QString& password);
    void start();
    void stop();
    void processPendingDatagrams();
    void onGetMessageFromClient();
    void sendDeviceInfo(const QHostAddress &host, int port);
    void sendPingResponse(const QHostAddress &host, int port);
    void parseDataAndExec(const QByteArray &data, const QHostAddress& address, int port);
    void execRemoteAction(const QJsonObject &json, const QHostAddress& address, int port);
protected:
    MagProfile* m_profile;
    QString m_password;
    QString m_iv_salt;
    Device* m_device;
    QUdpSocket* m_multicast_socket;
    QUdpSocket* m_udp_socket;
    QString m_ip;
    QByteArray aes_256_enc_dec(QByteArray &strToEnrypt, QCA::Direction direction);
};

}

#endif // REMOTECONTROLHANDLER_H
