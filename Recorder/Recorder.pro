#-------------------------------------------------
#
# Project created by QtCreator 2019-10-10T20:59:01
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Recorder
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


SOURCES += main.cpp

include($$PWD/recorder.pri)

INCLUDEPATH += $$PWD/../thirdpart/libqui/include
LIBS += -L$$PWD/../thirdpart/libqui/lib -lQtUi

INCLUDEPATH += $$PWD/../thirdpart/libskin/include
LIBS += -L$$PWD/../thirdpart/libskin/lib -lSkin

#temp file
DESTDIR         = $$PWD/../app_bin
MOC_DIR         = $$PWD/../build/record
OBJECTS_DIR     = $$PWD/../build/record
