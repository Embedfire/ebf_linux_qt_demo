/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : photolistview.h --- PhotoListView
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/8
*******************************************************************/
#ifndef PHOTOLISTVIEW_H
#define PHOTOLISTVIEW_H

#include <QWidget>
#include "qtpagelistwidget.h"

class PhotoListView : public QtPageListWidget
{
    Q_OBJECT
public:
    explicit PhotoListView(QWidget *parent = 0);
    ~PhotoListView();

signals:

public slots:

protected:
    void drawItemInfo(QPainter *painter, QtPageListWidgetItem *item);
};

#endif // PHOTOLISTVIEW_H
