/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : clickedwidget.cpp --- ClickedWidget
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "clickedwidget.h"
#include "skin.h"

#include <QPainter>

ClickedWidget::ClickedWidget(QWidget *parent) : QWidget(parent)
{
    m_nIndex = 0;
    m_strText = "";
    this->setMinimumHeight(44);
}

ClickedWidget::~ClickedWidget()
{

}

void ClickedWidget::setIndex(int index, const QString &text)
{
     m_nIndex = index;
     m_strText = text;
     this->update();
}

void ClickedWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QColor("#797979"));
    painter.drawLine(this->rect().bottomLeft(), this->rect().bottomRight());

    QFont font(Skin::m_strAppFontNormal);
    font.setPixelSize(24);
    painter.setFont(font);
    painter.setPen(QColor("#ffffff"));
    painter.drawText(this->rect(), Qt::AlignVCenter, m_strText);
    QPixmap pixmap(":/images/setting/ic_next.png");
    painter.drawPixmap(this->width() - pixmap.width() - 20, (this->height() - pixmap.height()) / 2, pixmap);
}

void ClickedWidget::mouseReleaseEvent(QMouseEvent *)
{
    emit signalClicked(m_nIndex);
}
