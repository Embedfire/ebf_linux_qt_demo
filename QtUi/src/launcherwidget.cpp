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
LauncherWidget::LauncherWidget(QWidget *parent) : QtWidgetBase(parent)
{
    m_pixmapWallpaper = QPixmap();
    m_backgroundColor = QColor("#c6c6c6");

    Init();
}

LauncherWidget::~LauncherWidget()
{
    delete m_btnNext;
    m_btnNext = NULL;

    delete m_btnPrev;
    m_btnPrev = NULL;
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
    int nStartX = (m_nBaseWidth - SPOT_WIDTH * (m_nPageCnt * 2 - 1)) / 2;
    for (int i = 0; i < m_nPageCnt; i++) {
        QRect rect(nStartX + i * 2 * SPOT_WIDTH, m_rectPage.bottom() - SPOT_WIDTH * 2, SPOT_WIDTH, SPOT_WIDTH);
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
        m_nMoveEndValue = -m_nBaseWidth;
        m_animation->setStartValue(0);
        m_animation->setEndValue(m_nMoveEndValue);
        m_animation->start();
    }
}

void LauncherWidget::SltShowPrevPage()
{
    if (m_nCurrentPage > 0) {
        m_nDirection = RightDirection;
        m_nMoveEndValue = m_nBaseWidth;
        m_animation->setStartValue(0);
        m_animation->setEndValue(m_nMoveEndValue);
        m_animation->start();
    }
}

void LauncherWidget::Init()
{
    m_nBaseWidth = 800;
    m_nBaseHeight = 480;
    m_rectPage = QRect(60, 0, 680, 400);
    m_rectAbout = QRect(0, 400, m_nBaseWidth, 80);

    m_nPageCnt = 3;
    m_nCurrentPage = 0;
    m_nPrevPage = -1;
    m_nCurrentIndex = -1;
    m_nLayoutRows = 3;
    m_nLayoutColumns = 4;
    m_nItemWidth = 145;
    m_nItemHeight = 100;

    m_nDirection = None;
    m_bLoopbackChange = false;
    m_bRecovery = false;

    m_bPressed = false;
    m_startPos = QPoint(0, 0);
    m_nStartPos = 0;
    m_nMoveEndValue = 0;

    m_animation = new QPropertyAnimation(this, "xPos");
    m_animation->setDuration(200);

    // 切换按钮
    m_btnPrev = new QtPixmapButton(0, QRect( 10, 180, 40, 40), QPixmap(":/images/mainwindow/ic_prev.png"), QPixmap(":/images/mainwindow/ic_prev_pre.png"));
    m_btnPrev->setPressed(true);
    m_btnNext = new QtPixmapButton(0, QRect(750, 180, 40, 40), QPixmap(":/images/mainwindow/ic_next.png"), QPixmap(":/images/mainwindow/ic_next_pre.png"));

    // 设置移动点
    SetPageCount(3);
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

        m_btnNext->setPressed(m_nCurrentPage == (m_nPageCnt - 1));
        m_btnPrev->setPressed(0 == m_nCurrentPage);
    }
    this->update();
}

void LauncherWidget::SltChangePage()
{

}

