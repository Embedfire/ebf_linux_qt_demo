#include "wavobject.h"

#include <QProcess>
#include <QFile>
#include <QDebug>

#define DEFAULT_CHANNELS         (1)
#define DEFAULT_SAMPLE_RATE      (8000)
#define DEFAULT_SAMPLE_LENGTH    (16)
#define DEFAULT_DURATION_TIME    (30)

WavObject *WavObject::self = 0;

WavObject::WavObject(QObject *parent) :
    QThread(parent),m_nfd(0)
{
    m_bRun = false;
    m_bPause = false;
    m_nType = 1;
    m_strWavName = "";

    record = new SndWavRecord(this);
}

ssize_t WavObject::SNDWAV_P_SaveRead(int fd, void *buf, size_t count)
{
    ssize_t result = 0, res;

    while (count > 0) {
        if ((res = read(fd, buf, count)) == 0)
            break;
        if (res < 0)
            return result > 0 ? result : res;
        count -= res;
        result += res;
        buf = (char *)buf + res;
    }
    return result;
}

void WavObject::SNDWAV_Play(SNDPCMContainer_t *sndpcm, WAVContainer_t *wav, int fd)
{
    int load, ret;
    off64_t written = 0;
    off64_t c;
    off64_t count = LE_INT(wav->chunk.length);

    load = 0;
    while (written < count) {
        /* Must read [chunk_bytes] bytes data enough. */
        do {
            c = count - written;
            if (c > sndpcm->chunk_bytes)
                c = sndpcm->chunk_bytes;
            c -= load;

            if (c == 0)
                break;
            ret = SNDWAV_P_SaveRead(fd, sndpcm->data_buf + load, c);
            if (ret < 0) {
                fprintf(stderr, "Error safe_read\n");
                return;
            }
            if (ret == 0)
                break;
            load += ret;
            // 用户终止
            if (!m_bRun) break;
        } while ((size_t)load < sndpcm->chunk_bytes);

        /* Transfer to size frame */
        load = load * 8 / sndpcm->bits_per_frame;
        ret = SNDWAV_WritePcm(sndpcm, load);
        if (ret != load)
            break;

        ret = ret * sndpcm->bits_per_frame / 8;
        written += ret;
        load = 0;
        // 用户终止
        if (!m_bRun) break;
    }
}

// 播放wav文件
int WavObject::playWav(const char *fileName)
{
    FILE *fp;
    fp = fopen(fileName, "rb");

    if(NULL == fp)
    {
        perror("open file failed:\n");
        return -1;
    }

    // 头文件信息
    s_wavhead_t wav_header;
    memset(&wav_header, 0x00, sizeof(s_wavhead_t));

    // 读取数据区
    fread(&wav_header, 1, sizeof(s_wavhead_t), fp);
    set_pcm_play(fp, &wav_header);
    fclose(fp);
    return 0;
}

//  解析wav参数
int WavObject::SNDWAV_PrepareWAVParams(WAVContainer_t *wav)
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
    wav->header.length = LE_INT((uint32_t)(wav->chunk.length) + sizeof(wav->chunk) + sizeof(wav->format) + sizeof(wav->header) - 8);

    return 0;
}

void WavObject::SNDWAV_Record(SNDPCMContainer_t *sndpcm, WAVContainer_t *wav, int fd)
{
    off64_t rest;
    size_t c, frame_size, ntemp;

    if (WAV_WriteHeader(fd, wav) < 0) {
        return;
    }

    rest = wav->chunk.length;
    while (rest > 0) {
        if (!m_bRun) break;

        if (m_bPause) {
            msleep(100);
            continue;
        }

        c = (rest <= (off64_t)sndpcm->chunk_bytes) ? (size_t)rest : sndpcm->chunk_bytes;
        frame_size = c * 8 / sndpcm->bits_per_frame;
        ntemp = SNDWAV_ReadPcm(sndpcm, frame_size);
        if (ntemp != frame_size)
            break;

        if (write(fd, sndpcm->data_buf, c) != (ssize_t)c) {
//            myError("SNDWAV_Record[write]" << write);
            return;
        }

        rest -= c;
    }
}

