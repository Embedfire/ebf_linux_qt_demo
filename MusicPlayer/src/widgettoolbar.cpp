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
#include "skin.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QTime>

///////////////////////////////////////////////////////////////////
WidgetToolBar::WidgetToolBar(QWidget *parent) : QtWidgetBase(parent)
{
    m_nBaseWidth = Skin::m_nScreenWidth;
    m_nBaseHeight = 69;

    m_strCurrTime = "00:00";
    m_strDuration = "00:00";

    m_bPlaying = false;
    m_nMaxValue = 0;
    m_nCurrentValue = 0;

    InitWidget();
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
    m_strCurrTime = currentTime.toString(format);
    m_strDuration = totalTime.toString(format);
    m_progressBar->SetValue(postion);
    this->update();
}

void WidgetToolBar::SetDuration(int duration)
{
    this->m_nMaxValue = duration;
    m_progressBar->SetMaxValue(duration);
    m_progressBar->SetValue(0);
    m_nCurrentValue = 0;

    QTime totalTime = GetTimeByPostion(m_nMaxValue);
    QString format = "mm:ss";
    if (m_nMaxValue > 3600) format = "hh:mm:ss";
    m_strCurrTime = "00:00";
    m_strDuration = totalTime.toString(format);
    this->update();
}

void WidgetToolBar::SetPlayState(bool state)
{
    m_bPlaying = state;
    m_btns.value(1)->setChecked(state);
}

void WidgetToolBar::InitWidget()
{
    m_progressBar = new QtSliderBar(this);
    m_progressBar->SetHorizontal(true);
    m_progressBar->SetMaxValue(0);
    m_progressBar->SetValue(0);
    connect(m_progressBar, SIGNAL(currentValueChanged(int)), this, SIGNAL(currentPostionChanged(int)));

    m_btns.insert(0, new QtPixmapButton(0, QRect(12, 4, 60, 60), QPixmap(":/images/music/ic_prev.png"), QPixmap(":/images/music/ic_prev_pre.png")));
    m_btns.insert(1, new QtPixmapButton(1, QRect(64, 4, 60, 60), QPixmap(":/images/music/ic_play.png"), QPixmap(":/images/music/ic_pause.png")));
    m_btns.insert(2, new QtPixmapButton(2, QRect(128, 4, 60, 60), QPixmap(":/images/music/ic_next.png"), QPixmap(":/images/music/ic_next_pre.png")));
    m_btns.insert(3, new QtPixmapButton(3, QRect(680, 4, 60, 60), QPixmap(":/images/video/ic_volume.png"), QPixmap(":/images/video/ic_volume_pre.png")));
    m_btns.insert(4, new QtPixmapButton(4, QRect(740, 4, 60, 60), QPixmap(":/images/video/ic_menu_list.png"), QPixmap(":/images/video/ic_menu_list_pre.png")));
    m_btns.value(1)->setCheckAble(true);
    connect(this, SIGNAL(signalBtnClicked(int)), this, SLOT(SltBtnClicket(int)));
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
    m_btns.value(1)->setChecked(m_bPlaying);
    if (m_bPlaying) {emit play();}
    else {emit pause();}
}

void WidgetToolBar::SltBtnClicket(int index)
{
    if (0 == index) {
        emit previous();
    } else if (1 == index) {
        SltBtnPlayClicked();
    } else if (2 == index) {
        emit next();
    } else if (3 == index) {
        emit toolBarClicked(2);
    } else if (4 == index) {
        emit toolBarClicked(3);
    }
}

void WidgetToolBar::resizeEvent(QResizeEvent *e)
{
    SetScaleValue();

    m_progressBar->resize(350 * m_scaleX, 30 * m_scaleX);
    m_progressBar->SetSliderSize(1, 30 * m_scaleX);
    m_progressBar->move(245 * m_scaleX, 20 * m_scaleX);
    m_progressBar->SetValue(m_progressBar->value());

    QWidget::resizeEvent(e);
}

void WidgetToolBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.scale(m_scaleX, m_scaleY);
    painter.setBrush(QColor("#72ffffff"));
    painter.drawRect(0, 0, m_nBaseWidth, m_nBaseHeight);

    painter.setPen(QColor("#ffffff"));
    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(18);
    painter.setFont(font);

    painter.drawText(QRect(188, 15, 60, 40), Qt::AlignCenter, m_strCurrTime);
    painter.drawText(QRect(610, 15, 60, 40), Qt::AlignCenter, m_strDuration);

    foreach (QtPixmapButton *btn, m_btns) {
        int nX = btn->rect().left() + (btn->rect().width() - btn->pixmap().width()) / 2;
        int nY = btn->rect().top() + (btn->rect().height() - btn->pixmap().height()) / 2;
        painter.drawPixmap(nX, nY, btn->pixmap());
    }
}

