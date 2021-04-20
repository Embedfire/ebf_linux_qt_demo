
INCLUDEPATH         += $$PWD

SOURCES += \
    $$PWD/controlhandlewidget.cpp \
    #$$PWD/nesemulatewindow.cpp \
    $$PWD/nesscreenwidget.cpp \
    $$PWD/neswidget.cpp

HEADERS += \
    $$PWD/controlhandlewidget.h \
    #$$PWD/nesemulatewindow.h \
    $$PWD/nesscreenwidget.h \
    $$PWD/neswidget.h

include($$PWD/audio/audio.pri)
include($$PWD/infones/infones.pri)
