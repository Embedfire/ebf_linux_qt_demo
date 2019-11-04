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
#ifndef SNDWAVRECORD_H
#define SNDWAVRECORD_H

#include <QThread>

#include "sndwav_common.h"

class SndWavRecord : public SndWavObj
{
    Q_OBJECT
public:
    explicit SndWavRecord(QObject *parent = 0);
    ~SndWavRecord();

    void run();

    int record(char *filename);
    int SNDWAV_PrepareWAVParams(WAVContainer_t *wav);
    void SNDWAV_Record(SNDPCMContainer_t *sndpcm, WAVContainer_t *wav, int fd);
signals:

public slots:
};

#endif // SNDWAVRECORD_H
