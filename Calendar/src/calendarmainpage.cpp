/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : calendarmainpage.cpp --- CalendarMainPage
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/11/10
*******************************************************************/
#include "calendarmainpage.h"
#include "minicalendarwidget.h"
#include "qtstackedwidget.h"
#include "qtclockwidget.h"
#include "qtlcdclockwidget.h"
#include "appconfig.h"
#include "skin.h"

#include <QPainter>

CalendarMainPage::CalendarMainPage(QWidget *parent) : QtWidgetBase(parent)
{
    m_nBaseWidth = Skin::m_nScreenWidth;
    m_nBaseHeight = 400;

    m_stackedClock = new QtStackedWidget(this);
    m_stackedClock->setPressMove(false);
    m_stackedClock->SetBackground(Qt::transparent);

    int style = AppConfig::ReadSetting("Clock", "style", 0).toInt();
    QtClockWidget *imageClock = new QtClockWidget(m_stackedClock);
    imageClock->SetClockStyle((QtClockWidget::ClockStyle)style);
    m_stackedClock->addWidget(0, imageClock);
    connect(imageClock, SIGNAL(signalClicked(int,int,int)), m_stackedClock, SLOT(setCurrentIndex(int,int,int)));
    connect(this, SIGNAL(changeClockStyle(QtClockWidget::ClockStyle)), imageClock, SLOT(SetClockStyle(QtClockWidget::ClockStyle)));

    QtLcdClockWidget *lcdClock = new QtLcdClockWidget(m_stackedClock);
    lcdClock->setApMode(!AppConfig::ReadSetting("Clock", "ap", false).toBool());
    m_stackedClock->addWidget(1, lcdClock);
    connect(lcdClock, SIGNAL(signalClicked(int,int,int)), m_stackedClock, SLOT(setCurrentIndex(int,int,int)));
    connect(this, SIGNAL(signalChangeApMode(bool)), lcdClock, SLOT(setApMode(bool)));

    m_miniCalendar = new MiniCalendarWidget(this);
    connect(m_miniCalendar, SIGNAL(changeCurrentPage(int,int)), this, SIGNAL(changeCurrentPage(int,int)));

    // 配置按钮
    m_btns.insert(2, new QtPixmapButton(2, QRect(317, 310, 166, 70), QPixmap(":/images/calendar/ic_btn.png"), QPixmap(":/images/calendar/ic_btn_pre.png")));
}

CalendarMainPage::~CalendarMainPage()
{

}

void CalendarMainPage::resizeEvent(QResizeEvent *e)
{
    SetScaleValue();
    m_stackedClock->resize(233 * m_scaleX, 243 * m_scaleY);
    m_stackedClock->move(60 * m_scaleX, 30 * m_scaleY);

    m_miniCalendar->resize(220 * m_scaleX, 240 * m_scaleY);
    m_miniCalendar->move(460 * m_scaleX, 30 * m_scaleY);
    QWidget::resizeEvent(e);
}

void CalendarMainPage::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.scale(m_scaleX, m_scaleY);
    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(30);
    painter.setFont(font);
    painter.setPen(QColor("#ffffff"));
    QtPixmapButton *btn = m_btns.value(2);
    if (NULL != btn) {
        painter.drawPixmap(btn->rect(), btn->pixmap());
        painter.drawText(btn->rect(), Qt::AlignCenter, tr("设置"));
    }
}
