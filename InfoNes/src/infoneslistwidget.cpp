/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : infoneslistwidget.cpp --- InfoNesListWidget
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/10/19
*******************************************************************/
#include "infoneslistwidget.h"
#include "skin.h"

#include <QFileInfo>
#include <QDir>
#include <QPainter>
#include <QDebug>

InfoNesListWidget::InfoNesListWidget(QWidget *parent) : QtListWidget(parent)
{
    m_backgroundColor = Qt::transparent;
    m_nItemSize = 60;
    m_bHorizontal = false;
    m_nBaseWidth = Skin::m_nScreenWidth;
    m_nBaseHeight = 400;
}

InfoNesListWidget::~InfoNesListWidget()
{

}

void InfoNesListWidget::LoadNesResource(const QString &path)
{
    QDir dir(path);
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QFileInfoList list = dir.entryInfoList(QStringList() << "*.nes");
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        m_listItems.insert(i, new QtListWidgetItem(i, fileInfo.absoluteFilePath(), fileInfo.fileName(), QPixmap(":/images/infones/ic_next.png")));
    }

    this->update();
}

void InfoNesListWidget::drawItemInfo(QPainter *painter, QtListWidgetItem *item)
{
    painter->save();
    painter->setPen(QColor("#797979"));
    painter->drawLine(QPoint(item->m_rect.left() - m_nMargin, item->m_rect.bottom()),
                      QPoint(item->m_rect.right() + m_nMargin, item->m_rect.bottom()));

    QRect rect(item->m_rect.left() + 20, item->m_rect.top(), item->m_rect.width() - 40, item->m_rect.height());
    QFont font(Skin::m_strAppFontNormal);
    font.setPixelSize(24);
    painter->setFont(font);
    painter->setPen(QColor("#ffffff"));
    painter->drawText(rect, Qt::AlignVCenter, item->m_strBaseName);

    QPixmap pixmap = item->m_pixmapIcon;
    painter->drawPixmap(m_nBaseWidth - pixmap.width() - 20, rect.top() + (rect.height() - pixmap.height()) / 2, pixmap);

    painter->restore();
}

