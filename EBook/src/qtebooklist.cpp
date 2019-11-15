/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : qtebooklist.cpp --- QtEbookList
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/8
*******************************************************************/
#include "qtebooklist.h"
#include "skin.h"

#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QFileInfo>

QtEbookList::QtEbookList(QWidget *parent) : QtPageListWidget(parent)
{
    m_nBaseWidth = Skin::m_nScreenWidth;
    m_nBaseHeight = 400;
    this->SetItemLayut(3, 4);
}

QtEbookList::~QtEbookList()
{

}

void QtEbookList::drawItemInfo(QPainter *painter, QtPageListWidgetItem *item)
{
    painter->save();
    painter->setPen("#dddddd");
    painter->setBrush(QColor("#eaeceb"));
    painter->drawRect(item->m_rect);

    QRect rectText = QRect(item->m_rect.left() + 10, item->m_rect.top() + 5, item->m_rect.width() - 20, item->m_rect.height() - 10);
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor("#e0e0e2"));
    painter->drawRect(rectText);

    QFileInfo fileInfo(item->m_strText);
    QFont font(Skin::m_strAppFontNormal);
    font.setPixelSize(18);;
    painter->setFont(font);
    painter->setPen("#333333");
    QTextOption option;
    option.setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    painter->drawText(QRectF(rectText.left() + 2, rectText.top() + 2, rectText.width() - 4, rectText.height() - 30),
                      fileInfo.baseName(), option);

    QString strSuffix = QString("- %1 -").arg( fileInfo.suffix());
    painter->drawText(QRect(rectText.left() + 2, rectText.bottom() - 30, rectText.width() - 4, 28),
                      Qt::AlignCenter, strSuffix);
    painter->restore();
}
