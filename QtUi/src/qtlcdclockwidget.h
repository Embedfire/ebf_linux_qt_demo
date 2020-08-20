/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : qtlcdclockwidget.h --- QtLcdClockWidget
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/10/13
*******************************************************************/
#ifndef QTLCDCLOCKWIDGET_H
#define QTLCDCLOCKWIDGET_H

#include <QLCDNumber>
#include <QTimer>

#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT QtLcdClockWidget : public QLCDNumber {
#else
class QtLcdClockWidget : public QLCDNumber {
#endif
    Q_OBJECT
public:
    explicit QtLcdClockWidget(QWidget *parent = 0);
    ~QtLcdClockWidget();

signals:
     void signalClicked(int index = 0, int direction = 2, int resize = -1);

public slots:
     void setApMode(bool on);

private:
    QTimer  *m_timer;
    QString  m_strTimeFormat;

private slots:
    void SltUpdateTime();

protected:
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);
    void mousePressEvent(QMouseEvent *);
};

#endif // QTLCDCLOCKWIDGET_H
