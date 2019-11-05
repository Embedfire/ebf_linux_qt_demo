#-------------------------------------------------
#
# Project created by QtCreator 2019-04-19T11:05:29
# App的基础控件库，自定义，可以移植
#
#-------------------------------------------------

QT       += network multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtUi
TEMPLATE = lib

DEFINES += QTUI_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS +=  $$PWD/include/qtui_global.h
HEADERS +=  $$PWD/include/QtUi

include($$PWD/src/src.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH     += $$PWD/include
DEFINES         += QtUi

DESTDIR         = $$PWD/../thirdpart/libqui/lib
MOC_DIR         = $$PWD/../build/qui
OBJECTS_DIR     = $$PWD/../build/qui

win32 {
    isexists = false;
    src_dir = $$PWD\src\*.h
    QtUi = $$PWD\include\QtUi
    dst_dir = $$PWD\\..\\thirdpart\\libqui\\include\\
    # dst_dir 最后的 \\ 是必须的，用来标示 xcopy 到一个文件夹，若不存在，创建之

    # Replace slashes in paths with backslashes for Windows
    src_dir ~= s,/,\\,g
    QtUi ~= s,/,\\,g
    dst_dir ~= s,/,\\,g
    exists($$dst_dir): isexists = true

    system(xcopy $$src_dir $$dst_dir /y /e)
#    !$$isexists: system(xcopy $$src_dir $$dst_dir /y /e)
#    !$$isexists: system(xcopy $$QtUi $$dst_dir /y /e)
}


unix {
    src_dir = $$PWD/src/*.h
    QtUi = $$PWD/include/QtUi
    dst_dir = $$PWD/../thirdpart/libqui/include/

    !exists($$dst_dir): system(mkdir -p $$dst_dir)

    system(cp $$src_dir $$dst_dir -arf)
    system(cp $$QtUi $$dst_dir -arf)
}
