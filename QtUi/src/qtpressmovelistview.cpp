/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : qtpressmovelistview.cpp --- QtPressMoveListView
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/21
*******************************************************************/
#include "qtpressmovelistview.h"
#include <QMouseEvent>

QtPressMoveListView::QtPressMoveListView(QWidget *parent) : QListView(parent)
{
    m_bPressed = false;
    m_scrollbar = this->verticalScrollBar();
}

QtPressMoveListView::~QtPressMoveListView()
{

}

void QtPressMoveListView::SetIconMode()
{
    this->setDragEnabled(false);
    this->setViewMode(QListView::IconMode);
    this->setIconSize(QSize(60, 60));
    this->setGridSize(QSize(100, 100));
    this->setResizeMode(QListView::Adjust);
}

void QtPressMoveListView::mousePressEvent(QMouseEvent *e)
{
    m_bPressed = true;
    m_startPos = e->pos();
    QListView::mousePressEvent(e);
}

void QtPressMoveListView::mouseReleaseEvent(QMouseEvent *e)
{
    m_bPressed = false;
    m_startPos = e->pos();
    QListView::mouseReleaseEvent(e);
}

void QtPressMoveListView::mouseMoveEvent(QMouseEvent *e)
{
    if (m_bPressed) {
        int nOffset = m_startPos.y() - e->pos().y();
        int nValue = m_scrollbar->value();
        nValue += nOffset;
        if (nValue < 0) nValue = 0;
        m_scrollbar->setValue(nValue);
        m_startPos = e->pos();
    }

    QListView::mouseMoveEvent(e);
}

