/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : dhtcollection.cpp ---
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "dhtcollection.h"
#include "skin.h"

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QRegExp>
#include <QTimer>

#define DHT_DEVICE_FILE "cat /sys/bus/iio/devices/iio:device1/in_temp_input"

DhtCollection::DhtCollection(QWidget *parent)
    : QtAnimationWidget(parent)
{
    m_nIndex = 0;

    // 初始化界面
    InitWidget();

    // 读取进程
    m_cmd = new QProcess(this);
    connect(m_cmd, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(SltProcessFinished(int,QProcess::ExitStatus)));

    m_timer = new QTimer(this);
    m_timer->setInterval(5000);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(StartCmd()));
    m_timer->start();
}

DhtCollection::~DhtCollection()
{
    if (m_cmd->state() != QProcess::NotRunning) {
        m_cmd->kill();
    }

    delete m_cmd;
    m_cmd = NULL;
}

void DhtCollection::InitWidget()
{
    m_widgetTitle= new QtWidgetTitleBar(this);
    m_widgetTitle->SetScalSize(Skin::m_nScreenWidth, 80);
    m_widgetTitle->SetBackground(Qt::transparent);
    m_widgetTitle->SetBtnHomePixmap(QPixmap(":/images/backlight/menu_icon.png"), QPixmap(":/images/backlight/menu_icon_pressed.png"));
    m_widgetTitle->setFont(QFont(Skin::m_strAppFontBold));
    m_widgetTitle->SetTitle(tr("温湿度采集"), "#ffffff", 32);
    connect(m_widgetTitle, SIGNAL(signalBackHome()), this, SIGNAL(signalBackHome()));

    m_stackedWidget = new QtStackedWidget(this);
    m_stackedWidget->setPressMove(true);
    connect(m_stackedWidget, SIGNAL(currentChanged(int)), this, SLOT(SltCurrentChanged(int)));
    m_stackedWidget->SetBackground(Qt::transparent);

    m_realData = new DisplayRealData(m_stackedWidget);
    m_recordData = new DisplayRecordData(m_stackedWidget);
    m_stackedWidget->addWidget(0, m_realData);
    m_stackedWidget->addWidget(1, m_recordData);

    QVBoxLayout *m_verLayoutAll = new QVBoxLayout(this);
    m_verLayoutAll->setContentsMargins(0, 0, 0, 0);
    m_verLayoutAll->setSpacing(0);
    m_verLayoutAll->addWidget(m_widgetTitle, 1);
    m_verLayoutAll->addStretch(5);
}

void DhtCollection::SltCurrentChanged(int index)
{
    if (index < 2 && index >= 0) {
        m_nIndex = index;
        this->update();
    }
}

// dht11 dht11: DHT11: 77 0 25 4
void DhtCollection::SltProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (QProcess::NormalExit == exitStatus) {
        QString strResult = m_cmd->readAll();
        QRegExp regExp("DHT11: ([0-9 ])");
        if (-1 != regExp.indexIn(strResult)) {
            qDebug() << "Read yes" << regExp.cap(1);
        } else {
//            qDebug() << "time out" << exitCode;
        }
    }

    Q_UNUSED(exitCode)
}

void DhtCollection::StartCmd()
{
#ifdef __arm__
    m_cmd->start(DHT_DEVICE_FILE);
#endif
}

void DhtCollection::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    // 设置放大倍数
    painter.scale(m_scaleX, m_scaleY);

    painter.drawPixmap(0, 0, QPixmap(":/images/dht/background.png"));
    QPixmap pixmap2Dots(":/images/dht/controls_2dots.png");
    QRect rectDots(333, 402, 133, 54);
    painter.drawPixmap(rectDots, pixmap2Dots);

    painter.drawPixmap(rectDots.left() + (m_nIndex + 1) * 35, rectDots.top() + 12,
                       QPixmap(":/images/dht/dot_indicator_selected.png"));
}

void DhtCollection::showEvent(QShowEvent *e)
{
    m_timer->start();
    QWidget::showEvent(e);
}

void DhtCollection::hideEvent(QHideEvent *e)
{
    m_timer->stop();
    QWidget::hideEvent(e);
}

void DhtCollection::resizeEvent(QResizeEvent *e)
{
    SetScaleValue();
    m_stackedWidget->setGeometry(0, 83 * m_scaleY, this->width(), 343 * m_scaleY);
    QWidget::resizeEvent(e);
}
