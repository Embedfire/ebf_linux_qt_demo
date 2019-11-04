/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : launcherwidget.cpp --- LauncherWidget
 作 者    : Niyh(lynnhua)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "launcherwidget.h"

#include <QtMath>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

#define ITEM_SPACE          20
#define SPOT_WIDTH          10
#define MOVE_STEP           20
#define ICON_SIZE           80

LauncherItem::LauncherItem(int id, int index, const QString &name, const QPixmap &icon)
{
    m_nAppId = id;
    m_nPageIndex = index;
    m_strAppName = name;
    m_pixmapIcon = icon;
}

////////////////////////////////////////////////////////////////////////////////
/// \brief LauncherWidget::LauncherWidget
/// \param parent
LauncherWidget::LauncherWidget(QWidget *parent) : QWidget(parent)
{
    m_pixmapWallpaper = QPixmap();
    m_backgroundColor = QColor("#c6c6c6");

    m_nPageCnt = 3;
    m_nCurrentPage = 0;
    m_nPrevPage = -1;
    m_nCurrentIndex = -1;
    m_nLayoutRows = 3;
    m_nLayoutColumns = 4;

    m_nDirection = None;
    m_bLoopbackChange = false;
    m_bRecovery = false;

    m_bPressed = false;
    m_startPos = QPoint(0, 0);
    m_nStartPos = 0;
    m_nMoveEndValue = 0;

    m_animation = new QPropertyAnimation(this, "xPos");
    m_animation->setDuration(200);
    //    this->setMouseTracking(true);
}

LauncherWidget::~LauncherWidget()
{

}

void LauncherWidget::AddItem(int id, LauncherItem *item)
{
    m_itemApps.insert(id, item);
    this->update();
}

void LauncherWidget::SetItems(QMap<int, LauncherItem *> items)
{
    m_itemApps.clear();
    m_itemApps = items;
    this->update();
}

void LauncherWidget::SetWallpaper(const QPixmap &pixmap)
{
    if (pixmap.isNull()) return;
    this->m_pixmapWallpaper = pixmap;
    this->update();
}

void LauncherWidget::SetWallpaper(const QColor &color)
{
    if (!color.isValid()) return;
    this->m_backgroundColor = color;
    this->update();
}

void LauncherWidget::SetPageCount(int count)
{
    if (count < 1) return;
    this->m_nPageCnt = count;
    m_rectPageSpot.clear();
    int nStartX = (this->width() - SPOT_WIDTH * (m_nPageCnt * 2 - 1)) / 2;
    for (int i = 0; i < m_nPageCnt; i++) {
        QRect rect(nStartX + i * 2 * SPOT_WIDTH, this->height() - SPOT_WIDTH * 2, SPOT_WIDTH, SPOT_WIDTH);
        m_rectPageSpot.insert(i, rect);
    }
    this->update();
}

void LauncherWidget::SetItemLayut(int rows, int columns)
{
    if (0 == rows || 0 == columns) return;

    this->m_nLayoutRows = rows;
    this->m_nLayoutColumns = columns;
    this->update();
}

void LauncherWidget::SetLoopbackChange(bool bOk)
{
    this->m_bLoopbackChange = bOk;
}

void LauncherWidget::SltShowNextPage()
{
    if (m_nCurrentPage < (m_nPageCnt - 1)) {
        m_nDirection = LeftDirection;
        m_nMoveEndValue = -this->width();
        m_animation->setStartValue(0);
        m_animation->setEndValue(m_nMoveEndValue);
        m_animation->start();
    }
}

void LauncherWidget::SltShowPrevPage()
{
    if (m_nCurrentPage > 0) {
        m_nDirection = RightDirection;
        m_nMoveEndValue = this->width();
        m_animation->setStartValue(0);
        m_animation->setEndValue(m_nMoveEndValue);
        m_animation->start();
    }
}

void LauncherWidget::setXPos(int nValue)
{
    m_nStartPos = nValue;
    if (m_nStartPos == m_nMoveEndValue) {
        if (!m_bRecovery && LeftDirection == m_nDirection)  {
            m_nCurrentPage = m_nCurrentPage + 1;
            if (m_nCurrentPage >= m_nPageCnt) m_nCurrentPage = m_nPageCnt - 1;
            emit currentPageChanged(m_nCurrentPage);
        }
        else if (!m_bRecovery && RightDirection == m_nDirection) {
            m_nCurrentPage = m_nCurrentPage - 1;
            if (m_nCurrentPage < 0) m_nCurrentPage = 0;
            emit currentPageChanged(m_nCurrentPage);
        }

        m_nDirection = None;
        m_bRecovery = false;
        m_nStartPos = 0;
    }
    this->update();
}

void LauncherWidget::SltChangePage()
{

}

void LauncherWidget::resizeEvent(QResizeEvent *e)
{
    SetPageCount(m_nPageCnt);
    m_nItemHeight = (this->height() -  (m_nLayoutRows + 1) * ITEM_SPACE - SPOT_WIDTH * 2) / m_nLayoutRows;
    m_nItemWidth = (this->width() -  (m_nLayoutColumns + 1) * ITEM_SPACE) / m_nLayoutColumns;
    QWidget::resizeEvent(e);
}

