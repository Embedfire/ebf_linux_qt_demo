/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : adcviewer.h ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/1
*******************************************************************/
#ifndef ADCVIEWER_H
#define ADCVIEWER_H

#include "qtwidgetbase.h"

#include <QBoxLayout>
#include <QLabel>
#include <QTimer>

class CircularProgressBar;

class AdcViewer : public QtAnimationWidget
{
    Q_OBJECT

public:
    AdcViewer(QWidget *parent = 0);
    ~AdcViewer();

private:
    CircularProgressBar     *m_adcValueDisplay;
    QLabel                  *m_labelAdcValue;
    QTimer *m_timer;

    QVBoxLayout             *m_verLayoutAll;
private:
    void InitWidget();

private slots:
    void SltAdcValueChanged(int value);
    void SltTestValue();

protected:
    void resizeEvent(QResizeEvent *e);
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);
};

#endif // ADCVIEWER_H
