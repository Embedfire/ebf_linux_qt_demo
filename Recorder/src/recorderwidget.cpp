/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : recorderwidget.cpp ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/10/10
*******************************************************************/
#include "recorderwidget.h"
#include "skin.h"

#include <QPainter>
#include <QApplication>
#include <QBoxLayout>
#include <QApplication>
#include <QDateTime>
#include <QPushButton>
#include <QFileInfo>
#include <QTimer>
#include <QMouseEvent>

RecorderWidget::RecorderWidget(QWidget *parent) : QtAnimationWidget(parent)
{
    this->SetBackground(QPixmap(":/images/record/ic_background.png"));

    m_strCurrTime = "00:00";
    m_strDuration = "00:00";

    InitWidget();

    QTimer::singleShot(500, this, SLOT(InitPlayList()));
}

RecorderWidget::~RecorderWidget()
{
}

void RecorderWidget::InitWidget()
{
    m_recordWidget = new ARecordWidget(this);
    m_btns.insert(0, new QtPixmapButton(0, QRect(746, 5, 54, 54), QPixmap(":/images/record/menu_icon.png"), QPixmap(":/images/record/menu_icon_pressed.png")));
    m_btns.insert(1, new QtPixmapButton(1, QRect(453, 431, 38, 38), QPixmap(":/images/record/ic_prev.png"), QPixmap(":/images/record/ic_prev_pre.png")));
    m_btns.insert(2, new QtPixmapButton(2, QRect(532, 425, 50, 50), QPixmap(":/images/record/ic_play.png"), QPixmap(":/images/record/ic_pause.png")));
    m_btns.insert(3, new QtPixmapButton(3, QRect(623, 431, 38, 38), QPixmap(":/images/record/ic_next.png"), QPixmap(":/images/record/ic_next_pre.png")));
    m_btns.value(2)->setCheckAble(true);
    connect(this, SIGNAL(signalBtnClicked(int)), this, SLOT(SltBtnClicked(int)));

    // 进度条
    m_progressBar = new QtSliderBar(this);
    m_progressBar->SetReadOnly(false);
    m_progressBar->SetHorizontal(true);
    m_progressBar->SetHandleBgColor(QColor("#95F204"));
    m_progressBar->SetHandleColor(QColor("#95F204"));
    m_progressBar->SetSliderSize(1, 30);
    m_progressBar->SetMaxValue(0);
    connect(m_progressBar, SIGNAL(currentValueChanged(int)), this, SLOT(SltChangePostion(int)));

    // 播放列表
    m_playlistWidget = new WavPlayListWidget(this);
    connect(m_recordWidget, SIGNAL(signalRecordFile(QString)), m_playlistWidget, SLOT(SltAddWavFile(QString)));

    m_player = new QMediaPlayer(this);
    m_player->setPlaylist(m_playlistWidget->palyList());
    connect(m_player, SIGNAL(durationChanged(qint64)), this, SLOT(SltDurationChanged(qint64)));
    connect(m_player, SIGNAL(positionChanged(qint64)), this, SLOT(SltPostionChanged(qint64)));
    connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(stateChanged(QMediaPlayer::State)));

    m_sliderVolume = new QtSliderBar(this);
    m_sliderVolume->SetReadOnly(false);
    m_sliderVolume->SetHorizontal(true);
    m_sliderVolume->SetMaxValue(100);
    m_sliderVolume->SetValue(100);
    m_sliderVolume->SetHandleBgColor(QColor("#95F204"));
    m_sliderVolume->SetHandleColor(QColor("#95F204"));
    m_sliderVolume->SetSliderSize(1, 24);
    connect(m_sliderVolume, SIGNAL(currentValueChanged(int)), m_player, SLOT(setVolume(int)));

    // 中间区域
    QVBoxLayout *verLayoutList = new QVBoxLayout();
    verLayoutList->setContentsMargins(0, 0, 0, 0);
    verLayoutList->setSpacing(0);
    verLayoutList->addStretch(1);
    verLayoutList->addWidget(m_playlistWidget, 5);
    verLayoutList->addStretch(2);

    QHBoxLayout *horLayoutAll = new QHBoxLayout(this);
    horLayoutAll->setContentsMargins(0, 0, 0, 0);
    horLayoutAll->setSpacing(0);
    horLayoutAll->addWidget(m_recordWidget, 3);
    horLayoutAll->addLayout(verLayoutList, 5);
}

