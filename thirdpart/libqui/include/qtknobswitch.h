/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : qtknobswitch.h --- QtKnobSwitch
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef QTKNOBSWITCH_H
#define QTKNOBSWITCH_H

#include "qtwidgetbase.h"

#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT QtKnobSwitch : public QtWidgetBase {
#else
class QtKnobSwitch : public QtWidgetBase {
#endif
    Q_OBJECT
public:
    explicit QtKnobSwitch(QWidget *parent = 0);
    ~QtKnobSwitch();

signals:
    void valueChanged(int value);

public slots:
    void setValue(int value);

private:
    int m_nMinValue;                // 最小值
    int m_nMaxValue;                // 最大值
    int m_value;                   // 当前值

    bool m_bPressed;

protected:
    void paintEvent(QPaintEvent *);
    void drawHandle(QPainter *painter);
    void drawValue(QPainter *painter);

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
};

#endif // QTKNOBSWITCH_H
