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

QtPixmapButton::QtPixmapButton(QPixmap pixmapNormal, QPixmap pixmapPressed)  :
    m_nId(0),m_rect(0, 0, 0, 0),m_pixmapNormal(pixmapNormal),
    m_pixmapPressed(pixmapPressed),m_bPressed(false)
{

}

QtPixmapButton::QtPixmapButton(int id, QRect rect, QPixmap pixmapNormal, QPixmap pixmapPressed) :
    m_nId(id),m_rect(rect),m_pixmapNormal(pixmapNormal),
    m_pixmapPressed(pixmapPressed),m_bPressed(false)
{

}

int QtPixmapButton::id()
{
    return m_nId;
}

QRect QtPixmapButton::rect()
{
    return m_rect;
}

void QtPixmapButton::setRect(QRect rect)
{
    m_rect = rect;
}

QPixmap QtPixmapButton::pixmap()
{
    return m_bPressed ? m_pixmapPressed : m_pixmapNormal;
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

QSize QtPixmapButton::size() const
{
    return (m_pixmapNormal.isNull()) ? QSize(60, 30) : m_pixmapNormal.size();
}
