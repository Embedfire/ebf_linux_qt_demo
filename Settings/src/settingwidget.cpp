/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : settingwidget.cpp ---
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "settingwidget.h"
#include "skin.h"
#include "appconfig.h"

#include "settingmainpage.h"
#include "aboutboard.h"
#include "backlightpage.h"
#include "datetimesettingpage.h"
#include "versionupdatepage.h"

#include <QBoxLayout>
#include <QDebug>

SettingWidget::SettingWidget(QWidget *parent) : QtAnimationWidget(parent)
{
    this->SetBackground(QPixmap(":/images/setting/ic_background.png"));
    m_strListTitle = QStringList() << tr("系统设置") << tr("关于开发板") << tr("亮度调节")
                                   << tr("设置时间") << tr("设置日期") << tr("检查更新");
    InitWidget();
    InitSettingPage();
}

SettingWidget::~SettingWidget()
{

}

void SettingWidget::InitWidget()
{
    m_widgetTitle = new QtWidgetTitleBar(this);
    m_widgetTitle->setObjectName("widgetTitle");
    m_widgetTitle->setMinimumHeight(82);
    m_widgetTitle->SetBackground(Qt::transparent);
    m_widgetTitle->setFont(QFont(Skin::m_strAppFontBold));
    m_widgetTitle->SetTitle(m_strListTitle.at(0), QColor("#ffffff"), 32);

    m_btnBack = new QPushButton(this);
    m_btnBack->setVisible(false);
    m_btnBack->setStyleSheet(QString("QPushButton {border-image: url(:/images/calendar/ic_back.png);}"
                                     "QPushButton:pressed {border-image: url(:/images/calendar/ic_back_pressed.png);}"));

    m_btnBack->setFixedSize(32, 32);
    connect(m_btnBack, SIGNAL(clicked(bool)), this, SLOT(SltBtnBackClicked()));

    m_btnHome = new QPushButton(this);
    m_btnHome->setFixedSize(54, 54);

    QHBoxLayout *horLayoutTitle = new QHBoxLayout(m_widgetTitle);
    horLayoutTitle->setContentsMargins(10, 0, 10, 0);
    horLayoutTitle->setSpacing(18);
    horLayoutTitle->addWidget(m_btnBack);
    horLayoutTitle->addStretch();
    horLayoutTitle->addWidget(m_btnHome);
    connect(m_btnHome, SIGNAL(clicked(bool)), this, SIGNAL(signalBackHome()));
    m_btnHome->setStyleSheet(QString("QPushButton {border-image: url(:/images/music/menu_icon.png);}"
                                     "QPushButton:pressed {border-image: url(:/images/music/menu_icon_pressed.png);}"));

    m_stackedWidget = new QtStackedWidget(this);
    m_stackedWidget->setPressMove(false);
    m_stackedWidget->SetBackground(Qt::transparent);

    connect(m_stackedWidget, SIGNAL(currentChanged(int)), this, SLOT(SltCurrentPageChanged(int)));

    // 全局布局
    QVBoxLayout *verLayoutAll = new QVBoxLayout(this);
    verLayoutAll->setContentsMargins(0, 0, 0, 0);
    verLayoutAll->setSpacing(0);
    verLayoutAll->addWidget(m_widgetTitle, 1);
    verLayoutAll->addWidget(m_stackedWidget, 5);
}

void SettingWidget::InitSettingPage()
{
    SettingMainPage *mainPage = new SettingMainPage(m_stackedWidget);
    m_stackedWidget->addWidget(0, mainPage);
    connect(mainPage, SIGNAL(signalChangePage(int)), this, SLOT(SltChangePage(int)));
    connect(mainPage, SIGNAL(signalChangeCursorShape(Qt::CursorShape)),
            this, SIGNAL(signalChangeCursorShape(Qt::CursorShape)));

    AboutBoard *aboutPage = new AboutBoard(m_stackedWidget);
    connect(aboutPage, SIGNAL(signalChangePage(int)), this, SLOT(SltChangePage(int)));
    m_stackedWidget->addWidget(1, aboutPage);

    // 背光
    BackLightPage *backlight = new BackLightPage(m_stackedWidget);
    m_stackedWidget->addWidget(2, backlight);

    // 时间
    DateTimeSettingPage *timeSetting = new DateTimeSettingPage(m_stackedWidget, QtDateTimeConfig::TimeFormat);
    connect(timeSetting, SIGNAL(signalFinished()), this, SLOT(SltBtnBackClicked()));
    m_stackedWidget->addWidget(3, timeSetting);

    // 日期
    DateTimeSettingPage *dateSetting = new DateTimeSettingPage(m_stackedWidget);
    connect(dateSetting, SIGNAL(signalFinished()), this, SLOT(SltBtnBackClicked()));
    m_stackedWidget->addWidget(4, dateSetting);

    // 检查更新
    VersionUpdatePage *checkVersion = new VersionUpdatePage(m_stackedWidget);
    m_stackedWidget->addWidget(5, checkVersion);
}

// 返回
void SettingWidget::SltBtnBackClicked()
{
    int index = 0;
    if (!m_pageStack.isEmpty()) {
        index = m_pageStack.last();
        m_pageStack.removeLast();
    }

    m_btnBack->setVisible(0 != index);
    m_stackedWidget->setCurrentIndex(index, QtStackedWidget::RightDirection);
}

void SettingWidget::SltCurrentPageChanged(int index)
{
    if (index < m_strListTitle.size()) {
        m_widgetTitle->SetTitle(m_strListTitle.at(index));
    }
    else {
        m_widgetTitle->SetTitle(tr("系统设置"));
    }

    m_btnHome->setVisible(index == 0);
}

void SettingWidget::SltChangePage(int index)
{
    m_btnBack->setVisible(0 != index);
    m_pageStack.append(m_stackedWidget->currentIndex());
    m_stackedWidget->setCurrentIndex(index, QtStackedWidget::LeftDirection);
}
