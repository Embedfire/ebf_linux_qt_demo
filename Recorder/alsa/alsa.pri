HEADERS += \
    $$PWD/sndwav_common.h \
    $$PWD/wav_parser.h \
    $$PWD/wavobject.h \
    $$PWD/sndwavrecord.h

SOURCES += \
    $$PWD/wavobject.cpp \
    $$PWD/sndwav_common.cpp \
    $$PWD/wav_parser.cpp \
    $$PWD/sndwavrecord.cpp


FORMS +=


INCLUDEPATH     += $$PWD

unix { LIBS             += -lasound }
