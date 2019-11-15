/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : widgettoolbar.h --- WidgetToolBar
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef WIDGETTOOLBAR_H
#define WIDGETTOOLBAR_H

#include "qtwidgetbase.h"
#include "qtsliderbar.h"

///////////////////////////////////////////////////////////////////
/// \brief The WidgetToolBar class
///
class WidgetToolBar : public QtWidgetBase
{
    Q_OBJECT
public:
    explicit WidgetToolBar(QWidget *parent = 0);
    ~WidgetToolBar();

    void UpdateDurationInfo(int postion);
    void SetDuration(int duration);

    void SetPlayState(bool state);
signals:
    void play();
    void stop();
    void pause();
    void next();
    void previous();

    void currentMuteChanged(int value);
    void toolBarClicked(int index);
    void currentPostionChanged(int postiion);

private:
    void InitWidget();

    int     m_nMaxValue;
    int     m_nCurrentValue;

    bool    m_bPlaying;

    QtSliderBar              *m_progressBar;
    QString             m_strCurrTime;
    QString             m_strDuration;
private:
    void InitProperty();

    QTime GetTimeByPostion(int postion);
private slots:
    void SltBtnPlayClicked();
    void SltBtnClicket(int index);

protected:
    void resizeEvent(QResizeEvent *e);
    void paintEvent(QPaintEvent *);
};
#endif // WIDGETTOOLBAR_H
