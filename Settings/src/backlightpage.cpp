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

BackLightPage::BackLightPage(QWidget *parent) : QWidget(parent),
    m_nLevel(0)
{
    InitWidget();
}

BackLightPage::~BackLightPage()
{

}

void BackLightPage::InitWidget()
{
    m_knobSwitch = new QtKnobSwitch(this);
    m_knobSwitch->setFont(QFont(Skin::m_strAppFontBold));
    m_knobSwitch->setFixedSize(350, 350);
    connect(m_knobSwitch, SIGNAL(valueChanged(int)), this, SLOT(SltValueChanged(int)));

    QHBoxLayout *horLayout = new QHBoxLayout(this);
    horLayout->setContentsMargins(10, 20, 10, 20);
    horLayout->addWidget(m_knobSwitch, 1);
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
