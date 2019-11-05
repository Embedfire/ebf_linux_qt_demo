#-------------------------------------------------
# 陀螺仪测试
#-------------------------------------------------

INCLUDEPATH         += $$PWD/src

HEADERS += \
    $$PWD/src/gyroscope.h \
    $$PWD/src/mpu6050thread.h

SOURCES += \
    $$PWD/src/gyroscope.cpp \
    $$PWD/src/mpu6050thread.cpp


DEFINES     += USE_TEXT_BOARD
