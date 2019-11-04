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

#include <QApplication>
#include <QBoxLayout>
#include <QApplication>
#include <QDateTime>
#include <QPushButton>
#include <QFileInfo>
#include <QTimer>

RecorderWidget::RecorderWidget(QWidget *parent) : QtAnimationWidget(parent)
{
    this->SetBackground(QPixmap(":/images/record/ic_background.png"));

    InitWidget();
    QTimer::singleShot(500, this, SLOT(InitPlayList()));
}

RecorderWidget::~RecorderWidget()
{

}

void RecorderWidget::InitWidget()
{
    m_recordWidget = new ARecordWidget(this);

    QtWidgetTitleBar *widgetTitle= new QtWidgetTitleBar(this);
    widgetTitle->setMinimumHeight(60);
    widgetTitle->SetBackground(Qt::transparent);
    widgetTitle->setFont(QFont(Skin::m_strAppFontRegular));
    widgetTitle->SetTitle(tr("录音文件"), "#333333", 24);

    QPushButton *btnHome = new QPushButton(this);
    btnHome->setFixedSize(51, 51);
    connect(btnHome, SIGNAL(clicked(bool)), this, SIGNAL(signalBackHome()));
    btnHome->setStyleSheet(QString("QPushButton {border-image: url(:/images/record/menu_icon.png);}"
                                   "QPushButton:pressed {border-image: url(:/images/record/menu_icon_pressed.png);}"));

    QHBoxLayout *horLayoutTitle = new QHBoxLayout(widgetTitle);
    horLayoutTitle->setContentsMargins(0, 0, 10, 0);
    horLayoutTitle->addStretch();
    horLayoutTitle->addWidget(btnHome);

    // 播放列表
    m_playlistWidget = new WavPlayListWidget(this);
    connect(m_recordWidget, SIGNAL(signalRecordFile(QString)), m_playlistWidget, SLOT(SltAddWavFile(QString)));

    m_player = new QMediaPlayer(this);
    m_player->setPlaylist(m_playlistWidget->palyList());
    connect(m_player, SIGNAL(durationChanged(qint64)), this, SLOT(SltDurationChanged(qint64)));
    connect(m_player, SIGNAL(positionChanged(qint64)), this, SLOT(SltPostionChanged(qint64)));
    connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(stateChanged(QMediaPlayer::State)));

    QWidget *widgetPlayBar = new QWidget(this);
    CreatePlayBar(widgetPlayBar);
    widgetPlayBar->setMinimumHeight(120);

    // 中间区域
    QVBoxLayout *verLayoutList = new QVBoxLayout();
    verLayoutList->setContentsMargins(0, 0, 0, 0);
    verLayoutList->setSpacing(0);
    verLayoutList->addWidget(widgetTitle, 1);
    verLayoutList->addWidget(m_playlistWidget, 5);
    verLayoutList->addWidget(widgetPlayBar, 2);

    QHBoxLayout *horLayoutAll = new QHBoxLayout(this);
    horLayoutAll->setContentsMargins(0, 0, 0, 0);
    horLayoutAll->setSpacing(0);
    horLayoutAll->addWidget(m_recordWidget);
    horLayoutAll->addLayout(verLayoutList);
}

