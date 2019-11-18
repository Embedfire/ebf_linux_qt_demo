/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : backlightwidget.h ---
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef BACKLIGHTWIDGET_H
#define BACKLIGHTWIDGET_H

#include "qtwidgetbase.h"
#include "qtknobswitch.h"

class BackLightWidget : public QtAnimationWidget
{
    Q_OBJECT
public:
    BackLightWidget(QWidget *parent = 0);
    ~BackLightWidget();

private:
    void InitWidget();
    void ReadBacklight();
private:
    QtKnobSwitch        *m_knobSwitch;
    int                  m_nLevel;
private slots:
    void SltValueChanged(int value);

protected:
    void resizeEvent(QResizeEvent *e);
};

#endif // BACKLIGHTWIDGET_H
