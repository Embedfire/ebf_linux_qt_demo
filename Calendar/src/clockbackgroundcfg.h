/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : clockbackgroundcfg.h --- ClockBackgroundCfg
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef CLOCKBACKGROUNDCFG_H
#define CLOCKBACKGROUNDCFG_H

#include "qtwidgetbase.h"
#include "qtpixmapbutton.h"

class ClockBackgroundCfg : public QtWidgetBase
{
    Q_OBJECT
public:
    explicit ClockBackgroundCfg(QWidget *parent = 0);
    ~ClockBackgroundCfg();

    void setIndexStyle(const int &style);

signals:
    void signalBackground(int index);
    void signalChangePage(int index, int direction);

public slots:

private:
    QList<QPixmap> m_pixmaps;
    QList<QRect>   m_rects;

    QPixmap        m_pixmapSelected;
    int            m_nIndex;

    QtPixmapButton  m_btnSure;
    QtPixmapButton  m_btnNext;

protected:
    void paintEvent(QPaintEvent *);
    void drawButton(QPainter *painter);

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // CLOCKBACKGROUNDCFG_H
