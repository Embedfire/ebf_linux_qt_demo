/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : keypresswidget.h ---
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef KEYPRESSWIDGET_H
#define KEYPRESSWIDGET_H

#include "qtwidgetbase.h"
#include "qtpixmapbutton.h"

#include <QMap>

class KeyPressWidget : public QtAnimationWidget
{
    Q_OBJECT
    typedef enum {BtnHome, BtnUser, BtnOnOff, BtnKey, BtnLedR, BtnLedG, BtnLedB, BtnCount} E_BTNS;
public:
    KeyPressWidget(QWidget *parent = 0);
    ~KeyPressWidget();

public slots:
    void SltKeyPressed(const quint8 &type);

private:
    void InitButtons();

    void KeyPressed(int index);
    void ChangeRgbLightValue(QString led, bool on);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // KEYPRESSWIDGET_H
