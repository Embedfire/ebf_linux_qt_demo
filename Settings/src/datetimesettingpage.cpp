/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : timesettingpage.cpp --- TimeSettingPage
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "datetimesettingpage.h"
#include "skin.h"

#include <QPainter>
#include <QDateTime>
#include <QProcess>
#include <QBoxLayout>
#include <QPushButton>
#include <QMouseEvent>

#include <QDebug>

DateTimeSettingPage::DateTimeSettingPage(QWidget *parent,
                                         QtDateTimeConfig::ConfigFromat format) :
    QtWidgetBase(parent)
{
    m_nBaseWidth = Skin::m_nScreenWidth;
    m_nBaseHeight = 400;

    m_timeConfig = new QtDateTimeConfig(this);
    m_timeConfig->SetFont(Skin::m_strAppFontNormal);
    m_timeConfig->setConfigFormat(format);
    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(24);
    m_timeConfig->setFont(font);

    m_btnOk = new QtPixmapButton(0, QRect(317, 320, 166, 70), QPixmap(":/images/calendar/ic_btn.png"), QPixmap(":/images/calendar/ic_btn_pre.png"));
}

DateTimeSettingPage::~DateTimeSettingPage()
{
    delete m_btnOk;
    m_btnOk = NULL;
}

void DateTimeSettingPage::SetSystemDatetime()
{
    if (QtDateTimeConfig::TimeFormat == m_timeConfig->getFormat()) {
#ifdef __arm__
        QTime time = m_timeConfig->getCurrentTime();
        QDate date = QDate::currentDate();
        QString strDatetime = date.toString("yyyy-MM-dd ")  + time.toString("hh:mm:ss");

        QProcess cmd;
        cmd.start("date", QStringList() << "-s" << strDatetime);
        cmd.waitForFinished(500);
        cmd.execute("hwclock -w");
        cmd.waitForFinished(500);
#endif
    }
    else {
#ifdef __arm__
        QDate date = m_timeConfig->getCurrentDate();
        QTime time = QTime::currentTime();
        QString strDatetime = date.toString("yyyy-MM-dd ")  + time.toString("hh:mm:ss");

        QProcess cmd;
        cmd.start("date", QStringList() << "-s" << strDatetime);
        cmd.waitForFinished(500);
        cmd.execute("hwclock -w");
        cmd.waitForFinished(500);
#endif
    }

    emit signalFinished();
}

void DateTimeSettingPage::resizeEvent(QResizeEvent *e)
{
    SetScaleValue();
    m_timeConfig->resize(375 * m_scaleX, 280 * m_scaleY);
    m_timeConfig->move((this->width() - m_timeConfig->width()) / 2, 20 * m_scaleY);
    QWidget::resizeEvent(e);
}

void DateTimeSettingPage::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.scale(m_scaleX, m_scaleY);
    painter.drawPixmap(m_btnOk->rect(), m_btnOk->pixmap());
    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(30);
    painter.setFont(font);
    painter.setPen(QColor("#ffffff"));
    painter.drawText(m_btnOk->rect(), Qt::AlignCenter, tr("确定"));
}

void DateTimeSettingPage::mousePressEvent(QMouseEvent *e)
{
    QRect rect;
    ScaleRect(rect, m_btnOk->rect());
    if (rect.contains(e->pos())) {
        m_btnOk->setPressed(true);
        this->update();
    }
}

void DateTimeSettingPage::mouseReleaseEvent(QMouseEvent *e)
{
    if (m_btnOk->isPressed()) {
        m_btnOk->setPressed(false);
        this->update();

        QRect rect;
        ScaleRect(rect, m_btnOk->rect());
        if (rect.contains(e->pos())) {
            SetSystemDatetime();
        }
    }
}
