#-------------------------------------------------
# 15天天气预报
#-------------------------------------------------

INCLUDEPATH         += $$PWD/src

HEADERS += \
    $$PWD/src/json.h \
    $$PWD/src/citybook.h \
    $$PWD/src/weatherwidget.h \
    $$PWD/src/weatherapi.h \
    $$PWD/src/citymanagerwidget.h \
    $$PWD/src/qtwaitwidget.h

SOURCES += \
    $$PWD/src/json.cpp \
    $$PWD/src/citybook.cpp \
    $$PWD/src/weatherwidget.cpp \
    $$PWD/src/weatherapi.cpp \
    $$PWD/src/citymanagerwidget.cpp \
    $$PWD/src/qtwaitwidget.cpp
