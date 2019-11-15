/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : timesettingpage.h --- TimeSettingPage
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef DATETIMESETTINGPAGE_H
#define DATETIMESETTINGPAGE_H

#include <QWidget>
#include "qtdatetimeconfig.h"

class DateTimeSettingPage : public QtWidgetBase
{
    Q_OBJECT
public:
    explicit DateTimeSettingPage(QWidget *parent = 0,
                                 QtDateTimeConfig::ConfigFromat format = QtDateTimeConfig::DateFormat);
    ~DateTimeSettingPage();

signals:
    void signalFinished();

public slots:

private:
    QtDateTimeConfig *m_timeConfig;
    QtPixmapButton   *m_btnOk;

private slots:
    void SetSystemDatetime();

protected:
    void resizeEvent(QResizeEvent *e);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // DATETIMESETTINGPAGE_H
