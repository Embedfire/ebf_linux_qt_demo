/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : settingmainpage.cpp --- SettingMainPage
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "settingmainpage.h"
#include "qtswitchbutton.h"
#include "appconfig.h"
#include "clickedwidget.h"
#include "skin.h"

#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <QDebug>
#include <QApplication>
#include <QCursor>
#include <QPainter>

/////////////////////////////////////////////////////////////////////////////
SettingMainPage::SettingMainPage(QWidget *parent) : QWidget(parent)
{
    InitWidget();
}

SettingMainPage::~SettingMainPage()
{

}

void SettingMainPage::SltSwitchClicked(bool on)
{
    AppConfig::SaveSetting("System", "mouse", on);
    if (AppConfig::m_bMouseInsert) return;
    emit signalChangeCursorShape(on ? Qt::ArrowCursor : Qt::BlankCursor);
}

void SettingMainPage::InitWidget()
{
    QVBoxLayout *verLayoutAll = new QVBoxLayout(this);
    verLayoutAll->setContentsMargins(20, 20, 0, 20);
    verLayoutAll->setSpacing(10);

    ClickedWidget *widgetBoard = new ClickedWidget(this);
    widgetBoard->setIndex(1, tr("关于开发板"));
    connect(widgetBoard, SIGNAL(signalClicked(int)), this, SIGNAL(signalChangePage(int)));
    verLayoutAll->addWidget(widgetBoard);

    {
        QWidget *widget = new QWidget(this);
        widget->setMinimumHeight(44);
        widget->setObjectName("widgetItem");

        QHBoxLayout *horLayout = new QHBoxLayout(widget);
        horLayout->setContentsMargins(0, 0, 20, 0);

        horLayout->addWidget(new QLabel(tr("打开/关闭鼠标"), widget));
        horLayout->addStretch();

        QtSwitchButton *btnSwitch = new QtSwitchButton(widget);
        btnSwitch->setBackgroundColor(QColor("#0199ff"));
        btnSwitch->setFixedSize(65, 30);
        btnSwitch->setHandleColor(QColor("#ffffff"));
        btnSwitch->setChecked(AppConfig::ReadSetting("System", "mouse", true).toBool());
        connect(btnSwitch, SIGNAL(buttonChecked(bool)), this, SLOT(SltSwitchClicked(bool)));

        horLayout->addWidget(btnSwitch);
        verLayoutAll->addWidget(widget);
    }

    ClickedWidget *widgetBacklight = new ClickedWidget(this);
    widgetBacklight->setIndex(2, tr("背光调节"));
    connect(widgetBacklight, SIGNAL(signalClicked(int)), this, SIGNAL(signalChangePage(int)));
    verLayoutAll->addWidget(widgetBacklight);

    ClickedWidget *widgetTime = new ClickedWidget(this);
    widgetTime->setIndex(3, tr("时间设置"));
    connect(widgetTime, SIGNAL(signalClicked(int)), this, SIGNAL(signalChangePage(int)));
    verLayoutAll->addWidget(widgetTime);

    ClickedWidget *widgetDate = new ClickedWidget(this);
    widgetDate->setIndex(4, tr("日期设置"));
    connect(widgetDate, SIGNAL(signalClicked(int)), this, SIGNAL(signalChangePage(int)));
    verLayoutAll->addWidget(widgetDate);

//    ClickedWidget *widgetEth = new ClickedWidget(this);
//    widgetEth->setIndex(5, tr("网络设置"));
//    connect(widgetEth, SIGNAL(signalClicked(int)), this, SIGNAL(signalChangePage(int)));
//    verLayoutAll->addWidget(widgetEth);

    this->setStyleSheet(QString("QWidget#widgetItem{border: none; border-bottom: 1px solid #797979; background: none;}"
                        "QPushButton#btnNext{border-image: url(:/images/setting/ic_next.png);}"
                        "QLabel{font-family: '%1'; font: 24px; color: #ffffff;}")
                        .arg(Skin::m_strAppFontNormal));
    verLayoutAll->addStretch();
}


