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
    virtual ~StbWebWindow();

signals:

public slots:
    void close();
    void FocusMiddleWindow();
    void FocusTopWindow();
    QString getCurrentUrl();
    void messageBroadcast(const QString& message, const QString& data);
    void messageSend(int windowId, const QString& message, const QString& data = "");
    void NavigateBack();
    void NavigateForward();
    void ReloadDocument();
    void SendVirtualKeypress(const QString& unicodeText, const int key);
    void SetFullScreenMode(bool mode);
    void SetZoomFactor(int ratio);
    void StopLoading();

    int windowId();

protected:
    MagProfile *m_profile;
    SDK::WebPage* m_page;
};

}


#endif // STBWEBWINDOW_H
