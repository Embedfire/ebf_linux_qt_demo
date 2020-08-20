/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : qtlcdclockwidget.cpp --- QtLcdClockWidget
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/10/13
*******************************************************************/
#include "qtlcdclockwidget.h"

#include <QTime>

QtLcdClockWidget::QtLcdClockWidget(QWidget *parent) : QLCDNumber(parent)
{
    this->setSegmentStyle(QLCDNumber::Filled);
    this->setDigitCount(5);

    m_strTimeFormat = "hh:mm";

    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(SltUpdateTime()));

    this->setStyleSheet(QString("QWidget {border: none; color: #ffffff;}"));
}

QtLcdClockWidget::~QtLcdClockWidget()
{
    m_timer->stop();
    delete m_timer;
    m_timer = NULL;
}

void QtLcdClockWidget::setApMode(bool on)
{
    if (on) {
        this->setDigitCount(5);
        m_strTimeFormat = "hh:mm";
    } else {
        this->setDigitCount(8);
        m_strTimeFormat = "hh:mm AP";
    }
}

void QtLcdClockWidget::SltUpdateTime()
{
    this->display(QTime::currentTime().toString(m_strTimeFormat));
}

void QtLcdClockWidget::showEvent(QShowEvent *e)
{
    if (!m_timer->isActive()) m_timer->start();
    this->display(QTime::currentTime().toString(m_strTimeFormat));
    QWidget::showEvent(e) ;
}

void QtLcdClockWidget::hideEvent(QHideEvent *e)
{
    m_timer->stop();
    QWidget::hideEvent(e);
}

void QtLcdClockWidget::mousePressEvent(QMouseEvent *)
{
    emit signalClicked();
}
