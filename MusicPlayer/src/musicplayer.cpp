/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : musicplayer.cpp --- MusicPlayer
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "musicplayer.h"
#include "skin.h"
#include "qffmpegobject.h"
#include "mp3infoobject.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QDebug>
#include <QDateTime>
#include <QPainter>
#include <QUrl>
#include <QDir>
#include <QRegExp>
#include <QWidgetAction>

#ifndef FLASH_FILE_EMMC
#define FLASH_FILE_EMMC     "/sys/class/mmc_host/mmc1/mmc1:0001/block/mmcblk1/size"
#endif

MusicPlayer::MusicPlayer(QWidget *parent) : QtAnimationWidget(parent)
{
    InitWidget();
    InitPlayer();
#ifdef BUILD_BY_PRO
    InitPlayList();
#endif
}

MusicPlayer::~MusicPlayer()
{
    if (m_player->state() != QMediaPlayer::StoppedState) {
        m_player->stop();
    }
}

void MusicPlayer::StopMusic()
{
    if (m_player->state() == QMediaPlayer::PlayingState) {
        m_player->pause();
    }
}

void MusicPlayer::InitWidget()
{
    QtWidgetTitleBar *widgetTitle = new QtWidgetTitleBar(this);
    widgetTitle->SetScalSize(Skin::m_nScreenWidth, 60);
    widgetTitle->SetBackground(Qt::transparent);
    widgetTitle->setFont(QFont(Skin::m_strAppFontNormal));
    widgetTitle->SetTitle(tr("音乐播放器"), "#ffffff", 24);
    connect(widgetTitle, SIGNAL(signalBackHome()), this, SIGNAL(signalBackHome()));

    QHBoxLayout *horLayoutCentor = new QHBoxLayout();
    horLayoutCentor->setContentsMargins(0, 0, 0, 0);
    horLayoutCentor->setSpacing(0);

    m_recorder = new WidgetRecord(this);
    horLayoutCentor->addWidget(m_recorder, 1);

    m_lyricWidget = new LyricWidget(this);
    horLayoutCentor->addWidget(m_lyricWidget, 1);

    m_playerToolBar = new WidgetToolBar(this);

    connect(m_playerToolBar, SIGNAL(play()), this, SLOT(SltMusicPlay()));
    connect(m_playerToolBar, SIGNAL(pause()), this, SLOT(SltMusicPause()));
    connect(m_playerToolBar, SIGNAL(toolBarClicked(int)), this, SLOT(SltToolbarClicked(int)));

    QVBoxLayout *verLayoutAll = new QVBoxLayout(this);
    verLayoutAll->setContentsMargins(0, 0, 0, 0);
    verLayoutAll->setSpacing(0);
    verLayoutAll->addWidget(widgetTitle, 1);
    verLayoutAll->addLayout(horLayoutCentor, 6);
    verLayoutAll->addWidget(m_playerToolBar);

    // 均衡器
    m_eaualizeWidget = new EqualizeWidget(this);
    m_eaualizeWidget->hide();

    // 播放列表
    m_widgetMusicList = new MusicPlayListWidget(this);
    connect(m_widgetMusicList, SIGNAL(signalMediaChanged(QString,QString)), this, SLOT(SltCurrentSongChanged(QString,QString)));
    m_widgetMusicList->hide();

    connect(m_playerToolBar, SIGNAL(next()), m_widgetMusicList->playList(), SLOT(next()));
    connect(m_playerToolBar, SIGNAL(previous()), m_widgetMusicList->playList(), SLOT(previous()));
    connect(m_playerToolBar, SIGNAL(currentPostionChanged(int)), this, SLOT(SltChangePostion(int)));
}

void MusicPlayer::InitPlayer()
{
    m_player = new QMediaPlayer(this);
    m_player->setPlaylist(m_widgetMusicList->playList());
    connect(m_player, SIGNAL(durationChanged(qint64)), this, SLOT(SltDurationChanged(qint64)));
    connect(m_player, SIGNAL(positionChanged(qint64)), this, SLOT(SltPostionChanged(qint64)));
    connect(m_player, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(SltMediaError(QMediaPlayer::Error)));

    m_volumeSlider = new QtSliderBar(this);
    m_volumeSlider->SetHorizontal(false);
    m_volumeSlider->SetValue(100);
    m_volumeSlider->hide();
    connect(m_volumeSlider, SIGNAL(currentValueChanged(int)), m_player, SLOT(setVolume(int)));

    m_ffmpeg = new QFFmpegObject(this);
}

