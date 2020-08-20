#-------------------------------------------------
#
# Project created by QtCreator 2018-08-27T16:35:30
#
#-------------------------------------------------

QT       -= gui

TARGET = v4l2Cam
TEMPLATE = lib

DEFINES += V4L2CAM_LIBRARY

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
        v4l2cam.cpp

HEADERS += \
        v4l2cam.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DEFINES        += QtV4l2

DESTDIR         = $$PWD/../thirdpart/libv4l2/lib
MOC_DIR         = $$PWD/../build/v4l2
OBJECTS_DIR     = $$PWD/../build/v4l2


unix {
    src_dir = $$PWD/*.h
    dst_dir = $$PWD/../thirdpart/libv4l2/include/

    !exists($$dst_dir): system(mkdir -p $$dst_dir)

    system(cp $$src_dir $$dst_dir -arf )
}
