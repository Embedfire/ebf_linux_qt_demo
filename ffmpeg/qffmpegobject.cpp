/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : qffmpegobject.cpp --- QFFmpegObject
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "qffmpegobject.h"
#include <QImage>
#include <QDebug>

QFFmpegObject::QFFmpegObject(QObject *parent) : QObject(parent)
{
    #ifdef __arm__
    // 注册库中所有可用的文件格式和解码器
    av_register_all();
#endif
}

QFFmpegObject::~QFFmpegObject()
{
}

QImage QFFmpegObject::getAritstPic(const QString &fileName)
{
    QImage m_InfoImage;
#ifdef __arm__
    m_AVFormatContext = avformat_alloc_context();
    // 打开文件
    int result = avformat_open_input(&m_AVFormatContext, fileName.toLocal8Bit().data(), NULL, NULL);
    if (result != 0 || m_AVFormatContext == NULL) {
        qDebug() << "m_AVFormatContext error" << result << fileName;
        return m_InfoImage;
    }

    // 查找流信息，把它存入AVFormatContext中
    if (avformat_find_stream_info(m_AVFormatContext, NULL) < 0) {
        qDebug() << "save stream error";
        return m_InfoImage;
    }

    int streamsCount = m_AVFormatContext->nb_streams;

    for (int i=0; i<streamsCount; ++i)
    {
        if (m_AVFormatContext->streams[i]->disposition & AV_DISPOSITION_ATTACHED_PIC)
        {
            AVPacket pkt = m_AVFormatContext->streams[i]->attached_pic;
            m_InfoImage = QImage::fromData((uchar*)pkt.data, pkt.size);
        }
    }
#else
    Q_UNUSED(fileName);
#endif
    return m_InfoImage;
}
