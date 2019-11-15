/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : infoneslistwidget.h --- InfoNesListWidget
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/10/19
*******************************************************************/
#ifndef INFONESLISTWIDGET_H
#define INFONESLISTWIDGET_H

#include <QWidget>
#include "qtlistwidget.h"

class InfoNesListWidget : public QtListWidget
{
    Q_OBJECT
public:
    explicit InfoNesListWidget(QWidget *parent = 0);
    ~InfoNesListWidget();

    void LoadNesResource(const QString &path);

signals:

public slots:

protected:
    void drawItemInfo(QPainter *painter, QtListWidgetItem *item);
};

#endif // INFONESLISTWIDGET_H
