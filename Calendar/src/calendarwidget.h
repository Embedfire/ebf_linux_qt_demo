/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : calendarwidget.h ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/6
*******************************************************************/
#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "qtwidgetbase.h"
#include "qtclockwidget.h"
#include "qtstackedwidget.h"
#include "qtlcdclockwidget.h"
#include "minicalendarwidget.h"

class CalendarWidget : public QtAnimationWidget
{
    Q_OBJECT

public:
    CalendarWidget(QWidget *parent = 0);
    ~CalendarWidget();

signals:

private:
    QtWidgetTitleBar    *m_widgetTitle;
    QPushButton         *m_btnBack;
    QLabel              *m_labelDate;

    QtStackedWidget     *m_stackedWidget;
    QtClockWidget       *m_imageClock;
    QtLcdClockWidget    *m_lcdClock;

    MiniCalendarWidget  *m_miniCalendar;

    QStringList         m_strListTitle;
    QVBoxLayout        *m_verLayoutMain;
private:
    void InitWidget();
    void CreateMainPage();
    void CreateConfigPage();

private slots:
    void SltCurrentPageChanged(int index);
    void SltChangePage(int index, int direction);
    void SltBtnBackClicked();
    void SltBtnSetting();
    void SltCurrentDateChanged(const QDate &date);

    void SltChangeClockStyle(int index);

protected:
    void resizeEvent(QResizeEvent *e);
};

#endif // CALENDARWIDGET_H
