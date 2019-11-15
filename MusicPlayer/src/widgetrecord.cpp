/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : widgetrecord.cpp --- WidgetRecord
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "widgetrecord.h"

#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

WidgetRecord::WidgetRecord(QWidget *parent) : QtWidgetBase(parent)
{
    m_nRotateCD = 0;
    m_nRotateHandle = 0;
    m_bPlay = false;

    m_nBaseWidth = 400;
    m_nBaseHeight = 350;

    m_handlePixmap = new PixmapItem(QPixmap(":/images/music/ic_handle.png"), this);
    m_pixmapRecord = QPixmap(":/images/music/ic_blackrecord.png");
    m_pixmapArtist = QPixmap(":/images/music/ic_cd.png");

    m_timer = new QTimer(this);
    m_timer->setInterval(100);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(SltCicleRun()));

    m_animationHandle = new QPropertyAnimation(m_handlePixmap, "ratote");
    m_animationHandle->setDuration(300);
    m_animationHandle->setEasingCurve(QEasingCurve::Linear);
    connect(m_animationHandle, SIGNAL(valueChanged(QVariant)), this, SLOT(SltHandleMove(QVariant)));
}

WidgetRecord::~WidgetRecord()
{

}

void WidgetRecord::SetImage(const QImage &image)
{
    if (image.isNull()) {
        m_pixmapArtist = QPixmap(":/images/music/ic_cd.png");
    } else {
        m_pixmapArtist = QPixmap::fromImage(image);
        m_pixmapArtist = m_pixmapArtist.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    this->update();
}

void WidgetRecord::Start()
{
    m_bPlay = true;
    m_timer->start();

    m_animationHandle->setStartValue(0);
    m_animationHandle->setEndValue(30);
    m_animationHandle->start();
    this->update();
}

void WidgetRecord::Stop()
{
    m_bPlay = false;
    m_timer->stop();
    m_animationHandle->setStartValue(30);
    m_animationHandle->setEndValue(0);
    m_animationHandle->start();
    this->update();
}

void WidgetRecord::SltCicleRun()
{
    m_nRotateCD += 1;
    if (m_nRotateCD >= 360) {
        m_nRotateCD = 0;
    }
    this->update();
}

void WidgetRecord::SltHandleMove(const QVariant &/*rotate*/)
{
    this->update();
}

void WidgetRecord::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
    painter.scale(m_scaleX, m_scaleY);

    int nX = m_nBaseWidth / 2;
    int nY = m_nBaseHeight - m_pixmapRecord.height() / 2  - m_handlePixmap->pixmap().height() / 2 ;

    painter.save();
    painter.translate(nX, nY);
    painter.rotate(m_nRotateCD);
    painter.translate(-nX, -nY);

    painter.drawPixmap(nX - m_pixmapArtist.width() / 2, nY - m_pixmapArtist.height() / 2 + 5, m_pixmapArtist.scaled(200, 200));
    painter.drawPixmap(nX - m_pixmapRecord.width() / 2, nY - m_pixmapRecord.height() / 2 + 5, m_pixmapRecord);
    painter.restore();

    painter.save();
    nY = nY - m_pixmapRecord.height() / 2 - m_handlePixmap->pixmap().height() / 2;
    painter.translate(m_nBaseWidth / 2, nY);
    painter.rotate(m_handlePixmap->ratote());
    painter.translate(-m_nBaseWidth / 2, -nY);
    painter.drawPixmap(m_nBaseWidth / 2, nY, m_handlePixmap->pixmap());
    painter.restore();
}
