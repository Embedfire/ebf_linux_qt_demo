/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : rgblightmonitor.cpp ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/8/31
*******************************************************************/
#include "rgblightmonitor.h"
#include "skin.h"

#include <QMouseEvent>
#include <QPainter>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMouseEvent>

RgbLightMonitor::RgbLightMonitor(QWidget *parent) : QtAnimationWidget(parent)
{
    m_nValue = 78;
    m_nCurrentLight = 1;
    m_bPressed = false;

    m_btnHome = new QtPixmapButton(0, QRect(736, 13, 54, 54), QPixmap(":/images/music/menu_icon.png"), QPixmap(":/images/music/menu_icon_pressed.png"));
    m_lightObjs.insert(0, new LightObect(0, QRect(105, 383, 66, 66), 75, tr("红灯")));
    m_lightObjs.insert(1, new LightObect(1, QRect(368, 383, 66, 66), 200, tr("绿灯")));
    m_lightObjs.insert(2, new LightObect(2, QRect(633, 383, 66, 66), 185, tr("蓝灯")));

    // 读取值
    ReadRgbLightValues();
}

RgbLightMonitor::~RgbLightMonitor()
{
    delete m_btnHome;
    m_btnHome = NULL;

    foreach (LightObect *obj, m_lightObjs) {
        m_lightObjs.remove(obj->m_nId);
        delete obj;
        obj = NULL;
    }
}

void RgbLightMonitor::ChangeRgbLightValue()
{
#ifdef __arm__
    QStringList strLights = QStringList() << "red" << "green" << "blue";
    QString strLight = QString("/sys/class/leds/%1/brightness").arg(strLights.at(m_nCurrentLight));
    QFile file(strLight);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        qDebug() << "open Leds failed!" << strLight;
        return;
    }

    QTextStream in(&file);
    in << m_lightObjs.value(m_nCurrentLight)->m_nValue;
    file.close();
#endif
}

void RgbLightMonitor::ReadRgbLightValues()
{
#ifdef __arm__
    QStringList strLights = QStringList() << "red" << "green" << "blue";
    for (int i = 0; i < 3; i++) {
        QString strLight = QString("/sys/class/leds/%1/brightness").arg(strLights.at(i));
        QFile file(strLight);
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "open Leds failed!" << strLight;
            return;
        }

        QString strValue = file.readAll();
        m_lightObjs.value(i)->m_nValue = strValue.toInt();
//        qDebug() << "Read value:" << strLights.at(i) << strValue << m_lightObjs.value(i)->m_nValue;
        file.close();
    }

    m_nValue = (m_lightObjs.value(m_nCurrentLight)->m_nValue * 100) / 255;
    this->update();
#endif
}

void RgbLightMonitor::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    // 设置放大倍数
    painter.scale(m_scaleX, m_scaleY);

    // 绘制背景
    drawBackground(&painter);

    // 绘制文字信息
    drawValue(&painter);

    // 绘制进度控制
    drawSliderBar(&painter);

    // RGB灯选择
    drawBottomLight(&painter);
}

void RgbLightMonitor::drawBackground(QPainter *painter)
{
    painter->save();
    painter->drawPixmap(0, 0, QPixmap(":/images/rgblight/background.png"));
    painter->drawPixmap(m_btnHome->rect(), m_btnHome->pixmap());
    painter->restore();
}

void RgbLightMonitor::drawValue(QPainter *painter)
{
    QFont font(Skin::m_strAppFontNormal);
    font.setBold(true);
    font.setPixelSize(22);
    painter->setFont(font);
    painter->setPen(QColor("#ffffff"));
    QRect rectTitle(0, 0, Skin::m_nScreenWidth, 80);
    painter->drawText(rectTitle, Qt::AlignCenter, tr("RGB灯亮度调节"));

    // 绘制亮度灯
    QRect rect(100, 126, 60, 60);
    drawRgbLight(painter, rect);

    rect = QRect(rectTitle.right() - 180, 110, 80, 80);
    drawRgbLight(painter, rect);

    font.setFamily("Arial");
    font.setPixelSize(80);
    painter->setFont(font);
    int nTextW = painter->fontMetrics().width("100");
    rect = QRect((Skin::m_nScreenWidth - nTextW) / 2, 120, nTextW, 92);
    painter->drawText(rect, Qt::AlignCenter, QString::number(m_nValue));

    font.setPixelSize(40);
    painter->setFont(font);
    nTextW = painter->fontMetrics().width("%");
    int nTextH = painter->fontMetrics().height();
    rect = QRect(rect.right() + 10, rect.bottom() - nTextH - 10, nTextW, nTextH);
    painter->drawText(rect, Qt::AlignCenter, QStringLiteral("%"));
}

void RgbLightMonitor::drawSliderBar(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    QRect rect(100, 250, Skin::m_nScreenWidth - 200, 45);
    painter->drawPixmap(rect, QPixmap(":/images/rgblight/ic_slider.png"));

    painter->setBrush(QColor("#000000"));
    int nValue = Skin::m_nScreenWidth - 200 - 48;
    QRect rectValue(rect.left() + 17, rect.top() + 18, nValue, 8);
    painter->drawRoundedRect(rectValue, 4, 4);
    painter->setBrush(QColor("#c9dcec"));

    qreal offset = (nValue * m_nValue * 1.0) / 100;
    rectValue = QRect(rectValue.left() + 1, rectValue.top() + 1, offset, 6);
    painter->drawRoundedRect(rectValue, 3, 3);

    // 绘制最后的滑块
    m_nRectHandle = QRect(rectValue.right() - 45, rect.top() - 22, 90, 90);
    painter->drawPixmap(m_nRectHandle, QPixmap(":/images/rgblight/ic_handle.png"));
    painter->restore();
}

