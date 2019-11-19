/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : backlightpage.cpp --- BackLightPage
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "backlightpage.h"
#include "skin.h"

#include <QBoxLayout>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QApplication>

BackLightPage::BackLightPage(QWidget *parent) : QtWidgetBase(parent),
    m_nLevel(0)
{
    m_nBaseHeight = 400;
    InitWidget();
}

BackLightPage::~BackLightPage()
{

}

void BackLightPage::InitWidget()
{
    m_knobSwitch = new QtKnobSwitch(this);
    m_knobSwitch->setFont(QFont(Skin::m_strAppFontBold));
    connect(m_knobSwitch, SIGNAL(valueChanged(int)), this, SLOT(SltValueChanged(int)));
    // 读取配置
    ReadBacklight();
}

// 读取配置
void BackLightPage::ReadBacklight()
{
#ifdef __arm__
    QString strFile = "/sys/class/backlight/backlight/brightness";
    QFile file(strFile);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "open Leds failed!";
        m_nLevel = 5;
        return;
    }

    QString strTemp = file.readAll();
    m_nLevel = strTemp.toInt();
    if (m_nLevel > 5 && m_nLevel < 100) {
        m_knobSwitch->setValue(m_nLevel);
    }
    file.close();
#endif
}

void BackLightPage::SltValueChanged(int value)
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

void BackLightPage::resizeEvent(QResizeEvent *e)
{
    SetScaleValue();
    m_knobSwitch->setGeometry(242 * m_scaleX, 20 * m_scaleY, 316 * m_scaleY, 316 * m_scaleY);
    QWidget::resizeEvent(e);
}
