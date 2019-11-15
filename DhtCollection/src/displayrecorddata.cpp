/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : displayrecorddata.cpp --- DisplayRecordData
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/2
*******************************************************************/
#include "displayrecorddata.h"
#include "skin.h"
#include <QPainter>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QButtonGroup>

DisplayRecordData::DisplayRecordData(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    InitWidget();
}

DisplayRecordData::~DisplayRecordData()
{

}

void DisplayRecordData::InitWidget()
{
    QWidget *widgetBtn = new QWidget(this);
    widgetBtn->setObjectName("widgetBtn");
    widgetBtn->setFixedSize(66, 155);
    widgetBtn->setStyleSheet(QString("#widgetBtn {background-color: #03303c; border: none; border-radius: 33px;}"
                                     "QPushButton {font-family: '%1';font: bold 24px; color: #ffffff;border: none; "
                                     "border-radius: 30px;background-color: none;}"
                                     "QPushButton:checked{background-color: #2698f8;}").arg(Skin::m_strAppFontNormal));

    QVBoxLayout *verLayoutBtns = new QVBoxLayout(widgetBtn);
    verLayoutBtns->setContentsMargins(3, 3, 3, 3);
    QButtonGroup *btnGroup = new QButtonGroup(this);
    QPushButton  *btnTemp = new QPushButton(widgetBtn);
    btnGroup->addButton(btnTemp, 0);
    btnTemp->setCheckable(true);
    btnTemp->setChecked(true);
    btnTemp->setText(tr("温度"));
    btnTemp->setFixedSize(60, 60);
    verLayoutBtns->addWidget(btnTemp);
    verLayoutBtns->addStretch();

    QPushButton  *btnHumidity = new QPushButton(widgetBtn);
    btnGroup->addButton(btnHumidity, 1);
    btnHumidity->setCheckable(true);
    btnHumidity->setText(tr("湿度"));
    btnHumidity->setFixedSize(60, 60);
    verLayoutBtns->addWidget(btnHumidity);
    connect(btnGroup, SIGNAL(buttonClicked(int)), this, SLOT(SltChangePage(int)));

    m_stackedWidget = new QtStackedWidget(this);
    m_stackedWidget->SetBackground(Qt::transparent);
    m_stackedWidget->setPressMove(false);

    m_customPlotTemp = new QtCustomPlot(m_stackedWidget);
    m_customPlotTemp->setBackgroundColor(Qt::transparent);
    m_customPlotTemp->setYStep(6);
    m_customPlotTemp->setMaxValue(60);
    m_customPlotTemp->StartTest();

    m_customPlotHumidity = new QtCustomPlot(m_stackedWidget);
    m_customPlotHumidity->setBackgroundColor(Qt::transparent);
    m_customPlotHumidity->setLabels(tr("时间/S"), tr("湿度/%"));
    m_customPlotHumidity->StartTest();

    m_stackedWidget->addWidget(0, m_customPlotTemp);
    m_stackedWidget->addWidget(1, m_customPlotHumidity);

    QHBoxLayout *horLayoutALL = new QHBoxLayout(this);
    horLayoutALL->setContentsMargins(10, 5, 10, 5);
    horLayoutALL->setSpacing(30);
    horLayoutALL->addWidget(widgetBtn);
    horLayoutALL->addWidget(m_stackedWidget, 1);
}

void DisplayRecordData::SltChangePage(int index)
{
    if (index == m_stackedWidget->currentIndex()) return;

    if (0 == index) {
        m_stackedWidget->setPrevPage(QtStackedWidget::DownDirection);
    } else {
        m_stackedWidget->setNextPage(QtStackedWidget::UpDirection);
    }
}

void DisplayRecordData::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), Qt::transparent);
}

