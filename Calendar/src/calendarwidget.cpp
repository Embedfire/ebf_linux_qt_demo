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
#include "qtclockwidget.h"

#include <QPainter>
#include <QDateTime>

#include <QPainter>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

CalendarWidget::CalendarWidget(QWidget *parent) : QtAnimationWidget(parent)
{
    this->SetBackground(QPixmap(":/images/calendar/ic_background.png"));

    m_nCurrentPage = 0;
    m_strTitle = tr("时间&日历");
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
    m_stackedWidget = new QtStackedWidget(this);
    m_stackedWidget->setPressMove(false);
    m_stackedWidget->SetBackground(Qt::transparent);
    connect(m_stackedWidget, SIGNAL(currentChanged(int)), this, SLOT(SltCurrentPageChanged(int)));

    QVBoxLayout *verLayoutAll = new QVBoxLayout(this);
    verLayoutAll->setContentsMargins(0, 0, 0, 0);
    verLayoutAll->setSpacing(0);
    verLayoutAll->addStretch(1);
    verLayoutAll->addWidget(m_stackedWidget, 5);

    m_btnBack = new QtPixmapButton(0, QRect(10, 20, 40, 40), QPixmap(":/images/calendar/ic_back.png"), QPixmap(":/images/calendar/ic_back_pressed.png"));
    m_btns.insert(0, m_btnBack);
    m_btnBack->setVisible(false);

    m_btnHome = new QtPixmapButton(1, QRect(736, 13, 54, 54), QPixmap(":/images/backlight/menu_icon.png"), QPixmap(":/images/backlight/menu_icon_pressed.png"));
    m_btns.insert(1, m_btnHome);
    connect(this, SIGNAL(signalBtnClicked(int)), this, SLOT(SltBtnClicked(int)));
}

void CalendarWidget::CreateMainPage()
{
    m_mainPage = new CalendarMainPage(m_stackedWidget);
    connect(this, SIGNAL(changeClockStyle(QtClockWidget::ClockStyle)), m_mainPage, SIGNAL(changeClockStyle(QtClockWidget::ClockStyle)));
    connect(m_mainPage, SIGNAL(signalBtnClicked(int)), m_stackedWidget, SLOT(setCurrentIndex(int)));
    m_stackedWidget->addWidget(0, m_mainPage);

    // 日历界面
    QtCalendarWidget *calendar = new QtCalendarWidget(m_stackedWidget);
    calendar->SetBackground(Qt::transparent);
    calendar->SetFont(QFont(Skin::m_strAppFontBold));
    m_stackedWidget->addWidget(1, calendar);

    connect(calendar, SIGNAL(currentDateChanged(QDate)), this, SLOT(SltCurrentDateChanged(QDate)));
    connect(m_mainPage, SIGNAL(changeCurrentPage(int,int)), this, SLOT(SltChangePage(int,int)));
}

void CalendarWidget::CreateConfigPage()
{
    int style = AppConfig::ReadSetting("Clock", "style", 0).toInt();
    ClockBackgroundCfg *widgetBgconfig = new ClockBackgroundCfg(m_stackedWidget);
    widgetBgconfig->setFont(QFont(Skin::m_strAppFontBold));
    widgetBgconfig->setIndexStyle(style);
    connect(widgetBgconfig, SIGNAL(signalBackground(int)), this, SLOT(SltChangeClockStyle(int)));
    connect(widgetBgconfig, SIGNAL(signalChangePage(int,int)), this, SLOT(SltChangePage(int,int)));
    m_stackedWidget->addWidget(2, widgetBgconfig);

    TimeFormatConf *timeformatCfg = new TimeFormatConf(m_stackedWidget);
    timeformatCfg->setFont(QFont(Skin::m_strAppFontBold));
    connect(timeformatCfg, SIGNAL(signalChangePage(int,int)), this, SLOT(SltChangePage(int,int)));
    connect(timeformatCfg, SIGNAL(signalChangeApMode(bool)), m_mainPage, SIGNAL(signalChangeApMode(bool)));

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
    m_nCurrentPage = index;
    m_btnHome->setVisible(0 == index);
    m_btnBack->setVisible(0 != index);
    if (1 == index) m_strCurrDate = QDate::currentDate().toString(tr("yyyy年MM月dd日"));
    this->SetBackground(QPixmap(QString(":/images/calendar/%1.png").arg(1 == index ? "ic_background_none" : "ic_background")));
}

void CalendarWidget::SltChangePage(int index, int direction)
{
    m_stackedWidget->setCurrentIndex(index, (QtStackedWidget::MoveDirection)direction);
    m_strTitle = m_strListTitle.at(index);
    this->update();
}

void CalendarWidget::SltBtnBackClicked()
{
    m_stackedWidget->setCurrentIndex(0, QtStackedWidget::RightDirection);
    m_strTitle = m_strListTitle.at(0);
    this->update();
}

void CalendarWidget::SltBtnSetting()
{
    m_btnBack->setVisible(true);
    m_btnHome->setVisible(false);
    this->update();
    m_stackedWidget->setCurrentIndex(2);
}

void CalendarWidget::SltCurrentDateChanged(const QDate &date)
{
    m_strCurrDate = date.toString(tr("yyyy年MM月dd日"));
    this->update();
}

void CalendarWidget::SltChangeClockStyle(int index)
{
    AppConfig::SaveSetting("Clock", "style", index);
    emit changeClockStyle((QtClockWidget::ClockStyle)index);
}

void CalendarWidget::SltBtnClicked(int index)
{
    if (0 == index) {
        SltBtnBackClicked();
    } else if (1 == index) {
        emit signalBackHome();
    }
}

void CalendarWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.scale(m_scaleX, m_scaleY);
    painter.drawPixmap(0, 0, m_nBaseWidth, m_nBaseHeight, m_pixmapBackground);

    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(32);
    painter.setFont(font);
    painter.setPen(QColor("#ffffff"));
    painter.drawText(0, 0, m_nBaseWidth, 80, Qt::AlignCenter, m_strTitle);

    font.setFamily(Skin::m_strAppFontNormal);
    font.setPixelSize(24);
    painter.setFont(font);
    if (1 == m_nCurrentPage) {
        painter.drawText(60, 0, 200, 80, Qt::AlignVCenter, m_strCurrDate);
    }

    // 绘制按钮
    foreach (QtPixmapButton *btn, m_btns) {
        painter.drawPixmap(btn->rect(), btn->pixmap());
    }
}

