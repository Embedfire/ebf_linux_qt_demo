/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : qtplaytoolbar.cpp --- QtPlayToolBar
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/14
*******************************************************************/
#include "qtplaytoolbar.h"
#include "skin.h"

#include <QPainter>
#include <QMouseEvent>
#include <QButtonGroup>

//////////////////////////////////////////////////////////////////////////////////////
PlayTitleBarWidget::PlayTitleBarWidget(QWidget *parent) : QtToolBar(parent)
{
    m_strText = "";
    this->setFixedHeight(50);
    m_rectBack = QRect(20, 10, 40, 40);
}

PlayTitleBarWidget::~PlayTitleBarWidget()
{

}

void PlayTitleBarWidget::SetText(const QString &text)
{
    m_strText = text;
    this->update();
}

void PlayTitleBarWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), QColor("#7f182E3A"));

    painter.drawPixmap(m_rectBack.topLeft(), QPixmap(":/images/photos/toolbar/ic_back.png"));

    painter.setPen("#ffffff");
    painter.setFont(QFont(Skin::m_strAppFontNormal, 18));
    painter.drawText(this->rect(), Qt::AlignCenter, m_strText);
}

void PlayTitleBarWidget::mousePressEvent(QMouseEvent *e)
{
    if (m_rectBack.contains(e->pos())) {
        emit signalBack();
    }
    QWidget::mousePressEvent(e);
}


//////////////////////////////////////////////////////////////////////////////////////
PlayerBarWidget::PlayerBarWidget(QWidget *parent) : QtToolBar(parent)
{
    this->setFixedHeight(102);
    this->setAttribute(Qt::WA_TranslucentBackground);
    InitWidget();
}

PlayerBarWidget::~PlayerBarWidget()
{

}

void PlayerBarWidget::setPlayState(bool bOk)
{
    m_btnPlay->setChecked(bOk);
}

void PlayerBarWidget::setPostion(int postion)
{
    m_sliderBar->SetValue(postion);
    m_labelPostion->setText(QString("%1:%2").arg(postion / 60, 2, 10, QChar('0')).arg(postion % 60, 2, 10, QChar('0')));
}

void PlayerBarWidget::setDuration(int duration)
{
    m_sliderBar->SetMaxValue(duration);
    m_labelDuration->setText(QString("%1:%2").arg(duration / 60, 2, 10, QChar('0')).arg(duration % 60, 2, 10, QChar('0')));
}

void PlayerBarWidget::InitWidget()
{
    m_labelPostion = new QLabel(this);
    m_labelPostion->setText("00:00");
    m_labelDuration = new QLabel(this);
    m_labelDuration->setText("00:00");

    m_sliderBar = new QtSliderBar(this);
    m_sliderBar->SetHorizontal(true);
    m_sliderBar->setMinimumHeight(40);
    m_sliderBar->SetSliderSize(2, 40);
    connect(m_sliderBar, SIGNAL(currentValueChanged(int)), this, SIGNAL(currentPostionChanged(int)));

    QHBoxLayout *horLayoutDuration = new QHBoxLayout();
    horLayoutDuration->setContentsMargins(0, 0, 0, 0);
    horLayoutDuration->setSpacing(0);
    horLayoutDuration->addWidget(m_labelPostion);
    horLayoutDuration->addWidget(m_sliderBar, 1);
    horLayoutDuration->addWidget(m_labelDuration);

    QHBoxLayout *horLayoutBtns = new QHBoxLayout();
    horLayoutBtns->setContentsMargins(10, 10, 10, 10);
    horLayoutBtns->setSpacing(28);
    horLayoutBtns->addStretch(1);

    m_btnPrev = new QPushButton(this);
    m_btnPrev->setStyleSheet(QString("QPushButton {border-image: url(:/images/video/ic_prev.png);}"
                                     "QPushButton:pressed {border-image: url(:/images/video/ic_prev_pre.png);}"));
    horLayoutBtns->addWidget(m_btnPrev);
    connect(m_btnPrev, SIGNAL(clicked(bool)), this, SIGNAL(signalPrev()));

    m_btnPlay = new QPushButton(this);
    connect(m_btnPlay, SIGNAL(clicked(bool)), this, SIGNAL(signalPlay(bool)));
    m_btnPlay->setCheckable(true);
    m_btnPlay->setChecked(true);
    m_btnPlay->setStyleSheet(QString("QPushButton {border-image: url(:/images/video/ic_play.png);}"
                                     "QPushButton:checked {border-image: url(:/images/video/ic_pause.png);}"));
    horLayoutBtns->addWidget(m_btnPlay);

    m_btnNext = new QPushButton(this);
    m_btnNext->setStyleSheet(QString("QPushButton {border-image: url(:/images/video/ic_next.png);}"
                                     "QPushButton:pressed {border-image: url(:/images/video/ic_next_pre.png);}"));
    horLayoutBtns->addWidget(m_btnNext);
    connect(m_btnNext, SIGNAL(clicked(bool)), this, SIGNAL(signalNext()));

    horLayoutBtns->addStretch(1);
    m_btnVolume = new QPushButton(this);
    m_btnVolume->setStyleSheet(QString("QPushButton {border-image: url(:/images/video/ic_volume.png);}"
                                       "QPushButton:pressed {border-image: url(:/images/video/ic_volume_pre.png);}"));
    horLayoutBtns->addWidget(m_btnVolume);
    connect(m_btnVolume, SIGNAL(clicked(bool)), this, SIGNAL(signalVolume()));

    m_btnMenuList = new QPushButton(this);
    m_btnMenuList->setStyleSheet(QString("QPushButton {border-image: url(:/images/video/ic_menu_list.png);}"
                                         "QPushButton:pressed {border-image: url(:/images/video/ic_menu_list_pre.png);}"));
    horLayoutBtns->addWidget(m_btnMenuList);
    connect(m_btnMenuList, SIGNAL(clicked(bool)), this, SIGNAL(signalMuenList()));

    QVBoxLayout *verLayoutAll =  new QVBoxLayout(this);
    verLayoutAll->setContentsMargins(5, 5, 5, 5);
    verLayoutAll->setSpacing(0);
    verLayoutAll->addLayout(horLayoutDuration);
    verLayoutAll->addLayout(horLayoutBtns);

    this->setStyleSheet(QString("QPushButton {min-width: 40px; min-height: 40px;} "
                                "QLabel {font-family:'%1';font: 18px; color: #ffffff;"
                                "min-width: 60px;}").arg(Skin::m_strAppFontBold));
}

void PlayerBarWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QLinearGradient linearGradient(QPoint(0, 0), QPoint(0, this->height()));
    linearGradient.setColorAt(0, QColor("#00aaaaaa"));
    linearGradient.setColorAt(1, QColor("#d0aaaaaa"));
    painter.setPen(Qt::NoPen);
    painter.setBrush(linearGradient);
    painter.drawRect(this->rect());
}
