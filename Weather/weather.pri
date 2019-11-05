#-------------------------------------------------
# 15天天气预报
#-------------------------------------------------

INCLUDEPATH         += $$PWD/src

HEADERS += \
    $$PWD/src/json.h \
    $$PWD/src/citybook.h \
    $$PWD/src/weatherwidget.h \
    $$PWD/src/weatherapi.h \
    $$PWD/src/qtrefreshbutton.h \
    $$PWD/src/citymanagerwidget.h

SOURCES += \
    $$PWD/src/json.cpp \
    $$PWD/src/citybook.cpp \
    $$PWD/src/weatherwidget.cpp \
    $$PWD/src/weatherapi.cpp \
    $$PWD/src/qtrefreshbutton.cpp \
    $$PWD/src/citymanagerwidget.cpp
