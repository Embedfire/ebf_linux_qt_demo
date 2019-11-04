/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : calendarwidget.cpp ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/6
*******************************************************************/
#include "calendarwidget.h"
#include "skin.h"
#include "qtcalendarwidget.h"
#include "clockbackgroundcfg.h"
#include "timeconfigwidget.h"
#include "timeformatconf.h"
#include "dateconfigwidget.h"
#include "appconfig.h"

#include <QPainter>
#include <QDateTime>

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

CalendarWidget::CalendarWidget(QWidget *parent) : QtAnimationWidget(parent)
{
    this->SetBackground(QPixmap(":/images/calendar/ic_background.png"));
    m_strListTitle = QStringList() << tr("时间&日历") << tr("日历") << tr("选择表盘")
                                   << tr("时间格式") << tr("设置时间") << tr("设置日期");
    InitWidget();
    CreateMainPage();
    CreateConfigPage();
}

CalendarWidget::~CalendarWidget()
{

}

void CalendarWidget::InitWidget()
{
    m_widgetTitle = new QtWidgetTitleBar(this);
    m_widgetTitle->setObjectName("widgetTitle");
    m_widgetTitle->setMinimumHeight(80);
    m_widgetTitle->SetBackground(Qt::transparent);
    m_widgetTitle->setFont(QFont(Skin::m_strAppFontBold));
    m_widgetTitle->SetTitle(m_strListTitle.at(0), QColor("#ffffff"), 32);

    m_btnBack = new QPushButton(this);
    m_btnBack->setVisible(false);
    m_btnBack->setStyleSheet(QString("QPushButton {border-image: url(:/images/calendar/ic_back.png);}"
                                     "QPushButton:pressed {border-image: url(:/images/calendar/ic_back_pressed.png);}"));

    m_btnBack->setFixedSize(32, 32);
    connect(m_btnBack, SIGNAL(clicked(bool)), this, SLOT(SltBtnBackClicked()));

    m_labelDate = new QLabel(this);
    m_labelDate->setText(QDate::currentDate().toString("yyyy年MM月dd日"));
    m_labelDate->setVisible(false);
    m_labelDate->setStyleSheet(QString("color: #ffffff; font-family: '%1'; font: 24px;").arg(Skin::m_strAppFontBold));

    QPushButton *btnHome = new QPushButton(this);
    btnHome->setFixedSize(54, 54);
    QHBoxLayout *horLayoutTitle = new QHBoxLayout(m_widgetTitle);
    horLayoutTitle->setContentsMargins(10, 0, 10, 0);
    horLayoutTitle->setSpacing(18);
    horLayoutTitle->addWidget(m_btnBack);
    horLayoutTitle->addWidget(m_labelDate);
    horLayoutTitle->addStretch();
    horLayoutTitle->addWidget(btnHome);
    connect(btnHome, SIGNAL(clicked(bool)), this, SIGNAL(signalBackHome()));
    btnHome->setStyleSheet(QString("QPushButton {border-image: url(:/images/music/menu_icon.png);}"
                                   "QPushButton:pressed {border-image: url(:/images/music/menu_icon_pressed.png);}"));

    m_stackedWidget = new QtStackedWidget(this);
    m_stackedWidget->setPressMove(false);
    m_stackedWidget->SetBackground(Qt::transparent);
    connect(m_stackedWidget, SIGNAL(currentChanged(int)), this, SLOT(SltCurrentPageChanged(int)));

    QVBoxLayout *verLayoutAll = new QVBoxLayout(this);
    verLayoutAll->setContentsMargins(0, 0, 0, 0);
    verLayoutAll->setSpacing(0);
    verLayoutAll->addWidget(m_widgetTitle, 1);
    verLayoutAll->addWidget(m_stackedWidget, 4);
}

void CalendarWidget::CreateMainPage()
{
    QWidget *widgetMain = new QWidget(m_stackedWidget);
    QHBoxLayout *horLayout = new QHBoxLayout();
    horLayout->setContentsMargins(20, 20, 20, 20);
    horLayout->setSpacing(100);

    QtStackedWidget *stackedClock = new QtStackedWidget(widgetMain);
    stackedClock->setMaximumWidth(350);
    stackedClock->setPressMove(false);
    stackedClock->SetBackground(Qt::transparent);

    m_imageClock = new QtClockWidget(stackedClock);
    stackedClock->addWidget(0, m_imageClock);
    connect(m_imageClock, SIGNAL(signalClicked(int,int,int)), stackedClock, SLOT(setCurrentIndex(int,int,int)));

    m_lcdClock = new QtLcdClockWidget(stackedClock);
    m_lcdClock->setApMode(!AppConfig::ReadSetting("Clock", "ap", false).toBool());
    stackedClock->addWidget(1, m_lcdClock);
    connect(m_lcdClock, SIGNAL(signalClicked(int,int,int)), stackedClock, SLOT(setCurrentIndex(int,int,int)));

    m_miniCalendar = new MiniCalendarWidget(widgetMain);
    m_miniCalendar->setFixedSize(220, 240);

    horLayout->addStretch();
    horLayout->addWidget(stackedClock, 1);
    horLayout->addWidget(m_miniCalendar, 1);
    horLayout->addStretch();

    QPushButton *btnConfig = new QPushButton(this);
    btnConfig->setText(tr("设置"));
    btnConfig->setFixedSize(166, 70);
    btnConfig->setStyleSheet(QString("QPushButton{ border-image: url(:/images/calendar/ic_btn.png);"
                                     "color: #ffffff; font: 30px; font-family:'%1'}"
                                     "QPushButton::pressed{border-image: url(:/images/calendar/ic_btn_pre.png);}").arg(Skin::m_strAppFontBold));

    connect(btnConfig, SIGNAL(clicked(bool)), this, SLOT(SltBtnSetting()));

    // 主界面布局
    m_verLayoutMain = new QVBoxLayout(widgetMain);
    m_verLayoutMain->addStretch();
    m_verLayoutMain->addLayout(horLayout);
    m_verLayoutMain->addStretch();
    m_verLayoutMain->addWidget(btnConfig, 0, Qt::AlignHCenter);

    m_stackedWidget->addWidget(0, widgetMain);

    // 日历界面
    QtCalendarWidget *calendar = new QtCalendarWidget(m_stackedWidget);
    calendar->SetBackground(Qt::transparent);
    calendar->SetFont(QFont(Skin::m_strAppFontBold));
    calendar->setFixedHeight(400);
    m_stackedWidget->addWidget(1, calendar);

    connect(calendar, SIGNAL(currentDateChanged(QDate)), this, SLOT(SltCurrentDateChanged(QDate)));
    connect(m_miniCalendar, SIGNAL(changeCurrentPage(int,int)), this, SLOT(SltChangePage(int,int)));
}

