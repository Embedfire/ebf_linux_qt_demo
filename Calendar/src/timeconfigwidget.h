/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : timeconfigwidget.h --- TimeConfigWidget
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef TIMECONFIGWIDGET_H
#define TIMECONFIGWIDGET_H

#include "qtwidgetbase.h"
#include "qtpixmapbutton.h"
#include "qtdatetimeconfig.h"

class TimeConfigWidget : public QtWidgetBase
{
    Q_OBJECT
public:
    explicit TimeConfigWidget(QWidget *parent = 0);
~TimeConfigWidget();

signals:
    void signalChangePage(int index, int direction);

private slots:
    void SltBtnClicked(int index);

private:
    QtDateTimeConfig    *m_timeConfig;

private:
    void setSystemTime(bool bOk);

protected:
    void resizeEvent(QResizeEvent *e);
    void paintEvent(QPaintEvent *);
    void drawButton(QPainter *painter);
};

#endif // TIMECONFIGWIDGET_H
