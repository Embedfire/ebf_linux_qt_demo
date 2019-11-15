/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : displayrealdata.cpp --- DisplayRealData
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/2
*******************************************************************/
#include "displayrealdata.h"
#include "skin.h"

#include <QPainter>
#include <QDebug>

DisplayRealData::DisplayRealData(QWidget *parent) : QtWidgetBase(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    m_pixmap = QPixmap(":/images/dht/dht_background.png");
}

DisplayRealData::~DisplayRealData()
{

}

void DisplayRealData::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.scale(this->width() * 1.0 / Skin::m_nScreenWidth, this->height() * 1.0 / 343);
    painter.drawPixmap(0, 0, m_pixmap);
    painter.setPen(QPen(Qt::white, 3, Qt::SolidLine, Qt::RoundCap));
    painter.drawLine(QPoint(280, 140), QPoint(280, 240));

    // 绘制提示文字
    painter.setPen(Qt::white);
    QTextOption option;
    option.setAlignment(Qt::AlignCenter);
    option.setWrapMode(QTextOption::WordWrap);
    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(24);
    painter.setFont(font);
    painter.drawText(QRect(202, 240, 127, 66), tr("插入DHT11\n采集温湿度"), option);

    // 绘制温湿度
    drawValues(&painter);
}

void DisplayRealData::drawValues(QPainter *painter)
{
    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(86);
    painter->setFont(font);

    painter->setPen(Qt::white);
    painter->drawPixmap(440, 62, QPixmap(":/images/dht/temperature.png"));
    painter->drawPixmap(440, 187, QPixmap(":/images/dht/humidity.png"));

    QString strText = "26.1";
    QRect rectTemp(550, 57, 218, 100)    ;
    painter->drawText(rectTemp, Qt::AlignLeft | Qt::AlignVCenter, strText);

    strText = "76";
    QRect rectHumidity(rectTemp.left(), 180, 218, 100);
    painter->drawText(rectHumidity, Qt::AlignLeft | Qt::AlignVCenter, strText);

    font.setPixelSize(48);
    painter->setFont(font);
    int nTextWidth = painter->fontMetrics().width("℃");
    int nTextHeight = painter->fontMetrics().height();
    painter->drawText(rectTemp.right() - nTextWidth, rectTemp.bottom() - nTextHeight, nTextHeight, nTextHeight,
                     Qt::AlignCenter, QString("℃"));

    painter->drawText(rectHumidity.right() - nTextWidth, rectHumidity.bottom() - nTextHeight, nTextHeight, nTextHeight,
                      Qt::AlignCenter, QString("%"));
}

void DisplayRealData::mousePressEvent(QMouseEvent *e)
{
    QWidget::mousePressEvent(e);
}

void DisplayRealData::mouseReleaseEvent(QMouseEvent *e)
{
    QWidget::mouseReleaseEvent(e);
}