void RecorderWidget::CreatePlayBar(QWidget *parent)
{
    QHBoxLayout *horLayoutProgress = new QHBoxLayout();
    horLayoutProgress->setContentsMargins(0, 0, 0, 0);
    horLayoutProgress->setSpacing(0);

    m_labelCurrTime = new QLabel(this);
    m_labelCurrTime->setText("00:00");
    horLayoutProgress->addWidget(m_labelCurrTime);

    // 进度条
    m_progressBar = new QtSliderBar(this);
    m_progressBar->SetReadOnly(false);
    m_progressBar->SetHorizontal(true);
    m_progressBar->SetHandleBgColor(QColor("#95F204"));
    m_progressBar->SetHandleColor(QColor("#95F204"));
    m_progressBar->SetSliderSize(1, 30);
    m_progressBar->SetMaxValue(0);
    connect(m_progressBar, SIGNAL(currentValueChanged(int)), this, SLOT(SltChangePostion(int)));
    horLayoutProgress->addWidget(m_progressBar, 1);

    m_labelDuraTime = new QLabel(this);
    m_labelDuraTime->setText("00:00");
    horLayoutProgress->addWidget(m_labelDuraTime);

    ////////////////////////////////////////////////////////////////////////
    // 播放按钮
    QHBoxLayout *horLayoutPlaybtn = new QHBoxLayout();
    horLayoutPlaybtn->setContentsMargins(0, 0, 0, 0);
    horLayoutPlaybtn->setSpacing(30);
    horLayoutPlaybtn->addStretch();

    QPushButton *btnPrev = new QPushButton(this);
    btnPrev->setFocusPolicy(Qt::NoFocus);
    connect(btnPrev, SIGNAL(clicked(bool)), m_playlistWidget->palyList(), SLOT(previous()));
    horLayoutPlaybtn->addWidget(btnPrev);
    btnPrev->setFixedSize(38, 38);
    btnPrev->setStyleSheet(QString("QPushButton{border-image: url(:/images/record/ic_prev.png);}"
                                   "QPushButton:pressed{border-image: url(:/images/record/ic_prev_pre.png);}"));

    m_btnPlay = new QPushButton(this);
    m_btnPlay->setFocusPolicy(Qt::NoFocus);
    m_btnPlay->setCheckable(true);
    connect(m_btnPlay, SIGNAL(clicked(bool)), this, SLOT(SltBtnPlayClicked()));
    horLayoutPlaybtn->addWidget(m_btnPlay);
    m_btnPlay->setFixedSize(50, 50);
    m_btnPlay->setStyleSheet(QString("QPushButton{border-image: url(:/images/record/ic_play.png);}"
                                     "QPushButton::checked{border-image: url(:/images/record/ic_pause.png);}"));

    QPushButton *btnNext = new QPushButton(this);
    btnNext->setFocusPolicy(Qt::NoFocus);
    connect(btnNext, SIGNAL(clicked(bool)), m_playlistWidget->palyList(), SLOT(next()));
    horLayoutPlaybtn->addWidget(btnNext);
    btnNext->setFixedSize(38, 38);
    btnNext->setStyleSheet(QString("QPushButton{border-image: url(:/images/record/ic_next.png);}"
                                   "QPushButton:pressed{border-image: url(:/images/record/ic_next_pre.png);}"));


    horLayoutPlaybtn->addStretch();
    //////////////////////////////////////////////////////////////////
    QLabel *labelVolume = new QLabel(this);
    labelVolume->setFixedSize(42, 42);
    labelVolume->setStyleSheet(QString("QLabel{min-width: 42px;}"));
    labelVolume->setPixmap(QPixmap(":/images/record/ic_volume.png"));

    QtSliderBar *sliderVolume = new QtSliderBar(this);
    sliderVolume->SetReadOnly(false);
    sliderVolume->SetHorizontal(true);
    sliderVolume->SetMaxValue(100);
    sliderVolume->SetValue(100);
    sliderVolume->SetHandleBgColor(QColor("#95F204"));
    sliderVolume->SetHandleColor(QColor("#95F204"));
    sliderVolume->SetSliderSize(1, 24);
    connect(sliderVolume, SIGNAL(currentValueChanged(int)), m_player, SLOT(setVolume(int)));

    QHBoxLayout *horLayoutVolume = new QHBoxLayout();
    horLayoutVolume->setContentsMargins(0, 0, 0, 0);
    horLayoutVolume->setSpacing(0);
    horLayoutVolume->addWidget(labelVolume);
    horLayoutVolume->addWidget(sliderVolume, 1);

    QHBoxLayout *horLayoutBtns = new QHBoxLayout();
    horLayoutBtns->setContentsMargins(0, 0, 0, 0);
    horLayoutBtns->setSpacing(10);
    horLayoutBtns->addLayout(horLayoutVolume, 1);
    horLayoutBtns->addLayout(horLayoutPlaybtn);
    horLayoutBtns->addStretch(1);
    //////////////////////////////////////////////////////////////////
    QVBoxLayout *verLayout = new QVBoxLayout(parent);
    verLayout->setContentsMargins(10, 10, 10, 10);
    verLayout->setSpacing(10);
    verLayout->addLayout(horLayoutProgress);
    verLayout->addLayout(horLayoutBtns);

    parent->setStyleSheet(QString("QLabel{font-family: '%1'; font: 24px; color: #333333; min-width: 60px;}")
                          .arg(Skin::m_strAppFontRegular));
}

void RecorderWidget::InitPlayList()
{
    m_playlistWidget->LoadLocalFiles(qApp->applicationDirPath() + "/record/");
}

void RecorderWidget::SltBtnPlayClicked()
{
    if (m_recordWidget->isRecording()) {
        m_btnPlay->setChecked(false);
        return;
    }

    if (m_btnPlay->isChecked()) {
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
    m_labelDuraTime->setText(totalTime.toString(format));
    m_progressBar->SetMaxValue(duration / 1000);
}

void RecorderWidget::SltPostionChanged(qint64 postion)
{
    if (0 == postion) return;
    QTime currentTime = GetTimeByPostion(postion / 1000);
    QString format = "mm:ss";
    m_labelCurrTime->setText(currentTime.toString(format));
    m_progressBar->SetValue(postion/ 1000);
}

void RecorderWidget::stateChanged(QMediaPlayer::State newState)
{
    m_recordWidget->setEnabled(QMediaPlayer::PlayingState != newState);
}

void RecorderWidget::SltChangePostion(int postion)
{
    m_player->setPosition(postion * 1000);
}

void RecorderWidget::resizeEvent(QResizeEvent *e)
{
#ifdef BUILD_WITH_HDMI
    m_recordWidget->setMinimumWidth(this->width() * 0.375);
#endif
    QWidget::resizeEvent(e);
}

QTime RecorderWidget::GetTimeByPostion(int postion)
{
    return QTime((postion / 3600) % 60,
                 (postion / 60 ) % 60,
                 postion % 60, (postion * 1000) % 1000);
}

