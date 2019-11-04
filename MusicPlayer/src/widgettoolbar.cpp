/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : widgettoolbar.cpp --- WidgetToolBar
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "widgettoolbar.h"
#include "unit.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QTime>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QButtonGroup>

QtVolumeSlider::QtVolumeSlider(QWidget *parent) :
    QtSliderBar(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::SubWindow);
    this->SetHorizontal(false);
    this->SetSliderSize(4, 36);
    this->setFixedSize(36, 120);
}

QtVolumeSlider::~QtVolumeSlider()
{

}

void QtVolumeSlider::showEvent(QShowEvent *e)
{
    this->setFocus();
    QWidget::showEvent(e);
}

void QtVolumeSlider::focusOutEvent(QFocusEvent *e)
{
    this->hide();
    QWidget::focusOutEvent(e);
}

///////////////////////////////////////////////////////////////////
WidgetToolBar::WidgetToolBar(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);

    InitWidget();
    m_bPlaying = false;
    m_nMaxValue = 0;
    m_nCurrentValue = 0;
}

WidgetToolBar::~WidgetToolBar()
{

}

void WidgetToolBar::UpdateDurationInfo(int postion)
{
    m_nCurrentValue = postion;
    QTime currentTime = GetTimeByPostion(postion);
    QTime totalTime = GetTimeByPostion(m_nMaxValue);
    QString format = "mm:ss";
    if (m_nMaxValue > 3600) format = "hh:mm:ss";
    m_labelCurrTime->setText(currentTime.toString(format));
    m_labelDuraTime->setText(totalTime.toString(format));
    m_progressBar->SetValue(postion);
}

void WidgetToolBar::SetDuration(int duration)
{
    this->m_nMaxValue = duration;
    m_progressBar->SetMaxValue(duration);
    m_nCurrentValue = 0;
}

void WidgetToolBar::SetPlayState(bool state)
{
    m_bPlaying = state;
    m_btnPlay->setStyleSheet(QString("QPushButton{border-image: url(:/images/music/ic_%1.png);}")
                             .arg(m_bPlaying ? "pause" : "play"));
}

