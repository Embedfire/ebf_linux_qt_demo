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
#include "qtlistwidget.h"

#include <QtMath>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

#define MOVE_STEP           20
#define ICON_SIZE           80

QtListWidgetItem::QtListWidgetItem(int id, const QStringList &args) :
    m_nId(id),m_strMultiParameters(args),m_bPressed(false)
{

}

QtListWidgetItem::QtListWidgetItem(int id, const QString &name) :
    m_nId(id),m_strText(name)
{
    m_pixmapIcon = QPixmap();
    m_bPressed = false;
}

QtListWidgetItem::QtListWidgetItem(int id, const QString &name, const QPixmap &icon)
{
    m_nId = id;
    m_strText = name;
    m_pixmapIcon = icon;
    m_bPressed = false;
}

QtListWidgetItem::QtListWidgetItem(int id, const QString &path, const QString &name, const QPixmap &icon)
{
    m_nId = id;
    m_strText = path;
    m_strBaseName = name;
    m_strPath = path;
    m_pixmapIcon = icon;
    m_bPressed = false;
}

////////////////////////////////////////////////////////////////////////////////
/// \brief QtListWidget::QtListWidget
/// \param parent
QtListWidget::QtListWidget(QWidget *parent) : QtWidgetBase(parent)
{
    m_pixmapWallpaper = QPixmap();
    m_backgroundColor = QColor("#fafafa");
    m_colorText   = QColor("#333333");
    m_nStartIndex = 0;
    m_nCurrentIndex = 0;

    m_nDirection = None;
    m_bRecovery = false;

    m_bPressed = false;
    m_startPos = QPoint(0, 0);
    m_nStartPos = 0;
    m_nMoveEndValue = 0;

    m_nItemSize = 60;
    m_nMargin = 10;
    m_nSpace = 5;
    m_bHorizontal = true;
    m_alignment = Qt::AlignCenter;

    m_animationMove = new QPropertyAnimation(this, "xPos");
    m_animationMove->setDuration(200);
}

QtListWidget::~QtListWidget()
{
    ClearItems();
}

QtListWidgetItem *QtListWidget::currentItem()
{
    return m_listItems.value(m_nCurrentIndex);
}

void QtListWidget::AddItem(int id, QtListWidgetItem *item)
{
    m_listItems.insert(id, item);
}

void QtListWidget::SetItems(const QMap<int, QtListWidgetItem *> &items)
{
    if (items.isEmpty()) {
        this->setVisible(false);
        return;
    }

    ClearItems();
    m_nStartIndex = 0;
    m_nCurrentIndex = 0;
    m_nStartPos = 0;
    m_listItems = items;
    this->show();
    this->update();
}

void QtListWidget::SetBackground(const QPixmap &pixmap)
{
    if (pixmap.isNull()) return;
    this->m_pixmapWallpaper = pixmap;
    this->update();
}

void QtListWidget::SetBackground(const QColor &color)
{
    if (!color.isValid()) return;
    this->m_backgroundColor = color;
    this->update();
}

void QtListWidget::setItemSize(int size)
{
    m_nItemSize = size;
    if (m_bHorizontal) {
        this->setMinimumHeight(m_nItemSize + m_nMargin * 2);
    } else {
        this->setMinimumWidth(m_nItemSize + m_nMargin * 2);
    }
    this->update();
}

void QtListWidget::setHoriazontal(bool bOk)
{
    m_bHorizontal = bOk;
    this->update();
}

void QtListWidget::setAlignment(Qt::Alignment aligns)
{
    m_alignment = aligns;
    this->update();
}

void QtListWidget::setScaleSize(int w, int h)
{
    m_nBaseHeight = h;
    m_nBaseWidth = w;
    m_nItemShowCnt = m_bHorizontal ? ((m_nBaseWidth - m_nMargin * 2) / m_nItemSize) :
                                     ((m_nBaseHeight - m_nMargin * 2) / m_nItemSize);
    SetScaleValue();
}

void QtListWidget::setPrevIndex()
{
    if (m_nCurrentIndex > 0) {
        setCurrentIndex(m_nCurrentIndex - 1);
    }
}

