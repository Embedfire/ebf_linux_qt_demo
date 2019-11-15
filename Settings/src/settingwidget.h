/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : settingwidget.h ---
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QPushButton>

#include "qtwidgetbase.h"
#include "qtstackedwidget.h"

class SettingWidget : public QtAnimationWidget
{
    Q_OBJECT

public:
    SettingWidget(QWidget *parent = 0);
    ~SettingWidget();

signals:
    void signalChangeCursorShape(Qt::CursorShape);

private:
    QtWidgetTitleBar    *m_widgetTitle;
    QStringList          m_strListTitle;

    QtPixmapButton       *m_btnBack;

    QtStackedWidget     *m_stackedWidget;
    QList <int>          m_pageStack;

private:
    void InitWidget();
    void InitSettingPage();

private slots:
    void SltToolBtnClicked(int index);
    void SltBtnBackClicked();
    void SltCurrentPageChanged(int index);
    void SltChangePage(int index);

protected:

};

#endif // SETTINGWIDGET_H