void WidgetToolBar::InitWidget()
{
    // 播放按钮
    QHBoxLayout *horLayoutPlaybtn = new QHBoxLayout();
    horLayoutPlaybtn->setContentsMargins(0, 0, 0, 0);
    horLayoutPlaybtn->setSpacing(14);

    QPushButton *btnPrev = new QPushButton(this);
    btnPrev->setFocusPolicy(Qt::NoFocus);
    connect(btnPrev, SIGNAL(clicked(bool)), this, SIGNAL(previous()));
    horLayoutPlaybtn->addWidget(btnPrev);
    btnPrev->setFixedSize(38, 38);
    btnPrev->setStyleSheet(QString("QPushButton{border-image: url(:/images/music/ic_prev.png);}"
                                   "QPushButton:pressed{border-image: url(:/images/music/ic_prev_pre.png);}"));

    m_btnPlay = new QPushButton(this);
    m_btnPlay->setFocusPolicy(Qt::NoFocus);
    connect(m_btnPlay, SIGNAL(clicked(bool)), this, SLOT(SltBtnPlayClicked()));
    horLayoutPlaybtn->addWidget(m_btnPlay);
    m_btnPlay->setFixedSize(50, 50);
    m_btnPlay->setStyleSheet(QString("QPushButton{border-image: url(:/images/music/ic_play.png);}"));

    QPushButton *btnNext = new QPushButton(this);
    btnNext->setFocusPolicy(Qt::NoFocus);
    connect(btnNext, SIGNAL(clicked(bool)), this, SIGNAL(next()));
    horLayoutPlaybtn->addWidget(btnNext);
    btnNext->setFixedSize(38, 38);
    btnNext->setStyleSheet(QString("QPushButton{border-image: url(:/images/music/ic_next.png);}"
                                   "QPushButton:pressed{border-image: url(:/images/music/ic_next_pre.png);}"));


    //--------- 进度 -------------//
    QHBoxLayout *horLayoutProgress = new QHBoxLayout();
    horLayoutProgress->setContentsMargins(0, 0, 0, 0);
    horLayoutProgress->setSpacing(5);

    m_labelCurrTime = new QLabel(this);
    horLayoutProgress->addWidget(m_labelCurrTime);
    m_labelCurrTime->setText("00:00");

    // 进度条
    m_progressBar = new QtSliderBar(this);
    m_progressBar->SetReadOnly(false);
    horLayoutProgress->addWidget(m_progressBar, 1);
    m_progressBar->SetHorizontal(true);
    m_progressBar->SetSliderSize(2, 36);
    m_progressBar->SetMaxValue(0);
    m_progressBar->SetValue(0);
    connect(m_progressBar, SIGNAL(currentValueChanged(int)), this, SIGNAL(currentPostionChanged(int)));

    m_labelDuraTime = new QLabel(this);
    horLayoutProgress->addWidget(m_labelDuraTime);
    m_labelDuraTime->setText("00:00");

    //--------- 播放列表 -------------//
    QHBoxLayout *horLayoutList = new QHBoxLayout();
    horLayoutList->setContentsMargins(0, 0, 0, 0);
    horLayoutList->setSpacing(0);

    QButtonGroup *btnGroup = new QButtonGroup(this);
    connect(btnGroup, SIGNAL(buttonClicked(int)), this, SIGNAL(toolBarClicked(int)));

    QPushButton *btnEqualize = new QPushButton(this);
    btnEqualize->setVisible(false);
    btnEqualize->setFocusPolicy(Qt::NoFocus);
    btnGroup->addButton(btnEqualize, 1);
    horLayoutList->addWidget(btnEqualize);
    btnEqualize->setFixedSize(27, 27);
    btnEqualize->setStyleSheet(QString("QPushButton{border-image: url(:/images/music/ic_equalizer.png);}"
                                       "QPushButton:pressed{border-image: url(:/images/music/ic_equalizer_pre.png);}"));

    QPushButton *btnVolume = new QPushButton(this);
    btnGroup->addButton(btnVolume, 2);
    horLayoutList->addWidget(btnVolume);
    btnVolume->setFocusPolicy(Qt::NoFocus);
    btnVolume->setMinimumSize(69, 69);
    btnVolume->setIconSize(QSize(27, 27));
    btnVolume->setIcon(QIcon(":/images/music/ic_volume.png"));
    btnVolume->setStyleSheet(QString("border: none; background: none;"));

    QPushButton *btnMusicList = new QPushButton(this);
    btnMusicList->setFocusPolicy(Qt::NoFocus);
    btnGroup->addButton(btnMusicList, 3);
    horLayoutList->addWidget(btnMusicList);
    btnMusicList->setMinimumSize(69, 69);
    btnMusicList->setIconSize(QSize(27, 27));
    btnMusicList->setIcon(QIcon(":/images/music/ic_list.png"));
    btnMusicList->setStyleSheet(QString("border: none; background: none;"));

    QHBoxLayout *horLayoutAll = new QHBoxLayout(this);
    horLayoutAll->setContentsMargins(10, 10, 10, 10);
    horLayoutAll->setSpacing(20);
    horLayoutAll->addLayout(horLayoutPlaybtn);
    horLayoutAll->addLayout(horLayoutProgress, 1);
    horLayoutAll->addLayout(horLayoutList);
    this->setStyleSheet(QString("QLabel{font-family: '%1'; font: bold 18px; color: #333333; min-width: 50px;}").arg(APP_FONT_FAMILY));
}

void WidgetToolBar::InitProperty()
{
    m_bPlaying = false;
    m_nMaxValue = 100;
    m_nCurrentValue = 1;
}

QTime WidgetToolBar::GetTimeByPostion(int postion)
{
    return QTime((postion / 3600) % 60,
                 (postion / 60 ) % 60,
                 postion % 60, (postion * 1000) % 1000);
}

void WidgetToolBar::SltBtnPlayClicked()
{
    m_bPlaying = !m_bPlaying;
    m_btnPlay->setStyleSheet(QString("QPushButton{border-image: url(:/images/music/ic_%1.png);}")
                             .arg(m_bPlaying ? "pause" : "play"));
    if (m_bPlaying) {emit play();}
    else {emit pause();}
}

void WidgetToolBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), QColor("#72ffffff"));

}

