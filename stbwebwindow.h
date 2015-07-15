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
    explicit StbWebWindow(MagProfile *profile, SDK::WebPage* m_page);


signals:

public slots:
    void close();

    QString windowId();
protected:
    MagProfile *profile;
    SDK::WebPage* m_page;
};

}


#endif // STBWEBWINDOW_H
