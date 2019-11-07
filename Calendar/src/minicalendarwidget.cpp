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

MiniCalendarWidget::MiniCalendarWidget(QWidget *parent) : QWidget(parent)
{
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

    QString strWeek = "星期";
    switch (nWeek) {
    case 1: strWeek += "一"; break;
    case 2: strWeek += "二"; break;
    case 3: strWeek += "三"; break;
    case 4: strWeek += "四"; break;
    case 5: strWeek += "五"; break;
    case 6: strWeek += "六"; break;
    case 7: strWeek += "日"; break;
    default:
        break;
    }

    return strWeek;
}

QSize MiniCalendarWidget::sizeHint() const
{
    return QSize(257, 281);
}

void MiniCalendarWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawPixmap(this->rect(), m_pixmapBackground);

    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(28);
    painter.setFont(font);
    painter.setPen("#ffffff");
    painter.drawText(0, 30, this->width(), 50, Qt::AlignCenter, getCurrendDayOfWeek());

    font.setPixelSize(78);
    painter.setFont(font);
    painter.setPen("#333333");
    painter.drawText(0, 75, this->width(), 80, Qt::AlignCenter, QDate::currentDate().toString("dd"));

    font.setPixelSize(32);
    painter.setFont(font);
    painter.drawText(0, 160, this->width(), 40, Qt::AlignCenter, QDate::currentDate().toString("M月"));
}

void MiniCalendarWidget::mousePressEvent(QMouseEvent *e)
{
    emit changeCurrentPage(1, 1);
    QWidget::mousePressEvent(e);
}
