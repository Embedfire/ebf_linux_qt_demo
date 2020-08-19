INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD

unix {
LIBS += -L$$PWD/linuxlib/ -lavfilter -lavformat -lavdevice -lavcodec -lswscale -lavutil -lswresample -lpthread -lm -lrt -ldl
}

HEADERS += \
    $$PWD/qffmpegobject.h

SOURCES += \
    $$PWD/qffmpegobject.cpp

