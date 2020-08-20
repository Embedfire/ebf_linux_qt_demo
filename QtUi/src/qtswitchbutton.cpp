/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : qtswitchbutton.cpp --- QtSwitchButton
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/15
*******************************************************************/
#include "qtswitchbutton.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

QtSwitchButton::QtSwitchButton(QWidget *parent) : QWidget(parent)
{
    m_bHorizontal = true;
    m_bChecked = false;
    m_colorBackground = QColor("#ffffff");
    m_colorHandle = QColor("#00ffff");
}

QtSwitchButton::~QtSwitchButton()
{

}

void QtSwitchButton::setHorizontal(bool bOk)
{
    m_bHorizontal = bOk;
    this->update();
}

bool QtSwitchButton::isChecked()
{
    return m_bChecked;
}

void QtSwitchButton::setChecked(bool bOk)
{
    if (m_bChecked != bOk) {
        m_bChecked = bOk;
        emit buttonChecked(m_bChecked);
        this->update();
    }
}

void QtSwitchButton::setBackgroundColor(const QColor &color)
{
    if (!color.isValid()) return;
    m_colorBackground = color;
    this->update();
}

void QtSwitchButton::setHandleColor(const QColor &color)
{
    if (!color.isValid()) return;
    m_colorHandle = color;
    this->update();
}

QSize QtSwitchButton::sizeHint() const
{
    return QSize(50, 25);
}

void QtSwitchButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_colorBackground);
    qreal randius = m_bHorizontal ? this->height() : this->width();
    painter.drawRoundedRect(this->rect(), randius / 2, randius / 2);

    drawRandStyle(&painter);
}

void QtSwitchButton::drawRandStyle(QPainter *painter)
{
    painter->save();
    qreal randius = m_bHorizontal ? this->height() : this->width();
    randius -= 2;
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_colorHandle);

    if (m_bHorizontal) {
        int nX = m_bChecked ? (this->width() - 1 - randius) : 1;
        painter->drawEllipse(nX, 1, randius, randius);
    } else {
        int nY= m_bChecked ? (this->height() - 1 - randius) : 1;
        painter->drawEllipse(1, nY, randius, randius);
    }
    painter->restore();
}

void QtSwitchButton::mousePressEvent(QMouseEvent *)
{
    m_bChecked = !m_bChecked;
    emit buttonChecked(m_bChecked);
    this->update();
}
