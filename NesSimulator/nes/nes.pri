INCLUDEPATH     += $$PWD

HEADERS += \
    $$PWD/common.h \
    $$PWD/cpu.h \
    $$PWD/cpu-internal.h \
    $$PWD/fce.h \
    $$PWD/gamewidget.h \
    $$PWD/hal.h \
    $$PWD/memory.h \
    $$PWD/mmc.h \
    $$PWD/nes.h \
    $$PWD/ppu.h \
    $$PWD/ppu-internal.h \
    $$PWD/psg.h

SOURCES += \
    $$PWD/common.cpp \
    $$PWD/cpu.cpp \
    $$PWD/cpu-addressing.cpp \
    $$PWD/fce.cpp \
    $$PWD/gamewidget.cpp \
    $$PWD/hal.cpp \
    $$PWD/memory.cpp \
    $$PWD/mmc.cpp \
    $$PWD/ppu.cpp \
    $$PWD/psg.cpp
