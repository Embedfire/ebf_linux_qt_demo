/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : backlightwidget.cpp ---
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "backlightwidget.h"
#include "skin.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#ifdef __arm__

#endif

BackLightWidget::BackLightWidget(QWidget *parent) : QtAnimationWidget(parent)
{
    this->SetBackground(QPixmap(":/images/backlight/ic_background.png"));
    m_nLevel = 6;
    InitWidget();
}

BackLightWidget::~BackLightWidget()
{

}

void BackLightWidget::InitWidget()
{
    QtWidgetTitleBar *widgetTitle= new QtWidgetTitleBar(this);
    widgetTitle->setFixedHeight(80);
    widgetTitle->SetBackground(Qt::transparent);
    widgetTitle->setFont(QFont(Skin::m_strAppFontBold));
    widgetTitle->SetTitle("屏幕亮度调节", "#ffffff", 24);

    QPushButton *btnHome = new QPushButton(widgetTitle);
    btnHome->setFixedSize(54, 54);
    connect(btnHome, SIGNAL(clicked(bool)), this, SIGNAL(signalBackHome()));
    btnHome->setStyleSheet(QString("QPushButton {border-image: url(:/images/backlight/menu_icon.png);}"
                                   "QPushButton:pressed {border-image: url(:/images/backlight/menu_icon_pressed.png);}"));

    QHBoxLayout *horLayoutTitle = new QHBoxLayout(widgetTitle);
    horLayoutTitle->setContentsMargins(9, 0, 10, 0);
    horLayoutTitle->setSpacing(18);
    horLayoutTitle->addStretch();
    horLayoutTitle->addWidget(btnHome);

    m_knobSwitch = new QtKnobSwitch(this);
    m_knobSwitch->setFixedSize(350, 350);
    m_knobSwitch->setFont(QFont(Skin::m_strAppFontBold));
    connect(m_knobSwitch, SIGNAL(valueChanged(int)), this, SLOT(SltValueChanged(int)));

    QVBoxLayout *verLayout = new QVBoxLayout(this);
    verLayout->setContentsMargins(0, 0, 0, 50);
    verLayout->setSpacing(0);
    verLayout->addWidget(widgetTitle);
    verLayout->addStretch();
    verLayout->addWidget(m_knobSwitch, 1, Qt::AlignHCenter);
    verLayout->addStretch();
}

void BackLightWidget::SltValueChanged(int value)
{
    if (m_nLevel == value)  return;

    m_nLevel = (value < 5 ? 5 : value);
#ifdef __arm__
    QString strFile = "/sys/class/backlight/backlight/brightness";
    QFile file(strFile);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        qDebug() << "open Leds failed!";
        return;
    }

    QTextStream in(&file);
    in << m_nLevel;
    file.close();
#endif
}
