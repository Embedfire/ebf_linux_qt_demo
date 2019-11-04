/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : qtebooklist.h --- QtEbookList
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/8
*******************************************************************/
#ifndef QTEBOOKLIST_H
#define QTEBOOKLIST_H

#include <QWidget>
#include "qtpagelistwidget.h"

class QtEbookList : public QtPageListWidget
{
    Q_OBJECT
public:
    explicit QtEbookList(QWidget *parent = 0);
    ~QtEbookList();

signals:

public slots:

protected:
    void drawItemInfo(QPainter *painter, QtPageListWidgetItem *item);
};

#endif // QTEBOOKLIST_H
