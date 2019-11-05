/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : backlightpage.h --- BackLightPage
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef BACKLIGHTPAGE_H
#define BACKLIGHTPAGE_H

#include <QWidget>
#include "qtknobswitch.h"

class BackLightPage : public QWidget
{
    Q_OBJECT
public:
    explicit BackLightPage(QWidget *parent = 0);
    ~BackLightPage();

signals:

public slots:

private:
    QtKnobSwitch *m_knobSwitch;
    int           m_nLevel;
private:
    void InitWidget();

private slots:
    void SltValueChanged(int value);
};

#endif // BACKLIGHTPAGE_H
