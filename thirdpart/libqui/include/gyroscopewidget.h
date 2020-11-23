/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : gyroscopewidget.h --- GyroscopeWidget
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef GYROSCOPEWIDGET_H
#define GYROSCOPEWIDGET_H

#include <QWidget>

#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT GyroscopeWidget : public QWidget {
#else
class GyroscopeWidget : public QWidget {
#endif
    Q_OBJECT
public:
    explicit GyroscopeWidget(QWidget *parent = 0);
    ~GyroscopeWidget();

    void setRollValue(int value);
    void setPitchValue(int value);
    void setYawValue(int value);

    void SetFont(QFont font);
signals:

public slots:

private:
    int m_nPitchValue;
    int m_nRollValue;
    int m_nYawValue;

    QFont m_font;
protected:
    void paintEvent(QPaintEvent *);

    void drawYawBoard(QPainter *painter);
    void drawRollBoard(QPainter *painter);
    void drawPitchBoard(QPainter *painter);
    void drawPitchScale(QPainter *painter);
};

#endif // GYROSCOPEWIDGET_H
