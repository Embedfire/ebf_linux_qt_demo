/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : wavplaylistwidget.h --- WavPlayListWidget
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef WAVPLAYLISTWIDGET_H
#define WAVPLAYLISTWIDGET_H

#include <QWidget>
#include "qtlistwidget.h"

#include <QMediaPlaylist>

class WavPlayListWidget : public QtListWidget
{
    Q_OBJECT
public:
    explicit WavPlayListWidget(QWidget *parent = 0);
    ~WavPlayListWidget();

    void LoadLocalFiles(const QString &path);
    QMediaPlaylist *palyList();

signals:

public slots:
    void SltAddWavFile(const QString &file);

private:
    QMediaPlaylist *m_playList;

protected:
    void drawItemInfo(QPainter *painter, QtListWidgetItem *item);
};

#endif // WAVPLAYLISTWIDGET_H
