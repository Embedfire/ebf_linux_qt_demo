/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : videolistviewer.cpp --- VideoListViewer
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "videolistviewer.h"
#include "skin.h"

#include <QPainter>
#include <QDebug>
#include <QFileInfo>

VideoListViewer::VideoListViewer(QWidget *parent) : QtPageListWidget(parent)
{
    this->SetItemLayoutSpace(5, 20);
    this->SetItemLayut(3, 5);

    m_nBaseWidth = Skin::m_nScreenWidth;
    m_nBaseHeight = 400;
}

VideoListViewer::~VideoListViewer()
{

}

void VideoListViewer::drawItemInfo(QPainter *painter, QtPageListWidgetItem *item)
{
    painter->save();
    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(18);
    painter->setFont(font);

    QPixmap pixmap = item->m_pixmapIcon;
    int nXoffset = (item->m_rect.width() - pixmap.width()) / 2;
    int nYoffset = (item->m_rect.height() - pixmap.height() - painter->fontMetrics().height() - 10) / 2;
    QRect rectPixmap(nXoffset + item->m_rect.left(), item->m_rect.top() + nYoffset, pixmap.width(), pixmap.height());
    if (pixmap.isNull()) {
        painter->setPen(QColor("#7effffff"));
        painter->drawRect(item->m_rect);
    } else {
        painter->drawPixmap(rectPixmap.topLeft(), pixmap);
    }

    painter->setPen(Qt::white);
    painter->drawText(item->m_rect.left(), rectPixmap.bottom() + 10, item->m_rect.width(), 30, Qt::AlignCenter, item->m_strBaseName);
    painter->restore();
}
