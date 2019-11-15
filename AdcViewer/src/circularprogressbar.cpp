/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : circularprogressbar.cpp --- CircularProgressBar
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/1
*******************************************************************/
#include "circularprogressbar.h"

#include <QPainter>
#include <QDebug>
#include <QTimer>

CircularProgressBar::CircularProgressBar(QWidget *parent) : QtWidgetBase(parent)
{
    m_nMaxValue = 330;
    m_MinValue = 0;
    m_nCurrentValue = 99;

    m_nBaseWidth = 320;
    m_nBaseHeight = 320;

    m_animation = new QPropertyAnimation(this, "value");
    m_animation->setDuration(100);
    m_animation->setEasingCurve(QEasingCurve::OutBounce);
}

CircularProgressBar::~CircularProgressBar()
{

}

void CircularProgressBar::SetMaxValue(int value)
{
    m_nMaxValue = value;
}

void CircularProgressBar::setCurrentValue(int value)
{
    if (m_animation->state() == QPropertyAnimation::Running) {
        m_animation->stop();
    }

    m_animation->setStartValue(m_nCurrentValue);
    m_animation->setEndValue(value);
    m_animation->start();
}

void CircularProgressBar::SetValue(int value)
{
    m_nCurrentValue = value;
    emit currentValueChanged(value);
    this->update();
}

void CircularProgressBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.scale(m_scaleX, m_scaleY);

    // 绘制背景
    drawBackground(&painter);

    int side = qMin(m_nBaseWidth, m_nBaseHeight);
    painter.translate(m_nBaseWidth / 2, m_nBaseHeight / 2);
    painter.scale(side / 200.0, side / 200.0);

    // 用图片效果好一点
    drawRing(&painter);
    drawPointerTriangle(&painter);
    drawValue(&painter);
}

void CircularProgressBar::drawBackground(QPainter *painter)
{
    QPixmap pixmap(":/images/adc/ring_background.png");
    int nX = (m_nBaseWidth - pixmap.width()) / 2;
    int nY = (m_nBaseHeight - pixmap.height()) / 2;
    painter->drawPixmap(nX, nY, pixmap);
}

void CircularProgressBar::drawRing(QPainter *painter)
{
    int radius = 88;
    painter->save();
    painter->setBrush(Qt::NoBrush);
    //计算总范围角度,当前值范围角度,剩余值范围角度
    //绘制外边框圆弧
    painter->setPen(QPen(QColor("#11ffffff"), 8, Qt::SolidLine, Qt::RoundCap));
    QRectF rect = QRectF(-radius, -radius, radius * 2, radius * 2);
    painter->drawArc(rect, -45 * 16, 270 * 16);

    painter->setPen(QPen(QColor("#000000"), 4, Qt::SolidLine, Qt::RoundCap));
    rect = QRectF(-radius, -radius, radius * 2, radius * 2);
    painter->drawArc(rect, -45 * 16, 270 * 16);

    double dbRotate = (270 * m_nCurrentValue / m_nMaxValue);
    painter->setPen(QPen(QColor("#ffffff"), 4, Qt::SolidLine, Qt::RoundCap));
    painter->drawArc(rect, -135 * 16, -dbRotate * 16);
    painter->restore();
}

void CircularProgressBar::drawPointerTriangle(QPainter *painter)
{
    int radius = 40;
    painter->save();
    painter->rotate(45);
    double degRotate = (270.0 * (m_nCurrentValue - m_MinValue)) / (m_nMaxValue - m_MinValue);
    painter->rotate(degRotate);
    painter->drawPixmap(QRect(-10, radius, 20, 20), QPixmap(":/images/adc/triangle.png"));
    painter->restore();
}

void CircularProgressBar::drawValue(QPainter *painter)
{
    painter->save();
    painter->setPen("#ffffff");
    QFont font("思源黑体 CN Bold");
    font.setBold(true);
    font.setPixelSize(35);
    painter->setFont(font);

    QString strValue = QString("%1").arg(m_nCurrentValue * 100 / m_nMaxValue);
    int nValueW = painter->fontMetrics().width(strValue);

    font.setPixelSize(18);
    QFontMetrics fm(font);
    nValueW += fm.width("%");

    int nFontHeith = painter->fontMetrics().height();
    QRect rect(-nValueW / 2, -nFontHeith / 2, nValueW, nFontHeith);
    painter->drawText(rect, Qt::AlignLeft | Qt::AlignTop, strValue);

    painter->setFont(font);
    int nW = painter->fontMetrics().width("%");
    nFontHeith = painter->fontMetrics().height();
    rect = QRect(rect.right() - nW, rect.bottom() - nFontHeith - 5, nW, nFontHeith);
    painter->drawText(rect, Qt::AlignCenter, "%");
    painter->restore();
}
