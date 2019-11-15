/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : displayrealdata.h --- DisplayRealData
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/2
*******************************************************************/
#ifndef DISPLAYREALDATA_H
#define DISPLAYREALDATA_H

#include "qtwidgetbase.h"

class DisplayRealData : public QtWidgetBase
{
    Q_OBJECT
public:
    explicit DisplayRealData(QWidget *parent = 0);
    ~DisplayRealData();

signals:

public slots:

private:
    QPixmap m_pixmap;
protected:
    void paintEvent(QPaintEvent *);
    void drawValues(QPainter *painter);

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // DISPLAYREALDATA_H
