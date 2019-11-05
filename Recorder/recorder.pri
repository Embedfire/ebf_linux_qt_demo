#-------------------------------------------------
# 录音机
#-------------------------------------------------

INCLUDEPATH += $$PWD/src

HEADERS += \
    $$PWD/src/recorderwidget.h \
    $$PWD/src/arecordwidget.h \
    $$PWD/src/wavplaylistwidget.h

SOURCES += \
    $$PWD/src/recorderwidget.cpp \
    $$PWD/src/arecordwidget.cpp \
    $$PWD/src/wavplaylistwidget.cpp

unix {include($$PWD/alsa/alsa.pri)}
