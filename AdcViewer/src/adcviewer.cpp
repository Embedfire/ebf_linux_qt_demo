/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : adcviewer.cpp ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/1
*******************************************************************/
#include "adcviewer.h"
#include "skin.h"
#include "boardlogowidget.h"
#include "circularprogressbar.h"

#include <QPainter>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>
#include <QDebug>
#include <QFile>

#define ADC_DEVICE "/sys/bus/iio/devices/iio:device0/in_voltage3_raw"

AdcViewer::AdcViewer(QWidget *parent) : QtAnimationWidget(parent)
{
    InitWidget();

    m_timer = new QTimer(this);
    m_timer->setInterval(200);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(SltTestValue()));
    m_timer->start();
}

AdcViewer::~AdcViewer()
{

}

void AdcViewer::InitWidget()
{
    QtWidgetTitleBar *widgetTitle = new QtWidgetTitleBar(this);
    widgetTitle->SetScalSize(Skin::m_nScreenWidth, 60);
    widgetTitle->SetBackground(Qt::transparent);
    widgetTitle->setFont(QFont(Skin::m_strAppFontNormal));
    widgetTitle->SetTitle(tr("ADC采集电压试验"), "#ffffff", 24);
    widgetTitle->SetBtnHomePixmap(QPixmap(":/images/backlight/menu_icon.png"), QPixmap(":/images/backlight/menu_icon_pressed.png"));
    connect(widgetTitle, SIGNAL(signalBackHome()), this, SIGNAL(signalBackHome()));

    m_adcValueDisplay = new CircularProgressBar(this);

    QVBoxLayout *verLayoutAll = new QVBoxLayout(this);
    verLayoutAll->addWidget(widgetTitle, 1);
    verLayoutAll->addStretch(7);
}

void AdcViewer::SltTestValue()
{
    int nValue = 0;
#ifdef __arm__
    QFile file(ADC_DEVICE);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "read failed!";
        return;
    }

    QString strValue = file.readAll();
    nValue = strValue.toInt();
    file.close();
#else
    nValue = qrand() % 4096;
#endif
    m_nAdcValue = nValue * 330 / 4096;
    m_adcValueDisplay->setCurrentValue(m_nAdcValue);
}

void AdcViewer::resizeEvent(QResizeEvent *e)
{
    m_scaleX = (this->width() * 1.0) / m_nBaseWidth;
    m_scaleY = (this->height() * 1.0) / m_nBaseHeight;

    m_adcValueDisplay->setGeometry(m_nBaseWidth * m_scaleX / 2, 100 * m_scaleY, 320 * m_scaleX, 320 * m_scaleY);
    QWidget::resizeEvent(e);
}

void AdcViewer::showEvent(QShowEvent *e)
{
    m_timer->start();
    QWidget::showEvent(e);
}

void AdcViewer::hideEvent(QHideEvent *e)
{
    m_timer->stop();
    QWidget::hideEvent(e);
}

void AdcViewer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    painter.scale(m_scaleX, m_scaleY);

    // 绘制背景
    painter.drawPixmap(0, 0, QPixmap(":/images/adc/adc_background.png"));

    // 绘制logo
    drawBoardLogo(&painter);

    // 绘制值
    drawValue(&painter);
}

void AdcViewer::drawBoardLogo(QPainter *painter)
{
    painter->save();
    int nY = 83;
    painter->drawPixmap(1, nY, QPixmap(":/images/adc/ic_board.png"));
    QPainterPath path;
    path.moveTo(45, 195 + nY);
    path.lineTo(221, 195 + nY);
    path.lineTo(221, 300 + nY);
    painter->setPen(QPen(QColor("#ffffff"), 2));
    painter->drawPath(path);

    QFont font(Skin::m_strAppFontNormal);
    font.setPixelSize(28);
    font.setBold(true);
    painter->setFont(font);
    int nH = painter->fontMetrics().height();
    painter->drawText(230, 300 + nY, tr("调节电压"));

    font.setPixelSize(22);
    painter->setFont(font);
    painter->drawText(230, 290 - nH + nY, tr("旋转电位器"));
    painter->restore();
}

void AdcViewer::drawValue(QPainter *painter)
{
    painter->save();
    QString strValue = tr("当前电压：%1V").arg(m_nAdcValue * 1.0 / 100, 0, 'f', 2, QChar('0'));
    QFont font(Skin::m_strAppFontNormal);
    font.setPixelSize(20);
    painter->setFont(font);
    int nH = painter->fontMetrics().height();
    painter->setPen(QColor("#ffffff"));

    QRect rect(m_nBaseWidth / 2, m_nBaseHeight - 60 - nH, 320, nH);
    painter->drawText(rect, Qt::AlignCenter, strValue);
    painter->restore();
}

