/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : qtwidgetbase.h --- QtWidgetBase
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef QTWIDGETBASE_H
#define QTWIDGETBASE_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QMap>

#include "qtpixmapbutton.h"

#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT QtWidgetBase : public QWidget {
#else
class QtWidgetBase : public QWidget {
#endif
    Q_OBJECT
public:
    explicit QtWidgetBase(QWidget *parent = 0);
    ~QtWidgetBase();

    void addBtn(int index, QtPixmapButton *btn);
signals:
    void signalBackHome();
    void signalBtnClicked(int index);
public slots:

protected:
    bool m_bZoom;
    qreal m_scaleX;
    qreal m_scaleY;

    int   m_nBaseWidth;
    int   m_nBaseHeight;

    QMap<int,QtPixmapButton*> m_btns;
protected:
    void ScaleRect(QRect &rectRet, const QRect &rect);
    void SetScaleValue();

    void resizeEvent(QResizeEvent *e);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
};

////////////////////////////////////////////////////////////////////
// 专用标题栏
#ifdef QtUi
class QTUISHARED_EXPORT QtWidgetTitleBar : public QtWidgetBase {
#else
class QtWidgetTitleBar : public QtWidgetBase {
#endif
    Q_OBJECT
public:
    explicit QtWidgetTitleBar(QWidget *parent = 0);
    QtWidgetTitleBar(const QString &title, QWidget *parent  = 0);

    ~QtWidgetTitleBar();

    void SetBackground(const QColor &color);
    void SetBackground(const QPixmap &pixmap);

    QString title() const;
    void SetTitle(const QString &title);
    void SetTitle(const QString &title, const QColor &textClr, const int &fontSize = 18);

    void SetScalSize(int w, int h);
    void SetBtnHomePixmap(const QPixmap &normal, const QPixmap &pressed);
    void SetBtnVisible(bool bOk, int index = 0);

    void SetToolButtons(QMap<int, QtPixmapButton*> btns);
signals:

protected slots:
    virtual void SltBtnClicked(int index);

private:
    QPixmap     m_pixmapBackground;
    QColor      m_colorBackground;
    QColor      m_colorText;

    QString     m_strTitle;
    int         m_nFontSize;

    QtPixmapButton  *m_btnHome;

protected:
    void paintEvent(QPaintEvent *);
};

////////////////////////////////////////////////////////////////
// 属性动画移动widget
#ifdef QtUi
class QTUISHARED_EXPORT QtAnimationWidget : public QtWidgetBase {
#else
class QtAnimationWidget : public QtWidgetBase {
#endif
    Q_OBJECT
public:
    explicit QtAnimationWidget(QWidget *parent = 0);
    QtAnimationWidget(QEasingCurve curve,  QWidget *parent = 0);
    ~QtAnimationWidget();

    void StartAnimation(const QPoint &startPos, const QPoint &endPos,
                        int duration, bool bShow = true);

    void SetAnimationCurve(QEasingCurve curve);
    void SetBackground(const QPixmap &pixmap);
    void SetBackground(const QColor &color);

signals:
    void signalAnimationFinished();

protected:
    bool m_bShow;
    QPropertyAnimation  *m_animation;
    QPixmap              m_pixmapBackground;
    QColor               m_colorBackground;

protected slots:
    virtual void SltAnimationFinished();

protected:
    void paintEvent(QPaintEvent *);
};

#endif // QTWIDGETBASE_H
