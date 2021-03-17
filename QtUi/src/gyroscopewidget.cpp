/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : gyroscopewidget.cpp --- GyroscopeWidget
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "gyroscopewidget.h"

#include <QPainter>
#include <QDebug>

static const QStringList strDirections = QStringList()
        << "N" << "NE" << "E" << "SE"
        << "S" << "SW" << "W" << "NW";

GyroscopeWidget::GyroscopeWidget(QWidget *parent) : QWidget(parent)
{
    m_nPitchValue = 0;
    m_nRollValue = 0;
    m_nYawValue = 0;

    m_font.setFamily("Microsoft YaHei");
    m_font.setPixelSize(12);
}

GyroscopeWidget::~GyroscopeWidget()
{

}

void GyroscopeWidget::setRollValue(int value)
{
    m_nRollValue = value;
    this->update();
}

void GyroscopeWidget::setPitchValue(int value)
{
    m_nPitchValue = value;
    this->update();
}

void GyroscopeWidget::setYawValue(int value)
{
    m_nYawValue = value;
    this->update();
}

void GyroscopeWidget::SetFont(QFont font)
{
    m_font = font;
    this->update();
}

void GyroscopeWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    drawYawBoard(&painter);
    drawRollBoard(&painter);
    drawPitchBoard(&painter);
    // 绘制刻度线
    drawPitchScale(&painter);
}

void GyroscopeWidget::drawYawBoard(QPainter *painter)
{
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor("#013c88"));
    QRectF rectangle(-radius, -radius, radius * 2, radius * 2);
    painter->drawChord(rectangle, 0 * 16, 180 * 16);
    m_font.setPixelSize(12);
    m_font.setBold(true);
    painter->setFont(m_font);

    // 顶部的三角形
    int nTriangleW = 12;
    QPointF points[3] = {
        QPointF(-nTriangleW / 2, -radius),
        QPointF(nTriangleW / 2, -radius),
        QPointF(0, -radius + 12),
    };
    painter->setBrush(QColor("#ffffff"));
    painter->drawConvexPolygon(points, 3);
    painter->setClipRect(QRectF(-radius, -radius, radius * 2, radius - 10));

    // 绘制刻度
    radius = 98;
    // 设置画笔颜色
    painter->setPen(Qt::white);
    // 线条长度
    int len = 6;

    // 逐个绘制方位角
    painter->rotate(135);
    painter->rotate(m_nYawValue);

    int nTextWidth = painter->fontMetrics().width("NE");
    int nTextHeight = painter->fontMetrics().height();
    for (int i = 0; i < 8; i++) {
        painter->rotate(45);
        painter->drawLine(1, radius - len, 1, radius);

        painter->save();
        QRect rectText(-nTextWidth / 2, radius - len - nTextHeight - 5, nTextWidth, nTextHeight);
        painter->translate(rectText.left() + rectText.width() /2 , rectText.top() + rectText.height() / 2);
        painter->rotate(180);
        painter->translate(-(rectText.left() + rectText.width() /2), -(rectText.top() + rectText.height() / 2));
        painter->drawText(rectText, Qt::AlignCenter, strDirections.at(i));
        painter->restore();
    }

    painter->restore();
}

void GyroscopeWidget::drawRollBoard(QPainter *painter)
{
    int radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor("#c81924"));
    m_font.setPixelSize(12);
    m_font.setBold(true);
    painter->setFont(m_font);

    QRectF rectangle(-radius, -radius, radius * 2, radius * 2);
    painter->drawChord(rectangle, 0 * 16, -180 * 16);
    painter->setClipRect(QRectF(-radius, 10, radius * 2, radius -10));
    // 顶部的三角形
    int nTriangleW = 12;
    QPointF points[3] = {
        QPointF(-nTriangleW / 2, radius),
        QPointF(nTriangleW / 2, radius),
        QPointF(0, radius - 12),
    };
    painter->setBrush(QColor("#ffffff"));
    painter->drawConvexPolygon(points, 3);

    // 绘制刻度
    radius = 98;
    // 设置画笔颜色
    painter->setPen(Qt::white);
    // 线条长度
    int len = 6;
    int nTextWidth = painter->fontMetrics().width("-100");
    int nTextHeight = painter->fontMetrics().height();

    // 逐个绘制方位角
    painter->rotate(-90);
    painter->rotate(m_nRollValue);

    for (int i = 0; i < 8; i++) {
        painter->rotate(45);
        painter->drawLine(1, radius - len, 1, radius);
        QRect rectText(-nTextWidth / 2, radius - len - nTextHeight - 5, nTextWidth, nTextHeight);
        if (i < 4) {
            painter->drawText(rectText, Qt::AlignCenter, QString("%1").arg(-i * 45 + 45));
        } else if (i > 4) {
            painter->drawText(rectText, Qt::AlignCenter, QString("%1").arg(180 - (i - 5) * 45));
        } else {
            painter->drawText(rectText, Qt::AlignCenter, QString("%1").arg(-135));
        }
    }

    painter->restore();
}

void GyroscopeWidget::drawPitchBoard(QPainter *painter)
{
    double radius = 72;
    painter->save();
    painter->rotate(m_nRollValue);
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor("#6ec3c9"));
    QRect rect(-radius, -radius, radius * 2, radius * 2);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    qreal offset = -(1 - m_nPitchValue * radius * 1.0 / 180);
    qreal startAngle = 180 + offset;
    qreal endAngle = offset;
    qreal span = endAngle + startAngle;
    painter->drawChord(rect, 16 * startAngle, -16 * span);

    painter->setBrush(QColor("#50a625"));
    offset = -(m_nPitchValue * radius * 1.0 / 180);

    startAngle = 180 + offset;
    endAngle = offset;
    span = endAngle + startAngle;
    painter->drawChord(rect, -16 * startAngle, 16 * span);

    painter->restore();
}

void GyroscopeWidget::drawPitchScale(QPainter *painter)
{
    double radius = 72;
    painter->save();
    m_font.setPixelSize(9);
    painter->setFont(m_font);

    painter->setPen(QPen(QColor("#ffffff"), 1));
    // 绘制水平线
    painter->drawLine(-30, 1, 30, 1);
    painter->rotate(m_nRollValue);
    painter->drawLine(-30, 1, 30, 1);

    double offset = (m_nPitchValue * radius * 1.0 / 180);

    int nTextWidth = painter->fontMetrics().width("-180");
    int nTextHeight = painter->fontMetrics().height();
    int nX = 10 + nTextWidth;

    painter->setClipRect(-radius, -radius, radius * 2, radius * 2);

    double space = 20.5;
    int nCnt = 71;
    int nLineHeight = 20.5 * nCnt;
    for (int i = 0; i < nCnt; i++) {
        double nY = -offset + i * space - nLineHeight / 2 - 10;
        painter->drawLine(-nX / 2, nY, nX - nTextWidth -10, nY);
        painter->drawText(nX - nTextWidth -10, nY - nTextHeight / 2, nTextWidth, nTextHeight,
                          Qt::AlignCenter, QString::number((i - 36) * 5));
    }

    painter->restore();
}
