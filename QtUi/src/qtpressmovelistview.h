/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : qtpressmovelistview.h --- QtPressMoveListView
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/21
*******************************************************************/
#ifndef QTPRESSMOVELISTVIEW_H
#define QTPRESSMOVELISTVIEW_H

#include <QWidget>
#include <QListView>
#include <QScrollBar>

#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT QtPressMoveListView : public QListView {
#else
class QtPressMoveListView : public QListView {
#endif
    Q_OBJECT
public:
    explicit QtPressMoveListView(QWidget *parent = 0);
    ~QtPressMoveListView();

    void SetIconMode();

private:
    bool m_bPressed;
    QPoint m_startPos;
    QScrollBar *m_scrollbar;
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
};

#endif // QTPRESSMOVELISTVIEW_H
