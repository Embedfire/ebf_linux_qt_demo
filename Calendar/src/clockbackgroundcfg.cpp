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
#include "skin.h"

#include <QDebug>
#include <QPaintEvent>
#include <QPainter>

ClockBackgroundCfg::ClockBackgroundCfg(QWidget *parent) : QtWidgetBase(parent)
{
    m_nBaseWidth = Skin::m_nScreenWidth;
    m_nBaseHeight = 400;

    m_nIndex = 0;
    m_pixmaps.append(QPixmap(":/images/calendar/clock_00_background.png"));
    m_pixmaps.append(QPixmap(":/images/calendar/clock_01_background.png"));
    m_pixmaps.append(QPixmap(":/images/calendar/clock_02_background.png"));
    m_pixmapSelected = QPixmap(":/images/calendar/blue_glow.png");

    m_rects.append(QRect(-4, 8, 272, 272));
    m_rects.append(QRect(264, 8, 272, 272));
    m_rects.append(QRect(532, 8, 272, 272));

    m_btnSure = QtPixmapButton(QPixmap(":/images/calendar/ic_btn.png"), QPixmap(":/images/calendar/ic_btn_pre.png"));
    m_btnSure.setRect(QRect(317, 308, 166, 70));

    m_btnNext = QtPixmapButton(QPixmap(":/images/calendar/ic_btn.png"), QPixmap(":/images/calendar/ic_btn_pre.png"));
    m_btnNext.setRect(QRect(565, 308, 166, 70));
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

void ClockBackgroundCfg::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.scale(m_scaleX, m_scaleY);

    for (int i = 0; i < m_pixmaps.size(); i++) {
        QPixmap pixmap = m_pixmaps.at(i);
        QRect rect = m_rects.at(i);
        painter.drawPixmap(rect.center().x() - pixmap.width() / 2, rect.center().y() - pixmap.height() / 2, pixmap);
    }

    // 绘制选择框
    QRect rect((m_nIndex + 1) * -4 + m_pixmapSelected.width() * m_nIndex, 0, m_pixmapSelected.width(), m_pixmapSelected.height());
    painter.drawPixmap(rect, m_pixmapSelected);

    // 绘制底部确定按钮
    drawButton(&painter);
}

void ClockBackgroundCfg::drawButton(QPainter *painter)
{
    painter->save();
    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(30);
    painter->setFont(font);
    painter->setPen(QColor("#ffffff"));
    painter->drawPixmap(m_btnSure.rect(), m_btnSure.pixmap());
    painter->drawText(m_btnSure.rect(), Qt::AlignCenter, tr("完成"));

    painter->drawPixmap(m_btnNext.rect(), m_btnNext.pixmap());
    painter->drawText(m_btnNext.rect(), Qt::AlignCenter, tr("下一步"));
    painter->restore();
}

void ClockBackgroundCfg::mousePressEvent(QMouseEvent *e)
{
    QRect rect;
    ScaleRect(rect, m_btnSure.rect());
    if (rect.contains(e->pos())) {
        m_btnSure.setPressed(true);
        this->update();
        return;
    }

    ScaleRect(rect, m_btnNext.rect());
    if (rect.contains(e->pos())) {
        m_btnNext.setPressed(true);
        this->update();
        return;
    }

    for (int i = 0; i < m_rects.size(); i++) {
        ScaleRect(rect, m_rects.at(i));
        if (rect.contains(e->pos())) {
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
        emit signalChangePage(0, 2);
    }

    if (m_btnNext.isPressed()) {
        m_btnNext.setPressed(false);
        this->update();
        emit signalChangePage(3, 1);
    }

    QWidget::mouseReleaseEvent(e);
}

