/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : timeformatconf.cpp --- TimeFormatConf
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "timeformatconf.h"
#include "appconfig.h"
#include "skin.h"

#include <QTime>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

TimeFormatConf::TimeFormatConf(QWidget *parent) : QtWidgetBase(parent)
{
    m_nBaseWidth = Skin::m_nScreenWidth;
    m_nBaseHeight = 400;

    m_timeFormat = new QtSwitchButton(this);
    m_timeFormat->setBackgroundColor(QColor("#02a7f0"));
    m_timeFormat->setHandleColor(QColor("#ffffff"));
    m_timeFormat->setChecked(!AppConfig::ReadSetting("Clock", "ap", false).toBool());
    connect(m_timeFormat, SIGNAL(buttonChecked(bool)), this, SLOT(SltSwitchBtnClicked(bool)));

    m_rectCenter = QRect(200, 65, 400, 80);

    m_btns.insert(0, new QtPixmapButton(0, QRect(68, 308, 166, 70), QPixmap(":/images/calendar/ic_btn.png"), QPixmap(":/images/calendar/ic_btn_pre.png")));
    m_btns.insert(1, new QtPixmapButton(1, QRect(317, 308, 166, 70), QPixmap(":/images/calendar/ic_btn.png"), QPixmap(":/images/calendar/ic_btn_pre.png")));
    m_btns.insert(2, new QtPixmapButton(2, QRect(565, 308, 166, 70), QPixmap(":/images/calendar/ic_btn.png"), QPixmap(":/images/calendar/ic_btn_pre.png")));
    m_btns.value(0)->setText(tr("上一步"));
    m_btns.value(1)->setText(tr("确  定"));
    m_btns.value(2)->setText(tr("下一步"));

    connect(this, SIGNAL(signalBtnClicked(int)), this, SLOT(SltBtnClicked(int)));
}

TimeFormatConf::~TimeFormatConf()
{

}

void TimeFormatConf::SltSwitchBtnClicked(bool on)
{
    AppConfig::SaveSetting("Clock", "ap", !on);
    emit signalChangeApMode(on);
}

void TimeFormatConf::SltBtnClicked(int index)
{
    if (0 == index) {
        emit signalChangePage(2, 2);
    } else if (1 == index) {
        emit signalChangePage(0, 2);
    } else if (2 == index) {
        emit signalChangePage(4, 1);
    }
}

void TimeFormatConf::resizeEvent(QResizeEvent *e)
{
    SetScaleValue();
    m_timeFormat->resize(60 * m_scaleX, 30 * m_scaleY);
    m_timeFormat->move(520 * m_scaleX, 90 * m_scaleY);
    QWidget::resizeEvent(e);
}

void TimeFormatConf::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
    painter.scale(m_scaleX, m_scaleY);

    // 绘制提示
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#ffffff"));
    painter.drawRoundedRect(m_rectCenter, 10, 10);
    painter.setPen(QColor("#333333"));

    QFont font(Skin::m_strAppFontNormal);
    font.setPixelSize(24);
    painter.setFont(font);
    painter.drawText(m_rectCenter.left() + 20, m_rectCenter.top(), m_rectCenter.width(), m_rectCenter.height(),
                     Qt::AlignVCenter, tr("使用24小时制"));

    // 绘制底部确定按钮
    drawButton(&painter);
}

void TimeFormatConf::drawButton(QPainter *painter)
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