/**
 * @brief WavObject::recordWav 录音
 * @param filename
 * @return
 */
int WavObject::recordWav(int fd)
{
    const char *devicename = "default";
    WAVContainer_t wav;

    if (snd_output_stdio_attach(&s_sndpcm_t.log, stderr, 0) < 0) {
//        myError("snd_output_stdio_attach");
        goto Err;
    }

    // 打开pcm设备
    if (snd_pcm_open(&s_sndpcm_t.handle, devicename, SND_PCM_STREAM_CAPTURE, 0) < 0) {
//        myError("snd_pcm_open: " << devicename);
        goto Err;
    }

    // 配置wav采样信息
    if (SNDWAV_PrepareWAVParams(&wav) < 0) {
//        myError("SNDWAV_PrepareWAVParams");
        goto Err;
    }

    if (SNDWAV_SetParams(&s_sndpcm_t, &wav) < 0) {
//        myError("Error set_snd_pcm_params");
        goto Err;
    }

    snd_pcm_dump(s_sndpcm_t.handle, s_sndpcm_t.log);

    SNDWAV_Record(&s_sndpcm_t, &wav, fd);

    snd_pcm_drain(s_sndpcm_t.handle);

    close(m_nfd);
    free(s_sndpcm_t.data_buf);
    snd_output_close(s_sndpcm_t.log);
    snd_pcm_close(s_sndpcm_t.handle);
    return 0;
Err:
    close(fd);
    if (s_sndpcm_t.data_buf) free(s_sndpcm_t.data_buf);
    if (s_sndpcm_t.log) snd_output_close(s_sndpcm_t.log);
    if (s_sndpcm_t.handle) snd_pcm_close(s_sndpcm_t.handle);
    return -1;
}

/**
 * @brief WavObject::setRecodeVolum 设置录音音量
 * @param value
 */
int WavObject::setRecodeVolume(int value)
{
    QStringList args = QStringList() << "cset" << "numid=37" << QString::number(value);
    int nret = QProcess::execute("amixer", args);
    return nret;
}

int WavObject::setPlayVolume(int value)
{
    QStringList args = QStringList() << "cset" << "numid=1" << QString::number(value);
    int nret = QProcess::execute("amixer", args);
    return nret;
}

void WavObject::pause()
{
    m_bPause = !m_bPause;
}

void WavObject::run()
{
    m_nfd = -1;

    if (WAV_PLAY == m_nType) {
        playWav(m_strWavName.toLatin1().constData());
    }
    else {

        printf("Recode wav: %d.\n", m_nType);
        if (QFile::exists(m_strWavName)) {
            QFile::remove(m_strWavName);
        }

        if ((m_nfd = open(m_strWavName.toLatin1().constData(), O_WRONLY | O_CREAT, 0644)) == -1) {
//            myDebug("open file failed:" << m_strWavName);
            return;
        }

        memset(&s_sndpcm_t, 0x0, sizeof(s_sndpcm_t));
        recordWav(m_nfd);
    }

//    if (WAV_RECORD == m_nType) {
//        myDebug("stop");
//    }
}

/**
 * @brief WavObject::startTest 开始测试
 * @param nType 播放还是录音
 * @param strFile   音频文件
 */
void WavObject::startTest(int nType, QString strFile)
{
    // 如果有声音文件正在播放和录音，先结束，并响应本次
    stopTest();

    // 初始化参数
    m_nType         = nType;
    m_strWavName    = strFile;
    m_bRun          = true;

    this->start();
}

/**
 * @brief WavObject::stopTest 停止测试
 */