void LauncherWidget::mousePressEvent(QMouseEvent *e)
{
    if (!this->isEnabled()) return;
    bool bOk = false;

    foreach (QRect rect, m_rectPageSpot) {
        if (rect.contains(e->pos())) {
            int nKey = m_rectPageSpot.key(rect);
            if (m_nCurrentPage != nKey) {
                m_nPrevPage = m_nCurrentPage;
                m_nCurrentPage = nKey;
                m_nDirection = (m_nCurrentPage > m_nPrevPage) ? LeftDirection : RightDirection;
                bOk = true;
            }
            break;
        }
    }

    foreach (LauncherItem *item, m_itemApps) {
        if (item->m_rect.contains(e->pos())) {
            m_nCurrentIndex = item->m_nAppId;
            this->update();
            break;
        }
    }

    if (!bOk) {
        m_bPressed = true;
        m_startPos = e->pos();
    }

    QWidget::mousePressEvent(e);
}

void LauncherWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (None == m_nDirection && -1 != m_nCurrentIndex) {
        emit currentItemClicked(m_nCurrentIndex);
    }

    m_nCurrentIndex = -1;
    this->update();

    m_bPressed = false;
    m_animation->setStartValue(m_nStartPos);

    if (qAbs(m_nStartPos) > 100) {
        m_nMoveEndValue = (m_nStartPos < 0) ? -this->width() : this->width();
        m_nDirection = (m_nStartPos < 0) ? LeftDirection : RightDirection;
    }
    else {
        m_nMoveEndValue = 0;
        m_bRecovery = true;
    }

    m_animation->setEndValue(m_nMoveEndValue);
    m_animation->start();

    QWidget::mouseReleaseEvent(e);
}

void LauncherWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (m_bPressed) {
        int nXoffset = e->pos().x() - m_startPos.x();
        m_startPos = e->pos();

        // 向左滑动--显示下一页
        m_nDirection = (nXoffset < 0) ? LeftDirection : RightDirection;
        m_nStartPos += nXoffset;
        if (RightDirection == m_nDirection && m_nCurrentPage == 0 && m_nStartPos > 50) {
            m_nStartPos = 50;
        }
        else if (LeftDirection == m_nDirection && ((m_nCurrentPage + 1) == m_nPageCnt) && m_nStartPos < -50) {
            m_nStartPos = -50;
        }
        this->update();
    }

    QWidget::mouseMoveEvent(e);
}

void LauncherWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    if (!m_pixmapWallpaper.isNull()) {
        painter.drawPixmap(0, 0, this->width(), this->height(), m_pixmapWallpaper);
    } else {
        painter.setBrush(m_backgroundColor);
        painter.drawRect(this->rect());
    }

    // 绘制中心区域
    if (None == m_nDirection) {
        drawAppItem(&painter, m_nCurrentPage);
    }
    else {
        drawAppItem(&painter, m_nCurrentPage, m_nStartPos);
        if (m_nStartPos < 0) {
            drawAppItem(&painter, m_nCurrentPage + 1, this->width() + m_nStartPos);
        }
        else {
            drawAppItem(&painter, m_nCurrentPage - 1, -this->width() + m_nStartPos);
        }
    }
    //  绘制底部的点
    drawItemSpot(&painter);
}

void LauncherWidget::drawAppItem(QPainter *painter, int page, int xOffset)
{
    QRect rect;
    int nIndex = 0;
    foreach (LauncherItem *item, m_itemApps) {
        item->m_rect = QRect(0, 0, 0, 0);
        if (page == item->m_nPageIndex) {
            if (0 == (nIndex % m_nLayoutColumns)) {
                rect = QRect(xOffset, (nIndex / m_nLayoutColumns) * (m_nItemHeight + ITEM_SPACE) + ITEM_SPACE, 0, 0);
            }

            rect = QRect(rect.right() + ITEM_SPACE, rect.top(), m_nItemWidth, m_nItemHeight);
            item->m_rect = rect;
            nIndex ++;
            // 绘制app信息
            drawAppInfo(painter, rect, item);
        }
    }
}

void LauncherWidget::drawItemSpot(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    foreach (QRect rect, m_rectPageSpot) {
        int nKey = m_rectPageSpot.key(rect);
        painter->setBrush(nKey == m_nCurrentPage ? QColor("#182e3a") : QColor("#ffffff"));
        painter->drawEllipse(rect.left(), rect.top(), SPOT_WIDTH, SPOT_WIDTH);
    }
    painter->restore();
}

void LauncherWidget::drawAppInfo(QPainter *painter, QRect rect, LauncherItem *item)
{
    painter->save();
    QFont font = painter->font();
    font.setPixelSize(16);
    painter->setFont(font);
    int nTextHeight = painter->fontMetrics().height();

    int nXoffset = (rect.width() > ICON_SIZE) ? (rect.width() - ICON_SIZE) / 2 : 0;
    int nYOffset = (rect.height() > ICON_SIZE) ? (rect.height() - ICON_SIZE - nTextHeight - 5) / 2 : 0;
    QRect rectPixmap(rect.left() + nXoffset + ICON_SIZE / 2, rect.top() + ICON_SIZE / 2 + nYOffset, ICON_SIZE, ICON_SIZE);
    if (item->m_pixmapIcon.isNull()) {
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor("#02a7f0"));
        painter->drawEllipse(rectPixmap.topLeft(), ICON_SIZE / 2, ICON_SIZE / 2);
    } else {
        painter->drawPixmap(rectPixmap.left() - ICON_SIZE / 2, rectPixmap.top() - ICON_SIZE / 2, item->m_pixmapIcon);
    }

    if (m_nCurrentIndex == item->m_nAppId) {
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor("#32000000"));
        painter->drawEllipse(rectPixmap.topLeft(), ICON_SIZE / 2, ICON_SIZE / 2);
    }

    painter->setPen("#ffffff");
    QRect rectText(rect.left(), rect.top() + ICON_SIZE + nYOffset + 10, rect.width(), nTextHeight);
    painter->drawText(rectText, Qt::AlignCenter, item->m_strAppName);
    painter->restore();
}
