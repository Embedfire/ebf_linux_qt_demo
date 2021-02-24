/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : qtclockwidget.h --- QtClockWidget
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/7
*******************************************************************/
#ifndef QTCLOCKWIDGET_H
#define QTCLOCKWIDGET_H

#include "qtwidgetbase.h"
#include <QTimer>
#include <QPropertyAnimation>

#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT QtClockWidget : public QtWidgetBase {
#else
class QtClockWidget : public QtWidgetBase {
#endif
    Q_OBJECT
public:
    explicit QtClockWidget(QWidget *parent = 0);
    ~QtClockWidget();

    typedef enum {DefaultStyle, BlackStyle, LightStyle, StyleCount} ClockStyle;

signals:
    void signalClicked(int index = 1, int direction = 1, int resize = -1);

public slots:
    void SetClockStyle(QtClockWidget::ClockStyle style);

private:
    QPixmap     m_pixmapBackground;
    QPixmap     m_pixmapHourHand;
    QPixmap     m_pixmapMinuteHand;
    QPixmap     m_pixmapSecondHand;

    QTimer     *m_timer;
    QPropertyAnimation *m_animation;
    ClockStyle  m_colorStyle;
private slots:
    void SltUpdateTime();

protected:
    QSize sizeHint() const;

    void paintEvent(QPaintEvent *);
    void drawBackground(QPainter *painter);
    void drawHourHand(QPainter *painter);
    void drawMinuteHand(QPainter *painter);
    void drawSecondHand(QPainter *painter);

    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);

    void mousePressEvent(QMouseEvent *);
};

#endif // QTCLOCKWIDGET_H
