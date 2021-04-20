INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/InfoNES.h \
    $$PWD/InfoNES_Mapper.h \
    $$PWD/InfoNES_System.h \
    $$PWD/InfoNES_Types.h \
    $$PWD/InfoNES_pAPU.h \
    $$PWD/K6502.h \
    $$PWD/K6502_rw.h

SOURCES += \
    $$PWD/InfoNES.cpp \
    $$PWD/InfoNES_Mapper.cpp \
    $$PWD/InfoNES_pAPU.cpp \
    $$PWD/K6502.cpp

unix {
    $$PWD/linux/joypad_input.cpp
}
