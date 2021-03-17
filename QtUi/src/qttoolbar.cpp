/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : qttoolbar.cpp --- QtToolBar
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "qttoolbar.h"

QtToolBar::QtToolBar(QWidget *parent) : QtWidgetBase(parent)
{
    m_animation = new QPropertyAnimation(this, "pos");
    m_animation->setDuration(200);
    m_animation->setEasingCurve(QEasingCurve::Linear);
    connect(m_animation, SIGNAL(finished()), this, SIGNAL(signalFinihed()));
}

QtToolBar::~QtToolBar()
{
    m_animation->stop();
    delete m_animation;
    m_animation = NULL;
}

void QtToolBar::SetAnimation(const QPoint &startPos, const QPoint &endPos)
{
    m_animation->setStartValue(startPos);
    m_animation->setEndValue(endPos);
    m_animation->start();
}
