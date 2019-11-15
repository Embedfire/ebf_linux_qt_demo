/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : photolistview.cpp --- PhotoListView
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/8
*******************************************************************/
#include "photolistview.h"
#include <QPainter>
#include <QDebug>

PhotoListView::PhotoListView(QWidget *parent) : QtPageListWidget(parent)
{
    this->SetItemLayoutSpace(0, 0);
    this->SetItemLayut(2, 4);
}

PhotoListView::~PhotoListView()
{

}

void PhotoListView::drawItemInfo(QPainter *painter, QtPageListWidgetItem *item)
{
    painter->save();

    if (item->m_pixmapIcon.isNull()) {
        QFont font = painter->font();
        font.setPixelSize(32);
        painter->setFont(font);
        painter->setPen("#ff0000");
        painter->drawText(item->m_rect, Qt::AlignCenter, tr("图片已损坏"));
    }
    else {
        painter->drawPixmap(item->m_rect, item->m_pixmapIcon);
        painter->setPen(QPen(QColor("#ffffff"), 2));
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(item->m_rect);
    }
    painter->restore();
}
