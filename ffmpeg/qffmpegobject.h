/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : qffmpegobject.h --- QFFmpegObject
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef QFFMPEGOBJECT_H
#define QFFMPEGOBJECT_H

#include <QObject>
extern "C" {
#ifdef __arm__
#include "include/libavformat/avformat.h"
#include "include/libavcodec/avcodec.h"
#endif
}

class QFFmpegObject : public QObject
{
    Q_OBJECT
public:
    explicit QFFmpegObject(QObject *parent = 0);
    ~QFFmpegObject();

    QImage getAritstPic(const QString &fileName);
signals:

public slots:

private:
#ifdef __arm__
    AVFormatContext *m_AVFormatContext;
#endif
};

#endif // QFFMPEGOBJECT_H
