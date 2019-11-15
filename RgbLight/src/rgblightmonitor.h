/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : rgblightmonitor.h ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/8/31
*******************************************************************/
#ifndef RGBLIGHTMONITOR_H
#define RGBLIGHTMONITOR_H

#include "qtwidgetbase.h"
#include "qtpixmapbutton.h"
#include <QMap>


class LightObect {
public:

    LightObect(int id, QRect rect, int value, QString name) :
        m_nId(id),m_rect(rect),m_nValue(value),m_strText(name)
    {
    }

    int     m_nId;
    QRect   m_rect;
    int     m_nValue;
    QString m_strText;
};

class RgbLightMonitor : public QtAnimationWidget
{
    Q_OBJECT

public:
    RgbLightMonitor(QWidget *parent = 0);
    ~RgbLightMonitor();

private:
    int     m_nValue;
    int     m_nCurrentLight;

    QMap<int, LightObect *> m_lightObjs;
    QtPixmapButton  *m_btnHome;
    QRect   m_nRectHandle;
    QRect   m_nRectHome;

private:
    bool m_bPressed;

private:
    void ChangeRgbLightValue();
    void ReadRgbLightValues();

protected:
    void paintEvent(QPaintEvent *);
    void drawBackground(QPainter *painter);
    void drawValue(QPainter *painter);
    void drawSliderBar(QPainter *painter);
    void drawRgbLight(QPainter *painter, QRect rect);
    void drawBottomLight(QPainter *painter);

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
};

#endif // RGBLIGHTMONITOR_H
