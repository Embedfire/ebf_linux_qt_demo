/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : calendarmainpage.h --- CalendarMainPage
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/11/10
*******************************************************************/
#ifndef CALENDARMAINPAGE_H
#define CALENDARMAINPAGE_H

#include "qtwidgetbase.h"
#include "qtclockwidget.h"
#include "minicalendarwidget.h"
#include "qtstackedwidget.h"

class CalendarMainPage : public QtWidgetBase
{
    Q_OBJECT
public:
    explicit CalendarMainPage(QWidget *parent = 0);
    ~CalendarMainPage();

signals:
    void changeCurrentPage(int index, int direction);
    void signalChangeApMode(bool on);
    void changeClockStyle(QtClockWidget::ClockStyle style);

public slots:

private:
    QtStackedWidget     *m_stackedClock;
    MiniCalendarWidget  *m_miniCalendar;

protected:
    void resizeEvent(QResizeEvent *e);
    void paintEvent(QPaintEvent *);
};

#endif // CALENDARMAINPAGE_H
