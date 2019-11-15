/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : dhtcollection.h ---
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef DHTCOLLECTION_H
#define DHTCOLLECTION_H

#include "qtwidgetbase.h"
#include "qtstackedwidget.h"
#include "displayrealdata.h"
#include "displayrecorddata.h"

#include <QProcess>
#include <QTimer>
#include <QVBoxLayout>

class DhtCollection : public QtAnimationWidget
{
    Q_OBJECT

public:
    DhtCollection(QWidget *parent = 0);
    ~DhtCollection();

private:
    void InitWidget();

private:
    QtWidgetTitleBar    *m_widgetTitle;
    QtStackedWidget     *m_stackedWidget;
    int                  m_nIndex;

    DisplayRealData     *m_realData;
    DisplayRecordData   *m_recordData;

    QProcess            *m_cmd;
    QTimer              *m_timer;

private slots:
    void SltCurrentChanged(int index);
    void SltProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

    void StartCmd();

protected:
    void paintEvent(QPaintEvent *);

    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);

    void resizeEvent(QResizeEvent *e);
};

#endif // DHTCOLLECTION_H
