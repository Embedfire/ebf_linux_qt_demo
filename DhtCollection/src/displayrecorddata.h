/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : displayrecorddata.h --- DisplayRecordData
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/2
*******************************************************************/
#ifndef DISPLAYRECORDDATA_H
#define DISPLAYRECORDDATA_H

#include <QWidget>
#include <QPushButton>

#include "qtstackedwidget.h"
#include "qtcustomplot.h"

class DisplayRecordData : public QWidget
{
    Q_OBJECT
public:
    explicit DisplayRecordData(QWidget *parent = 0);
    ~DisplayRecordData();

signals:

public slots:

private:
    QtStackedWidget     *m_stackedWidget;
    QtCustomPlot        *m_customPlotTemp;
    QtCustomPlot        *m_customPlotHumidity;

private:
    void InitWidget();

private slots:
    void SltChangePage(int index);

protected:
    void paintEvent(QPaintEvent *);
};

#endif // DISPLAYRECORDDATA_H
