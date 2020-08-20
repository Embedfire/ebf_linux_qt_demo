/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : qtlistwidget.cpp --- QtListWidget
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/8
*******************************************************************/
#include "qtpagelistwidget.h"

#include <QtMath>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

#define MOVE_STEP           20
#define ICON_SIZE           80

QtPageListWidgetItem::QtPageListWidgetItem(int id, const QStringList &args) :
    m_nId(id),m_strMultiParameters(args)
{

}

QtPageListWidgetItem::QtPageListWidgetItem(int id, const QString &name) :
    m_nId(id),m_strText(name)
{
    m_pixmapIcon = QPixmap();
}

QtPageListWidgetItem::QtPageListWidgetItem(int id, const QString &name, const QPixmap &icon)
{
    m_nId = id;
    m_strText = name;
    m_pixmapIcon = icon;
}

QtPageListWidgetItem::QtPageListWidgetItem(int id, const QString &path, const QString &name, const QPixmap &icon)
{
    m_nId = id;
    m_strText = path;
    m_strBaseName = name;
    m_strPath = path;
    m_pixmapIcon = icon;
}

////////////////////////////////////////////////////////////////////////////////
/// \brief QtListWidget::QtListWidget
/// \param parent
QtPageListWidget::QtPageListWidget(QWidget *parent) : QtWidgetBase(parent)
{
    m_pixmapWallpaper = QPixmap();
    m_backgroundColor = Qt::transparent;

    m_nPageCnt = 1;
    m_nCurrentPage = 0;
    m_nPrevPage = -1;
    m_nCurrentIndex = -1;

    m_nDirection = None;
    m_bLoopbackChange = false;
    m_bRecovery = false;

    m_bPressed = false;
    m_startPos = QPoint(0, 0);
    m_nStartPos = 0;
    m_nMoveEndValue = 0;

    m_nLayoutRows = 3;
    m_nLayoutColumns = 4;
    m_nHorSpace = 18;
    m_nVSpace = 6;
    resizeRect();

    m_animationMove = new QPropertyAnimation(this, "xPos");
    m_animationMove->setDuration(200);
    //    this->setMouseTracking(true);
}

QtPageListWidget::~QtPageListWidget()
{
    foreach (QtPageListWidgetItem *item, m_listItems) {
        delete item;
        item = NULL;
    }
}

void QtPageListWidget::AddItem(int id, QtPageListWidgetItem *item)
{
    m_listItems.insert(id, item);
    this->update();
}

void QtPageListWidget::SetItems(const QMap<int, QtPageListWidgetItem *> &items)
{
    m_listItems.clear();
    m_listItems = items;
    m_nPageCnt = items.size() / (m_nLayoutColumns * m_nLayoutRows);
    if (0 != (items.size() % (m_nLayoutColumns * m_nLayoutRows))) m_nPageCnt += 1;
    this->update();
}

void QtPageListWidget::SetBackground(const QPixmap &pixmap)
{
    if (pixmap.isNull()) return;
    this->m_pixmapWallpaper = pixmap;
    this->update();
}

void QtPageListWidget::SetBackground(const QColor &color)
{
    if (!color.isValid()) return;
    this->m_backgroundColor = color;
    this->update();
}

void QtPageListWidget::SetPageCount(int count)
{
    if (count < 1) return;
    this->m_nPageCnt = count;
}

void QtPageListWidget::SetItemLayut(int rows, int columns)
{
    if (0 == rows || 0 == columns) return;

    this->m_nLayoutRows = rows;
    this->m_nLayoutColumns = columns;
    resizeRect();
}

void QtPageListWidget::SetItemLayoutSpace(int row, int col)
{
    m_nHorSpace = col;
    m_nVSpace = row;
    resizeRect();
}

void QtPageListWidget::SetLoopbackChange(bool bOk)
{
    this->m_bLoopbackChange = bOk;
}

void QtPageListWidget::setXPos(int nValue)
{
    m_nStartPos = nValue;
    if (m_nStartPos == m_nMoveEndValue) {
        if (!m_bRecovery && LeftDirection == m_nDirection)  {
            m_nCurrentPage = m_nCurrentPage + 1;
            emit currentPageChanged(m_nCurrentPage);
        }
        else if (!m_bRecovery && RightDirection == m_nDirection) {
            m_nCurrentPage = m_nCurrentPage - 1;
            emit currentPageChanged(m_nCurrentPage);
        }

        m_nDirection = None;
        m_bRecovery = false;
        m_nStartPos = 0;
    }
    this->update();
}

void QtPageListWidget::resizeRect()
{
    m_nItemHeight = (m_nBaseHeight -  (m_nLayoutRows + 1) * m_nVSpace) / m_nLayoutRows;
    m_nItemWidth = (m_nBaseWidth -  (m_nLayoutColumns + 1) * m_nHorSpace) / m_nLayoutColumns;
    this->update();
}

void QtPageListWidget::mousePressEvent(QMouseEvent *e)
{
    bool bOk = false;
    m_nCurrentIndex = -1;
    QRect rect;
    foreach (QtPageListWidgetItem *item, m_listItems) {
        ScaleRect(rect, item->m_rect);
        if (rect.contains(e->pos())) {
            m_nCurrentIndex = item->m_nId;
            this->update();
            break;
        }
    }

    if (!bOk) {
        m_bPressed = true;
        m_startPos = e->pos();
    }
}

