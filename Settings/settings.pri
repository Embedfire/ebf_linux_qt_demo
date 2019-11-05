#-------------------------------------------------
# 系统设置
#-------------------------------------------------

INCLUDEPATH     += $$PWD/src

HEADERS += \
    $$PWD/src/settingwidget.h \
    $$PWD/src/settingmainpage.h \
    $$PWD/src/aboutboard.h \
    $$PWD/src/backlightpage.h \
    $$PWD/src/datetimesettingpage.h \
    $$PWD/src/clickedwidget.h \
    $$PWD/src/versionupdatepage.h \
    $$PWD/src/downloadnetworkmanager.h

SOURCES += \
    $$PWD/src/settingwidget.cpp \
    $$PWD/src/settingmainpage.cpp \
    $$PWD/src/aboutboard.cpp \
    $$PWD/src/backlightpage.cpp \
    $$PWD/src/datetimesettingpage.cpp \
    $$PWD/src/clickedwidget.cpp \
    $$PWD/src/versionupdatepage.cpp \
    $$PWD/src/downloadnetworkmanager.cpp

win32 {
INCLUDEPATH += $$PWD/../thirdpart/quazip
LIBS += -L$$PWD/../thirdpart/libzip -lquazip
}