QString WavObject::stopTest()
{
    m_bRun = false;
    QString strFile = m_strWavName;
    m_strWavName = "";

    // 如果有声音文件正在播放和录音，先结束，并响应本次
    if (this->isRunning()) {
        this->quit();
    }

    return strFile;
}

void WavObject::WAV_P_PrintHeader(WAVContainer_t *container)
{
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\n");

    printf("File Magic:         [%c%c%c%c]\n",
           (char)(container->header.magic),
           (char)(container->header.magic >> 8),
           (char)(container->header.magic >> 16),
           (char)(container->header.magic >> 24));
    printf("File Length:        [%d]\n", container->header.length);
    printf("File Type:          [%c%c%c%c]\n",
           (char)(container->header.type),
           (char)(container->header.type >>  8),
           (char)(container->header.type >> 16),
           (char)(container->header.type >> 24));

    printf("\n");

    printf("Fmt Magic:          [%c%c%c%c]\n",
           (char)(container->format.magic),
           (char)(container->format.magic >>  8),
           (char)(container->format.magic >> 16),
           (char)(container->format.magic >> 24));
    printf("Fmt Size:           [%d]\n", container->format.fmt_size);
    //    printf("Fmt Format:         [%s]\n", WAV_P_FmtString(container->format.format));
    printf("Fmt Channels:       [%d]\n", container->format.channels);
    printf("Fmt Sample_rate:    [%d](HZ)\n", container->format.sample_rate);
    printf("Fmt Bytes_p_second: [%d]\n", container->format.bytes_p_second);
    printf("Fmt Blocks_align:   [%d]\n", container->format.blocks_align);
    printf("Fmt Sample_length:  [%d]\n", container->format.sample_length);

    printf("\n");

    printf("Chunk Type:         [%c%c%c%c]\n",
           (char)(container->chunk.type),
           (char)(container->chunk.type >>  8),
           (char)(container->chunk.type >> 16),
           (char)(container->chunk.type >> 24));
    printf("Chunk Length:       [%d]\n", container->chunk.length);

    printf("\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

int WavObject::WAV_P_CheckValid(WAVContainer_t *container)
{
    if (container->header.magic != WAV_RIFF ||
            container->header.type != WAV_WAVE ||
            container->format.magic != WAV_FMT ||
            container->format.fmt_size != LE_INT(16) ||
            (container->format.channels != LE_SHORT(1) && container->format.channels != LE_SHORT(2)) ||
            container->chunk.type != WAV_DATA) {

//        myError("non standard wav file.");
        return -1;
    }

    return 0;
}

// 读取wav头部信息
int WavObject::WAV_ReadHeader(int fd, WAVContainer_t *container)
{
    assert((fd >=0) && container);

    if (read(fd, &container->header, sizeof(container->header)) != sizeof(container->header) ||
            read(fd, &container->format, sizeof(container->format)) != sizeof(container->format) ||
            read(fd, &container->chunk, sizeof(container->chunk)) != sizeof(container->chunk)) {

//        myError("WAV_ReadHeader read error!");
        return -1;
    }

    if (WAV_P_CheckValid(container) < 0)
        return -1;

#ifdef WAV_PRINT_MSG
    WAV_P_PrintHeader(container);
#endif

    return 0;
}

// 写入wav头部信息
int WavObject::WAV_WriteHeader(int fd, WAVContainer_t *container)
{
    assert((fd >=0) && container);

    if (WAV_P_CheckValid(container) < 0)
        return -1;

    if (write(fd, &container->header, sizeof(container->header)) != sizeof(container->header) ||
            write(fd, &container->format, sizeof(container->format)) != sizeof(container->format) ||
            write(fd, &container->chunk, sizeof(container->chunk)) != sizeof(container->chunk)) {

//        myError("WAV_WriteHeader");
        return -1;
    }

#ifdef WAV_PRINT_MSG
    WAV_P_PrintHeader(container);
#endif

    return 0;
}

// 获取wav格式16k/8k
int WavObject::SNDWAV_P_GetFormat(WAVContainer_t *wav, snd_pcm_format_t *snd_format)
{
    if (LE_SHORT(wav->format.format) != WAV_FMT_PCM)
        return -1;

    switch (LE_SHORT(wav->format.sample_length)) {
    case 16:
        *snd_format = SND_PCM_FORMAT_S16_LE;
        break;
    case 8:
        *snd_format = SND_PCM_FORMAT_U8;
        break;
    default:
        *snd_format = SND_PCM_FORMAT_UNKNOWN;
        break;
    }

    return 0;
}

// 读取pcm音频数据
ssize_t WavObject::SNDWAV_ReadPcm(SNDPCMContainer_t *sndpcm, size_t rcount)
{
    ssize_t r;
    size_t result = 0;
    size_t count = rcount;
    uint8_t *data = sndpcm->data_buf;

    if (count != sndpcm->chunk_size) {
        count = sndpcm->chunk_size;
    }

    while (count > 0) {
        r = snd_pcm_readi(sndpcm->handle, data, count);

        if (r == -EAGAIN || (r >= 0 && (size_t)r < count)) {
            snd_pcm_wait(sndpcm->handle, 1000);
        } else if (r == -EPIPE) {
            snd_pcm_prepare(sndpcm->handle);
            fprintf(stderr, "<<<<<<<<<<<<<<< Buffer Underrun >>>>>>>>>>>>>>>\n");
        } else if (r == -ESTRPIPE) {
            fprintf(stderr, "<<<<<<<<<<<<<<< Need suspend >>>>>>>>>>>>>>>\n");
        } else if (r < 0) {
            fprintf(stderr, "Error snd_pcm_writei: [%s]", snd_strerror(r));
            return -1;
        }

        if (r > 0) {
            result += r;
            count -= r;
            data += r * sndpcm->bits_per_frame / 8;
        }
    }
    return rcount;
}

// 写入pcm设备音频信息
ssize_t WavObject::SNDWAV_WritePcm(SNDPCMContainer_t *sndpcm, size_t wcount)
{
    ssize_t r;
    ssize_t result = 0;
    uint8_t *data = sndpcm->data_buf;

    if (wcount < sndpcm->chunk_size) {
        snd_pcm_format_set_silence(sndpcm->format,
                                   data + wcount * sndpcm->bits_per_frame / 8,
                                   (sndpcm->chunk_size - wcount) * sndpcm->channels);
        wcount = sndpcm->chunk_size;
    }
    while (wcount > 0) {
        r = snd_pcm_writei(sndpcm->handle, data, wcount);
        if (r == -EAGAIN || (r >= 0 && (size_t)r < wcount)) {
            snd_pcm_wait(sndpcm->handle, 1000);
        } else if (r == -EPIPE) {
            snd_pcm_prepare(sndpcm->handle);
            fprintf(stderr, "<<<<<<<<<<<<<<< Buffer Underrun >>>>>>>>>>>>>>>\n");
        } else if (r == -ESTRPIPE) {
            fprintf(stderr, "<<<<<<<<<<<<<<< Need suspend >>>>>>>>>>>>>>>\n");
        } else if (r < 0) {
            fprintf(stderr, "Error snd_pcm_writei: [%s]", snd_strerror(r));
            return -1;
        }
        if (r > 0) {
            result += r;
            wcount -= r;
            data += r * sndpcm->bits_per_frame / 8;
        }
    }
    return result;
}

// 设置采样信息
int WavObject::SNDWAV_SetParams(SNDPCMContainer_t *sndpcm, WAVContainer_t *wav)
{
    snd_pcm_hw_params_t *hwparams;
    snd_pcm_format_t format;
    uint32_t exact_rate;
    uint32_t buffer_time, period_time;

    /* Allocate the snd_pcm_hw_params_t structure on the stack. */
    snd_pcm_hw_params_alloca(&hwparams);

    /* Init hwparams with full configuration space */
    if (snd_pcm_hw_params_any(sndpcm->handle, hwparams) < 0) {
        fprintf(stderr, "Error snd_pcm_hw_params_any\n");
        return -1;
    }

    if (snd_pcm_hw_params_set_access(sndpcm->handle, hwparams, SND_PCM_ACCESS_RW_INTERLEAVED) < 0) {
        fprintf(stderr, "Error snd_pcm_hw_params_set_access\n");
        return -1;
    }

    /* Set sample format */
    if (SNDWAV_P_GetFormat(wav, &format) < 0) {
        fprintf(stderr, "Error get_snd_pcm_format\n");
        return -1;
    }
    if (snd_pcm_hw_params_set_format(sndpcm->handle, hwparams, format) < 0) {
        fprintf(stderr, "Error snd_pcm_hw_params_set_format\n");
        return -1;
    }
    sndpcm->format = format;

    /* Set number of channels */
    if (snd_pcm_hw_params_set_channels(sndpcm->handle, hwparams, LE_SHORT(wav->format.channels)) < 0) {
        fprintf(stderr, "Error snd_pcm_hw_params_set_channels\n");
        return -1;
    }
    sndpcm->channels = LE_SHORT(wav->format.channels);

    /* Set sample rate. If the exact rate is not supported */
    /* by the hardware, use nearest possible rate.         */
    exact_rate = LE_INT(wav->format.sample_rate);
    if (snd_pcm_hw_params_set_rate_near(sndpcm->handle, hwparams, &exact_rate, 0) < 0) {
        fprintf(stderr, "Error snd_pcm_hw_params_set_rate_near\n");
        return -1;
    }
    if (LE_INT(wav->format.sample_rate) != exact_rate) {
        fprintf(stderr, "The rate %d Hz is not supported by your hardware.\n ==> Using %d Hz instead.\n",
                LE_INT(wav->format.sample_rate), exact_rate);
    }

    if (snd_pcm_hw_params_get_buffer_time_max(hwparams, &buffer_time, 0) < 0) {
        fprintf(stderr, "Error snd_pcm_hw_params_get_buffer_time_max\n");
        return -1;
    }
    if (buffer_time > 500000) buffer_time = 500000;
    period_time = buffer_time / 4;

    if (snd_pcm_hw_params_set_buffer_time_near(sndpcm->handle, hwparams, &buffer_time, 0) < 0) {
        fprintf(stderr, "Error snd_pcm_hw_params_set_buffer_time_near\n");
        return -1;
    }

    if (snd_pcm_hw_params_set_period_time_near(sndpcm->handle, hwparams, &period_time, 0) < 0) {
        fprintf(stderr, "Error snd_pcm_hw_params_set_period_time_near\n");
        return -1;
    }

    /* Set hw params */
    if (snd_pcm_hw_params(sndpcm->handle, hwparams) < 0) {
        fprintf(stderr, "Error snd_pcm_hw_params(handle, params)\n");
        return -1;
    }

    snd_pcm_hw_params_get_period_size(hwparams, &sndpcm->chunk_size, 0);
    snd_pcm_hw_params_get_buffer_size(hwparams, &sndpcm->buffer_size);
    if (sndpcm->chunk_size == sndpcm->buffer_size) {
        fprintf(stderr, ("Can't use period equal to buffer size (%lu == %lu)\n"), sndpcm->chunk_size, sndpcm->buffer_size);
        return -1;
    }

    sndpcm->bits_per_sample = snd_pcm_format_physical_width(format);
    sndpcm->bits_per_frame = sndpcm->bits_per_sample * LE_SHORT(wav->format.channels);

    sndpcm->chunk_bytes = sndpcm->chunk_size * sndpcm->bits_per_frame / 8;

    /* Allocate audio data buffer */
    sndpcm->data_buf = (uint8_t *)malloc(sndpcm->chunk_bytes);
    if (!sndpcm->data_buf) {
        fprintf(stderr, "Error malloc: [data_buf]\n");
        return -1;
    }

    return 0;
}


/**
 * @brief WavSoundTest::set_pcm_play 播放pcm音频数据
 * @param fp
 * @return
 */
int WavObject::set_pcm_play(FILE *fp, s_wavhead_t *wav_header_t)
{
    int rc;
    int ret;
    int size;
    // PCI设备句柄
    snd_pcm_t* handle;
    // 硬件信息和PCM流配置
    snd_pcm_hw_params_t* params;
    unsigned int val;
    int dir = 0;
    snd_pcm_uframes_t frames;
    char *buffer = NULL;
    int channels = wav_header_t->wChannels;
    int frequency = wav_header_t->nSamplesPersec;
    int bit = wav_header_t->wBitsPerSample;
    int datablock = wav_header_t->wBlockAlign;
//        unsigned char ch[100]; //用来存储wav文件的头信息

    rc = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
    if (rc < 0)
    {
        perror("\nopen PCM device failed:");
        return (-1);
    }

    // 分配params结构体
    snd_pcm_hw_params_alloca(&params);
    if (rc < 0)
    {
        perror("\nsnd_pcm_hw_params_alloca:");
        return (-1);
    }

    // 初始化params
    rc = snd_pcm_hw_params_any(handle, params);
    if (rc < 0)
    {
        perror("\nsnd_pcm_hw_params_any:");
        return (-1);
    }

    // 初始化访问权限
    rc = snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    if(rc < 0)
    {
        perror("\nsed_pcm_hw_set_access:");
        return (-1);
    }

    // 采样位数
    switch (bit / 8)
    {
    case 1:
        snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_U8);
        break ;
    case 2:
        snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
        break ;
    case 3:
        snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S24_LE);
        break ;
    }

    // 设置声道,1表示单声>道，2表示立体声
    rc = snd_pcm_hw_params_set_channels(handle, params, channels);
    if (rc < 0)
    {
        perror("\nsnd_pcm_hw_params_set_channels:");
        return (-1);
    }

    val = frequency;
    // 设置>频率
    rc = snd_pcm_hw_params_set_rate_near(handle, params, &val, &dir);
    if (rc < 0)
    {
        perror("\nsnd_pcm_hw_params_set_rate_near:");
        return (-1);
    }

    rc = snd_pcm_hw_params(handle, params);
    if (rc < 0)
    {
        perror("\nsnd_pcm_hw_params: ");
        return (-1);
    }

    /*获取周期长度*/
    rc = snd_pcm_hw_params_get_period_size(params, &frames, &dir);
    if (rc < 0)
    {
        perror("\nsnd_pcm_hw_params_get_period_size:");
        return (-1);
    }

    /*4 代表数据快长度*/
    size = frames * datablock;

    buffer =(char*)malloc(size);
    // 定位歌曲到数据区
    fseek(fp, 58, SEEK_SET);

    while (m_bRun)
    {
        memset(buffer, 0, size * sizeof(char));

        ret = fread(buffer, 1, size, fp);
        if(ret == 0)
        {
//            printf("play finished!\n");
            break;
        }

        // 写音频数据到PCM设备
        while ((ret = snd_pcm_writei(handle, buffer, frames)) < 0)
        {
            usleep(2000);
            if (ret == -EPIPE)
            {
                /* EPIPE means underrun */
                fprintf(stderr, "underrun occurred\n");
                //完成硬件参数设置，使设备准备好
                snd_pcm_prepare(handle);
            }
            else if (ret < 0)
            {
                fprintf(stderr,
                        "error from writei: %s\n",
                        snd_strerror(ret));
            }
            // 终止
            if (!m_bRun) break;
        }
    }

    snd_pcm_drain(handle);
    snd_pcm_close(handle);
    free(buffer);
    return 0;
}
