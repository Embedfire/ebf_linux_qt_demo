/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : qtplaytoolbar.h --- QtPlayToolBar
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/14
*******************************************************************/
#ifndef QTPLAYTOOLBAR_H
#define QTPLAYTOOLBAR_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>
#include "qtsliderbar.h"
#include "qttoolbar.h"

class PlayTitleBarWidget : public QtToolBar
{
    Q_OBJECT
public:
    explicit PlayTitleBarWidget(QWidget *parent = 0);
    ~PlayTitleBarWidget();

public slots:
    void SetText(const QString &text);

signals:
    void signalBack();

private:
    QString m_strText;
    QRect   m_rectBack;
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
};


class PlayerBarWidget : public QtToolBar
{
    Q_OBJECT
public:
    explicit PlayerBarWidget(QWidget *parent = 0);
    ~PlayerBarWidget();
    void setPlayState(bool bOk);
    void setPostion(int postion);
    void setDuration(int duration);

signals:
    void buttonClicked(int index);
    void signalPlay(bool bOk);
    void signalVolume();
    void currentPostionChanged(int postion);

    void signalNext();
    void signalPrev();

    void signalMuenList();

private:
    QtSliderBar *m_progressBar;

    QString             m_strCurrTime;
    QString             m_strDuration;
private:
    void InitWidget();

private slots:
    void SltBtnClicked(int index);

protected:
    void resizeEvent(QResizeEvent *e);
    void paintEvent(QPaintEvent *);
};

#endif // QTPLAYTOOLBAR_H
