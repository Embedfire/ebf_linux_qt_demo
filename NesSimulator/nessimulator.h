/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : nessimulator.h ---
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef NESSIMULATOR_H
#define NESSIMULATOR_H

#include <QWidget>
#include "qtwidgetbase.h"
#include "gamewidget.h"
#include "qttoolbar.h"

class SimulatorTitleBar : public QtToolBar {
    Q_OBJECT
public:
    explicit SimulatorTitleBar(QWidget *parent = 0);
    ~SimulatorTitleBar();

public slots:
    void SetText(const QString &text);

signals:
    void signalBack();

private:
    QString m_strText;
    QRect   m_rectBack;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
};

////////////////////////////////////////////////////////
class NesSimulator : public QtAnimationWidget
{
    Q_OBJECT

public:
    NesSimulator(QWidget *parent = 0);
    ~NesSimulator();

    void sendKeyPressed(QKeyEvent *event);
    void sendKeyReleased(QKeyEvent *event);

private:
    SimulatorTitleBar *m_titleBar;

protected:
    void resizeEvent(QResizeEvent *e);
    void mousePressEvent(QMouseEvent *);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // NESSIMULATOR_H
