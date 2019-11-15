/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : calculator.h ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/8/31
*******************************************************************/
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "qtwidgetbase.h"
#include "calcfunction.h"

#include <QMap>
#include <QLineEdit>

#define  INPUT_BY_LINEEDIT     1

class CalcButton {
public:
    typedef enum { BtnFun, BtnSymbol, BtnOperator, BtnNumber, BtnResult} BtnType;
    CalcButton(int id, QRect rect, QString text):
        m_nId(id),m_nType(id),m_rect(rect),m_strText(text)
    {
    }

    int id() {return m_nId;}
    int type() {return m_nType;}

    QRect rect() {return m_rect;}
    void setRect(const QRect &rect) { m_rect = rect;}

    QString text() {return m_strText;}

private:
    int     m_nId;
    int     m_nType;
    QRect   m_rect;
    QString m_strText;
};


class Calculator : public QtAnimationWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = 0);
    ~Calculator();

    typedef enum {
        Bin, Oct, Dec, Hex, AC, BackSpace, Division,
        Square, Power, Ln, Number_7, Number_8, Number_9, Multiplication,
        Factorial, Log, SquareRoot, Number_4, Number_5, Number_6, Minus,
        Sin, Cos, Tan, Number_1, Number_2, Number_3, Plus,
        Mod, LeftBrackets, RightBrackets, Negative, Number_0, Point, Result,
        BtnCount
    } BtnType;

private:
    QMap<int, CalcButton*> m_calcBtns;
    QLineEdit              *express_lineEdit;

    int         m_nCurrentIndex;

    qreal       m_realTemp;
    QString     m_strHistory;
    QString     m_strResult;

    QRect       m_rectHome;
    bool        m_bRectHomePressed;
    bool        m_bInputSymbol;
    bool        m_bResult;

    CCalculator *ccalculator;
private:
    void InitData();
    void onButtonClicked(CalcButton *btn);

protected:
    void resizeEvent(QResizeEvent *e);
    void paintEvent(QPaintEvent *);
    void drawHistory(QPainter *painter);
    void drawButtons(QPainter *painter);

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // CALCULATOR_H
