/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : videowidget.cpp --- VideoWidget
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "qtvideowidget.h"

#include "appconfig.h"
#include <QPainter>

#include <QDebug>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QFileInfo>
#include <QApplication>

//////////////////////////////////////////////////////////////////////////////////////
QtVideoWidget::QtVideoWidget(QWidget *parent) : QtWidgetBase(parent)
{
    m_urlMedia = QUrl();
    m_bToolBarShow = false;

    m_nDuration = 0;
    m_nPostion = 0;

    m_player = new QMediaPlayer(this);
    surface = new QtVideoWidgetSurface(this);
    m_player->setVideoOutput(surface);

    m_playList = new MediaPlayListWidget(this);
    m_playList->setVisible(false);
    m_player->setPlaylist(m_playList->palyList());

    connect(m_player, SIGNAL(durationChanged(qint64)), this, SLOT(SltDurationChanged(qint64)));
    connect(m_player, SIGNAL(positionChanged(qint64)), this, SLOT(SltPostionChanged(qint64)));

    m_titleBar = new PlayTitleBarWidget(this);
    connect(m_playList, SIGNAL(signalMediaChanged(QString)), m_titleBar, SLOT(SetText(QString)));
    connect(m_titleBar, SIGNAL(signalBack()), this, SLOT(SltBackClicked()));

    m_playBar = new PlayerBarWidget(this);
    connect(m_playBar, SIGNAL(signalPlay(bool)), this, SLOT(SltBtnPlayClicked(bool)));
    connect(m_playBar, SIGNAL(currentPostionChanged(int)), this, SLOT(SltChangePostion(int)));
    connect(m_playBar, SIGNAL(signalPrev()), m_playList->palyList(), SLOT(previous()));
    connect(m_playBar, SIGNAL(signalNext()), m_playList->palyList(), SLOT(next()));
    connect(m_playBar, SIGNAL(signalMuenList()), this, SLOT(SltShowMenuList()));
    connect(m_playBar, SIGNAL(signalVolume()), this, SLOT(SltChangeVolume()));

    m_timerShow = new QTimer(this);
    m_timerShow->setSingleShot(true);
    m_timerShow->setInterval(5000);
    connect(m_timerShow, SIGNAL(timeout()), this, SLOT(SltAutoCloseToolBar()));

    m_volumeSlider = new QtSliderBar(this);
    m_volumeSlider->SetHorizontal(false);
    m_volumeSlider->SetValue(100);
    m_volumeSlider->hide();
    connect(m_volumeSlider, SIGNAL(currentValueChanged(int)), m_player, SLOT(setVolume(int)));
}

QtVideoWidget::~QtVideoWidget()
{
    if (m_timerShow->isActive()) {
        m_timerShow->stop();
    }

    AppConfig::m_bPlayVideo = false;
}

void QtVideoWidget::setMedia(const QString &name, int index)
{
    m_titleBar->SetText(name);
    if (index == m_playList->palyList()->currentIndex()) {
        if (m_player->state() == QMediaPlayer::PausedState) {
            m_player->play();
        } else {
            m_player->play();
        }
    } else {
        m_playList->palyList()->setCurrentIndex(index);
        m_player->play();
    }

    AppConfig::m_bPlayVideo = true;
    this->setCursor(m_player->state() == QMediaPlayer::PlayingState ?
                        Qt::BlankCursor : Qt::ArrowCursor);
    // 设置播放状态
    m_playBar->setPlayState(m_player->state() == QMediaPlayer::PlayingState);
}

void QtVideoWidget::ShowToolBar()
{
    m_playList->setVisible(false);
    m_volumeSlider->setVisible(false);
    m_bToolBarShow = !m_bToolBarShow;
    if (m_bToolBarShow) {
        m_titleBar->SetAnimation(QPoint(0, -m_titleBar->height()), QPoint(0, 0));
        m_playBar->SetAnimation(QPoint(0, this->height()), QPoint(0, this->height() - m_playBar->height()));
    } else {
        m_titleBar->SetAnimation(QPoint(0, 0), QPoint(0, -m_titleBar->height()));
        m_playBar->SetAnimation(QPoint(0, this->height() - m_playBar->height()), QPoint(0, this->height()));
    }

    this->setCursor(m_bToolBarShow ? Qt::ArrowCursor : Qt::BlankCursor);
}

void QtVideoWidget::SltAutoCloseToolBar()
{
    m_playList->setVisible(false);
    m_volumeSlider->setVisible(false);
    if (m_bToolBarShow) {
        ShowToolBar();
    }
}

void QtVideoWidget::SltBackClicked()
{
    if (m_player->state() == QMediaPlayer::PlayingState) {
        m_player->pause();
    }

    AppConfig::m_bPlayVideo = false;
    this->hide();
}

void QtVideoWidget::SltBtnPlayClicked(bool bOk)
{
    if (bOk) {
        m_player->play();
    } else {
        m_player->pause();
    }
}

void QtVideoWidget::SltPostionChanged(qint64 postion)
{
    m_nPostion = postion;
    m_playBar->setPostion(postion / 1000);
}

void QtVideoWidget::SltDurationChanged(qint64 duration)
{
    m_nDuration = duration;
    m_playBar->setDuration(duration / 1000);
}

void QtVideoWidget::SltChangePostion(int postion)
{
    m_player->setPosition(postion * 1000);
}

void QtVideoWidget::SltShowMenuList()
{
    m_playList->setVisible(!m_playList->isVisible());
    m_volumeSlider->setVisible(false);
}

void QtVideoWidget::SltChangeVolume()
{
    //    QPoint pos = m_titleBar->geometry().topRight();
    //    m_volumeSlider->move(pos.x() - 80, pos.y() - m_volumeSlider->height() + 20);
    m_volumeSlider->setVisible(!m_volumeSlider->isVisible());
}

void QtVideoWidget::resizeEvent(QResizeEvent *event)
{
    SetScaleValue();
    surface->updateVideoRect();

    m_titleBar->resize(this->width(), 50 * m_scaleY);
    m_titleBar->move(0, -m_titleBar->height());

    m_playBar->resize(this->width(), 102 * m_scaleY);
    m_playBar->move(0, this->height()  + m_playBar->height());

    m_playList->resize(405 * m_scaleX, 328 * m_scaleY);
    m_playList->move(this->width() - m_playList->width() + 5, m_titleBar->height() + 2);

    m_volumeSlider->resize(36 * m_scaleX, 136 * m_scaleY);
    int nW = 4 * m_scaleX;
    m_volumeSlider->SetSliderSize(nW < 1 ? 1 : nW, 36 * m_scaleX);
    m_volumeSlider->SetValue(m_volumeSlider->value());
    m_volumeSlider->move(670 * m_scaleX, 258 * m_scaleY);

    QWidget::resizeEvent(event);
}

void QtVideoWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(event->rect(), Qt::black);

    if (surface->isActive()) {
        surface->paint(&painter);
    }
}

void QtVideoWidget::mousePressEvent(QMouseEvent *)
{
    m_volumeSlider->setVisible(false);

    ShowToolBar();

    if (m_timerShow->isActive()) {
        m_timerShow->stop();
    }

    // 有点击重新响应
    if (m_bToolBarShow) {
        m_timerShow->start();
    }
}
