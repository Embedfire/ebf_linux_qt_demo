/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : keypresswidget.cpp ---
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "keypresswidget.h"
#include "skin.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QTimer>

const char *pchLedText[3] = { "LED_R", "LED_G", "LED_B"};

KeyPressWidget::KeyPressWidget(QWidget *parent) : QtAnimationWidget(parent)
{
    InitButtons();
}

KeyPressWidget::~KeyPressWidget()
{
}

void KeyPressWidget::InitButtons()
{
    m_btns.insert(BtnHome, new QtPixmapButton(BtnHome, QRect(736, 10, 54, 54), QPixmap(":/images/keyled/menu_icon.png"), QPixmap(":/images/keyled/menu_icon_pressed.png")));
    m_btns.insert(BtnUser, new QtPixmapButton(BtnUser, QRect(46, 392, 166, 70), QPixmap(":/images/keyled/ic_btn.png"), QPixmap(":/images/keyled/ic_btn_pre.png")));
    m_btns.insert(BtnOnOff, new QtPixmapButton(BtnOnOff, QRect(317, 392, 166, 70), QPixmap(":/images/keyled/ic_btn.png"), QPixmap(":/images/keyled/ic_btn_pre.png")));
    m_btns.insert(BtnKey, new QtPixmapButton(BtnKey, QRect(588, 392, 166, 70), QPixmap(":/images/keyled/ic_btn.png"), QPixmap(":/images/keyled/ic_btn_pre.png")));

    m_btns.insert(BtnLedR, new QtPixmapButton(BtnLedR, QRect(81, 120, 99, 182), QPixmap(":/images/keyled/led_off.png"), QPixmap(":/images/keyled/led_red.png")));
    m_btns.insert(BtnLedG, new QtPixmapButton(BtnLedG, QRect(351, 120, 99, 182), QPixmap(":/images/keyled/led_off.png"), QPixmap(":/images/keyled/led_green.png")));
    m_btns.insert(BtnLedB, new QtPixmapButton(BtnLedB, QRect(622, 120, 99, 182), QPixmap(":/images/keyled/led_off.png"), QPixmap(":/images/keyled/led_blue.png")));

    m_btns.value(BtnUser)->setText("USER");
    m_btns.value(BtnOnOff)->setText("ON/OFF");
    m_btns.value(BtnKey)->setText("KEY");
}

void KeyPressWidget::KeyPressed(int index)
{
    switch (index) {
    case BtnHome: emit signalBackHome(); break;
    case BtnUser:
    {
        QtPixmapButton *btn = m_btns.value(BtnLedR);
        btn->setPressed(!btn->isPressed());
        ChangeRgbLightValue("red", btn->isPressed());
    }
        break;
    case BtnOnOff:
    {
        QtPixmapButton *btn = m_btns.value(BtnLedG);
        btn->setPressed(!btn->isPressed());
        ChangeRgbLightValue("green", btn->isPressed());
    }
        break;
    case BtnKey:
    {
        QtPixmapButton *btn = m_btns.value(BtnLedB);
        btn->setPressed(!btn->isPressed());
        ChangeRgbLightValue("blue", btn->isPressed());
    }
        break;
    default:
        break;
    }
}

void KeyPressWidget::ChangeRgbLightValue(QString led, bool on)
{
#ifdef __arm__
    QString strLight = QString("/sys/class/leds/%1/brightness").arg(led);
    QFile file(strLight);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        qDebug() << "open Leds failed!" << strLight;
        return;
    }

    QTextStream in(&file);
    in << (on ? 255 : 0);
    file.close();
#else
    Q_UNUSED(led)
    Q_UNUSED(on)
#endif
}

void KeyPressWidget::SltKeyPressed(const quint8 &type)
{
    if (0 == type) {
        QtPixmapButton *btn = m_btns.value(BtnLedG);
        btn->setPressed(!btn->isPressed());
        ChangeRgbLightValue("green", btn->isPressed());
    } else {
        QtPixmapButton *btn = m_btns.value(BtnLedB);
        btn->setPressed(!btn->isPressed());
        ChangeRgbLightValue("blue", btn->isPressed());
    }

    this->update();
}

void KeyPressWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

#ifdef BUILD_WITH_HDMI
    // 设置放大倍数
    painter.scale(m_scaleX, m_scaleY);
#endif

    painter.drawPixmap(0, 0, QPixmap(":/images/keyled/ic_background.png"));

    painter.setPen(QColor("#ffffff"));
    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(32);
    painter.setFont(font);
    painter.drawText(0, 0, Skin::m_nScreenWidth, 80, Qt::AlignCenter, tr("按键&LED测试"));

    font.setFamily(Skin::m_strAppFontRegular);
    font.setPixelSize(30);
    painter.setFont(font);
    foreach (QtPixmapButton *btn, m_btns) {
        painter.drawPixmap(btn->rect(), btn->pixmap());
        if (!btn->text().isEmpty()) {
            painter.drawText(btn->rect(), Qt::AlignCenter, btn->text());
        }
    }

    for (int i = BtnLedR; i < BtnCount; i++) {
        QRect rect = m_btns.value(i)->rect();
        rect = QRect(rect.left(), rect.bottom() + 10, rect.width(), 40);
        painter.drawText(rect, Qt::AlignCenter, pchLedText[i - BtnLedR]);
    }
}

void KeyPressWidget::mousePressEvent(QMouseEvent *e)
{
    foreach (QtPixmapButton *btn, m_btns) {
        if (btn->id() > BtnKey) break;

        QRect rect;
        ScaleRect(rect, btn->rect());

        if (rect.contains(e->pos())) {
            btn->setPressed(true);
            this->update();
            break;
        }
    }
}

void KeyPressWidget::mouseReleaseEvent(QMouseEvent *e)
{
    foreach (QtPixmapButton *btn, m_btns) {
        if (btn->isPressed() && btn->id() < BtnLedR) {
            btn->setPressed(false);
            KeyPressed(btn->id());
        }
    }

    this->update();
    QWidget::mouseReleaseEvent(e);
}


