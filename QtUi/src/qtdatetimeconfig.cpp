/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : qtdatetimeconfig.cpp --- QtDateTimeConfig
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "qtdatetimeconfig.h"

#include <QBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QDateTime>
#include <QDebug>

NumberSelected::NumberSelected(QWidget *parent) : QtWidgetBase(parent),
    m_nItemHeight(50),m_nStartIndex(0),m_nIndex(0),m_nOffset(0),
    m_nDirection(None),m_nMinValue(1),m_nMaxValue(12)
{
    m_colorBackground = QColor("#ffffff");
    m_colorText = QColor("#333333");
    m_colorBackroundSelected = QColor("#f2f2f2");
    m_colorTextSelected = QColor("#000000");
    m_nBaseWidth = 125;
    m_nBaseHeight = 250;
}

NumberSelected::~NumberSelected()
{

}

void NumberSelected::setItmes(const QStringList &items)
{
    m_strListItems = items;
    this->update();
}

void NumberSelected::setMinValue(int value)
{
    m_nMinValue = value;
}

void NumberSelected::setMaxValue(int value)
{
    m_nMaxValue = value;
    if (m_nIndex > m_nMaxValue) {
        m_nIndex = m_nMaxValue;
    }
    this->update();
}

void NumberSelected::setCurrentIndex(int index)
{
    if (index < m_nMinValue || index > m_nMaxValue) return;

    if (index < (m_nMinValue + 2)) {
        m_nStartIndex = m_nMaxValue - index + m_nMinValue - 1;
    } else {
        m_nStartIndex = index - 2;
    }
    m_nIndex = index;
    this->update();
}

int NumberSelected::currentIndex()
{
    return m_nIndex;
}

void NumberSelected::setCurrentValue()
{
    if (UpDirection == m_nDirection && m_nStartIndex > m_nMaxValue) {
        m_nStartIndex = m_nMinValue;
    }
    else if (DownDirection == m_nDirection && m_nStartIndex < m_nMinValue) {
        m_nStartIndex = m_nMaxValue;
    }

    m_nIndex = m_nStartIndex + 2;
    if (m_nIndex > m_nMaxValue) {
        m_nIndex = m_nIndex - m_nMaxValue + m_nMinValue - 1;
    }

    emit signalIndexChanged();
}


void NumberSelected::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.scale(m_scaleX, m_scaleY);
    painter.fillRect(0, 0, m_nBaseWidth, m_nBaseHeight, m_colorBackground);

    // 绘制item
    drawListItem(&painter);
}


void NumberSelected::drawListItem(QPainter *painter)
{
    painter->save();
    QFont font = this->font();
    font.setPixelSize(20);
    painter->setFont(font);

    painter->setPen(Qt::NoPen);
    painter->setBrush(m_colorBackroundSelected);
    QRect rect(0, m_nItemHeight * 2, m_nBaseWidth, m_nItemHeight);
    painter->drawRect(rect);
    painter->setPen("#d9d9d9");
    painter->drawLine(rect.topLeft(), rect.topRight());
    painter->drawLine(rect.bottomLeft(), rect.bottomRight());
    painter->setPen(m_colorText);

    rect = QRect(0, m_nOffset - m_nItemHeight, m_nBaseWidth, m_nItemHeight);
    if (DownDirection == m_nDirection) {
        int value = m_nStartIndex - 1;
        if (value < m_nMinValue) value = m_nMaxValue;
        painter->drawText(rect, Qt::AlignCenter, QString("%1").arg(value, 2, 10, QChar('0')));
    }

    for (int i = 0; i < 5; i++) {
        rect = QRect(rect.left(), rect.bottom(), rect.width(), rect.height());
        int value = i + m_nStartIndex;
        if (value > m_nMaxValue) {
            value = i + m_nStartIndex - m_nMaxValue + m_nMinValue - 1;
        }
        font.setPixelSize(((i % 2) == 0 ) ? 21 : 25);
        painter->setPen(QColor("#333333"));
        if (i == 2) {
            font.setPixelSize(30);
            painter->setPen(QColor("#ec7e41"));
        }

        painter->setFont(font);
        painter->drawText(rect, Qt::AlignCenter, QString("%1").arg(value, 2, 10, QChar('0')));
    }

    if (UpDirection == m_nDirection) {
        rect = QRect(rect.left(), rect.bottom(), rect.width(), rect.height());
        int value = m_nStartIndex + 5;
        if (value > m_nMaxValue) value = value - m_nMaxValue + m_nMinValue - 1;
        painter->drawText(rect, Qt::AlignCenter, QString("%1").arg(value, 2, 10, QChar('0')));
    }

    painter->restore();
}


