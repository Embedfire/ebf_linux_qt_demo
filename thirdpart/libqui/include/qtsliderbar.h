/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : qtsliderbar.h --- QtSliderBar
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/8/30
*******************************************************************/
#ifndef QTSLIDERBAR_H
#define QTSLIDERBAR_H

#include <QWidget>

#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT QtSliderBar : public QWidget {
#else
class QtSliderBar : public QWidget {
#endif
    Q_OBJECT
public:
    explicit QtSliderBar(QWidget *parent = 0);
    ~QtSliderBar();

    typedef enum {Horizontal,Vertical} Direction;

    void SetHorizontal(bool bOk);
    void SetSliderSize(int sliderSize, int handleSize);

    void SetMaxValue(int value);
    void SetValue(int value);
    int value() {return m_nCurrentValue;}

    void SetReadOnly(bool bOk);

    void ShowHandleBackground(bool bOk);
    void SetSlidetColor(const QColor &color);
    void SetHandleColor(const QColor &color);
    void SetHandleBgColor(const QColor &color);
signals:
    void currentValueChanged(int value);

private:
    int     m_nDirection;
    int     m_nCurrentValue;
    int     m_nMaxValue;

    int     m_nSliderSize;
    int     m_nHandleSize;

    bool    m_bPressed;
    QPoint  m_starPos;
    int     m_nOffset;

    bool    m_bReadOnly;

    QColor  m_colorSlider;
    QColor  m_colorHandle;
    QColor  m_colorHandleBg;
    bool    m_bShowHandleBg;
protected:
    void paintEvent(QPaintEvent *);
    void drawHorizontalBar(QPainter *painter);
    void drawVerticalBar(QPainter *painter);

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
};
#endif // QTSLIDERBAR_H
