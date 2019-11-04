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
    this->SetBackground(QPixmap(":/images/adc/adc_background.png"));
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
    QtWidgetTitleBar *widgetTitle= new QtWidgetTitleBar(this);
    widgetTitle->setMinimumHeight(80);
    widgetTitle->SetBackground(Qt::transparent);
    widgetTitle->setFont(QFont(Skin::m_strAppFontNormal));
    widgetTitle->SetTitle("ADC采集电压试验", "#ffffff", 24);

    QPushButton *btnHome = new QPushButton(this);
    btnHome->setFixedSize(54, 54);
    QHBoxLayout *horLayoutTitle = new QHBoxLayout(widgetTitle);
    horLayoutTitle->setContentsMargins(10, 5, 10, 10);
    horLayoutTitle->addStretch();
    horLayoutTitle->addWidget(btnHome, 0, Qt::AlignTop);
    connect(btnHome, SIGNAL(clicked(bool)), this, SIGNAL(signalBackHome()));
    btnHome->setStyleSheet(QString("QPushButton {border-image: url(:/images/music/menu_icon.png);}"
                                   "QPushButton:pressed {border-image: url(:/images/music/menu_icon_pressed.png);}"));

    BoardLogoWidget *boardLogo = new BoardLogoWidget(this);

    QHBoxLayout *horLayoutCenter = new QHBoxLayout();
    horLayoutCenter->setContentsMargins(0, 0, 20, 0);
    horLayoutCenter->setSpacing(100);
    horLayoutCenter->addWidget(boardLogo, 1);

    QVBoxLayout *verLayoutValue = new QVBoxLayout();
    verLayoutValue->setContentsMargins(0, 0, 0, 0);
    verLayoutValue->setSpacing(0);
    verLayoutValue->addStretch();

    m_adcValueDisplay = new CircularProgressBar(this);
    m_adcValueDisplay->setMinimumSize(320, 280);
    connect(m_adcValueDisplay, SIGNAL(currentValueChanged(int)), this, SLOT(SltAdcValueChanged(int)));
    verLayoutValue->addWidget(m_adcValueDisplay);

    m_labelAdcValue = new QLabel(this);
    m_labelAdcValue->setText("当前电压：1.0V");
    m_labelAdcValue->setAlignment(Qt::AlignCenter);
    m_labelAdcValue->setStyleSheet(QString("QLabel {color: #ffffff; font-family: '%1'; font: bold 20px;}")
                                   .arg(Skin::m_strAppFontNormal));
    verLayoutValue->addWidget(m_labelAdcValue);
    verLayoutValue->addStretch();
    // 加入布局
    horLayoutCenter->addLayout(verLayoutValue, 1);

    m_verLayoutAll = new QVBoxLayout(this);
    m_verLayoutAll->setSpacing(10);
    m_verLayoutAll->addWidget(widgetTitle, 1);
    m_verLayoutAll->addLayout(horLayoutCenter, 5);
}

void AdcViewer::SltAdcValueChanged(int value)
{
    m_labelAdcValue->setText(QString("当前电压：%1V").arg(value * 1.0 / 100, 0, 'f', 2, QChar('0')));
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
    int nTemp = nValue * 330 / 4096;
    m_adcValueDisplay->setCurrentValue(nTemp);
}

void AdcViewer::resizeEvent(QResizeEvent *e)
{
#ifdef BUILD_WITH_HDMI
    m_verLayoutAll->setContentsMargins(0, 0, 0, this->height() * 55 / Skin::m_nScreenHeight + 2);
#else
    m_verLayoutAll->setContentsMargins(0, 0, 0, 55);
#endif
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

