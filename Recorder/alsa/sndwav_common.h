#ifndef __SNDWAV_COMMON_H
#define __SNDWAV_COMMON_H

#include "wav_parser.h"

typedef long long off64_t;

typedef struct SNDPCMContainer {
    snd_pcm_t *handle;
    snd_output_t *log;
    snd_pcm_uframes_t chunk_size;
    snd_pcm_uframes_t buffer_size;
    snd_pcm_format_t format;
    uint16_t channels;
    size_t chunk_bytes;
    size_t bits_per_sample;
    size_t bits_per_frame;

    uint8_t *data_buf;
} SNDPCMContainer_t;

class SndWavObj : public WavParser {
    Q_OBJECT
public:
    explicit SndWavObj(QObject *parent = 0);
    ssize_t SNDWAV_ReadPcm(SNDPCMContainer_t *sndpcm, size_t rcount);

    ssize_t SNDWAV_WritePcm(SNDPCMContainer_t *sndpcm, size_t wcount);

    int SNDWAV_SetParams(SNDPCMContainer_t *sndpcm, WAVContainer_t *wav);
    int SNDWAV_P_GetFormat(WAVContainer_t *wav, snd_pcm_format_t *snd_format);
};
#endif /* #ifndef __SNDWAV_COMMON_H */
