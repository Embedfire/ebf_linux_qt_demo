/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : dateconfigwidget.cpp --- DateConfigWidget
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "dateconfigwidget.h"
#include "skin.h"

#include <QPainter>
#include <QProcess>
#include <QMouseEvent>
#include <QDebug>
#include <QDate>

DateConfigWidget::DateConfigWidget(QWidget *parent) : QtWidgetBase(parent)
{
    m_nBaseWidth = Skin::m_nScreenWidth;
    m_nBaseHeight = 400;

    m_timeConfig = new QtDateTimeConfig(this);
    m_timeConfig->SetFont(Skin::m_strAppFontNormal);
    m_timeConfig->setConfigFormat(QtDateTimeConfig::DateFormat);
    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(24);
    m_timeConfig->setFont(font);

    m_btns.insert(0, new QtPixmapButton(0, QRect(68, 308, 166, 70), QPixmap(":/images/calendar/ic_btn.png"), QPixmap(":/images/calendar/ic_btn_pre.png")));
    m_btns.insert(1, new QtPixmapButton(1, QRect(317, 308, 166, 70), QPixmap(":/images/calendar/ic_btn.png"), QPixmap(":/images/calendar/ic_btn_pre.png")));

    m_btns.value(0)->setText(tr("上一步"));
    m_btns.value(1)->setText(tr("确  定"));
    connect(this, SIGNAL(signalBtnClicked(int)), this, SLOT(SltBtnClicked(int)));
}

DateConfigWidget::~DateConfigWidget()
{

}

void DateConfigWidget::SltBtnClicked(int index)
{
    if (0 == index) {
        emit signalChangePage(4, 2);
    } else if (1 == index) {
        setSystemDate();
    }
}

void DateConfigWidget::setSystemDate()
{
    QDate date = m_timeConfig->getCurrentDate();
    QTime time = QTime::currentTime();
    QString strDatetime = date.toString("yyyy-MM-dd ")  + time.toString("hh:mm:ss");
#ifdef __arm__
    QProcess cmd;
    cmd.start("date", QStringList() << "-s" << strDatetime);
    cmd.waitForFinished(500);
    cmd.start("hwclock -w");
    cmd.waitForFinished(500);
    cmd.kill();
#endif
    qDebug() << "date -s" << strDatetime;
    emit signalChangePage(0, 2);
}

void DateConfigWidget::resizeEvent(QResizeEvent *e)
{
    SetScaleValue();
    m_timeConfig->resize(375 * m_scaleX, 280 * m_scaleY);
    m_timeConfig->move((this->width() - m_timeConfig->width()) / 2, 20 * m_scaleY);
    QWidget::resizeEvent(e);
}

void DateConfigWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
    painter.scale(m_scaleX, m_scaleY);

    // 绘制底部确定按钮
    drawButton(&painter);
}

void DateConfigWidget::drawButton(QPainter *painter)
{
    painter->save();
    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(30);
    painter->setFont(font);
    painter->setPen(QColor("#ffffff"));
    foreach (QtPixmapButton *btn, m_btns) {
        painter->drawPixmap(btn->rect(), btn->pixmap());
        painter->drawText(btn->rect(), Qt::AlignCenter, btn->text());
    }
    painter->restore();
}