void RgbLightMonitor::drawRgbLight(QPainter *painter, QRect rect)
{
    painter->save();
    QColor color;
    color.setRed(m_lightObjs.value(0)->m_nValue);
    color.setGreen(m_lightObjs.value(1)->m_nValue);
    color.setBlue(m_lightObjs.value(2)->m_nValue);

    QPen pen(color);
    pen.setWidth(6);
    painter->setPen(pen);
    int nWidth = rect.width() / 2;
    int nX = rect.left() + rect.width() / 2;
    painter->drawEllipse(rect.left() + nWidth / 2, rect.top() + nWidth / 2, nWidth, nWidth);
    for (int i = 0; i < 8; i++) {
        painter->translate(rect.left() + rect.width() / 2, rect.top() + rect.height() / 2);
        painter->rotate(45);
        painter->translate(-rect.left() - rect.width() / 2, -(rect.top() + rect.height() / 2));
        painter->drawLine(QPoint(nX, rect.top()), QPoint(nX, rect.top() + rect.width() * 0.1) );
    }
    painter->restore();
}

void RgbLightMonitor::drawBottomLight(QPainter *painter)
{
    painter->save();

    QFont font(Skin::m_strAppFontBold);
    font.setBold(true);
    font.setPixelSize(22);
    painter->setFont(font);
#if 1
    foreach (LightObect *lightObj, m_lightObjs) {
        painter->setPen("#8897a0");
        if (m_nCurrentLight == lightObj->m_nId) {
            painter->setPen("#1d272f");
            painter->drawPixmap(lightObj->m_rect, QPixmap(":/images/rgblight/ic_rgblight_selected.png"));
        }

        // 绘制文字
        QRect rectText = lightObj->m_rect;
        rectText = QRect(rectText.left(), rectText.bottom(), rectText.width(), 30);
        painter->drawText(rectText, Qt::AlignCenter, lightObj->m_strText);
    }
#else
    int nW = (this->width() - 10) / 3;
    int radius = 77;

    QLinearGradient linear(0, 0, 0, 80);
    linear.setColorAt(0, QColor("#ffffff"));
    linear.setColorAt(1, QColor("#c1cfda"));

    for (int i = 0; i < 3; i++) {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        QRect rect((nW + 5) * i, this->height() - 80, nW, 80);
        path.addEllipse(rect.center().x() - radius / 2, rect.top() - radius * 0.3, radius, radius);
        path.addRect(rect);
        painter->setBrush(linear);
        painter->setPen(Qt::NoPen);
        painter->drawPath(path);

        int nLightW = 66;
        painter->setBrush((m_nCurrentLight == i) ? QColor("#1d272f") : QColor("#8897a0"));
        painter->drawEllipse(rect.center().x() - nLightW / 2, rect.top() - nLightW * 0.25, nLightW, nLightW);
        m_lightObjs.value(i)->m_rect = QRect(rect.center().x() - nLightW / 2, rect.top() - nLightW * 0.25, nLightW, nLightW);

        // 绘制light
        painter->drawPixmap(m_lightObjs.value(i)->m_rect, QPixmap(":/images/rgblight/ic_light.png"));
        // 绘制文字
        QRect rectText = QRect(rect.left(), rect.bottom() - 30, rect.width(), 30);
        painter->setPen((m_nCurrentLight == i) ? QColor("#1d272f") : QColor("#8897a0"));
        painter->drawText(rectText, Qt::AlignCenter, m_lightObjs.value(i)->m_strText);
    }
#endif

    painter->restore();
}

void RgbLightMonitor::mousePressEvent(QMouseEvent *e)
{
    QRect rect;
    ScaleRect(rect, m_nRectHandle);
    if (rect.contains(e->pos())) {
        m_bPressed = true;
        return;
    }

    ScaleRect(rect, m_btnHome->rect());
    if (rect.contains(e->pos())) {
        m_btnHome->setPressed(true);
        this->update();
    }
    else {
        foreach (LightObect *obj, m_lightObjs) {
            ScaleRect(rect, obj->m_rect);
            if (rect.contains(e->pos())) {
                if (m_nCurrentLight != obj->m_nId) {
                    m_nCurrentLight = obj->m_nId;
                    m_nValue = (obj->m_nValue * 100) / 255;
                    this->update();
                    break;
                }
            }
        }
    }
}

void RgbLightMonitor::mouseReleaseEvent(QMouseEvent *e)
{
    if (m_bPressed) {
        m_bPressed = false;
    }

    if (m_btnHome->isPressed()) {
        m_btnHome->setPressed(false);
        this->update();
        emit signalBackHome();
    }

    QWidget::mouseReleaseEvent(e);
}

void RgbLightMonitor::mouseMoveEvent(QMouseEvent *e)
{
    int nXoffset = e->pos().x();
    if (m_bPressed && (nXoffset > 100 * m_scaleX) && (nXoffset <= (700 * m_scaleX))) {
        int nValue = (nXoffset - 100 * m_scaleX) * 255 / (600 * m_scaleX);
        m_nValue = (nValue * 100) / 255;
        m_lightObjs.value(m_nCurrentLight)->m_nValue = (m_nValue * 255 / 100);
        ChangeRgbLightValue();
        this->update();
    }
}
