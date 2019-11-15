/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : circularprogressbar.h --- CircularProgressBar
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/1
*******************************************************************/
#ifndef CIRCULARPROGRESSBAR_H
#define CIRCULARPROGRESSBAR_H

#include "qtwidgetbase.h"
#include <QPropertyAnimation>

class CircularProgressBar : public QtWidgetBase
{
    Q_OBJECT
public:
    explicit CircularProgressBar(QWidget *parent = 0);
    ~CircularProgressBar();

    Q_PROPERTY(int value READ GetVaule WRITE SetValue NOTIFY currentValueChanged)

    void SetMaxValue(int value);
    int GetVaule() {return m_nCurrentValue;}
    void setCurrentValue(int value);

signals:
    void currentValueChanged(int value);

private slots:
    void SetValue(int value);

private:
    int     m_nCurrentValue;
    int     m_MinValue;
    int     m_nMaxValue;

    QPropertyAnimation *m_animation;

protected:
    void paintEvent(QPaintEvent *);
    void drawBackground(QPainter *painter);
    void drawRing(QPainter *painter);
    void drawPointerTriangle(QPainter *painter);
    void drawValue(QPainter *painter);
};

#endif // CIRCULARPROGRESSBAR_H

