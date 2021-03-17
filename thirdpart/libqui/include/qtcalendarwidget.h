/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : qtcalendarwidget.h --- QtCalendarWidget
 作 者    : Niyh(lynnhua)
 论 坛    : http:// www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef QTCALENDARWIDGET_H
#define QTCALENDARWIDGET_H

#include "qtwidgetbase.h"
#include <QDate>
#include <QPropertyAnimation>

#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT LunarCalendarInfo : public QObject {
#else
class LunarCalendarInfo : public QObject {
#endif
    Q_OBJECT
public:
    static LunarCalendarInfo *Instance();
    explicit LunarCalendarInfo(QObject *parent = 0);
    ~LunarCalendarInfo();

    bool isToday(const QDate &date);

    // 计算是否闰年
    bool isLoopYear(int year);

    // 计算指定年月该月共多少天
    int getMonthDays(int year, int month);

    // 计算指定年月对应到该月共多少天
    int getTotalMonthDays(int year, int month);

    // 计算指定年月对应星期几
    int getFirstDayOfWeek(int year, int month);

    // 计算国际节日
    QString getHoliday(int month, int day);

    // 计算二十四节气
    QString getSolarTerms(int year, int month, int day);

    // 计算农历节日(必须传入农历年份月份)
    QString getLunarFestival(int month, int day);

    // 计算农历年 天干+地支+生肖
    QString getLunarYear(int year);

    // 计算指定年月日农历信息,包括公历节日和农历节日及二十四节气
    void getLunarCalendarInfo(int year, int month, int day,
                              QString &strHoliday,
                              QString &strSolarTerms,
                              QString &strLunarFestival,
                              QString &strLunarYear,
                              QString &strLunarMonth,
                              QString &strLunarDay);

    // 获取指定年月日农历信息
    QString getLunarInfo(int year, int month, int day, bool yearInfo, bool monthInfo, bool dayInfo);
    QString getLunarYearMonthDay(int year, int month, int day);
    QString getLunarMonthDay(int year, int month, int day);
    QString getLunarDay(int year, int month, int day);
    QString getWeekName(int week, int type = 0);

    QDate   getNextMonth(const QDate &date);
    QDate   getPrevMonth(const QDate &date);
private:
    static LunarCalendarInfo *self;

    QList<int> lunarCalendarTable;      // 农历年表
    QList<int> springFestival;          // 春节公历日期
    QList<int> lunarData;               // 农历每月数据
    QList<int> chineseTwentyFourData;   // 农历二十四节气数据
    QList<int> monthAdd;                // 公历每月前面的天数

    QList<QString> listDayName;         // 农历日期名称集合
    QList<QString> listMonthName;       // 农历月份名称集合
    QList<QString> listSolarTerm;       // 二十四节气名称集合

    QList<QString> listTianGan;         // 天干名称集合
    QList<QString> listDiZhi;           // 地支名称集合
    QList<QString> listShuXiang;        // 属相名称集合
};

#ifdef QtUi
class QTUISHARED_EXPORT QtCalendarWidget : public QtWidgetBase {
#else
class QtCalendarWidget : public QtWidgetBase {
#endif
    Q_OBJECT
public:
    typedef enum {None, LeftDirection, RightDirection} MoveDirection;
    Q_PROPERTY(int xPos READ Xpos WRITE setXPos)

    explicit QtCalendarWidget(QWidget *parent = 0);
    ~QtCalendarWidget();

    void SetFont(QFont font);
    void SetBackground(const QColor &color);
    void SetCellSize(int w, int h);

signals:
    void currentDateChanged(const QDate &date);

public slots:

private:
    void setXPos(int nValue);
    int Xpos(){return m_nStartPos;}

private:
    QColor      m_colorBackground;
    QColor      m_colorText;

    QFont       m_font;
private:
    bool    m_bPressed;
    QPoint  m_startPos;
    int     m_nStartPos;

    int     m_nCurrentYear;
    int     m_nCurrentMonth;
    int     m_nCurrendDay;
    QDate   m_currentDate;

    int     m_nCurrentIndex;
    int     m_nDirection;

    qreal   m_cellWidth;
    qreal   m_cellHeight;

    QRect   m_calendarRect;

    LunarCalendarInfo   *m_lunarCalendarInfo;
    QPropertyAnimation  *m_animationMove;
    int                 m_nMoveEndValue;
    bool                m_bRecovery;
private:
    void CalcRectSize();

protected:    
    void paintEvent(QPaintEvent *);
    void drawTitle(QPainter *painter);
    void drawDays(QPainter *painter, const QDate &date, int nStartPos);

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
};

#endif //  QTCALENDARWIDGET_H
