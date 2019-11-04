/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : videolistviewer.h --- VideoListViewer
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef VIDEOLISTVIEWER_H
#define VIDEOLISTVIEWER_H

#include "qtpagelistwidget.h"

class VideoListViewer : public QtPageListWidget
{
    Q_OBJECT
public:
    explicit VideoListViewer(QWidget *parent = 0);
    ~VideoListViewer();

    void setItems();
signals:

public slots:

protected:
    void drawItemInfo(QPainter *painter, QtPageListWidgetItem *item);
};

#endif // VIDEOLISTVIEWER_H
