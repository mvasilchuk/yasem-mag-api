#-------------------------------------------------
#
# Project created by QtCreator 2014-02-04T10:31:10
#
#-------------------------------------------------

VERSION = 1.0.0

QT      = core gui widgets

CONFIG += c++11

TARGET = yasem-mag-api
TEMPLATE = lib

QMAKE_CXXFLAGS += -pedantic -Wall -Wextra -rdynamic -ldl

MOBILITY += systeminfo

DEFINES += MAGAPI_LIBRARY

INCLUDEPATH += ../../yasem-core/
DEPENDPATH += ../../yasem-core/

SOURCES += magapi.cpp \
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
    stbstorage.cpp

HEADERS += magapi.h\
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
    ../../yasem-core/mediasignalsender.h \
    stbstorage.h \
    NetworkThread.h



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
    resources/mag/keymap/default.ini

include(../../common.pri)
DESTDIR = $$DEFAULT_PLUGIN_DIR

RESOURCES += \
    resources.qrc
