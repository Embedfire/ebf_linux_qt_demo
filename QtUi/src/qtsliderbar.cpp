/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : qtsliderbar.cpp --- QtSliderBar
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/8/30
*******************************************************************/
#include "qtsliderbar.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

QtSliderBar::QtSliderBar(QWidget *parent) : QWidget(parent),
    m_nDirection(Vertical),m_nCurrentValue(100),m_nMaxValue(100),
    m_bPressed(false),m_starPos(0,0),m_nOffset(50)
{
    this->setAttribute(Qt::WA_TranslucentBackground);

    m_nSliderSize = 4;
    m_nHandleSize = 30;
    m_bReadOnly = false;

    m_bShowHandleBg = true;
    m_colorSlider = QColor("#ffffff");
    m_colorHandle = QColor("#00ffff");
    m_colorHandleBg = QColor("#7f00ffff");
}

QtSliderBar::~QtSliderBar()
{

}

void QtSliderBar::SetHorizontal(bool bOk)
{
    m_nDirection = bOk ? Horizontal : Vertical;
    this->update();
}

void QtSliderBar::SetSliderSize(int sliderSize, int handleSize)
{
    m_nSliderSize = sliderSize;
    m_nHandleSize = handleSize;
    if (Horizontal == m_nDirection) {
        this->setMinimumHeight(handleSize);
    } else {
        this->setMinimumWidth(handleSize);
    }
    this->update();
}

void QtSliderBar::SetMaxValue(int value)
{
    this->m_nMaxValue = value;
}

void QtSliderBar::SetValue(int value)
{
    if (0 == m_nMaxValue || value > m_nMaxValue) return;
    this->m_nCurrentValue = value;
    if (Horizontal == m_nDirection) {
        m_nOffset = (value * 1.0) / m_nMaxValue * (this->width() - m_nHandleSize) + m_nHandleSize / 2;
    } else {
        m_nOffset = this->height() - (value * 1.0) / m_nMaxValue * (this->height() - m_nHandleSize) - m_nHandleSize / 2;
    }
    this->update();
}

void QtSliderBar::SetReadOnly(bool bOk)
{
    this->m_bReadOnly = bOk;
}

void QtSliderBar::ShowHandleBackground(bool bOk)
{
    m_bShowHandleBg = bOk;
    this->update();
}

void QtSliderBar::SetSlidetColor(const QColor &color)
{
    m_colorSlider = color;
    this->update();
}

void QtSliderBar::SetHandleColor(const QColor &color)
{
    if (!color.isValid()) return;
    m_colorHandle = color;
    this->update();
}

void QtSliderBar::SetHandleBgColor(const QColor &color)
{
    if (!color.isValid()) return;
    m_colorHandleBg = color;
    this->update();
}

void QtSliderBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if (m_nDirection == Horizontal) {
        drawHorizontalBar(&painter);
    } else if (Vertical == m_nDirection) {
        drawVerticalBar(&painter);
    }
}

void QtSliderBar::drawHorizontalBar(QPainter *painter)
{
    painter->save();
    QPen pen(m_colorSlider, m_nSliderSize, Qt::SolidLine, Qt::RoundCap);
    painter->setPen(pen);
    int nY = this->height() / 2;
    int radius = m_nHandleSize / 2;
    painter->drawLine(radius, nY, this->width() - radius, nY);

    // 先绘制那个大圆
    QRect rect(m_nOffset - radius, nY - radius, m_nHandleSize, m_nHandleSize);
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_bShowHandleBg ? m_colorHandleBg : m_colorHandle);
    painter->drawEllipse(rect.left(), rect.top(), m_nHandleSize, m_nHandleSize);

    QPainterPath path;
    path.moveTo(radius, nY);
    path.lineTo((m_nOffset >= m_nHandleSize) ? m_nOffset - radius : radius, nY);
    path.addEllipse(rect.left() + radius / 2, nY - radius / 2, radius, radius);

    pen.setColor(m_colorHandle);
    painter->setPen(pen);
    painter->setBrush(m_colorHandle);
    painter->drawPath(path);
    painter->restore();
}

void QtSliderBar::drawVerticalBar(QPainter *painter)
{
    painter->save();
    QPen pen(m_colorSlider, m_nSliderSize, Qt::SolidLine, Qt::RoundCap);
    painter->setPen(pen);
    int nX = this->width() / 2;
    int radius = m_nHandleSize / 2;
    painter->drawLine(nX, radius, nX, this->height() - radius);

    // 先绘制那个大圆
    QRect rect((this->width() - m_nHandleSize) / 2, m_nOffset - radius, m_nHandleSize, m_nHandleSize);
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_bShowHandleBg ? m_colorHandleBg : m_colorHandle);
    painter->drawEllipse(rect.left(), rect.top(), m_nHandleSize, m_nHandleSize);

    QPainterPath path;
    path.moveTo(nX, this->height() - radius);
    path.lineTo(nX, (m_nOffset > (this->height() - m_nHandleSize)) ? m_nOffset : m_nOffset + radius);
    path.addEllipse(nX - radius / 2, rect.top() + radius / 2, radius, radius);

    pen.setColor(m_colorHandle);
    painter->setPen(pen);
    painter->setBrush(m_colorHandle);
    painter->drawPath(path);
    painter->restore();
}

void QtSliderBar::mousePressEvent(QMouseEvent *e)
{
    if (!m_bReadOnly) {
        m_bPressed = true;
        m_starPos = e->pos();
    }
}

void QtSliderBar::mouseReleaseEvent(QMouseEvent *e)
{
    m_bPressed = false;
    QWidget::mouseReleaseEvent(e);
}

void QtSliderBar::mouseMoveEvent(QMouseEvent *e)
{
    if (m_bPressed && 0 != m_nMaxValue) {
        if (Vertical == m_nDirection) {
            if ((e->y() >= (m_nHandleSize / 2)) && (e->y() <= (this->height() - m_nHandleSize / 2)))
            {
                m_nOffset = e->y();
                int nOffset = (this->height() - m_nOffset - m_nHandleSize / 2);
                m_nCurrentValue = (nOffset * 1.0 / (this->height() - m_nHandleSize)) * m_nMaxValue;
                emit currentValueChanged(m_nCurrentValue);
                this->update();
            }
        } else if (Horizontal == m_nDirection) {
            if ((e->x() >= m_nHandleSize / 2) && e->x() <= (this->width() - m_nHandleSize / 2)) {
                m_nOffset = e->x();
                m_nCurrentValue = ((m_nOffset - m_nHandleSize / 2) * 1.0 / (this->width() - m_nHandleSize)) * m_nMaxValue;
                emit currentValueChanged(m_nCurrentValue);
                this->update();
            }
        }
    }

    QWidget::mouseMoveEvent(e);
}
