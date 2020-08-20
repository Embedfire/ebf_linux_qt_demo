#-------------------------------------------------
#
# Project created by QtCreator 2019-09-02T10:55:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WebBrowser
TEMPLATE = app


SOURCES += main.cpp

include($$PWD/webbrowser.pri)

INCLUDEPATH += $$PWD/../thirdpart/libqui/include
LIBS += -L$$PWD/../thirdpart/libqui/lib -lQtUi

INCLUDEPATH += $$PWD/../thirdpart/libskin/include
LIBS += -L$$PWD/../thirdpart/libskin/lib -lSkin

#temp file
DESTDIR         = $$PWD/../app_bin
MOC_DIR         = $$PWD/../build/browser
OBJECTS_DIR     = $$PWD/../build/browser
DEFINES         += BUILD_BY_PRO
