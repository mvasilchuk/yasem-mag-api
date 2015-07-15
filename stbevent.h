#ifndef STBEVENT_H
#define STBEVENT_H

#include <QObject>

namespace yasem
{
class MagProfile;

namespace SDK {
class WebPage;
}

class StbEvent : public QObject
{
    Q_OBJECT
public:
    explicit StbEvent(MagProfile *profile, SDK::WebPage* page);

    Q_PROPERTY(int event READ getEventCode)

    /**
     * The code of the last event.
     * The following events are defined:
     *   1 - The player reached the end of the media content or detected a discontinuity of the stream.
     *   2 - Information on audio and video tracks of the media content is received.
     *   4 - Video and/or audio playback has begun.
     *   5 - Error when opening the content: content not found on the server or connection with the server was rejected.
     *   6 - Detected DualMono AC-3 sound.
     *   7 - Detected information about video content.
     *   8 - Error occurred while loading external subtitles.
     *   0x20 - HDMI connected.
     *   0x21 - HDMI disconnected.
     *   0x22 - Recording task has been finished successfully. See Appendix 13. JavaScript API for PVR subsystem.
     *   0x23 - Recording task has been finished with error. See Appendix 13. JavaScript API for PVR subsystem.
     *   0x81 - When playing RTP-stream the numbering of RTP-packets was broken.
     * @type {Number}
     */
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
    void initEvents();

protected:
    MagProfile *profile;
    int getEventCode();
    int eventCode;
    SDK::WebPage* m_page;
};

}

#endif // STBEVENT_H
