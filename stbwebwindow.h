#ifndef STBWEBWINDOW_H
#define STBWEBWINDOW_H


#include <QObject>

namespace yasem
{
class MagProfile;

namespace SDK {
class WebPage;
}

class StbWebWindow : public QObject
{
    Q_OBJECT
public:
    explicit StbWebWindow(MagProfile *m_profile, SDK::WebPage* m_page);


signals:

public slots:
    void close();

    QString windowId();
    void messageSend(int windowId, const QString& message, const QString& data);
protected:
    MagProfile *m_profile;
    SDK::WebPage* m_page;
};

}


#endif // STBWEBWINDOW_H
