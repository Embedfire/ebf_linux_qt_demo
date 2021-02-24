#-------------------------------------------------
# 照相机
#-------------------------------------------------

INCLUDEPATH         += $$PWD/src

HEADERS += \
    $$PWD/src/camerawidget.h \
    $$PWD/src/cameraconfig.h \
    $$PWD/src/qtviewfinder.h

SOURCES += \
    $$PWD/src/camerawidget.cpp \
    $$PWD/src/cameraconfig.cpp \
    $$PWD/src/qtviewfinder.cpp



#DEFINES     += LIB_V4L2
if(contains(DEFINES,LIB_V4L2)){
INCLUDEPATH += $$PWD/../thirdpart/libv4l2/include
LIBS += -L$$PWD/../thirdpart/libv4l2/lib -lv4l2Cam
}
