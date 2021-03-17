/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : qttextbroswer.cpp --- QtTextBroswer
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "qttextbroswer.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QTextOption>

QtTextBroswer::QtTextBroswer(QWidget *parent) : QWidget(parent)
{
    m_nOffset = 0;
    m_bPressed = false;

    m_colorText = QColor("#ffffff");
    m_strText = "";
    m_nTextHeight = 0;

    m_align = Qt::AlignLeft | Qt::AlignTop;
}

QtTextBroswer::~QtTextBroswer()
{

}

void QtTextBroswer::setAlignment(Qt::Alignment align)
{
    m_align = align;
    this->update();
}

void QtTextBroswer::setText(const QString &text)
{
    m_strText = text;
    QFontMetrics fm(this->font());
    m_nTextHeight = fm.boundingRect(this->rect(), Qt::TextWordWrap, m_strText).height();

    this->update();
}

QString QtTextBroswer::text() const
{
    return m_strText;
}

void QtTextBroswer::append(const QString &text)
{
    m_strText.append("\n");
    m_strText.append(text);
    setText(m_strText);
}

void QtTextBroswer::resizeEvent(QResizeEvent *e)
{
    setText(m_strText);
    QWidget::resizeEvent(e);
}

void QtTextBroswer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::TextAntialiasing);

    painter.setPen(m_colorText);
    painter.setFont(this->font());

    QTextOption option;
    option.setWrapMode(QTextOption::WordWrap);
    option.setAlignment(m_align);

    QRect rectText(0, m_nOffset, this->width(), m_nTextHeight);
    painter.drawText(rectText, m_strText, option);
}

void QtTextBroswer::mousePressEvent(QMouseEvent *e)
{
    m_bPressed = true;
    m_startPos = e->pos();
    QWidget::mousePressEvent(e);
}

void QtTextBroswer::mouseReleaseEvent(QMouseEvent *e)
{
    m_bPressed = false;
    m_startPos = e->pos();
    if (m_nOffset > 0) m_nOffset = 0;
    this->update();
    QWidget::mouseReleaseEvent(e);
}

void QtTextBroswer::mouseMoveEvent(QMouseEvent *e)
{
    int nOffset = e->y() - m_startPos.y();
    m_startPos = e->pos();
    moveStep(nOffset);
    QWidget::mouseMoveEvent(e);
}

void QtTextBroswer::wheelEvent(QWheelEvent *e)
{
    QPoint numDegrees = e->angleDelta() / 8;
    moveStep(numDegrees.y(), true);
    QWidget::wheelEvent(e);
}

void QtTextBroswer::moveStep(int offset, bool wheel)
{
    if ((!m_bPressed && !wheel) || (m_nOffset + offset) > 10) return;
    if (m_nTextHeight < (this->height())) return;
    if ((-(m_nOffset + offset) + this->height()) > m_nTextHeight) return;

    m_nOffset += offset;
    this->update();
}
