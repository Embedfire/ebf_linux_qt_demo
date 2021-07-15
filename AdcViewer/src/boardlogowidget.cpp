/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : boardlogowidget.cpp --- BoardLogoWidget
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/1
*******************************************************************/
#include "boardlogowidget.h"
#include "skin.h"
#include <QPainter>
#include <QPainterPath>

BoardLogoWidget::BoardLogoWidget(QWidget *parent) : QWidget(parent)
{
    this->setMinimumSize(364, 332);
    m_pixmap = QPixmap(":/images/adc/ic_board_157.png");
}

BoardLogoWidget::~BoardLogoWidget()
{

}

void BoardLogoWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
#ifdef BUILD_WITH_HDMI
    if (this->height() > Skin::m_nScreenHeight) {
        painter.scale(this->width() * 1.0 / 364, this->height() * 1.0 / 332);
    }
#endif
    painter.drawPixmap(0, 0, m_pixmap.width(), m_pixmap.height(), m_pixmap);
    drawPointLine(&painter);
}

void BoardLogoWidget::drawPointLine(QPainter *painter)
{
    painter->save();
    QPainterPath path;
    //path.moveTo(45, 195);
    //path.lineTo(221, 195);
    //path.lineTo(221, 300);
    path.moveTo(300, 165);
    path.lineTo(300, 205);

    painter->setPen(QPen(QColor("#ffffff"), 2));
    painter->drawPath(path);

    QFont font(Skin::m_strAppFontNormal);
    font.setPixelSize(22);
    font.setBold(true);
    painter->setFont(font);
    int nH = painter->fontMetrics().height();
    //painter->drawText(230, 300, tr("调节电压"));
    painter->drawText(250, 300, tr("调节电压"));

    font.setPixelSize(18);
    painter->setFont(font);
    //painter->drawText(230, 290 - nH, tr("旋转电位器"));
    painter->drawText(250, 290 - nH, tr("旋转电位器"));
    painter->restore();

}

