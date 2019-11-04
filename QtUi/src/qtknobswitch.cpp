/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : qtknobswitch.cpp --- QtKnobSwitch
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "qtknobswitch.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QtMath>
#include <QTimer>

QtKnobSwitch::QtKnobSwitch(QWidget *parent) : QWidget(parent)
{
    m_nMinValue = 0;
    m_nMaxValue = 100;
    m_value = 84;

    m_bPressed = false;
}

QtKnobSwitch::~QtKnobSwitch()
{

}

void QtKnobSwitch::setValue(int value)
{
    if (value < m_nMinValue || value > m_nMaxValue) {
        return;
    }

    this->m_value = value;
    this->update();
}

void QtKnobSwitch::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
    QPixmap pixmap(":/images/backlight/ic_ring.png");
    int nX = (this->width() - pixmap.width()) / 2 + 1;
    int nY = (this->height() - pixmap.height()) / 2 + 1;
    painter.drawPixmap(nX, nY, pixmap);

    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);
    drawHandle(&painter);
    drawValue(&painter);
}

void QtKnobSwitch::drawHandle(QPainter *painter)
{
    qreal radius = 81;

    double degRotate = (m_value - m_nMinValue) * 360.0/ (m_nMaxValue - m_nMinValue);
    painter->save();
    painter->rotate(degRotate);
    QPixmap pixmap(":/images/backlight/ic_hand_30.png");
    painter->drawPixmap(-pixmap.width() / 2, -70, pixmap);
    painter->restore();

    painter->save();
    painter->rotate(-90);
    painter->setPen(QPen(QColor("#ffffff"), 6, Qt::SolidLine, Qt::RoundCap));
    painter->drawArc(-radius, -radius, radius * 2, radius * 2, 0, -degRotate * 16);
    painter->restore();

}

void QtKnobSwitch::drawValue(QPainter *painter)
{
    painter->save();
    QFont font = this->font();
    font.setPixelSize(24);
    painter->setFont(font);
    QString strValue = QString::number(m_value);
    int nTextWidth = painter->fontMetrics().width(strValue);
    int nTextHeight = painter->fontMetrics().height() / 2 + 10;
    QRect rectText(-nTextWidth / 2 - 6, -nTextHeight / 2, nTextWidth, nTextHeight);
    painter->setPen(Qt::white);
    painter->drawText(rectText, Qt::AlignCenter, strValue);

    font.setPixelSize(12);
    painter->setFont(font);
    rectText = QRect(rectText.right(), rectText.bottom() - 10, 20, 10);
    painter->drawText(rectText, Qt::AlignCenter, QString("%"));
    painter->restore();
}

void QtKnobSwitch::mousePressEvent(QMouseEvent *e)
{
    m_bPressed = true;
    QWidget::mousePressEvent(e);
}

void QtKnobSwitch::mouseReleaseEvent(QMouseEvent *e)
{
    m_bPressed = false;
    QWidget::mouseReleaseEvent(e);
}

void QtKnobSwitch::mouseMoveEvent(QMouseEvent *e)
{
    if (m_bPressed) {
        // 计算最近的刻度
        QPointF point = e->pos() - rect().center();
        double theta = -atan2(point.x(), point.y()) * 180 / M_PI;
        theta = theta + 180;

        double increment = (m_nMaxValue - m_nMinValue) * 1.0 / 360;
        m_value = (theta * increment) + m_nMinValue;
        emit valueChanged(m_value);
        this->update();
    }
}
