/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : videoplaylistwidget.h --- VideoPlayListWidget
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef VIDEOPLAYLISTWIDGET_H
#define VIDEOPLAYLISTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QMediaPlaylist>

#include "qtlistwidget.h"
#include "qtwidgetbase.h"

class VideoPlayListWidget : public QtListWidget
{
    Q_OBJECT
public:
    explicit VideoPlayListWidget(QWidget *parent = 0);
    ~VideoPlayListWidget();

signals:

public slots:

private:

protected:
    void drawItemInfo(QPainter *painter, QtListWidgetItem *item);
};


/////////////////////////////////////////////////////////////////////
class MediaPlayListWidget : public QtAnimationWidget {
    Q_OBJECT
public:
    explicit MediaPlayListWidget(QWidget *parent = 0);
    ~MediaPlayListWidget();

    void setTitle(const QString &title);
    QMediaPlaylist *palyList();
    QMap<int,QtListWidgetItem*> items();

    void LoadLocalFiles(const QString &path);
signals:
    void signalMediaChanged(const QString &fileName);

private:
    QLabel *m_labelTitle;
    VideoPlayListWidget *m_listWidget;
    QMediaPlaylist *m_playList;
    QMap<int,QtListWidgetItem*> m_mapItems;

    void ScanDirMedias(const QString &path);

private slots:
    void SltCurrMediaChanged(int index);

protected:
    void paintEvent(QPaintEvent *);
};

#endif // VIDEOPLAYLISTWIDGET_H
