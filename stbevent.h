#ifndef STBEVENT_H
#define STBEVENT_H

#include <QObject>

namespace yasem
{
class MagProfile;

class StbEvent : public QObject
{
    Q_OBJECT
public:
    explicit StbEvent(MagProfile *profile);

    enum Events {
        STB_EVENT_NO_ERROR = 0,
        STB_EVENT_EOF = 1,
        STB_EVENT_GOT_INFO = 2,
        STB_EVENT_PLAY_START = 4,
        STB_EVENT_PLAY_ERROR = 5,
        STB_EVENT_DUAL_MONO_AC3 = 6,
        STB_EVENT_GOT_VIDEO_INFO = 7,
        STB_EVENT_SUBTITLE_LOAD_ERROR = 8
    };

signals:

public slots:

    void sendEvent(int eventCode);
    void onEvent(int eventCode);

protected:
    MagProfile *profile;
};

}

#endif // STBEVENT_H
