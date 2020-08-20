QT       += webenginewidgets network

INCLUDEPATH     += $$PWD/src

HEADERS += \
    $$PWD/src/browserwindow.h

SOURCES += \
    $$PWD/src/browserwindow.cpp

DEFINES         += BUILD_WITH_WEBVIEW