void MusicPlayer::InitPlayList()
{
    if (!m_widgetMusicList->playList()->isEmpty()) return ;

    // emmc设备检测
    m_widgetMusicList->LoadLocalFiles("/run/media/");
}

void MusicPlayer::SltBackHome()
{
    if (m_widgetMusicList->isVisible()) m_widgetMusicList->setVisible(false);
    emit signalBackHome();
}

void MusicPlayer::SltMusicPlay()
{
    if (m_widgetMusicList->playList()->isEmpty()) {
        m_playerToolBar->SetPlayState(false);
        return;
    }

    if (QMediaPlayer::StoppedState == m_player->state()) {
        m_player->play();
        m_recorder->Start();
    }
    else if (QMediaPlayer::PausedState == m_player->state()) {
        m_player->play();
        m_recorder->Start();
    }
}

void MusicPlayer::SltMusicPause()
{
    if (QMediaPlayer::PlayingState == m_player->state()) {
        m_player->pause();
        m_recorder->Stop();
    }
}

void MusicPlayer::SltDurationChanged(qint64 duration)
{
    if (0 == duration) return;
    m_playerToolBar->SetDuration(duration / 1000);
}

void MusicPlayer::SltPostionChanged(qint64 postion)
{
    m_lyricWidget->ChangePostion(postion);
    m_playerToolBar->UpdateDurationInfo(postion / 1000);
}

void MusicPlayer::SltMediaError(QMediaPlayer::Error error)
{
    qDebug() << "MusicPlayer: play error" << error;
    m_lyricWidget->ShowErrorString();
    m_recorder->Stop();
    m_playerToolBar->SetPlayState(false);
}

void MusicPlayer::SltToolbarClicked(int index)
{
    if (1 == index) {
        m_volumeSlider->setVisible(false);
        if (m_widgetMusicList->isVisible()) m_widgetMusicList->setVisible(false);
        m_eaualizeWidget->StartAutoMove(!m_eaualizeWidget->isVisible(), this->width());
    } else if (2 == index) {
        m_volumeSlider->setVisible(!m_volumeSlider->isVisible());
    } else if (3 == index) {
        m_volumeSlider->setVisible(false);
        if (m_eaualizeWidget->isVisible()) m_eaualizeWidget->setVisible(false);
        m_widgetMusicList->StartAutoMove(!m_widgetMusicList->isVisible(), this->width());
    }
}

void MusicPlayer::SltCurrentSongChanged(const QString &name, const QString &path)
{
    if (m_widgetMusicList->isVisible()) {
        m_widgetMusicList->hide();
    }

    // 如果再播放上一首歌，停止
    if (m_player->state() != QMediaPlayer::StoppedState) {
        m_player->stop();
    }

    // 设置新歌曲
    m_lyricWidget->LoadLyricFile(name, path);
    m_playerToolBar->SetPlayState(true);

    QImage image = m_ffmpeg->getAritstPic(path);
    m_recorder->SetImage(image);
    m_recorder->Start();
    m_player->play();
}

void MusicPlayer::SltChangePostion(int postion)
{
    m_lyricWidget->SetLyricPostion(postion * 1000);
    m_playerToolBar->UpdateDurationInfo(postion);
    m_player->setPosition(postion * 1000);
}

void MusicPlayer::resizeEvent(QResizeEvent *e)
{
    SetScaleValue();
    m_playerToolBar->setMinimumHeight(69 * m_scaleY);

    m_widgetMusicList->resize(405 * m_scaleX, 350 * m_scaleY);
    m_widgetMusicList->move(this->width() - m_widgetMusicList->width() + 5, 55 * m_scaleY);
    m_widgetMusicList->m_nYPos = 55 * m_scaleY;

    int nW = 4 * m_scaleX;
    m_volumeSlider->resize(36 * m_scaleX, 100 * m_scaleY);
    m_volumeSlider->SetSliderSize(nW < 1 ? 1 : nW, 36 * m_scaleX);
    m_volumeSlider->move(690 * m_scaleX, 320 * m_scaleY);
    m_volumeSlider->SetValue(m_volumeSlider->value());
    QWidget::resizeEvent(e);
}

void MusicPlayer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/images/music/background.png"));
}

void MusicPlayer::mousePressEvent(QMouseEvent *)
{
    if (m_volumeSlider->isVisible()) {
        m_volumeSlider->setVisible(false);
    }
}
