/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : qttoolbar.h --- QtToolBar
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef QTTOOLBAR_H
#define QTTOOLBAR_H

#include "qtwidgetbase.h"
#include <QPropertyAnimation>

#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT QtToolBar : public QtWidgetBase {
#else
class QtToolBar : public QtWidgetBase {
#endif
    Q_OBJECT
public:
    explicit QtToolBar(QWidget *parent = 0);
    ~QtToolBar();

    virtual void SetAnimation(const QPoint &startPos, const QPoint &endPos);
signals:
    void signalFinihed();

protected:
    QPropertyAnimation *m_animation;
};

#endif // QTTOOLBAR_H
