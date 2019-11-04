INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD

win32 {
LIBS += -L$$PWD/winlib/ -lavcodec -lavfilter -lavformat -lswscale -lavutil
}

unix {
LIBS += -L$$PWD/linuxlib/ -lavfilter -lavformat -lavdevice -lavcodec -lswscale -lavutil -lswresample -lpthread -lm -lrt -ldl
}

HEADERS += \
    $$PWD/qffmpegobject.h

SOURCES += \
    $$PWD/qffmpegobject.cpp