void CalendarWidget::CreateConfigPage()
{
    int style = AppConfig::ReadSetting("Clock", "style", 0).toInt();
    m_imageClock->SetClockStyle((QtClockWidget::ClockStyle)style);

    ClockBackgroundCfg *widgetBgconfig = new ClockBackgroundCfg(m_stackedWidget);
    widgetBgconfig->setFont(QFont(Skin::m_strAppFontBold));
    widgetBgconfig->setIndexStyle(style);
    connect(widgetBgconfig, SIGNAL(signalBackground(int)), this, SLOT(SltChangeClockStyle(int)));
    connect(widgetBgconfig, SIGNAL(signalChangePage(int,int)), this, SLOT(SltChangePage(int,int)));
    m_stackedWidget->addWidget(2, widgetBgconfig);

    TimeFormatConf *timeformatCfg = new TimeFormatConf(m_stackedWidget);
    timeformatCfg->setFont(QFont(Skin::m_strAppFontBold));
    connect(timeformatCfg, SIGNAL(signalChangePage(int,int)), this, SLOT(SltChangePage(int,int)));
    connect(timeformatCfg, SIGNAL(signalChangeApMode(bool)), m_lcdClock, SLOT(setApMode(bool)));

    m_stackedWidget->addWidget(3, timeformatCfg);

    TimeConfigWidget *timeConfig = new TimeConfigWidget(m_stackedWidget);
    timeConfig->setFont(QFont(Skin::m_strAppFontBold));
    connect(timeConfig, SIGNAL(signalChangePage(int,int)), this, SLOT(SltChangePage(int,int)));
    m_stackedWidget->addWidget(4, timeConfig);

    DateConfigWidget *dateConfig = new DateConfigWidget(m_stackedWidget);
    dateConfig->setFont(QFont(Skin::m_strAppFontBold));
    connect(dateConfig, SIGNAL(signalChangePage(int,int)), this, SLOT(SltChangePage(int,int)));
    m_stackedWidget->addWidget(5, dateConfig);
}

void CalendarWidget::SltCurrentPageChanged(int index)
{
    m_btnBack->setVisible(0 != index);
    m_labelDate->setVisible(1 == index);
    this->SetBackground(QPixmap(QString(":/images/calendar/%1.png").arg(1 == index ? "ic_background_none" : "ic_background")));
}

void CalendarWidget::SltChangePage(int index, int direction)
{
    m_stackedWidget->setCurrentIndex(index, (QtStackedWidget::MoveDirection)direction);
    m_widgetTitle->SetTitle(m_strListTitle.at(index));
}

void CalendarWidget::SltBtnBackClicked()
{
    m_stackedWidget->setCurrentIndex(0, QtStackedWidget::RightDirection);
    m_widgetTitle->SetTitle(m_strListTitle.at(0));
}

void CalendarWidget::SltBtnSetting()
{
    m_btnBack->setVisible(false);
    m_stackedWidget->setCurrentIndex(2);
}

void CalendarWidget::SltCurrentDateChanged(const QDate &date)
{
    m_labelDate->setText(date.toString("yyyy年MM月dd日"));
}

void CalendarWidget::SltChangeClockStyle(int index)
{
    m_imageClock->SetClockStyle((QtClockWidget::ClockStyle)index);
    AppConfig::SaveSetting("Clock", "style", index);
}

void CalendarWidget::resizeEvent(QResizeEvent *e)
{
#ifdef BUILD_WITH_HDMI
    if (this->height() < 500) {
        m_verLayoutMain->setContentsMargins(10, 0, 10, 20);
    } else {
        m_verLayoutMain->setContentsMargins(10, 0, 10, this->height() * 0.076);
    }
#else
    m_verLayoutMain->setContentsMargins(10, 10, 10, 20);
#endif
    QWidget::resizeEvent(e);
}
