/******************************************************************
 Copyright (C) 2016 - All Rights Reserved by
 重庆重邮汇测通信技术有限公司
 文 件 名 :
 作 者    : Niyh
 编写日期 :
 说 明    :
 历史纪录 : %TIME%
 <作者>    <日期>        <版本>        <内容>
 倪又华    2016/8/3    1.0.0.0 1     文件创建
*******************************************************************/
#include "sndwavrecord.h"

#include <QFile>
#include <QTextStream>

#define DEFAULT_CHANNELS         (2)
#define DEFAULT_SAMPLE_RATE      (8000)
#define DEFAULT_SAMPLE_LENGTH    (16)
#define DEFAULT_DURATION_TIME    (10)


SndWavRecord::SndWavRecord(QObject *parent) :
    SndWavObj(parent)
{


}

SndWavRecord::~SndWavRecord()
{

}


int SndWavRecord::SNDWAV_PrepareWAVParams(WAVContainer_t *wav)
{
    assert(wav);

    uint16_t channels = DEFAULT_CHANNELS;
    uint16_t sample_rate = DEFAULT_SAMPLE_RATE;
    uint16_t sample_length = DEFAULT_SAMPLE_LENGTH;
    uint32_t duration_time = DEFAULT_DURATION_TIME;

    /* Const */
    wav->header.magic = WAV_RIFF;
    wav->header.type = WAV_WAVE;
    wav->format.magic = WAV_FMT;
    wav->format.fmt_size = LE_INT(16);
    wav->format.format = LE_SHORT(WAV_FMT_PCM);
    wav->chunk.type = WAV_DATA;

    /* User definition */
    wav->format.channels = LE_SHORT(channels);
    wav->format.sample_rate = LE_INT(sample_rate);
    wav->format.sample_length = LE_SHORT(sample_length);

    /* See format of wav file */
    wav->format.blocks_align = LE_SHORT(channels * sample_length / 8);
    wav->format.bytes_p_second = LE_INT((uint16_t)(wav->format.blocks_align) * sample_rate);

    wav->chunk.length = LE_INT(duration_time * (uint32_t)(wav->format.bytes_p_second));
    wav->header.length = LE_INT((uint32_t)(wav->chunk.length) + \
                                sizeof(wav->chunk) + sizeof(wav->format) + sizeof(wav->header) - 8);

    return 0;
}

void SndWavRecord::SNDWAV_Record(SNDPCMContainer_t *sndpcm, WAVContainer_t *wav, int fd)
{
    off64_t rest;
    size_t c, frame_size;

    if (WAV_WriteHeader(fd, wav) < 0) {
        return;
    }

    rest = wav->chunk.length;


    QFile file("/opt/test.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate);
    QTextStream in(&file);

    while (rest > 0) {
        c = (rest <= (off64_t)sndpcm->chunk_bytes) ? (size_t)rest : sndpcm->chunk_bytes;
        frame_size = c * 8 / sndpcm->bits_per_frame;
        if (SNDWAV_ReadPcm(sndpcm, frame_size) != frame_size)
            break;

        if (write(fd, sndpcm->data_buf, c) != c) {
            fprintf(stderr, "Error SNDWAV_Record[write]\n");
            return;
        }

        in << QString("%1").arg(*sndpcm->data_buf) << endl;

        rest -= c;
    }
    file.close();
}

// 录音
int SndWavRecord::record(char *filename)
{
    const char *devicename = "default";
    int fd;
    WAVContainer_t wav;
    SNDPCMContainer_t record;

    memset(&record, 0x0, sizeof(record));

    ::remove(filename);
    if ((fd = open(filename, O_WRONLY | O_CREAT, 0644)) == -1) {
        fprintf(stderr, "Error open: [%s]\n", filename);
        return -1;
    }

    if (snd_output_stdio_attach(&record.log, stderr, 0) < 0) {
        fprintf(stderr, "Error snd_output_stdio_attach\n");
        goto Err;
    }

    if (snd_pcm_open(&record.handle, devicename, SND_PCM_STREAM_CAPTURE, 0) < 0) {
        fprintf(stderr, "Error snd_pcm_open [ %s]\n", devicename);
        goto Err;
    }

    if (SNDWAV_PrepareWAVParams(&wav) < 0) {
        fprintf(stderr, "Error SNDWAV_PrepareWAVParams\n");
        goto Err;
    }

    if (SNDWAV_SetParams(&record, &wav) < 0) {
        fprintf(stderr, "Error set_snd_pcm_params\n");
        goto Err;
    }

    snd_pcm_dump(record.handle, record.log);

    SNDWAV_Record(&record, &wav, fd);

    snd_pcm_drain(record.handle);

    close(fd);
    free(record.data_buf);
    snd_output_close(record.log);
    snd_pcm_close(record.handle);
    return 0;

Err:
    close(fd);
    remove(filename);
    if (record.data_buf) free(record.data_buf);
    if (record.log) snd_output_close(record.log);
    if (record.handle) snd_pcm_close(record.handle);
    return -1;
}

void SndWavRecord::run()
{

}

