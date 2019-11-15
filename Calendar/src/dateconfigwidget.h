/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : dateconfigwidget.h --- DateConfigWidget
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef DATECONFIGWIDGET_H
#define DATECONFIGWIDGET_H

#include "qtwidgetbase.h"
#include "qtpixmapbutton.h"
#include "qtdatetimeconfig.h"

class DateConfigWidget : public QtWidgetBase
{
    Q_OBJECT
public:
    explicit DateConfigWidget(QWidget *parent = 0);
    ~DateConfigWidget();

signals:
    void signalChangePage(int index, int direction);

private slots:
    void SltBtnClicked(int index);

private:
    QtPixmapButton  m_btnPrev;
    QtPixmapButton  m_btnSure;
    QtDateTimeConfig    *m_timeConfig;

private:
    void setSystemDate();

protected:
    void resizeEvent(QResizeEvent *e);
    void paintEvent(QPaintEvent *);
    void drawButton(QPainter *painter);
};


#endif // DATECONFIGWIDGET_H
