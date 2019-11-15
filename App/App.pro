#-------------------------------------------------
#
# Project created by QtCreator 2019-08-27T16:03:48
# Qt5-demo 综合代码
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia multimediawidgets

TARGET = App
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    statusbarwidget.cpp \
    threadkey.cpp \
    threadmousecheck.cpp

HEADERS += \
        mainwindow.h \
    statusbarwidget.h \
    threadkey.h \
    threadmousecheck.h

include($$PWD/common/common.pri)
include($$PWD/ui/ui.pri)

include($$PWD/../AdcViewer/adcviewer.pri)
include($$PWD/../BackLight/backlight.pri)
include($$PWD/../Beep/beep.pri)
include($$PWD/../Calendar/calendar.pri)
include($$PWD/../Calculator/calculator.pri)
include($$PWD/../Camera/camera.pri)
include($$PWD/../CarMeter/carmeter.pri)
include($$PWD/../DhtCollection/dht.pri)
include($$PWD/../EBook/ebook.pri)
include($$PWD/../FileSystem/filesystem.pri)
include($$PWD/../Gyroscope/gyroscope.pri)
include($$PWD/../KeyPressTest/keypress.pri)
include($$PWD/../MusicPlayer/musicplayer.pri)
include($$PWD/../NotePad/notepad.pri)
include($$PWD/../Photos/photos.pri)
include($$PWD/../Recorder/recorder.pri)
include($$PWD/../RgbLight/rgblight.pri)
include($$PWD/../Settings/settings.pri)
include($$PWD/../VideoPlayer/videoplayer.pri)
include($$PWD/../Weather/weather.pri)
#
include($$PWD/../InfoNes/infones.pri)
include($$PWD/../NesSimulator/simulator.pri)

#unix {include($$PWD/../WebBrowser/webbrowser.pri)}

#add libs
INCLUDEPATH += $$PWD/../thirdpart/libqui/include
LIBS += -L$$PWD/../thirdpart/libqui/lib -lQtUi

INCLUDEPATH += $$PWD/../thirdpart/libskin/include
LIBS += -L$$PWD/../thirdpart/libskin/lib -lSkin

#temp file
DESTDIR         = $$PWD/../app_bin
MOC_DIR         = $$PWD/../build/app
OBJECTS_DIR     = $$PWD/../build/app

win32 {
    src_dir = $$PWD\\..\\thirdpart\\libqui\\lib\\*.dll
    skin_lib = $$PWD\\..\\thirdpart\\libskin\\lib\\Skin.dll
    dst_dir = $$PWD\\..\\app_bin\\
    # dst_dir 最后的 \\ 是必须的，用来标示 xcopy 到一个文件夹，若不存在，创建之

    # Replace slashes in paths with backslashes for Windows
    src_dir ~= s,/,\\,g
    skin_lib ~= s,/,\\,g
    dst_dir ~= s,/,\\,g

    system(xcopy $$src_dir $$dst_dir /y /e)
    system(xcopy $$skin_lib $$dst_dir /y /e)
}


#编译HDMI版本，方便适配大屏显示
DEFINES      += BUILD_WITH_HDMI


TRANSLATIONS    = qt_zh.ts qt_en.ts
