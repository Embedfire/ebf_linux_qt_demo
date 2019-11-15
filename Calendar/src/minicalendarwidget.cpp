/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : minicalendarwidget.cpp --- MiniCalendarWidget
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/6
*******************************************************************/
#include "minicalendarwidget.h"
#include "skin.h"

#include <QDate>
#include <QPainter>
#include <QDebug>

#include <QMouseEvent>

MiniCalendarWidget::MiniCalendarWidget(QWidget *parent) : QtWidgetBase(parent)
{
    m_nBaseWidth = 220;
    m_nBaseHeight = 240;
    m_pixmapBackground = QPixmap(":/images/calendar/settings_calendar.png");
}

MiniCalendarWidget::~MiniCalendarWidget()
{

}

void MiniCalendarWidget::SetBackground(const QPixmap &pixmap)
{
    if (pixmap.isNull()) return;
    m_pixmapBackground = pixmap;
    this->update();
}

QString MiniCalendarWidget::getCurrendDayOfWeek()
{
    QDate date = QDate::currentDate();
    int nWeek = date.dayOfWeek();

    QString strWeek = "";
    if (1 == nWeek) strWeek = tr("星期一");
    else if (2 == nWeek) strWeek = tr("星期二");
    else if (3 == nWeek) strWeek = tr("星期三");
    else if (4 == nWeek) strWeek = tr("星期四");
    else if (5 == nWeek) strWeek = tr("星期五");
    else if (6 == nWeek) strWeek = tr("星期六");
    else if (7 == nWeek) strWeek = tr("星期日");

    return strWeek;
}

void MiniCalendarWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.scale(m_scaleX, m_scaleY);
    painter.drawPixmap(0, 0, m_pixmapBackground);

    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(28);
    painter.setFont(font);
    painter.setPen("#ffffff");
    painter.drawText(0, 30, m_nBaseWidth, 50, Qt::AlignCenter, getCurrendDayOfWeek());

    font.setPixelSize(78);
    painter.setFont(font);
    painter.setPen("#333333");
    painter.drawText(0, 75, m_nBaseWidth, 80, Qt::AlignCenter, QDate::currentDate().toString("dd"));

    font.setPixelSize(32);
    painter.setFont(font);
    painter.drawText(0, 160, m_nBaseWidth, 40, Qt::AlignCenter, QDate::currentDate().toString(tr("M月")));
}

void MiniCalendarWidget::mousePressEvent(QMouseEvent *e)
{
    emit changeCurrentPage(1, 1);
    QWidget::mousePressEvent(e);
}
