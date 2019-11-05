#-------------------------------------------------
# 温湿度采集
#-------------------------------------------------

INCLUDEPATH  += $$PWD/src

HEADERS += \
    $$PWD/src/dhtcollection.h \
    $$PWD/src/displayrealdata.h \
    $$PWD/src/displayrecorddata.h

SOURCES += \
    $$PWD/src/dhtcollection.cpp \
    $$PWD/src/displayrealdata.cpp \
    $$PWD/src/displayrecorddata.cpp
