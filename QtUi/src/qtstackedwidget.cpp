/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : qtstackedwidget.cpp --- QtStackedWidget
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "qtstackedwidget.h"

#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

QtStackedWidget::QtStackedWidget(QWidget *parent) : QWidget(parent)
{
    m_bPressed = false;
    m_startPos = QPoint(0, 0);
    m_nCurrentIndex = 0;
    m_nNextIndex = -1;
    m_nStartPos = 0;
    m_nEndPos = 0;
    m_nDirection = None;
    m_bRecovery = false;
    m_bPressMove = true;
    m_colorBackground = QColor("#ffffff");
    m_nResize = -1;

    m_animation = new QPropertyAnimation(this, "xPos");
    m_animation->setEasingCurve(QEasingCurve::Linear);
    m_animation->setDuration(200);
}

QtStackedWidget::~QtStackedWidget()
{
    foreach (QWidget *widget, m_children) {
        if (NULL != widget) {
            delete widget;
            widget = NULL;
        }
    }
}

QWidget *QtStackedWidget::currentWidget()
{
    return m_children.value(m_nCurrentIndex);
}

void QtStackedWidget::resizeEvent(QResizeEvent *e)
{
    foreach (QWidget *widget, m_children) {
        widget->setFixedSize(e->size());
        widget->move(0, 0);
    }
    QWidget::resizeEvent(e);
}

void QtStackedWidget::addWidget(int index, QWidget *widget)
{
    if (NULL == widget) return;
    widget->setGeometry(0, 0, this->width(), this->height());
    widget->setVisible(index == m_nCurrentIndex);
    m_children.insert(index, widget);
}

void QtStackedWidget::setCurrentIndex(int index)
{
    if (index < m_children.size() && index >= 0 && index != m_nCurrentIndex) {
        m_nCurrentIndex = index;
        foreach (QWidget *widget, m_children) {
            widget->setVisible(false);
        }
        m_children.value(index)->setVisible(true);
        m_children.value(index)->move(0, 0);
        emit currentChanged(index);
    }
}

void QtStackedWidget::setCurrentIndex(int index, int direction, int nResize)
{
    if (index < m_children.size() && index >= 0 && index != m_nCurrentIndex) {
        m_nNextIndex = index;
        m_nDirection = direction;
        m_nResize = nResize;
        foreach (QWidget *widget, m_children) {
            widget->setVisible(false);
        }

        m_children.value(m_nCurrentIndex)->setVisible(true);
        m_children.value(index)->setVisible(true);
        m_animation->setStartValue(0);

        if (LeftDirection == m_nDirection) {
            m_nEndPos = -this->width();
        } else if (UpDirection == m_nDirection) {
            m_nEndPos = -this->height();
        } else if (RightDirection == m_nDirection) {
            m_nEndPos = this->width();
        } else if (DownDirection == m_nDirection) {
            m_nEndPos = this->height();
        }

        m_animation->setEndValue(m_nEndPos);
        m_animation->start();

//        emit currentChanged(index);
    }
}

void QtStackedWidget::SetBackground(QColor color)
{
    if (!color.isValid()) return;
    m_colorBackground = color;
    this->update();
}

void QtStackedWidget::setPressMove(bool bok)
{
    m_bPressMove = bok;
}

void QtStackedWidget::setXPos(int nValue)
{
    m_nStartPos = nValue;
    if (LeftDirection == m_nDirection) {
        m_children.value(m_nCurrentIndex)->move(nValue, 0);
        if (-1 != m_nNextIndex) m_children.value(m_nNextIndex)->move(nValue + this->width(), 0);
    } else if (RightDirection == m_nDirection) {
        m_children.value(m_nCurrentIndex)->move(nValue, 0);
        if (-1 != m_nNextIndex) m_children.value(m_nNextIndex)->move(nValue - this->width(), 0);
    }
    else if (DownDirection == m_nDirection) {
        m_children.value(m_nCurrentIndex)->move(0, nValue);
        if (-1 != m_nNextIndex) m_children.value(m_nNextIndex)->move(0, nValue - this->height());
    }
    else if (UpDirection == m_nDirection) {
        m_children.value(m_nCurrentIndex)->move(0, nValue);
        if (-1 != m_nNextIndex) m_children.value(m_nNextIndex)->move(0, nValue + this->height());
    }

    // 判断是否移动完整
    if (m_nEndPos == nValue) {
        foreach (QWidget *widget, m_children) {
            widget->setVisible(false);
        }
        m_nCurrentIndex = m_bRecovery ? m_nCurrentIndex : (-1 == m_nNextIndex ? 0 : m_nNextIndex);
        m_children.value(m_nCurrentIndex)->setVisible(true);

        if (-1 != m_nResize) this->resize(this->width(), m_nResize);
        m_children.value(m_nCurrentIndex)->move(0, 0);
        m_nNextIndex = -1;
        m_nDirection = None;
        m_nStartPos = 0;
        m_bRecovery = false;

        emit currentChanged(m_nCurrentIndex);
    }
}

