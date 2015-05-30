SOURCES = main.cpp
QT = core
CONFIG = qt
win32: {
    INCLUDEPATH += $${top_srcdir}/third_party/qca/include
    INCLUDEPATH += $${top_srcdir}/third_party/qca-build
    LIBS += -L $${top_srcdir}/third_party/qca-build/lib -lqca
} else {
    LIBS += -lqca-qt5
}
