/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : citymanagerwidget.h --- CityManagerWidget
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef CITYMANAGERWIDGET_H
#define CITYMANAGERWIDGET_H

#include <QWidget>
#include <QLineEdit>

#include "qtlistwidget.h"
#include "qtwidgetbase.h"

class CityManagerWidget : public QtAnimationWidget
{
    Q_OBJECT
public:
    explicit CityManagerWidget(QWidget *parent = 0);
    ~CityManagerWidget();

signals:
    void signalCityChanged(const QString &city);

public slots:

private:
    QLineEdit       *m_lineEdit;
    QtListWidget    *m_listCitys;

    QString          m_strCurrentCity;

private:
    void InitWidget();

private slots:
    void SltSearcCitys();
    void SltCitySelected(QtListWidgetItem *item);
    void SltToolBtnClicked(int index);
protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
};

#endif // CITYMANAGERWIDGET_H
