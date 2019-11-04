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

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "qtsliderbar.h"

class QtVolumeSlider : public QtSliderBar {
    Q_OBJECT
public:
    explicit QtVolumeSlider(QWidget *parent = 0);
    ~QtVolumeSlider();

signals:

private:

protected:
    void showEvent(QShowEvent *e);
    void focusOutEvent(QFocusEvent *e);
};

///////////////////////////////////////////////////////////////////
/// \brief The WidgetToolBar class
///
class WidgetToolBar : public QWidget
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

    QPushButton     *m_btnPlay;
    QtSliderBar     *m_progressBar;
    QLabel          *m_labelCurrTime;
    QLabel          *m_labelDuraTime;
private:
    void InitProperty();

    QTime GetTimeByPostion(int postion);
private slots:
    void SltBtnPlayClicked();

protected:
    void paintEvent(QPaintEvent *);
};
#endif // WIDGETTOOLBAR_H
