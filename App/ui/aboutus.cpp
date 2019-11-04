/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : aboutus.cpp --- AboutUs
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "aboutus.h"
#include "skin.h"

#include <QPainter>
#include <QMouseEvent>

#define MOVE_STEP   20

AboutUs::AboutUs(QWidget *parent) : QtAnimationWidget(parent)
{
    this->SetAnimationCurve(QEasingCurve::Linear);
    this->SetBackground(QPixmap(":/images/mainwindow/ic_advert.png"));
}

AboutUs::~AboutUs()
{

}

void AboutUs::SltStartMove()
{
    this->setVisible(true);
    this->StartAnimation(QPoint(0, this->height()), QPoint(0, 0), 300, true);
}

QSize AboutUs::sizeHint() const
{
    return QSize(800, 480);
}

void AboutUs::mousePressEvent(QMouseEvent *e)
{
    this->StartAnimation(QPoint(0, 0), QPoint(0, this->height()), 300, false);
    QWidget::mousePressEvent(e);
}
