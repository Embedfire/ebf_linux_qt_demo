#ifndef WAVOBJECT_H
#define WAVOBJECT_H

#include <QThread>

#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <locale.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <assert.h>
#include <QMutex>

#ifdef Q_OS_UNIX
#include <alsa/asoundlib.h>
#endif
#include "sndwavrecord.h"

//typedef long long off64_t;

#if __BYTE_ORDER == __LITTLE_ENDIAN
#define COMPOSE_ID(a,b,c,d)	((a) | ((b)<<8) | ((c)<<16) | ((d)<<24))
#define LE_SHORT(v)		      (v)
#define LE_INT(v)		        (v)
#define BE_SHORT(v)		      bswap_16(v)
#define BE_INT(v)		        bswap_32(v)
#elif __BYTE_ORDER == __BIG_ENDIAN
#define COMPOSE_ID(a,b,c,d)	((d) | ((c)<<8) | ((b)<<16) | ((a)<<24))
#define LE_SHORT(v)		      bswap_16(v)
#define LE_INT(v)		        bswap_32(v)
#define BE_SHORT(v)		      (v)
#define BE_INT(v)		        (v)
#else
#error "Wrong endian"
#endif

#define WAV_RIFF		COMPOSE_ID('R','I','F','F')
#define WAV_WAVE		COMPOSE_ID('W','A','V','E')
#define WAV_FMT			COMPOSE_ID('f','m','t',' ')
#define WAV_DATA		COMPOSE_ID('d','a','t','a')

/* WAVE fmt block constants from Microsoft mmreg.h header */
#define WAV_FMT_PCM             0x0001
#define WAV_FMT_IEEE_FLOAT      0x0003
#define WAV_FMT_DOLBY_AC3_SPDIF 0x0092
#define WAV_FMT_EXTENSIBLE      0xfffe

/* Used with WAV_FMT_EXTENSIBLE format */
#define WAV_GUID_TAG		"/x00/x00/x00/x00/x10/x00/x80/x00/x00/xAA/x00/x38/x9B/x71"


// wav格式
typedef struct  {
    char rld[4];               // riff 标志符号
    int rLen;
    char wld[4];               // 格式类型（wave）
    char fld[4];               // "fmt"

    int fLen;                   // sizeof(wave format matex)

    short wFormatTag;           // 编码格式
    short wChannels;            // 声道数
    int nSamplesPersec ;        // 采样频率
    int nAvgBitsPerSample;      // WAVE文件采样大小
    short wBlockAlign;          // 块对齐
    short wBitsPerSample;       // WAVE文件采样大小

    char dld[4];                // ”data“
    int wSampleLength;          // 音频数据的大小

} s_wavhead_t;

typedef enum {
    WAV_PLAY        = 1,
    WAV_RECORD      = 2,
} E_WAV_TYPE;

class WavObject : public QThread
{
    Q_OBJECT
public:

    static WavObject *Instance()
    {
        static QMutex mutex;

        if (!self) {
            QMutexLocker locker(&mutex);

            if (!self) {
                self = new WavObject;
            }
        }

        return self;
    }

    explicit WavObject(QObject *parent = 0);
    // 设置录音音量
    int setRecodeVolume(int value);
    // 设置播放音量
    int setPlayVolume(int value);

    void pause();

    void startTest(int nType, QString strFile);
    QString stopTest();
signals:

public slots:

private:
    SNDPCMContainer_t s_sndpcm_t;

    int m_nfd;
    bool m_bRun;
    bool m_bPause;

    int m_nType;
    QString m_strWavName;
private:
    static WavObject *self;

    SndWavRecord *record;
    // 播放录音
    int playWav(const char *fileName);
    // 开始录音
    int recordWav(int fd);

    ssize_t SNDWAV_P_SaveRead(int fd, void *buf, size_t count);
    void SNDWAV_Play(SNDPCMContainer_t *sndpcm, WAVContainer_t *wav, int fd);

    void SNDWAV_Record(SNDPCMContainer_t *sndpcm, WAVContainer_t *wav, int fd);
    int SNDWAV_PrepareWAVParams(WAVContainer_t *wav);

    // parse
    int WAV_P_CheckValid(WAVContainer_t *container);
    int WAV_ReadHeader(int fd, WAVContainer_t *container);

    int WAV_WriteHeader(int fd, WAVContainer_t *container);
    void WAV_P_PrintHeader(WAVContainer_t *container);
//    char *WAV_P_FmtString(uint16_t fmt);

    //
    int SNDWAV_SetParams(SNDPCMContainer_t *sndpcm, WAVContainer_t *wav);
    int SNDWAV_P_GetFormat(WAVContainer_t *wav, snd_pcm_format_t *snd_format);
    ssize_t SNDWAV_ReadPcm(SNDPCMContainer_t *sndpcm, size_t rcount);
    ssize_t SNDWAV_WritePcm(SNDPCMContainer_t *sndpcm, size_t wcount);

    int set_pcm_play(FILE *fp, s_wavhead_t *wav_header_t);

protected:
    void run();
};

#endif // WAVOBJECT_H
