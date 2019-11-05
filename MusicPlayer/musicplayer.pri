#-------------------------------------------------
# 音乐播放器
#-------------------------------------------------

INCLUDEPATH     += $$PWD/src

HEADERS += \
    $$PWD/src/netdownlyric.h \
    $$PWD/src/musicplayer.h \
    $$PWD/src/lyricwidget.h \
    $$PWD/src/lyricfactory.h \
    $$PWD/src/widgettoolbar.h \
    $$PWD/src/widgetrecord.h \
    $$PWD/src/musicplaylistwidget.h \
    $$PWD/src/equalizewidget.h \
    $$PWD/src/mp3infoobject.h

SOURCES += \
    $$PWD/src/netdownlyric.cpp \
    $$PWD/src/musicplayer.cpp \
    $$PWD/src/lyricwidget.cpp \
    $$PWD/src/lyricfactory.cpp \
    $$PWD/src/widgettoolbar.cpp \
    $$PWD/src/widgetrecord.cpp \
    $$PWD/src/musicplaylistwidget.cpp \
    $$PWD/src/equalizewidget.cpp \
    $$PWD/src/mp3infoobject.cpp


# add ffmpeg lib
include($$PWD/../ffmpeg/ffmpeg.pri)
