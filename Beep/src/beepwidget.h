/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : beepwidget.h ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/28
*******************************************************************/
#ifndef BEEPWIDGET_H
#define BEEPWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPropertyAnimation>

#include "qtwidgetbase.h"
#include "qtpixmapbutton.h"

class BeepWidget : public QtAnimationWidget
{
    Q_OBJECT
    Q_PROPERTY(QRect switchRect READ switchRect WRITE setSwitchRect)
public:
    BeepWidget(QWidget *parent = 0);
    ~BeepWidget();

    QRect switchRect() const;
    void setSwitchRect(const QRect &value);

protected:
    QtPixmapButton      m_btnHome;
    QRect               m_rectHorn;

    int                 m_nIndex;
    QPixmap             m_pixmapHandle;
    QPixmap             m_pixmapHorn;

    QRect               m_rectLeftSwitch;
    bool                m_bLeftSwitch;

    QRect               m_rectRightSwitch;
    bool                m_bRightSwitch;

    int                 m_nSwitchIndex;

    QTimer              *m_timer;
    QPropertyAnimation  *m_animationMove;
    bool                m_bPwmBeep;
private:
    void InitDataRect();

    void CheckDevice();
    void setBeepState(int on);
    void StopTimer();

private slots:
    void SltLongPressed();

protected:
    void paintEvent(QPaintEvent *);

    void drawTitle(QPainter *painter);
    void drawSwitch(QPainter *painter, bool left = true);
    void drawHorn(QPainter *painter);

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // BEEPWIDGET_H
