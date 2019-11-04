/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : aboutus.h --- AboutUs
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef ABOUTUS_H
#define ABOUTUS_H

#include "qtwidgetbase.h"
#include <QTimer>

class AboutUs : public QtAnimationWidget
{
    Q_OBJECT
public:
    explicit AboutUs(QWidget *parent = 0);
    ~AboutUs();

signals:

public slots:
    void SltStartMove();

private:

protected:
    QSize sizeHint() const;
    void mousePressEvent(QMouseEvent *e);
};

#endif // ABOUTUS_H