void NumberSelected::mousePressEvent(QMouseEvent *e)
{
    m_bPressed = true;
    m_startPos = e->pos();
    m_nDirection = None;
    m_nOffset = 0;
    this->setFocus();
}

void NumberSelected::mouseReleaseEvent(QMouseEvent *)
{
    m_bPressed = false;
    if ((qAbs(m_nOffset) > m_nItemHeight / 2) && None != m_nDirection) {
        if (DownDirection == m_nDirection ) {
            m_nStartIndex -= 1;
        } else if (UpDirection == m_nDirection) {
            m_nStartIndex += 1;
        }

        setCurrentValue();
    }

    m_nOffset = 0;
    m_nDirection = None;
    this->update();
}

void NumberSelected::mouseMoveEvent(QMouseEvent *e)
{
    if (m_bPressed) {
        int nOffset = e->y() - m_startPos.y();
        moveStep(nOffset);
    }

    m_startPos = e->pos();
}

// 上为正，下为负
void NumberSelected::wheelEvent(QWheelEvent *e)
{
    if (e->orientation() == Qt::Vertical) {
        if (e->delta() > 0) {
            moveStep(m_nItemHeight);
        } else {
            moveStep(-m_nItemHeight);
        }
    }
}

void NumberSelected::moveStep(int nOffset)
{
    m_nOffset += nOffset;
    m_nDirection = (nOffset > 0) ? DownDirection : UpDirection;
    // DownDirection
    if (nOffset > 0) {
        if (m_nOffset >= m_nItemHeight) {
            m_nOffset = 0;
            m_nStartIndex -= 1;

            setCurrentValue();
        }
    }
    // UpDirection
    else if (nOffset < 0){
        if (qAbs(m_nOffset) >= m_nItemHeight) {
            m_nOffset = 0;
            m_nStartIndex += 1;
            if (m_nStartIndex > m_nMaxValue) m_nStartIndex = m_nMinValue;
            setCurrentValue();
        }
    }
    else {
        m_nOffset -= nOffset;
    }

    this->update();
}

//////////////////////////////////////////////////////////////////////
QtDateTimeConfig::QtDateTimeConfig(QWidget *parent) : QtWidgetBase(parent)
{
    m_nBaseWidth = 375;
    m_nBaseHeight = 280;

    InitWidget();
}

QtDateTimeConfig::~QtDateTimeConfig()
{

}

void QtDateTimeConfig::setConfigFormat(QtDateTimeConfig::ConfigFromat format)
{
    m_format = format;
    if (DateFormat == format) {
        QDate date = QDate::currentDate();
        m_strText = date.toString("yyyy年MM月dd日");
        m_numberSelected[0]->setMinValue(1970);
        m_numberSelected[0]->setMaxValue(2050);
        m_numberSelected[0]->setCurrentIndex(date.year());

        m_numberSelected[1]->setMaxValue(12);
        m_numberSelected[1]->setCurrentIndex(date.month());

        m_numberSelected[2]->setMaxValue(31);
        m_numberSelected[2]->setCurrentIndex(date.day());
    }
    else {
        QTime time = QTime::currentTime();
        m_strText = time.toString("hh:mm:ss");
        m_numberSelected[0]->setMinValue(0);
        m_numberSelected[0]->setMaxValue(23);
        m_numberSelected[0]->setCurrentIndex(time.hour());

        m_numberSelected[1]->setMinValue(0);
        m_numberSelected[1]->setMaxValue(59);
        m_numberSelected[1]->setCurrentIndex(time.minute());

        m_numberSelected[2]->setMinValue(0);
        m_numberSelected[2]->setMaxValue(59);
        m_numberSelected[2]->setCurrentIndex(time.second());
    }
}

