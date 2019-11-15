/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 :
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef MUSICPLAYLISTWIDGET_H
#define MUSICPLAYLISTWIDGET_H

#include "qtwidgetbase.h"
#include "qtlistwidget.h"

#include <QLabel>
#include <QMediaPlaylist>

/////////////////////////////////////////////////////////////////////
class PlayListWidget : public QtListWidget
{
    Q_OBJECT
public:
    explicit PlayListWidget(QWidget *parent = 0);
    ~PlayListWidget();

signals:

public slots:

private:

protected:
    void drawItemInfo(QPainter *painter, QtListWidgetItem *item);
};


/////////////////////////////////////////////////////////////////////
class MusicPlayListWidget : public QtAnimationWidget {
    Q_OBJECT
public:
    explicit MusicPlayListWidget(QWidget *parent = 0);
    ~MusicPlayListWidget();

    void setTitle(const QString &title);
    QMediaPlaylist *playList();

    void LoadLocalFiles(const QString &path);
    void StartAutoMove(bool bShow, int width);
    int             m_nYPos;

signals:
    void signalMediaChanged(const QString &fileName, const QString &filePath);

private:
    void ScanDirMedias(const QString &path);

private:
    QString         m_strTitle;
    PlayListWidget *m_listWidget;
    QMediaPlaylist *m_playList;
    QMap<int,QtListWidgetItem*> m_mapItems;

private slots:
    void SltCurrMediaChanged(int index);

protected:
    void paintEvent(QPaintEvent *);
};


#endif // MUSICPLAYLISTWIDGET_H
