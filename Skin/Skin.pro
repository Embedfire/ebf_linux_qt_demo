#-------------------------------------------------
#
# Project created by QtCreator 2019-08-31T11:16:39
# App皮肤文件
#
#-------------------------------------------------

QT       -= gui

TARGET = Skin
TEMPLATE = lib

DEFINES += SKIN_LIBRARY

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
        skin.cpp

HEADERS += \
        skin.h

CONFIG += resources_big

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DESTDIR         = $$PWD/../thirdpart/libskin/lib
MOC_DIR         = $$PWD/../build/skin
OBJECTS_DIR     = $$PWD/../build/skin

DEFINES         += QtSkin

RESOURCES += \
    images.qrc

win32 {
    src_dir = $$PWD\\*.h
    dst_dir = $$PWD\\..\\thirdpart\\libskin\\include\\
    # dst_dir 最后的 \\ 是必须的，用来标示 xcopy 到一个文件夹，若不存在，创建之

    # Replace slashes in paths with backslashes for Windows
    src_dir ~= s,/,\\,g
    dst_dir ~= s,/,\\,g

    system(xcopy $$src_dir $$dst_dir /y /e)
}

unix {
    src_dir = $$PWD/*.h
    dst_dir = $$PWD/../thirdpart/libskin/include/

    !exists($$dst_dir): system(mkdir -p $$dst_dir)

    system(cp $$src_dir $$dst_dir -arf )
}
