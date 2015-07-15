SOURCES = main.cpp
QT = core
CONFIG = qt c++11
exists($${top_srcdir}/third_party/qca):exists($${top_srcdir}/third_party/qca-build) {
    INCLUDEPATH += $${top_srcdir}/third_party/qca/include
    INCLUDEPATH += $${top_srcdir}/third_party/qca-build
    LIBS += -L $${top_srcdir}/third_party/qca-build/lib -lqca
} else {
    LIBS += -lqca-qt5
}
