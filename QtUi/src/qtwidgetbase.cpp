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
#include <QDebug>

QtWidgetBase::QtWidgetBase(QWidget *parent) : QWidget(parent),
    m_bZoom(true),m_scaleX(1.0),m_scaleY(1.0),m_nBaseWidth(800),m_nBaseHeight(480)
{

}

QtWidgetBase::~QtWidgetBase() {
    foreach (QtPixmapButton *btn, m_btns) {
        m_btns.remove(btn->id());
        delete btn;
        btn = NULL;
    }
}

void QtWidgetBase::addBtn(int index, QtPixmapButton *btn)
{
    m_btns.insert(index, btn);
    this->update();
}

void QtWidgetBase::ScaleRect(QRect &rectRet, const QRect &rect)
{
    if (m_bZoom) {
        rectRet.setX(rect.x() * m_scaleX);
        rectRet.setY(rect.y() * m_scaleY);
        rectRet.setWidth(rect.width() * m_scaleX);
        rectRet.setHeight(rect.height() * m_scaleY);
    } else {
        rectRet = rect;
    }
}

void QtWidgetBase::SetScaleValue()
{
    if (m_bZoom) {
        m_scaleX = (this->width() * 1.0 / m_nBaseWidth);
        m_scaleY = (this->height() * 1.0 / m_nBaseHeight);
    } else {
        m_nBaseWidth = this->width();
        m_nBaseHeight = this->height();
    }
}

void QtWidgetBase::resizeEvent(QResizeEvent *e)
{
    SetScaleValue();
    QWidget::resizeEvent(e);
}

void QtWidgetBase::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void QtWidgetBase::mousePressEvent(QMouseEvent *e)
{
    QRect rect;
    foreach (QtPixmapButton *btn, m_btns) {
        ScaleRect(rect, btn->rect());
        if (rect.contains(e->pos())) {
            if (btn->isCheckAble()) {
                btn->setChecked(!btn->isChecked());
                emit signalBtnClicked(btn->id());
            } else {
                btn->setPressed(true);
            }
            this->update();
            break;
        }
    }

    QWidget::mousePressEvent(e);
}

void QtWidgetBase::mouseReleaseEvent(QMouseEvent *e)
{
    foreach (QtPixmapButton *btn, m_btns) {
        if (btn->isPressed()) {
            btn->setPressed(false);
            this->update();
            emit signalBtnClicked(btn->id());
            break;
        }
    }

    QWidget::mouseReleaseEvent(e);
}

////////////////////////////////////////////////////////////////////
QtWidgetTitleBar::QtWidgetTitleBar(QWidget *parent) : QtWidgetBase(parent)
{
    m_strTitle = "";
    m_pixmapBackground = QPixmap();
    m_colorBackground = "#fafafa";
    m_colorText = "#333333";

    m_btnHome = new QtPixmapButton(0, QRect(746, 0, 54, 54),
                                   QPixmap(":/images/music/menu_icon.png"),
                                   QPixmap(":/images/music/menu_icon_pressed.png"));
    m_btns.insert(m_btnHome->id(), m_btnHome);
    connect(this, SIGNAL(signalBtnClicked(int)), this, SLOT(SltBtnClicked(int)));
}

QtWidgetTitleBar::QtWidgetTitleBar(const QString &title, QWidget *parent) :
    QtWidgetBase(parent)
{
    m_strTitle = title;
    m_pixmapBackground = QPixmap();
    m_colorBackground = "#fafafa";
    m_colorText = "#333333";
    m_nFontSize = 18;

    m_btnHome = new QtPixmapButton(0, QRect(746, 0, 54, 54),
                                   QPixmap(":/images/music/menu_icon.png"),
                                   QPixmap(":/images/music/menu_icon_pressed.png"));
    m_btns.insert(m_btnHome->id(), m_btnHome);
    connect(this, SIGNAL(signalBtnClicked(int)), this, SLOT(SltBtnClicked(int)));
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

void QtWidgetTitleBar::SetScalSize(int w, int h)
{
    m_nBaseWidth = w;
    m_nBaseHeight = h;

    m_btnHome->setRect(QRect(m_nBaseWidth - 10 - 54, (h - 54) / 2, 54, 54));

    this->update();
}

void QtWidgetTitleBar::SetBtnHomePixmap(const QPixmap &normal, const QPixmap &pressed)
{
    m_btnHome->setPixmap(normal, pressed);
    this->update();
}

void QtWidgetTitleBar::SetBtnVisible(bool bOk, int index)
{
    m_btns.value(index)->setVisible(bOk);
    this->update();
}

void QtWidgetTitleBar::SetToolButtons(QMap<int, QtPixmapButton *> btns)
{
    m_btns = btns;
    m_btns.insert(0, m_btnHome);
    this->update();
}

void QtWidgetTitleBar::SltBtnClicked(int index)
{
    if (0 == index) emit signalBackHome();
}

void QtWidgetTitleBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    painter.scale(m_scaleX, m_scaleY);

    QRect rect(0, 0, m_nBaseWidth, m_nBaseHeight);
    if (m_pixmapBackground.isNull()) {
        painter.fillRect(rect, m_colorBackground);
    }
    else {
        painter.drawPixmap(rect, m_pixmapBackground);
    }

    // 绘制文字
    QFont font = painter.font();
    font.setPixelSize(m_nFontSize);
    painter.setFont(font);
    painter.setPen(m_colorText);
    painter.drawText(rect, Qt::AlignCenter, m_strTitle);

    // 绘制按钮
    foreach (QtPixmapButton *btn, m_btns) {
        painter.drawPixmap(btn->rect(), btn->pixmap());
    }
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
