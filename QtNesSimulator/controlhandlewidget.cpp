/********************************************************************************
 * Copyright (C) 2020 - All Rights Reserved by xiaomutech
 * date: 2020/7/24
 * auth: yhni lynnhua@163.com QQ:393320854
 * desc:
 ********************************************************************************/
#include "controlhandlewidget.h"

#include <QtMath>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QDebug>

ControlHandleWidget::ControlHandleWidget(QWidget *parent) : QWidget(parent)
{
    m_nDirection = 0;
    m_value = 0.0;
}

ControlHandleWidget::~ControlHandleWidget()
{

}

QSize ControlHandleWidget::sizeHint() const
{
    return QSize(280, 280);
}

void ControlHandleWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.fillRect(this->rect(), Qt::white);
    drawDirectionCtrl(&painter);
}

void ControlHandleWidget::drawBMWLogo(QPainter *painter)
{
    painter->save();
    int nSize = qMin(this->width(), this->height());
    painter->translate(this->width() / 2, this->height() / 2);
    painter->scale(nSize / 200.0, nSize / 200.0);
    // 设置绘制半径
    int radius = 100;
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor("#dedede"));
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    radius = 95;
    QLinearGradient linear(radius, radius, -radius * 2, -radius * 2);
    linear.setColorAt(1, QColor("#eeeeee"));
    linear.setColorAt(0, QColor("#000000"));
    painter->setBrush(linear);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    radius = 70;
    painter->setBrush(QColor("#88959b"));
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    radius = 65;
    for (int i = 0; i < 4; i++) {
        if (i == 0) painter->setBrush(QColor("#ffffff"));
        else if (1 == i) painter->setBrush(QColor("#47b3e2"));
        else if (2 == i) painter->setBrush(QColor("#ffffff"));
        else if (3 == i) painter->setBrush(QColor("#47b3e2"));
        painter->drawPie(-radius, -radius, radius * 2, radius * 2, (i * 90) * 16, 90 * 16);
    }
    painter->setPen(QPen(QColor("#88959b"), 2, Qt::SolidLine));
    painter->drawLine(-radius, 0, radius, 0);
    painter->drawLine(0, -radius, 0, radius);

    painter->save();
    QFont font("Mircosoft YaHei");
    font.setPixelSize(24);
    font.setBold(true);
    painter->setFont(font);
    int tW = painter->fontMetrics().horizontalAdvance("B");
    int tH = painter->fontMetrics().height();
    painter->setPen(QPen(QColor("#ffffff"), 4, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin));
    QRect rectText(-tW / 2, -94, tW, tH);
    painter->rotate(-45);
    painter->drawText(rectText, Qt::AlignCenter, QString("B"));
    painter->rotate(45);
    painter->drawText(rectText, Qt::AlignCenter, QString("M"));
    painter->rotate(45);
    painter->drawText(rectText, Qt::AlignCenter, QString("W"));
    painter->restore();

    painter->restore();
}

void ControlHandleWidget::drawDirectionCtrl(QPainter *painter)
{
    painter->save();
    int nSize = qMin(this->width(), this->height());
    painter->translate(this->width() / 2, this->height() / 2);
    painter->scale(nSize / 200.0, nSize / 200.0);
    // 设置绘制半径
    int radius = 100;
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor("#dedede"));
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    radius = 95;
    QLinearGradient linear(radius, radius, -radius * 2, -radius * 2);
    linear.setColorAt(1, QColor("#eeeeee"));
    linear.setColorAt(0, QColor("#000000"));
    painter->setBrush(linear);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    QPolygon polygon;
    polygon << QPoint(0, -90) << QPoint(-10, -75) << QPoint(10, -75);
    for (int i = 0; i < 4; i++) {
        painter->setBrush(m_nDirection == i ? QColor("#999999") : QColor("#f0f0f0"));
        painter->drawPolygon(polygon);
        painter->rotate(90);
    }

    painter->save();
    double degRotate = (m_value) * 360.0/ 360;
    painter->rotate(degRotate);
    radius = 30;
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();

    painter->restore();
}

void ControlHandleWidget::mouseMoveEvent(QMouseEvent *e)
{
    int m_nMaxValue = 360;
    int m_nMinValue = 0;
    qreal m_value = 0;
    QPointF point = e->pos() - rect().center();
    double theta = -atan2(point.x(), point.y()) * 180 / M_PI;
    theta = theta + 180;

    double increment = (m_nMaxValue - m_nMinValue) * 1.0 / 360;
    m_value = (theta * increment) + m_nMinValue;
    m_nDirection = (m_value / 90.0);
    this->update();

    QWidget::mousePressEvent(e);

}