void RecorderWidget::InitPlayList()
{
    m_playlistWidget->LoadLocalFiles(qApp->applicationDirPath() + "/record/");
}

void RecorderWidget::SltBtnPlayClicked()
{
    QtPixmapButton *btnPlay = m_btns.value(2);
    if (m_recordWidget->isRecording()) {
        btnPlay->setChecked(false);
        return;
    }

    if (btnPlay->isChecked()) {
        m_player->play();
    } else {
        m_player->pause();
    }
}

void RecorderWidget::SltDurationChanged(qint64 duration)
{
    if (0 == duration) return;
    QTime totalTime = GetTimeByPostion(duration / 1000);
    QString format = "mm:ss";
    m_strDuration = totalTime.toString(format);
    m_progressBar->SetMaxValue(duration / 1000);
    this->update();
}

void RecorderWidget::SltPostionChanged(qint64 postion)
{
    if (0 == postion) return;
    QTime currentTime = GetTimeByPostion(postion / 1000);
    QString format = "mm:ss";
    m_strCurrTime = currentTime.toString(format);
    m_progressBar->SetValue(postion/ 1000);
    this->update();
}

void RecorderWidget::stateChanged(QMediaPlayer::State newState)
{
    m_recordWidget->setEnabled(QMediaPlayer::PlayingState != newState);
}

void RecorderWidget::SltChangePostion(int postion)
{
    m_player->setPosition(postion * 1000);
}

void RecorderWidget::SltBtnClicked(int index)
{
    if (0 ==index) {
        emit signalBackHome();
    } else if (1 == index) {
        m_playlistWidget->palyList()->previous();
    }  else if (2 == index) {
        SltBtnPlayClicked();
    }
    else if (3 == index) {
        m_playlistWidget->palyList()->next();
    }
}

void RecorderWidget::resizeEvent(QResizeEvent *e)
{
    SetScaleValue();
    m_progressBar->SetSliderSize(1, 30 * m_scaleY);
    m_progressBar->resize(340 * m_scaleX, 30 * m_scaleY);
    m_progressBar->move(380 * m_scaleX, 375 * m_scaleY);
    m_progressBar->SetValue(m_progressBar->value());

    m_sliderVolume->SetSliderSize(1, 24 * m_scaleY);
    m_sliderVolume->resize(90 * m_scaleX, 24 * m_scaleY);
    m_sliderVolume->move(360 * m_scaleX, 440 * m_scaleY);
    m_sliderVolume->SetValue(m_sliderVolume->value());

    QWidget::resizeEvent(e);
}

void RecorderWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.scale(m_scaleX, m_scaleY);
    painter.drawPixmap(0, 0, m_nBaseWidth, m_nBaseHeight, m_pixmapBackground);
    painter.setPen(QColor("#333333"));
    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(24);
    painter.setFont(font);
    painter.drawText(300, 0, m_nBaseWidth - 300, 60, Qt::AlignCenter, tr("录音文件"));

    painter.drawText(QRect(302, 375, 70, 30), Qt::AlignCenter, m_strCurrTime);
    painter.drawText(QRect(728, 375, 70, 30), Qt::AlignCenter, m_strDuration);

    foreach (QtPixmapButton *btn, m_btns) {
        painter.drawPixmap(btn->rect(), btn->pixmap());
    }

    painter.drawPixmap(314, 431, QPixmap(":/images/record/ic_volume.png"));
}

QTime RecorderWidget::GetTimeByPostion(int postion)
{
    return QTime((postion / 3600) % 60,
                 (postion / 60 ) % 60,
                 postion % 60, (postion * 1000) % 1000);
}

