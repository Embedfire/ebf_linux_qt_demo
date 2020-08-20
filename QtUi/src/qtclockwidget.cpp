/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : qtclockwidget.cpp --- QtClockWidget
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/7
*******************************************************************/
#include "qtclockwidget.h"

#include <QTime>
#include <QPainter>

QtClockWidget::QtClockWidget(QWidget *parent) : QtWidgetBase(parent)
{
    m_nBaseWidth = 233;
    m_nBaseHeight = 243;

    SetClockStyle(QtClockWidget::DefaultStyle);
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    m_timer->start();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(SltUpdateTime()));
}

QtClockWidget::~QtClockWidget()
{
    m_timer->stop();
}

void QtClockWidget::SetClockStyle(QtClockWidget::ClockStyle style)
{
    if (style >= StyleCount) return;
    m_colorStyle = style;
    int nIndex = m_colorStyle;
    m_pixmapBackground = QPixmap(QString(":/images/calendar/clock_%1_background.png").arg(nIndex, 2, 10, QChar('0')));
    m_pixmapHourHand = QPixmap(QString(":/images/calendar/clock_%1_hour_hand.png").arg(nIndex, 2, 10, QChar('0')));
    m_pixmapMinuteHand = QPixmap(QString(":/images/calendar/clock_%1_minute_hand.png").arg(nIndex, 2, 10, QChar('0')));
    m_pixmapSecondHand = QPixmap(QString(":/images/calendar/clock_%1_second_hand.png").arg(nIndex, 2, 10, QChar('0')));
    this->update();
}

void QtClockWidget::SltUpdateTime()
{
    this->update();
}

QSize QtClockWidget::sizeHint() const
{
   return QSize(233, 243);
}

void QtClockWidget::paintEvent(QPaintEvent *)
{
    // 绘制准备工作,启用反锯齿,启用图片平滑缩放
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.scale(m_scaleX, m_scaleY);
    // 绘制背景
    painter.drawPixmap(0, 0, m_nBaseWidth, m_nBaseHeight, m_pixmapBackground);

    // 绘制时分秒指针
    painter.translate(m_nBaseWidth / 2, m_nBaseHeight / 2);
    drawHourHand(&painter);
    drawMinuteHand(&painter);
    drawSecondHand(&painter);
}

void QtClockWidget::drawBackground(QPainter *painter)
{
    painter->save();
    int pixX = rect().center().x() - m_pixmapBackground.width() / 2;
    int pixY = rect().center().y() - m_pixmapBackground.height() / 2;
    QPoint point(pixX, pixY);
    painter->drawPixmap(point, m_pixmapBackground);
    painter->restore();
}

void QtClockWidget::drawHourHand(QPainter *painter)
{
    QTime time = QTime::currentTime();
    painter->save();
    painter->rotate(30.0 * ((time.hour() + time.minute() / 60.0)));

    if (BlackStyle == m_colorStyle) {
        painter->drawPixmap(0, -m_nBaseHeight / 2 + 20, m_pixmapHourHand);
    }
    else {
        int nOffset = (BlackStyle == m_colorStyle) ? -m_pixmapHourHand.width() / 2 : 10;
        int pixX =  -m_pixmapHourHand.width() / 2;
        int pixY =  -m_pixmapHourHand.height() + nOffset;
        painter->drawPixmap(pixX, pixY, m_pixmapHourHand);
    }

    painter->restore();
}

void QtClockWidget::drawMinuteHand(QPainter *painter)
{
    QTime time = QTime::currentTime();
    painter->save();
    painter->rotate(6.0 * (time.minute() + time.second() / 60.0));
    int pixX =  -m_pixmapMinuteHand.width() / 2;
    int pixY =  -m_pixmapMinuteHand.height() + 10;
    painter->drawPixmap(pixX, pixY, m_pixmapMinuteHand);
    painter->restore();
}

void QtClockWidget::drawSecondHand(QPainter *painter)
{
    QTime time = QTime::currentTime();
    qreal angleSpring = 6.0 * (time.second() + (double)time.msec() / 1000);
    painter->save();
    painter->rotate(angleSpring);
    int nOffset = 0;
    if ((DefaultStyle == m_colorStyle)) nOffset = 22;
    if (BlackStyle == m_colorStyle) nOffset = 15;
    if (LightStyle == m_colorStyle) nOffset = 20;

    int pixX =  -m_pixmapSecondHand.width() / 2;
    int pixY =  -m_pixmapSecondHand.height() + nOffset;
    painter->drawPixmap(pixX, pixY, m_pixmapSecondHand);
    painter->restore();
}

void QtClockWidget::showEvent(QShowEvent *e)
{
    if (!m_timer->isActive()) m_timer->start();
    QWidget::showEvent(e);
}

void QtClockWidget::hideEvent(QHideEvent *e)
{
    m_timer->stop();
    QWidget::hideEvent(e);
}

void QtClockWidget::mousePressEvent(QMouseEvent *)
{
    emit signalClicked();
}
