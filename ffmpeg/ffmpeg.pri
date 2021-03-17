INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD

#用于区分 ARM或UBUNTU
DEFINES      += ARM_X64
#DEFINES      += LINUX_UBUNTU

win32 {
LIBS += -L$$PWD/winlib/ -lavcodec -lavfilter -lavformat -lswscale -lavutil
}

if(contains(DEFINES,ARM_X64))
{
    unix {
    LIBS += -L$$PWD/armlib/ -lavfilter -lavformat -lavdevice -lavcodec -lswscale -lavutil -lswresample -lpthread -lm -lrt -ldl
    }
}

if(contains(DEFINES,LINUX_UBUNTU))
{
#    unix {
#    LIBS += -L$$PWD/linuxlib/ -lavfilter -lavformat -lavdevice -lavcodec -lswscale -lavutil -lswresample -lpthread -lm -lrt -ldl
#    }

    unix {
    LIBS += -L/usr/local/ffmpeg/lib/ -lavfilter -lavformat -lavdevice -lavcodec -lswscale -lavutil -lswresample -lpthread -lm -lrt -ldl
    }
}



HEADERS += \
    $$PWD/qffmpegobject.h

SOURCES += \
    $$PWD/qffmpegobject.cpp
