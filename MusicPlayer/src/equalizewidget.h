/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : equalizewidget.h --- EqualizeWidget
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/8/31
*******************************************************************/
#ifndef EQUALIZEWIDGET_H
#define EQUALIZEWIDGET_H

#include <QWidget>
#include "qtwidgetbase.h"
#include "qtsliderbar.h"

class QtEqualizeSliderBar : public QtSliderBar {
    Q_OBJECT
public:
    explicit QtEqualizeSliderBar(int id, QWidget *parent = 0);
    ~QtEqualizeSliderBar();

signals:
    void currentValueChanged(int id, int value);

public:
    int     m_nId;

private slots:
    void SltCurrentValueChanged(int value);
};


class EqualizeWidget : public QtAnimationWidget
{
    Q_OBJECT
public:
    explicit EqualizeWidget(QWidget *parent = 0);
    ~EqualizeWidget();

    void StartAutoMove(bool bShow, int width);
    int     m_nYPos;
signals:

public slots:

private:
   QtEqualizeSliderBar      *m_sliderBar[10];

private:
    void InitWidget();

private slots:
    void SltEqualizeClicked(int index, int value);

protected:
    QSize minimumSize() const;
    QSize sizeHint() const;
    void paintEvent(QPaintEvent *);
};

#endif // EQUALIZEWIDGET_H