void QtStackedWidget::setNextPage(int direction)
{
    if (m_nCurrentIndex < (m_children.size() - 1)) {
        m_nDirection = direction;
        m_nNextIndex = m_nCurrentIndex + 1;
        m_children.value(m_nNextIndex)->setVisible(true);
        m_animation->setStartValue(0);

        if (LeftDirection == m_nDirection) {
            m_nEndPos = -this->width();
        }
        else if (UpDirection == direction) {
            m_nEndPos = -this->height();
        }

        m_animation->setEndValue(m_nEndPos);
        m_animation->start();
    }
}

void QtStackedWidget::setPrevPage(int direction)
{
    if (m_nCurrentIndex > 0) {
        m_nDirection = direction;
        m_nNextIndex = m_nCurrentIndex - 1;
        m_children.value(m_nNextIndex)->setVisible(true);
        m_animation->setStartValue(0);

        if (RightDirection == m_nDirection) {
            m_nEndPos = this->width();
        }
        else if (DownDirection == m_nDirection) {
            m_nEndPos = this->height();
        }

        m_animation->setEndValue(m_nEndPos);
        m_animation->start();
    }
}

void QtStackedWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), m_colorBackground);
}

void QtStackedWidget::mousePressEvent(QMouseEvent *e)
{
    if (m_bPressMove) {
        if (m_children.size() < 2) return;
        m_bPressed = true;
        m_startPos = e->pos();
    }

    QWidget::mousePressEvent(e);
}

void QtStackedWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (m_bPressMove) {
        m_bPressed = false;
        if (None == m_nDirection) return;
        m_animation->setStartValue(m_nStartPos);
        m_bRecovery = (qAbs(m_nStartPos) < this->width() * 0.1);

        if (LeftDirection == m_nDirection) {
            m_nEndPos = m_bRecovery  ? 0 : -this->width();
        }
        else if (RightDirection == m_nDirection) {
            m_nEndPos = m_bRecovery  ? 0 : this->width();
        }

        m_animation->setEndValue(m_nEndPos);
        m_animation->start();
    }

    QWidget::mouseReleaseEvent(e);
}

void QtStackedWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (!m_bPressed || !m_bPressMove){
        QWidget::mouseReleaseEvent(e);
        return;
    }

    m_nNextIndex = -1;

    int nXoffset = e->pos().x() - m_startPos.x();
    // 向左滑动--显示下一页
    m_nDirection = (nXoffset < 0) ? LeftDirection : RightDirection;
    m_nStartPos += nXoffset;
    // 左边边缘检测
    if (RightDirection == m_nDirection && 0 == m_nCurrentIndex && qAbs(m_nStartPos) > this->width() * 0.1) {
        m_nStartPos -= nXoffset;
        return;
    }

    // 到右边边缘了
    if (LeftDirection == m_nDirection && ((m_children.size() - 1) == m_nCurrentIndex)
            && qAbs(m_nStartPos) > this->width() * 0.1) {
        m_nStartPos -= nXoffset;
        return;
    }

    m_children.value(m_nCurrentIndex)->move(m_nStartPos, 0);
    if (m_children.value(m_nCurrentIndex)->x() < 0) {
        if ((m_nCurrentIndex < (m_children.size() - 1))) {
            m_nNextIndex = m_nCurrentIndex + 1;
            m_children.value(m_nNextIndex)->setVisible(true);
            m_children.value(m_nNextIndex)->move(this->width() + m_nStartPos + 1, 0);
        }
    } else if (m_nCurrentIndex > 0) {
        m_nNextIndex = m_nCurrentIndex - 1;
        m_children.value(m_nNextIndex)->setVisible(true);
        m_children.value(m_nNextIndex)->move(m_nStartPos - 1 - this->width(), 0);
    }
    m_startPos = e->pos();

    QWidget::mouseMoveEvent(e);
}
