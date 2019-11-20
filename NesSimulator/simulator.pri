#-------------------------------------------------
# NES模拟器，功能不全，放弃
#-------------------------------------------------

INCLUDEPATH     += $$PWD

include($$PWD/nes/nes.pri)

HEADERS += \
    $$PWD/nessimulator.h

SOURCES += \
    $$PWD/nessimulator.cpp


DEFINES     += BUILD_WIN_NES
