/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : qtpixmapbutton.cpp --- QtPixmapButton
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "qtpixmapbutton.h"

QtPixmapButton::QtPixmapButton() : m_nId(0),m_rect(0, 0, 0, 0),
    m_strText(""),m_pixmapNormal(QPixmap()),m_pixmapPressed(QPixmap()),
    m_bPressed(false),m_bVisible(true),
    m_bCheckAble(false),m_bChecked(false),m_bEnable(true)
{

}

QtPixmapButton::QtPixmapButton(int id, QRect rect, QString text, QColor normal, QColor pressed) :
    m_nId(id),m_rect(rect),m_strText(text),m_colorNormal(normal),m_colorPressed(pressed),
    m_bPressed(false),m_bVisible(true),m_bCheckAble(false),m_bChecked(false),m_bEnable(true)
{

}

QtPixmapButton::QtPixmapButton(QPixmap pixmapNormal, QPixmap pixmapPressed)  :
    m_nId(0),m_rect(0, 0, 0, 0),m_strText(""),m_pixmapNormal(pixmapNormal),
    m_pixmapPressed(pixmapPressed),m_bPressed(false),m_bVisible(true),
    m_bCheckAble(false),m_bChecked(false),m_bEnable(true)
{

}

QtPixmapButton::QtPixmapButton(int id, QRect rect, QPixmap pixmapNormal, QPixmap pixmapPressed) :
    m_nId(id),m_rect(rect),m_strText(""),m_pixmapNormal(pixmapNormal),
    m_pixmapPressed(pixmapPressed),m_bPressed(false),m_bVisible(true),
    m_bCheckAble(false),m_bChecked(false),m_bEnable(true)
{

}

int QtPixmapButton::id()
{
    return m_nId;
}

QRect QtPixmapButton::rect()
{
    return m_bVisible ? m_rect : QRect(0, 0, 0, 0);
}

void QtPixmapButton::setRect(QRect rect)
{
    m_rect = rect;
}

QColor QtPixmapButton::color()
{
    if (!m_bEnable) return m_colorPressed;
    return (m_bPressed || m_bChecked) ? m_colorPressed : m_colorNormal;
}

void QtPixmapButton::setColor(QColor normal, QColor pressed)
{
    m_colorNormal = normal;
    m_colorPressed = pressed;
}

QPixmap QtPixmapButton::pixmap()
{
    return (m_bPressed || m_bChecked) ? m_pixmapPressed : m_pixmapNormal;
}

void QtPixmapButton::setPixmap(const QPixmap &normal, const QPixmap &pressed)
{
    if (normal.isNull() || pressed.isNull()) return;

    m_pixmapNormal = normal;
    m_pixmapPressed = pressed;
}

QString QtPixmapButton::text()
{
    return m_strText;
}

void QtPixmapButton::setText(const QString &text)
{
    m_strText = text;
}

void QtPixmapButton::setPressed(bool bOk)
{
    m_bPressed = bOk;
}

bool QtPixmapButton::isPressed()
{
    return m_bPressed;
}

void QtPixmapButton::setVisible(bool bOk)
{
    m_bVisible = bOk;
}

bool QtPixmapButton::isVisible()
{
    return m_bVisible;
}


void QtPixmapButton::setCheckAble(bool bOk)
{
    m_bCheckAble = bOk;
}

bool QtPixmapButton::isCheckAble()
{
    return m_bCheckAble;
}

void QtPixmapButton::setChecked(bool bOk)
{
    if (!m_bCheckAble) return;
    m_bChecked = bOk;
}

bool QtPixmapButton::isChecked()
{
    return m_bChecked;
}

void QtPixmapButton::setEnable(bool bOk)
{
    m_bEnable = bOk;
}

bool QtPixmapButton::isEnabled()
{
    return m_bEnable;
}

QSize QtPixmapButton::size() const
{
    return (m_pixmapNormal.isNull()) ? QSize(60, 30) : m_pixmapNormal.size();
}