QtDateTimeConfig::ConfigFromat QtDateTimeConfig::getFormat()
{
    return m_format;
}

void QtDateTimeConfig::SetFont(QFont font)
{
    for (int i = 0; i < 3; i++) {
        m_numberSelected[i]->setFont(font);
        m_numberSelected[i]->update();
    }
}

QDate QtDateTimeConfig::getCurrentDate()
{
    if (TimeFormat == m_format) {
        return QDate::currentDate();
    }

    return QDate(m_numberSelected[0]->currentIndex(),
            m_numberSelected[1]->currentIndex(),
            m_numberSelected[2]->currentIndex());
}

QTime QtDateTimeConfig::getCurrentTime()
{
    if (DateFormat == m_format) {
        return QTime::currentTime();
    }

    return QTime(m_numberSelected[0]->currentIndex(),
            m_numberSelected[1]->currentIndex(),
            m_numberSelected[2]->currentIndex());

}

void QtDateTimeConfig::InitWidget()
{
    QHBoxLayout *horLayoutNumber = new QHBoxLayout();
    horLayoutNumber->setContentsMargins(0, 0, 0, 0);
    horLayoutNumber->setSpacing(0);

    for (int i = 0; i < 3; i++) {
        m_numberSelected[i] = new NumberSelected(this);
        connect(m_numberSelected[i], SIGNAL(signalIndexChanged()), this, SLOT(SltNumberChanged()));
        horLayoutNumber->addWidget(m_numberSelected[i]);
    }

    QVBoxLayout *verLayoutAll = new QVBoxLayout(this);
    verLayoutAll->setContentsMargins(0, 10, 0, 10);
    verLayoutAll->setSpacing(0);
    verLayoutAll->addStretch(1);
    verLayoutAll->addLayout(horLayoutNumber, 8);
}

int QtDateTimeConfig::getCurrentMonthDays(int year, int month)
{
    int countDay = 0;
    int loopDay = (((0 == (year % 4)) && (0 != (year % 100))) || (0 == (year % 400))) ? 1 : 0;

    if (month < 8) {
        countDay = 30 + (month % 2);
    } else {
        countDay = 30 + !(month % 2);
    }

    if (2 == month) {
        countDay = 28 + loopDay;
    }

    return countDay;
}

void QtDateTimeConfig::SltNumberChanged()
{
    if (DateFormat == m_format) {
        int nYear = m_numberSelected[0]->currentIndex();
        int nMonth = m_numberSelected[1]->currentIndex();

        QDate date= QDate(nYear, nMonth, m_numberSelected[2]->currentIndex());
        m_strText = date.toString("yyyy年MM月dd日");
        m_numberSelected[2]->setMaxValue(getCurrentMonthDays(nYear, nMonth));
    } else {
        QTime time= QTime(m_numberSelected[0]->currentIndex(),
                m_numberSelected[1]->currentIndex(),
                m_numberSelected[2]->currentIndex());
        m_strText = time.toString("hh:mm:ss");
    }
    this->update();
}

void QtDateTimeConfig::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.scale(m_scaleX, m_scaleY);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawRoundedRect(0, 0, m_nBaseWidth, m_nBaseHeight, 5, 5);
    painter.setPen(QColor("#333333"));
    painter.drawText(0, 0, m_nBaseWidth, 30, Qt::AlignCenter, m_strText);
}
