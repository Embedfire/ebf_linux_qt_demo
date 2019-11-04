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

#include <QTime>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

TimeFormatConf::TimeFormatConf(QWidget *parent) : QWidget(parent)
{
    m_timeFormat = new QtSwitchButton(this);
    m_timeFormat->setBackgroundColor(QColor("#02a7f0"));
    m_timeFormat->setHandleColor(QColor("#ffffff"));
    m_timeFormat->setChecked(!AppConfig::ReadSetting("Clock", "ap", false).toBool());
    connect(m_timeFormat, SIGNAL(buttonChecked(bool)), this, SLOT(SltSwitchBtnClicked(bool)));

    m_btnPrev = QtPixmapButton(QPixmap(":/images/calendar/ic_btn.png"), QPixmap(":/images/calendar/ic_btn_pre.png"));
    m_btnSure = QtPixmapButton(QPixmap(":/images/calendar/ic_btn.png"), QPixmap(":/images/calendar/ic_btn_pre.png"));
    m_btnNext = QtPixmapButton(QPixmap(":/images/calendar/ic_btn.png"), QPixmap(":/images/calendar/ic_btn_pre.png"));
}

TimeFormatConf::~TimeFormatConf()
{

}

void TimeFormatConf::SltSwitchBtnClicked(bool on)
{
    AppConfig::SaveSetting("Clock", "ap", !on);
    emit signalChangeApMode(on);
}

void TimeFormatConf::resizeEvent(QResizeEvent *e)
{
    int nW = m_btnSure.size().width();
    int nH = m_btnSure.size().height();
    QRect rect(this->width() / 2 - nW / 2, this->height() * 0.86 - nH / 2, nW, nH);
    m_btnSure.setRect(rect);

    QRect rectPrev = QRect(rect.left() - nW / 2 - rect.width(), rect.top(), rect.width(), rect.height());
    m_btnPrev.setRect(rectPrev);

    QRect rectNext = QRect(rect.right() + nW / 2, rect.top(), rect.width(), rect.height());
    m_btnNext.setRect(rectNext);

    m_rectCenter = QRect(this->width() / 4, this->height() / 4 - 55, this->width() / 2, 80);
    m_timeFormat->move(m_rectCenter.right() - 80, m_rectCenter.center().y() - m_timeFormat->height() / 2);
    QWidget::resizeEvent(e);
}

void TimeFormatConf::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);

    // 绘制提示
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#ffffff"));
    painter.drawRoundedRect(m_rectCenter, 10, 10);
    painter.setPen(QColor("#333333"));
    QFont font = this->font();
    font.setPixelSize(24);
    painter.setFont(font);
    painter.drawText(m_rectCenter.left() + 20, m_rectCenter.top(), m_rectCenter.width(), m_rectCenter.height(),
                     Qt::AlignVCenter, QString("使用24小时制"));

    // 绘制底部确定按钮
    drawButton(&painter);
}

void TimeFormatConf::drawButton(QPainter *painter)
{
    painter->save();
    QFont font(this->font());
    font.setPixelSize(30);
    painter->setFont(font);
    painter->setPen(QColor("#ffffff"));

    painter->drawPixmap(m_btnPrev.rect(), m_btnPrev.pixmap());
    painter->drawText(m_btnPrev.rect(), Qt::AlignCenter, QString("上一步"));

    painter->drawPixmap(m_btnSure.rect(), m_btnSure.pixmap());
    painter->drawText(m_btnSure.rect(), Qt::AlignCenter, QString("完成"));

    painter->drawPixmap(m_btnNext.rect(), m_btnNext.pixmap());
    painter->drawText(m_btnNext.rect(), Qt::AlignCenter, QString("下一步"));
    painter->restore();
}

QSize TimeFormatConf::sizeHint() const
{
    return QSize(800, 390);
}

void TimeFormatConf::mousePressEvent(QMouseEvent *e)
{
    if (m_btnPrev.rect().contains(e->pos())) {
        m_btnPrev.setPressed(true);
        this->update();
        return;
    }

    if (m_btnSure.rect().contains(e->pos())) {
        m_btnSure.setPressed(true);
        this->update();
        return;
    }

    if (m_btnNext.rect().contains(e->pos())) {
        m_btnNext.setPressed(true);
        this->update();
        return;
    }
}

void TimeFormatConf::mouseReleaseEvent(QMouseEvent *e)
{
    if (m_btnPrev.isPressed()) {
        m_btnPrev.setPressed(false);
        this->update();
        if (m_btnPrev.rect().contains(e->pos())) {
            emit signalChangePage(2, 2);
        }
    }

    if (m_btnSure.isPressed()) {
        m_btnSure.setPressed(false);
        this->update();
        if (m_btnSure.rect().contains(e->pos())) {
            emit signalChangePage(0, 2);
        }
    }

    if (m_btnNext.isPressed()) {
        m_btnNext.setPressed(false);
        this->update();
        if (m_btnNext.rect().contains(e->pos())) {
            emit signalChangePage(4, 1);
        }
    }
}
