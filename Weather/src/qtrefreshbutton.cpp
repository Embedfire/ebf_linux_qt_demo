/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : qtrefreshbutton.cpp --- QtRefreshButton
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "qtrefreshbutton.h"
#include <QPainter>

QtRefreshButton::QtRefreshButton(QWidget *parent) : QWidget(parent)
{
    m_rotate = 0;
    m_step = 0;

    m_timer = new QTimer(this);
    m_timer->setInterval(50);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(SltBeginToRefresh()));
}

QtRefreshButton::~QtRefreshButton()
{
    if (m_timer->isActive()) {
        m_timer->stop();
    }

    delete m_timer;
    m_timer = NULL;
}

void QtRefreshButton::SetPixmap(const QPixmap &pixmap)
{
    m_pixmap = pixmap;
    this->update();
}

void QtRefreshButton::Start(int interval)
{
    m_nInterval = interval;
    m_timer->start();
}

void QtRefreshButton::SltBeginToRefresh()
{
    m_rotate += 9;
    if (m_rotate >= 360) {
        m_rotate = 0;
    }

    m_step += 50;
    if (m_step >= m_nInterval) {
        m_rotate = 0;
        m_step = 0;
        m_timer->stop();
    }

    this->update();
}

QSize QtRefreshButton::sizeHint() const
{
    return QSize(30, 30);
}

void QtRefreshButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    if (m_pixmap.isNull()) {
        painter.fillRect(this->rect(), QColor("#fafafa"));
    } else {
        painter.save();
        int nX = (this->width() - m_pixmap.width()) / 2;
        int nY = (this->height() - m_pixmap.height()) / 2;
        painter.translate(nX + m_pixmap.width() / 2, nY + m_pixmap.height() / 2);
        painter.rotate(m_rotate);
        painter.translate(-(nX + m_pixmap.width() / 2), -(nY + m_pixmap.height() / 2));
        painter.drawPixmap(nX, nY, m_pixmap);
        painter.restore();
    }
}
