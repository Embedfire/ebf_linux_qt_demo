/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : clockbackgroundcfg.cpp --- ClockBackgroundCfg
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "clockbackgroundcfg.h"

#include <QDebug>
#include <QPaintEvent>
#include <QPainter>

ClockBackgroundCfg::ClockBackgroundCfg(QWidget *parent) : QWidget(parent)
{
    m_nIndex = 0;
    m_pixmaps.append(QPixmap(":/images/calendar/clock_00_background.png"));
    m_pixmaps.append(QPixmap(":/images/calendar/clock_01_background.png"));
    m_pixmaps.append(QPixmap(":/images/calendar/clock_02_background.png"));
    m_pixmapSelected = QPixmap(":/images/calendar/blue_glow.png");

    m_btnSure = QtPixmapButton(QPixmap(":/images/calendar/ic_btn.png"), QPixmap(":/images/calendar/ic_btn_pre.png"));
    m_btnNext = QtPixmapButton(QPixmap(":/images/calendar/ic_btn.png"), QPixmap(":/images/calendar/ic_btn_pre.png"));
}

ClockBackgroundCfg::~ClockBackgroundCfg()
{

}

void ClockBackgroundCfg::setIndexStyle(const int &style)
{
    if (style > 2) return;
    m_nIndex = style;
    this->update();
}

void ClockBackgroundCfg::resizeEvent(QResizeEvent *e)
{
    m_rects.clear();

    int nXOffset = (this->width() - m_pixmapSelected.width() * m_pixmaps.size()) / 4;
    int nYOffset = (this->height() * 0.69 - m_pixmapSelected.height()) / 2 + 6;

    for (int i = 0; i < m_pixmaps.size(); i++) {
        QRect rect((i + 1) * nXOffset + m_pixmapSelected.width() * i, nYOffset, m_pixmapSelected.width(), m_pixmapSelected.height());
        m_rects.append(rect);
    }

    int nW = m_btnSure.size().width();
    int nH = m_btnSure.size().height();
    QRect rect(this->width() / 2 - nW / 2,
               this->height() * 0.86 - nH / 2,
               nW, nH);
    m_btnSure.setRect(rect);

    rect = QRect(rect.right() + nW / 2, rect.top(), rect.width(), rect.height());
    m_btnNext.setRect(rect);
    QWidget::resizeEvent(e);
}

void ClockBackgroundCfg::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    int nXOffset = (this->width() - m_pixmapSelected.width() * m_pixmaps.size()) / 4;
    for (int i = 0; i < m_pixmaps.size(); i++) {
        QPixmap pixmap = m_pixmaps.at(i);
        QRect rect = m_rects.at(i);
        painter.drawPixmap(rect.center().x() - pixmap.width() / 2, rect.center().y() - pixmap.height() / 2, pixmap);
    }

    // 绘制选择框
    int nYOffset = (this->height() * 0.69 - m_pixmapSelected.height()) / 2;
    QRect rect((m_nIndex + 1) * nXOffset + m_pixmapSelected.width() * m_nIndex, nYOffset, m_pixmapSelected.width(), m_pixmapSelected.height());
    painter.drawPixmap(rect, m_pixmapSelected);

    // 绘制底部确定按钮
    drawButton(&painter);
}

void ClockBackgroundCfg::drawButton(QPainter *painter)
{
    painter->save();
    QFont font(this->font());
    font.setPixelSize(30);
    painter->setFont(font);
    painter->setPen(QColor("#ffffff"));
    painter->drawPixmap(m_btnSure.rect(), m_btnSure.pixmap());
    painter->drawText(m_btnSure.rect(), Qt::AlignCenter, QString("完成"));

    painter->drawPixmap(m_btnNext.rect(), m_btnNext.pixmap());
    painter->drawText(m_btnNext.rect(), Qt::AlignCenter, QString("下一步"));
    painter->restore();
}

QSize ClockBackgroundCfg::sizeHint() const
{
    return QSize(800, 390);
}

void ClockBackgroundCfg::mousePressEvent(QMouseEvent *e)
{
    if (m_btnSure.rect().contains(e->pos())) {
        m_btnSure.setPressed(true);
        this->update();
        return;
    }

    if (m_btnNext.rect().contains(e->pos())) {
        m_btnNext.setPressed(true);
        this->update();
        return;
    }

    for (int i = 0; i < m_rects.size(); i++) {
        if (m_rects.at(i).contains(e->pos())) {
            if (m_nIndex != i) {
                m_nIndex = i;
                emit signalBackground(m_nIndex);
                this->update();
            }
            break;
        }
    }
}

void ClockBackgroundCfg::mouseReleaseEvent(QMouseEvent *e)
{
    if (m_btnSure.isPressed()) {
        m_btnSure.setPressed(false);
        this->update();
        if (m_btnSure.rect().contains(e->pos())) {
            emit signalChangePage(0, 2);
        }
    }

    if (m_btnNext.isPressed()) {
        m_btnNext.setPressed(false);
        this->update();
        if (m_btnNext.rect().contains(e->pos())) {
            emit signalChangePage(3, 1);
        }
    }
}

