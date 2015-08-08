#-------------------------------------------------
#
# Project created by QtCreator 2014-02-04T10:31:10
#
#-------------------------------------------------

VERSION = 0.1.0
TARGET = yasem-mag-api
TEMPLATE = lib

#CONFIG+=recheck

include($${top_srcdir}/common.pri)

QT      = core gui widgets network

MOBILITY += systeminfo

DEFINES += MAGAPI_LIBRARY

SOURCES += \
    gstb.cpp \
    pvrmanager.cpp \
    stbscreen.cpp \
    stbwindowmgr.cpp \
    stbupdate.cpp \
    stbwebwindow.cpp \
    timeshift.cpp \
    netscape.cpp \
    stbdownloadmanager.cpp \
    magprofile.cpp \
    stbevent.cpp \
    stbstorage.cpp \
    magapistbobject.cpp \
    magapiplugin.cpp

HEADERS +=\
    magapi_global.h \
    gstb.h \
    pvrmanager.h \
    stbscreen.h \
    stbwindowmgr.h \
    stbupdate.h \
    stbwebwindow.h \
    timeshift.h \
    netscape.h \
    stbdownloadmanager.h \
    mag_macros.h \
    magprofile.h \
    stbevent.h \
    magapiplugin.h \
    magapistbobject.h \
    stbstorage.h \
    NetworkThread.h \
    mag_enums.h

win32: {
HEADERS += \
    $${SDK_DIR}/mediaplayer.h
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

OTHER_FILES += \
    resources/metadata.json \
    resources/mag250-default-config.ini \
    resources/Ubuntu-R.ttf \
    resources/fontfix.css \
    resources/fontfix.js \
    resources/mag/languages_utf8.txt \
    resources/mag/timezone_list.txt \
    LICENSE \
    README.md \
    resources/mag/keymap/default.ini \
    resources/mag/config-options.json

RESOURCES += \
    resources.qrc

!build_pass:qtCompileTest(qca)

CONFIG(config_qca) {
    exists($${top_srcdir}/third_party/qca):exists($${top_srcdir}/third_party/qca-build) {
        INCLUDEPATH += $${top_srcdir}/third_party/qca/include
        INCLUDEPATH += $${top_srcdir}/third_party/qca-build
        INCLUDEPATH += .
        LIBS += -L $${top_srcdir}/third_party/qca-build/lib -lqca
    } else {
        LIBS += -lqca-qt5
    }

    HEADERS += remotecontrolhandler.h
    SOURCES += remotecontrolhandler.cpp
    DEFINES += CONFIG_QCA

} else {
    !build_pass:message("QCA library is missing. Wi-Fi/LAN remote control feature will be disabled")
}

