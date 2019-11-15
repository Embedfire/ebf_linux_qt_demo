/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : musicplayer.h --- MusicPlayer
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include "qtwidgetbase.h"
#include "lyricwidget.h"
#include "widgettoolbar.h"
#include "widgetrecord.h"
#include "equalizewidget.h"
#include "musicplaylistwidget.h"

#include <QMediaPlayer>
#include <QMenu>

class QFFmpegObject;

class MusicPlayer : public QtAnimationWidget
{
    Q_OBJECT
public:
    explicit MusicPlayer(QWidget *parent = 0);
    ~MusicPlayer();

    void StopMusic();
    void InitPlayList();

signals:

public slots:

private:
    WidgetRecord     *m_recorder;
    LyricWidget      *m_lyricWidget;
    WidgetToolBar    *m_playerToolBar;

    EqualizeWidget      *m_eaualizeWidget;
    MusicPlayListWidget *m_widgetMusicList;

    QtSliderBar         *m_volumeSlider;

    QMediaPlayer     *m_player;
    QFFmpegObject    *m_ffmpeg;

private:
    void InitWidget();
    void InitPlayer();

private slots:
    void SltBackHome();
    void SltMusicPlay();
    void SltMusicPause();

    void SltDurationChanged(qint64 duration);
    void SltPostionChanged(qint64 postion);
    void SltMediaError(QMediaPlayer::Error error);

    void SltToolbarClicked(int index);
    void SltCurrentSongChanged(const QString &name, const QString &path);
    void SltChangePostion(int postion);

protected:
    void resizeEvent(QResizeEvent *e);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
};

#endif // MUSICPLAYER_H
