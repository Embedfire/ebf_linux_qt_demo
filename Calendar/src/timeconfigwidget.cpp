/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : timeconfigwidget.cpp --- TimeConfigWidget
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "timeconfigwidget.h"
#include "skin.h"

#include <QPainter>
#include <QProcess>
#include <QMouseEvent>
#include <QDebug>
#include <QTime>

TimeConfigWidget::TimeConfigWidget(QWidget *parent) : QWidget(parent)
{
    m_btnPrev = QtPixmapButton(QPixmap(":/images/calendar/ic_btn.png"), QPixmap(":/images/calendar/ic_btn_pre.png"));
    m_btnSure = QtPixmapButton(QPixmap(":/images/calendar/ic_btn.png"), QPixmap(":/images/calendar/ic_btn_pre.png"));
    m_btnNext = QtPixmapButton(QPixmap(":/images/calendar/ic_btn.png"), QPixmap(":/images/calendar/ic_btn_pre.png"));

    m_timeConfig = new QtDateTimeConfig(this);
    m_timeConfig->SetFont(Skin::m_strAppFontNormal);
    m_timeConfig->setConfigFormat(QtDateTimeConfig::TimeFormat);
    m_timeConfig->setStyleSheet(QString("QWidget{background-color: #ffffff; border: none; border-radius: 10px;}"
                                        "QLabel{ font-family: '%1'; font: 24px; color: #333333; border-radius: 0px;}")
                                .arg(Skin::m_strAppFontBold));
}

TimeConfigWidget::~TimeConfigWidget()
{

}

void TimeConfigWidget::setSystemTime(bool bOk)
{
    QTime time = m_timeConfig->getCurrentTime();
#ifdef __arm__
    QProcess cmd;
    cmd.start("date", QStringList() << "-s" << time.toString("hh:mm:ss"));
    cmd.waitForFinished(500);
    cmd.execute("hwclock -w");
    cmd.waitForFinished(500);
#endif
    qDebug() << "date -s" << time.toString("hh:mm:ss");
    if (bOk) emit signalChangePage(0, 2);
}

void TimeConfigWidget::resizeEvent(QResizeEvent *e)
{
    int nW = m_btnSure.size().width();
    int nH = m_btnSure.size().height();

    QRect rect(this->width() / 2 - nW / 2, this->height() * 0.86 - nH / 2, nW, nH);
    m_btnSure.setRect(rect);

    QRect rectPrev = QRect(rect.left() - nW / 2 - rect.width(), rect.top(), rect.width(), rect.height());
    m_btnPrev.setRect(rectPrev);

    QRect rectNext = QRect(rect.right() + nW / 2, rect.top(), rect.width(), rect.height());
    m_btnNext.setRect(rectNext);

    m_timeConfig->setGeometry(this->width() / 4, 0, this->width() / 2, 280);
    QWidget::resizeEvent(e);
}

void TimeConfigWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);

    // 绘制底部确定按钮
    drawButton(&painter);
}

void TimeConfigWidget::drawButton(QPainter *painter)
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

QSize TimeConfigWidget::sizeHint() const
{
    return QSize(800, 390);
}

void TimeConfigWidget::mousePressEvent(QMouseEvent *e)
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

void TimeConfigWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if (m_btnPrev.isPressed()) {
        m_btnPrev.setPressed(false);
        this->update();
        if (m_btnPrev.rect().contains(e->pos())) {
            setSystemTime(false);
            emit signalChangePage(3, 2);
        }
    }

    if (m_btnSure.isPressed()) {
        m_btnSure.setPressed(false);
        this->update();
        if (m_btnSure.rect().contains(e->pos())) {
            setSystemTime(true);
        }
    }

    if (m_btnNext.isPressed()) {
        m_btnNext.setPressed(false);
        this->update();
        if (m_btnNext.rect().contains(e->pos())) {
            setSystemTime(false);
            emit signalChangePage(5, 1);
        }
    }
}
