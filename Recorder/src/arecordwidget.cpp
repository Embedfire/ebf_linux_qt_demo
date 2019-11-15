/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : arecordwidget.cpp --- ARecordWidget
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/10/10
*******************************************************************/
#include "arecordwidget.h"
#include "skin.h"

#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QDateTime>
#include <QDebug>

#define BUTTON_SIZE     40

ARecordWidget::ARecordWidget(QWidget *parent) : QtWidgetBase(parent)
{
    m_nBaseWidth = 300;
    m_nBaseHeight = Skin::m_nScreenHeight;

#ifdef __arm__
    m_wavObject = new WavObject(this);
#endif
    m_strRecordPath = qApp->applicationDirPath() + "/record/";

    m_bRecording = false;
    m_bPause = false;
    m_bEnable = true;
    m_nTimeCount = 0;

    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(SltBegingRecord()));
}

ARecordWidget::~ARecordWidget()
{

}

void ARecordWidget::setRecodeEnable(bool bOk)
{
    m_bEnable = bOk;
}

bool ARecordWidget::isRecording()
{
    return m_bRecording;
}

QString ARecordWidget::getTimeString()
{
    int nMin = m_nTimeCount / 60;
    int nSecond = m_nTimeCount % 60;
    return QString("%1:%2").arg(nMin, 2, 10, QChar('0')).arg(nSecond, 2, 10, QChar('0'));
}

void ARecordWidget::StartRecording()
{
    m_bRecording = true;
#ifdef __arm__
    QString strFile = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    strFile = m_strRecordPath + strFile;
    strFile.append(".wav");
    m_timer->start();
    // 开始录音
    m_wavObject->startTest(WAV_RECORD, strFile);
#endif
    m_nTimeCount = 0;
    m_timer->start();
    this->update();
}

void ARecordWidget::StopRecording()
{
    m_bRecording = false;
#ifdef __arm__
    QString strFile = m_wavObject->stopTest();
    emit signalRecordFile(strFile);
#endif

    StopTimer();
}

void ARecordWidget::PauseRecording()
{
    m_bPause = !m_bPause;
    if (m_bPause && m_timer->isActive()) {
        m_timer->stop();
    } else {
        m_timer->start();
    }

#ifdef __arm__
    m_wavObject->pause();
#endif
}

void ARecordWidget::SltBegingRecord()
{
    m_nTimeCount ++;
    this->update();
}

void ARecordWidget::StopTimer()
{
    if (m_timer->isActive()) {
        m_timer->stop();
    }

    m_nTimeCount = 0;
    this->update();
}

void ARecordWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.scale(m_scaleX, m_scaleY);

    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(24);
    font.setBold(true);
    painter.setFont(font);
    int nH = painter.fontMetrics().height();
    painter.setPen(QColor("#333333"));
    QRect rect(5, 120 - nH, 300, nH);
    painter.drawText(rect, Qt::AlignCenter, m_bRecording ? tr("正在录音") : tr("录音机"));

    font.setPixelSize(32);
    painter.setFont(font);
    nH = painter.fontMetrics().height();
    rect = QRect(5, 240 - nH, 300, nH);
    painter.drawText(rect, Qt::AlignCenter, getTimeString());

    // 绘制按钮
    drawButtons(&painter);
}

void ARecordWidget::drawButtons(QPainter *painter)
{
    painter->save();
    int nY = 360 - BUTTON_SIZE;
    int nX = 80;
    m_rectStop = QRect(nX, nY, BUTTON_SIZE, BUTTON_SIZE);
    painter->setPen(m_bRecording ? QColor("#ffffff") : QColor("#c8c8c8"));
    painter->drawArc(nX, nY, BUTTON_SIZE, BUTTON_SIZE, 0, 360 * 16);

    QRect rect(nX + 8, nY + 8, 24, 24);
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_bRecording ? QColor("#ffffff") : QColor("#c8c8c8"));
    painter->drawRoundedRect(rect, 8, 8);

    nX = 220 - BUTTON_SIZE;
    m_rectPause = QRect(nX, nY, BUTTON_SIZE, BUTTON_SIZE);
    painter->setPen(m_bRecording ? QColor("#ffffff") : QColor("#c8c8c8"));
    painter->drawArc(nX, nY, BUTTON_SIZE, BUTTON_SIZE, 0, 360 * 16);

    painter->setPen(Qt::NoPen);
    painter->setBrush(m_bRecording ? QColor("#ffffff") : QColor("#d91b1b"));
    if (!m_bRecording) {
        painter->drawEllipse(nX + 6, nY + 6, 28, 28);
    }
    else {
        painter->setPen(QPen(QColor("#ffffff"), 6));
        painter->drawLine(nX + 13, nY + 10, nX + 13, nY + 30);
        painter->drawLine(nX + 26, nY + 10, nX + 26, nY + 30);
    }

    painter->restore();
}

void ARecordWidget::mousePressEvent(QMouseEvent *e)
{
    if (!m_bEnable) return;

    QRect rect;
    ScaleRect(rect, m_rectPause);
    if (rect.contains(e->pos())) {
        if (m_bRecording) {
            PauseRecording();
        }
        else {
            StartRecording();
        }
    }

    ScaleRect(rect, m_rectStop);
    if (m_bRecording && rect.contains(e->pos())) {
        StopRecording();
    }
}