void LauncherWidget::mousePressEvent(QMouseEvent *e)
{
    if (!this->isEnabled()) return;
    bool bOk = false;
    QRect rectScale;

    ScaleRect(rectScale, m_rectAbout);
    if (rectScale.contains(e->pos())) {
        emit signalAboutClicked();
        return;
    }

    ScaleRect(rectScale, m_btnPrev->rect());
    if (rectScale.contains(e->pos())) {
        m_btnPrev->setPressed(true);
        this->update();
        return;
    }

    ScaleRect(rectScale, m_btnNext->rect());
    if (rectScale.contains(e->pos())) {
        m_btnNext->setPressed(true);
        this->update();
        return;
    }

    foreach (QRect rect, m_rectPageSpot) {
        ScaleRect(rectScale, rect);
        if (rectScale.contains(e->pos())) {
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
        ScaleRect(rectScale, item->m_rect);
        if (rectScale.contains(e->pos())) {
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
    m_bPressed = false;
    bool m_bMove = (0 != m_nStartPos);
    // 上一个
    if (m_btnPrev->isPressed() && m_nCurrentPage > 0) {
        m_btnPrev->setPressed(false);
        this->SltShowPrevPage();
    }

    // 下一个
    if (m_btnNext->isPressed() && m_nCurrentPage < (m_nPageCnt - 1)) {
        m_btnNext->setPressed(false);
        this->SltShowNextPage();
    }

    // 判断是否有app点击
    if (None == m_nDirection && -1 != m_nCurrentIndex) {
        emit currentItemClicked(m_nCurrentIndex);
    }

    m_nCurrentIndex = -1;
    this->update();

    if (!m_bMove) return;
    m_animation->setStartValue(m_nStartPos);

    if (qAbs(m_nStartPos) > 100 * m_scaleX) {
        m_nMoveEndValue = (m_nStartPos < 0) ? -m_nBaseWidth : m_nBaseWidth;
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
        if (m_bZoom) nXoffset = nXoffset;

        // 向左滑动--显示下一页
        m_nDirection = (nXoffset < 0) ? LeftDirection : RightDirection;
        m_nStartPos += nXoffset;
        if (RightDirection == m_nDirection && m_nCurrentPage == 0 && m_nStartPos > 50 * m_scaleX) {
            m_nStartPos = 50 * m_scaleX;
        }
        else if (LeftDirection == m_nDirection && ((m_nCurrentPage + 1) == m_nPageCnt) && m_nStartPos < -50 * m_scaleX) {
            m_nStartPos = -50 * m_scaleX;
        }
        this->update();
    }

    QWidget::mouseMoveEvent(e);
}

void LauncherWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    if (m_bZoom) painter.scale(m_scaleX, m_scaleY);
    if (!m_pixmapWallpaper.isNull()) {
        painter.drawPixmap(0, 0, m_pixmapWallpaper);
    } else {
        painter.setBrush(m_backgroundColor);
        painter.drawRect(this->rect());
    }

    // 绘制中心区域
    drawCenter(&painter);

    // 绘制界面切换按钮
    painter.drawPixmap(m_btnPrev->rect().topLeft(), m_btnPrev->pixmap());
    painter.drawPixmap(m_btnNext->rect().topLeft(), m_btnNext->pixmap());

    // 绘制底部广告标语
    painter.drawPixmap(m_rectAbout, QPixmap(":/images/mainwindow/statusbar_bg.png"));
}

void LauncherWidget::drawCenter(QPainter *painter)
{
    painter->save();
    painter->setClipRect(m_rectPage);
    painter->setPen(Qt::NoPen);
    if (None == m_nDirection) {
        drawAppItem(painter, m_nCurrentPage, m_rectPage.left());
    }
    else {
        int nXoffset = m_rectPage.left() + m_nStartPos;
        drawAppItem(painter, m_nCurrentPage, nXoffset);
        if (m_nStartPos < 0) {
            drawAppItem(painter, m_nCurrentPage + 1, m_rectPage.width() + nXoffset);
        }
        else {
            drawAppItem(painter, m_nCurrentPage - 1, -m_rectPage.width() + nXoffset);
        }
    }
    //  绘制底部的点
    drawItemSpot(painter);
    painter->restore();
}

// 绘制item
void LauncherWidget::drawAppItem(QPainter *painter, int page, int xOffset)
{
    QRect rect;
    int nIndex = 0;
    foreach (LauncherItem *item, m_itemApps) {
        item->m_rect = QRect(m_rectPage.left() , m_rectPage.top(), 0, 0);
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

// 绘制底部小圆圈
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

// 绘制app图标文字详细信息
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