void QtPageListWidget::mouseReleaseEvent(QMouseEvent *)
{
    if (None == m_nDirection && -1 != m_nCurrentIndex) {
        emit currentItemClicked(m_listItems.value(m_nCurrentIndex));
        m_nCurrentIndex = -1;
        this->update();
    }

    m_bPressed = false;
    m_animationMove->setStartValue(m_nStartPos);

    if (qAbs(m_nStartPos) > 100 * m_scaleX) {
        m_nMoveEndValue = (m_nStartPos < 0) ? -m_nBaseWidth : m_nBaseWidth;
        m_nDirection = (m_nStartPos < 0) ? LeftDirection : RightDirection;
    }
    else {
        m_nMoveEndValue = 0;
        m_bRecovery = true;
    }

    m_animationMove->setEndValue(m_nMoveEndValue);
    m_animationMove->start();
}

void QtPageListWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (m_bPressed) {
        int nXoffset = e->pos().x() - m_startPos.x();
        m_startPos = e->pos();

        // 向左滑动--显示下一页
        m_nDirection = (nXoffset < 0) ? LeftDirection : RightDirection;
        m_nStartPos += nXoffset;

        int ntemp = 50 * m_scaleX;
        if (RightDirection == m_nDirection && m_nCurrentPage == 0 && m_nStartPos > ntemp) {
            m_nStartPos = ntemp;
        }
        else if (LeftDirection == m_nDirection && ((m_nCurrentPage + 1) == m_nPageCnt) && m_nStartPos < -ntemp) {
            m_nStartPos = -ntemp;
        }

        this->update();
    }

}

void QtPageListWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);
    painter.scale(m_scaleX, m_scaleY);

    if (!m_pixmapWallpaper.isNull()) {
        painter.drawTiledPixmap(QRect(0, 0, m_nBaseWidth, m_nBaseHeight), m_pixmapWallpaper);
    } else {
        painter.setBrush(m_backgroundColor);
        painter.drawRect(0, 0, m_nBaseWidth, m_nBaseHeight);
    }

    // 绘制中心区域
    if (None == m_nDirection) {
        drawListItem(&painter, m_nCurrentPage);
    }
    else {
        drawListItem(&painter, m_nCurrentPage, m_nStartPos);
        if (m_nStartPos < 0 && (m_nCurrentPage < (m_nPageCnt - 1))) {
            drawListItem(&painter, m_nCurrentPage + 1, m_nBaseWidth + m_nStartPos);
        }
        else if (m_nCurrentPage > 0) {
            drawListItem(&painter, m_nCurrentPage - 1, -m_nBaseWidth + m_nStartPos);
        }
    }
}

void QtPageListWidget::drawListItem(QPainter *painter, int page, int xOffset)
{
    QRect rect;
    int nIndex = 0;
    int nCnt = (m_nLayoutColumns * m_nLayoutRows);

    foreach (QtPageListWidgetItem *item, m_listItems) {
        item->m_rect = QRect(0, 0, 0, 0);
        if ((page * nCnt) <= item->m_nId && nIndex < nCnt) {
            if (0 == (nIndex % m_nLayoutColumns)) {
                rect = QRect(xOffset, (nIndex / m_nLayoutColumns) * (m_nItemHeight + m_nVSpace) + m_nVSpace, 0, 0);
            }

            rect = QRect(rect.right() + m_nHorSpace, rect.top(), m_nItemWidth, m_nItemHeight);
            item->m_rect = rect;
            nIndex ++;
            // 绘制app信息
            drawItemInfo(painter, item);
        }
    }
}

void QtPageListWidget::drawItemInfo(QPainter *painter, QtPageListWidgetItem *item)
{
    painter->save();

    QRect rect = item->m_rect;
    int nXoffset = (rect.width() > ICON_SIZE) ? (rect.width() - ICON_SIZE) / 2 : 0;
    QRect rectPixmap(rect.left() + nXoffset + ICON_SIZE / 2, rect.top() + ICON_SIZE / 2, ICON_SIZE, ICON_SIZE);
    if (item->m_pixmapIcon.isNull()) {
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor("#02a7f0"));
        painter->drawEllipse(rectPixmap.topLeft(), ICON_SIZE / 2, ICON_SIZE / 2);
    } else {
        painter->drawPixmap(rect.left() + nXoffset, rect.top(), item->m_pixmapIcon);
    }

    if (m_nCurrentIndex == item->m_nId) {
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor("#32000000"));
        painter->drawEllipse(rectPixmap.topLeft(), ICON_SIZE / 2, ICON_SIZE / 2);
    }

    QFont font = painter->font();
    font.setPixelSize(16);
    painter->setFont(font);
    painter->setPen("#ffffff");
    int nTextHeight = painter->fontMetrics().height();
    QRect rectText(rect.left(), rect.bottom() - nTextHeight, rect.width(), nTextHeight);
    painter->drawText(rectText, Qt::AlignCenter, item->m_strText);
    painter->restore();
}
