INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD

#用于区分 ARM或UBUNTU
#DEFINES      += ARM_X64
DEFINES      += LINUX_UBUNTU

win32 {
LIBS += -L$$PWD/winlib/ -lavcodec -lavfilter -lavformat -lswscale -lavutil
}

#unix {
#    LIBS += -L/usr/local/ffmpeg/lib/ -lavfilter -lavformat -lavdevice -lavcodec -lswscale -lavutil -lswresample -lpthread -lm -lrt -ldl
#    #LIBS += -L$$PWD/linuxlib/ -lavfilter -lavformat -lavdevice -lavcodec -lswscale -lavutil -lswresample -lpthread -lm -lrt -ldl
#}

cross_compile{
    LIBS += -L$$PWD/armlib/ -lavfilter -lavformat -lavdevice -lavcodec -lswscale -lavutil -lswresample -lpthread -lm -lrt -ldl
}


HEADERS += \
    $$PWD/qffmpegobject.h

SOURCES += \
    $$PWD/qffmpegobject.cpp
