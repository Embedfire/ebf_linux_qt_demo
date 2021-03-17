/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : qtstackedwidget.h --- QtStackedWidget
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef QTSTACKEDWIDGET_H
#define QTSTACKEDWIDGET_H

#include <QWidget>
#include <QMap>
#include <QPropertyAnimation>

#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT QtStackedWidget : public QWidget {
#else
class QtStackedWidget : public QWidget {
#endif
    Q_OBJECT
public:
    typedef enum {None, LeftDirection, RightDirection, UpDirection, DownDirection} MoveDirection;
    Q_PROPERTY(int xPos READ Xpos WRITE setXPos)

    explicit QtStackedWidget(QWidget *parent = 0);
    ~QtStackedWidget();

    QWidget *currentWidget();

    void addWidget(int index, QWidget *widget);
    int  currentIndex() {return m_nCurrentIndex;}

    void SetBackground(QColor color);
    void setPressMove(bool bok);
private:
    void setXPos(int nValue);
    int Xpos(){return m_nStartPos;}

signals:
    void currentChanged(int index);

public slots:
    void setNextPage(int direction = LeftDirection);
    void setPrevPage(int direction = RightDirection);
    void setCurrentIndex(int index);
    void setCurrentIndex(int index, int direction, int nResize = -1);

private:
    bool    m_bPressMove;
    bool    m_bPressed;
    QPoint  m_startPos;

    QMap<int, QWidget*> m_children;
    int     m_nCurrentIndex;
    int     m_nNextIndex;

    int     m_nStartPos;
    int     m_nEndPos;
    int     m_nDirection;

    QPropertyAnimation *m_animation;
    bool    m_bRecovery;

    QColor  m_colorBackground;
    int     m_nResize;

protected:
    void resizeEvent(QResizeEvent *e);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
};

#endif // QTSTACKEDWIDGET_H
