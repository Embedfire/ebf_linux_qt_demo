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
#include "qtstackedwidget.h"
#include "calendarmainpage.h"
#include "qtclockwidget.h"

class CalendarWidget : public QtAnimationWidget
{
    Q_OBJECT

public:
    CalendarWidget(QWidget *parent = 0);
    ~CalendarWidget();

signals:
    void changeClockStyle(QtClockWidget::ClockStyle style);
private:
    QtWidgetTitleBar    *m_widgetTitle;
    QLabel              *m_labelDate;

    QtStackedWidget     *m_stackedWidget;
    CalendarMainPage    *m_mainPage;

    QStringList         m_strListTitle;
    QVBoxLayout        *m_verLayoutMain;
    QString             m_strTitle;
    int                 m_nCurrentPage;
    QString             m_strCurrDate;


    QtPixmapButton      *m_btnBack;
    QtPixmapButton      *m_btnHome;

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
    void SltBtnClicked(int index);

protected:
    void paintEvent(QPaintEvent *);
};

#endif // CALENDARWIDGET_H
