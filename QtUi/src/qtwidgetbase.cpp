/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : qtwidgetbase.cpp --- QtWidgetBase
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "qtwidgetbase.h"

#include <QPainter>
#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>

QtWidgetBase::QtWidgetBase(QWidget *parent) : QWidget(parent)
{

}

QtWidgetBase::~QtWidgetBase() {

}

void QtWidgetBase::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

////////////////////////////////////////////////////////////////////
QtWidgetTitleBar::QtWidgetTitleBar(QWidget *parent) : QWidget(parent)
{
    m_strTitle = "";
    m_pixmapBackground = QPixmap();
    m_colorBackground = "#fafafa";
    m_colorText = "#333333";
}

QtWidgetTitleBar::QtWidgetTitleBar(const QString &title, QWidget *parent) :
    QWidget(parent)
{
    m_strTitle = title;
    m_pixmapBackground = QPixmap();
    m_colorBackground = "#fafafa";
    m_colorText = "#333333";
    m_nFontSize = 18;
}

QtWidgetTitleBar::~QtWidgetTitleBar()
{

}

void QtWidgetTitleBar::SetBackground(const QColor &color)
{
    this->m_colorBackground = color;
    this->update();
}

void QtWidgetTitleBar::SetBackground(const QPixmap &pixmap)
{
    this->m_pixmapBackground = pixmap;
    this->update();
}

QString QtWidgetTitleBar::title() const
{
    return m_strTitle;
}

void QtWidgetTitleBar::SetTitle(const QString &title)
{
    this->m_strTitle = title;
    this->update();
}

void QtWidgetTitleBar::SetTitle(const QString &title, const QColor &textClr, const int &fontSize)
{
    this->m_strTitle = title;
    this->m_colorText = textClr;
    this->m_nFontSize = fontSize;
    this->update();
}

void QtWidgetTitleBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::TextAntialiasing);
    if (m_pixmapBackground.isNull()) {
        painter.fillRect(this->rect(), m_colorBackground);
    }
    else {
        painter.drawPixmap(0, 0, this->width(), this->height(), m_pixmapBackground);
    }

    // 绘制文字
    QFont font = painter.font();
    font.setPixelSize(m_nFontSize);
    painter.setFont(font);
    painter.setPen(m_colorText);
    painter.drawText(this->rect(), Qt::AlignCenter, m_strTitle);
}

//////////////////////////////////////////////////////////////////////
/// \brief QtAnimationWidget::QtAnimationWidget
/// \param parent
/// 属性动画移动窗体
QtAnimationWidget::QtAnimationWidget(QWidget *parent) : QtWidgetBase(parent)
{
    m_bShow = false;
    m_animation = new QPropertyAnimation(this, "pos");
    m_colorBackground = QColor("#ffffff");
    connect(m_animation, SIGNAL(finished()), this, SLOT(SltAnimationFinished()));
    connect(m_animation, SIGNAL(finished()), this, SIGNAL(signalAnimationFinished()));
}

QtAnimationWidget::QtAnimationWidget(QEasingCurve curve, QWidget *parent) :
    QtWidgetBase(parent)
{
    m_bShow = false;
    m_animation = new QPropertyAnimation(this, "pos");
    m_animation->setEasingCurve(curve);
    connect(m_animation, SIGNAL(finished()), this, SLOT(SltAnimationFinished()));
}

QtAnimationWidget::~QtAnimationWidget()
{
    if (m_animation->state() != QPropertyAnimation::Stopped)
    {
        m_animation->stop();
    }
}

void QtAnimationWidget::StartAnimation(const QPoint &startPos, const QPoint &endPos, int duration, bool bShow)
{
    if (m_animation->state() != QPropertyAnimation::Stopped)
    {
        m_animation->stop();
    }
    if (!this->isVisible()) this->setVisible(true);
    m_animation->setDuration(duration);
    m_animation->setStartValue(startPos);
    m_animation->setEndValue(endPos);
    m_bShow = bShow;
    m_animation->start();
}

void QtAnimationWidget::SetAnimationCurve(QEasingCurve curve)
{
    m_animation->setEasingCurve(curve);
}

void QtAnimationWidget::SetBackground(const QPixmap &pixmap)
{
    if (pixmap.isNull()) return;
    m_pixmapBackground = pixmap;
    this->update();
}

void QtAnimationWidget::SetBackground(const QColor &color)
{
    if (!color.isValid()) return;
    m_colorBackground = color;
    this->update();
}

void QtAnimationWidget::SltAnimationFinished()
{
    this->setVisible(m_bShow);
}

void QtAnimationWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (m_pixmapBackground.isNull()) {
        painter.fillRect(this->rect(), m_colorBackground);
    } else {
        painter.drawPixmap(0, 0, this->width(), this->height(), m_pixmapBackground);
    }
}
