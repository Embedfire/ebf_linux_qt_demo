/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : qtpalettewidget.h --- QtPaletteWidget
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/13
*******************************************************************/
#ifndef QTPALETTEWIDGET_H
#define QTPALETTEWIDGET_H

#include <QWidget>
#include <QMap>
#include "qtwidgetbase.h"

class ColorRole {
public:
    ColorRole(int id, QColor color, QRect rect) :
        m_nId(id),m_color(color),m_rect(rect)
    {

    }

    int     m_nId;
    QColor  m_color;
    QRect   m_rect;
};

#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT QtPaletteWidget : public QtAnimationWidget {
#else
class QtPaletteWidget : public QtAnimationWidget {
#endif
    Q_OBJECT
public:
    explicit QtPaletteWidget(QWidget *parent = 0);
    ~QtPaletteWidget();

signals:
    void signalFontChanged(int size);
    void signalColorChanged(const QColor &color);

public slots:

private:
    int m_nFontSize;
    QStringList m_strColors;
    QRect m_rectAdd;
    QRect m_rectMinus;
    QRect m_rectOther;

    QMap<int, ColorRole> m_colorRects;
    int m_nIndex;
    QColor m_currentColor;
    bool   m_bColorPanel;

    QPixmap m_colorPanel;
    QRect   m_rectPanel;
    QPoint  m_selectPos;

private:
    void CreatePanel(QRect rect);
    void ColorPanelClicked(QPoint pos);
    void InitValues();

protected:
    void paintEvent(QPaintEvent *);

    void drawFontConfig(QPainter *painter);
    void drawColorBoard(QPainter *painter);

    void mousePressEvent(QMouseEvent *e);

};

#endif // QTPALETTEWIDGET_H