void QtListWidget::setCurrentIndex(int index)
{
    if (index == m_nCurrentIndex) return;

    m_bRecovery = true;
    m_nStartPos = 0;
    m_nDirection = None;

    if (index < m_nCurrentIndex) {
        if (m_nStartIndex == m_nCurrentIndex && m_nStartIndex > 0) {
            m_nMoveEndValue = m_nItemSize;
            m_nDirection = m_bHorizontal ? LeftDirection : UpDirection;
            if (m_nStartIndex > 0) {
                m_nStartIndex -= 1;
            }
        }
        else if (index == 0) {
            m_nStartIndex = 0;
        }
    } else {
        if (index < m_nItemShowCnt) {
            m_nStartIndex = 0;
        }  else if (index == (m_listItems.size() - 1)) {
            m_nStartIndex = m_listItems.size() - m_nItemShowCnt;
            if (m_nStartIndex < 0) m_nStartIndex = 0;
        }
        else {
            m_nMoveEndValue = -m_nItemSize;
            m_nDirection = m_bHorizontal ? RightDirection : DownDirection;

            if ((m_nStartIndex + m_nItemShowCnt) < m_listItems.size()) {
                m_nStartIndex += 1;
            }
        }
    }

    m_nCurrentIndex = index;
    if (None != m_nDirection) {
        m_animationMove->setStartValue(m_nStartPos);
        m_animationMove->setEndValue(m_nMoveEndValue);
        m_animationMove->start();
    } else {
        this->update();
    }
}

void QtListWidget::setNexIndex()
{
    if (m_nCurrentIndex < (m_listItems.size() - 1)) {
        setCurrentIndex(m_nCurrentIndex + 1);
    }
}

void QtListWidget::setMovePos(int nValue)
{
    m_nStartPos = nValue;
    if (m_nStartPos == m_nMoveEndValue) {
        if (!m_bRecovery && LeftDirection == m_nDirection)  {
            m_nStartIndex += 1;
        }
        else if (!m_bRecovery && RightDirection == m_nDirection) {
            m_nStartIndex -= 1;
        }

        m_nDirection = None;
        m_bRecovery = false;
        m_nStartPos = 0;
    }

    this->update();
}

void QtListWidget::ClearItems()
{
    foreach (QtListWidgetItem *item, m_listItems) {
        delete item;
        item = NULL;
    }
}

QSize QtListWidget::sizeHint() const
{
    return QSize(100, 30);
}

void QtListWidget::resizeEvent(QResizeEvent *e)
{
    m_nItemShowCnt = m_bHorizontal ? ((m_nBaseWidth - m_nMargin * 2) / m_nItemSize) :
                                     ((m_nBaseHeight - m_nMargin * 2) / m_nItemSize);
    SetScaleValue();
    QWidget::resizeEvent(e);
}

void QtListWidget::mousePressEvent(QMouseEvent *e)
{
    m_nDirection = None;
    QRect rect;
    foreach (QtListWidgetItem *item, m_listItems) {
        ScaleRect(rect, item->m_rect);
        if (rect.contains(e->pos())) {
            item->m_bPressed = true;
            break;
        }
    }

    m_bPressed = true;
    m_startPos = e->pos();
}

void QtListWidget::mouseReleaseEvent(QMouseEvent *)
{
    foreach (QtListWidgetItem *item, m_listItems) {
        if (item->m_bPressed) {
            item->m_bPressed = false;
            if (None == m_nDirection) {
                m_nCurrentIndex = item->m_nId;
                this->update();
                emit currentItemClicked(item);
                emit currentIndexClicked(m_nCurrentIndex);
            }
            break;
        }
    }

    m_bPressed = false;
    m_animationMove->setStartValue(m_nStartPos);

    if (qAbs(m_nStartPos) > (m_nItemSize / 2)) {
        m_nMoveEndValue = (m_nStartPos < 0) ? -m_nItemSize : m_nItemSize;
        m_nDirection = (m_nStartPos < 0) ? (m_bHorizontal ? LeftDirection : UpDirection) :
                                           (m_bHorizontal ? RightDirection : DownDirection);
    }
    else {
        m_nMoveEndValue = 0;
        m_bRecovery = true;
    }

    m_animationMove->setEndValue(m_nMoveEndValue);
    m_animationMove->start();
}

void QtListWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (m_bPressed) {
        int nXoffset = m_bHorizontal ? (e->pos().x() - m_startPos.x()) :
                                       (e->pos().y() - m_startPos.y());
        m_startPos = e->pos();

        // 向左滑动--显示下一页
        m_nDirection = (nXoffset < 0) ? (m_bHorizontal ? LeftDirection : UpDirection) :
                                        (m_bHorizontal ? RightDirection : DownDirection);
        m_nStartPos += nXoffset;
        qreal scale = (m_bHorizontal ? m_scaleX : m_scaleY);
        int nOffset = (m_nItemSize + m_nSpace) * scale;
        if (RightDirection == m_nDirection || DownDirection == m_nDirection)
        {
            if (m_nStartIndex == 0 && m_nStartPos > (m_nItemSize / 2)) {
                m_nStartPos = m_nItemSize * scale / 2;
            }
            else if (m_nStartPos >= nOffset && m_nStartIndex > 0) {
                m_nStartPos = 0;
                m_nStartIndex -= 1;
            }
        }
        else if (LeftDirection == m_nDirection || UpDirection == m_nDirection)
        {
            if (m_nStartIndex == (m_listItems.size() - m_nItemShowCnt) && m_nStartPos < -(m_nItemSize / 2)) {
                m_nStartPos = -m_nItemSize * scale / 2;
            }
            else if (m_nStartPos <= -nOffset && m_nStartIndex < (m_listItems.size() - m_nItemShowCnt))
            {
                m_nStartPos = 0;
                m_nStartIndex += 1;
            }
        }

        this->update();
    }

}

void QtListWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);
    painter.scale(m_scaleX, m_scaleY);

    if (!m_pixmapWallpaper.isNull()) {
        painter.drawPixmap(0, 0, m_pixmapWallpaper);
    } else {
        painter.setBrush(m_backgroundColor);
        painter.drawRect(0, 0, m_nBaseWidth, m_nBaseHeight);
    }

    if (m_bHorizontal) {
        drawHorizontalItem(&painter);
    } else {
        drawVerticalItem(&painter);
    }
}

void QtListWidget::drawHorizontalItem(QPainter *painter)
{
    painter->save();
    QRect rect = QRect(m_nStartPos + m_nMargin - m_nSpace - m_nItemSize, m_nMargin, m_nItemSize, m_nBaseHeight - m_nMargin * 2);
    if (m_nStartIndex > 0 && RightDirection == m_nDirection) {
        QtListWidgetItem *item = m_listItems.value(m_nStartIndex - 1);
        item->m_rect = rect;
        drawItemInfo(painter, item);
    }

    int id = (m_nStartIndex + m_nItemShowCnt);
    foreach (QtListWidgetItem *item, m_listItems) {
        item->m_rect = QRect(0, 0, 0, 0);
        if (item->m_nId >= m_nStartIndex && item->m_nId < id) {
            rect = QRect(rect.right() + m_nSpace, rect.top(), rect.width(), rect.height());
            item->m_rect = rect;
            drawItemInfo(painter, item);
        }
    }

    if (id < m_listItems.size() && LeftDirection == m_nDirection) {
        rect = QRect(rect.right() + m_nSpace, rect.top(), rect.width(), rect.height());
        QtListWidgetItem *item = m_listItems.value(id);
        item->m_rect = rect;
        drawItemInfo(painter, item);
    }
    painter->restore();
}

void QtListWidget::drawVerticalItem(QPainter *painter)
{
    painter->save();
    QRect rect = QRect(m_nMargin, m_nMargin - m_nSpace + m_nStartPos - m_nItemSize, m_nBaseWidth  - m_nMargin * 2, m_nItemSize);
    if (m_nStartIndex > 0 && DownDirection == m_nDirection) {
        QtListWidgetItem *item = m_listItems.value(m_nStartIndex - 1);
        item->m_rect = rect;
        drawItemInfo(painter, item);
    }

    int id = (m_nStartIndex + m_nItemShowCnt);
    foreach (QtListWidgetItem *item, m_listItems) {
        item->m_rect = QRect(0, 0, 0, 0);
        if (item->m_nId >= m_nStartIndex && item->m_nId < id) {
            rect = QRect(rect.left(), rect.bottom() + m_nSpace, rect.width(), rect.height());
            item->m_rect = rect;
            drawItemInfo(painter, item);
        }
    }

    if (id < m_listItems.size() && UpDirection == m_nDirection) {
        rect = QRect(rect.left(), rect.bottom() + m_nSpace, rect.width(), rect.height());
        QtListWidgetItem *item = m_listItems.value(id);
        item->m_rect = rect;
        drawItemInfo(painter, item);
    }

    painter->restore();
}

void QtListWidget::drawItemInfo(QPainter *painter, QtListWidgetItem *item)
{
#if 0
    if (m_nCurrentIndex == item->m_nId) {
        painter->setPen("#ff0000");
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(item->m_rect);
    }
#endif

    QFont font = painter->font();
    font.setPixelSize(16);
    painter->setFont(font);
    painter->setPen(m_colorText);
    painter->drawText(item->m_rect, m_alignment, item->m_strText);
}
