/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : timeformatconf.h --- TimeFormatConf
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef TIMEFORMATCONF_H
#define TIMEFORMATCONF_H

#include <QWidget>
#include "qtswitchbutton.h"
#include "qtpixmapbutton.h"

class TimeFormatConf : public QWidget
{
    Q_OBJECT
public:
    explicit TimeFormatConf(QWidget *parent = 0);
    ~TimeFormatConf();

signals:
    void signalChangePage(int index, int direction);
    void signalChangeApMode(bool on);

public slots:

private slots:
    void SltSwitchBtnClicked(bool on);

private:
    QtPixmapButton  m_btnPrev;
    QtPixmapButton  m_btnSure;
    QtPixmapButton  m_btnNext;

    QtSwitchButton  *m_timeFormat;
    QRect           m_rectCenter;

protected:
    QSize sizeHint() const;
    void resizeEvent(QResizeEvent *e);
    void paintEvent(QPaintEvent *);
    void drawButton(QPainter *painter);

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // TIMEFORMATCONF_H
