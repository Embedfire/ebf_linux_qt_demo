/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : citymanagerwidget.cpp --- CityManagerWidget
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "citymanagerwidget.h"
#include "skin.h"
#include "citybook.h"

#include <QPushButton>
#include <QDebug>
#include <QBoxLayout>

CityManagerWidget::CityManagerWidget(QWidget *parent) : QtAnimationWidget(parent)
{
    this->SetBackground(QPixmap(":/images/weather/city_bg.png"));
    m_strCurrentCity = "test";

    InitWidget();
}

CityManagerWidget::~CityManagerWidget()
{
    delete m_listCitys;
    m_listCitys = NULL;
}

void CityManagerWidget::InitWidget()
{
    QtWidgetTitleBar *widgetTitle = new QtWidgetTitleBar(this);
    widgetTitle->SetBackground(Qt::transparent);
    widgetTitle->setFixedHeight(80);
    widgetTitle->SetTitle(tr("城市选择"), "#ffffff", 32);

    QHBoxLayout *horLayout = new QHBoxLayout(widgetTitle);
    horLayout->setContentsMargins(10, 0, 0, 0);
    horLayout->setSpacing(10);

    QPushButton *btnBack = new QPushButton(this);
    connect(btnBack, SIGNAL(clicked(bool)), this, SIGNAL(signalBackHome()));

    horLayout->addWidget(btnBack);
    btnBack->setFixedSize(30, 30);
    btnBack->setStyleSheet(QString("QPushButton {border-image: url(:/images/weather/ic_back.png);}"
                                   "QPushButton:pressed {border-image: url(:/images/weather/ic_back_pre.png);}"));
    horLayout->addStretch();

    QWidget *widgetInput = new QWidget(this);
    widgetInput->setObjectName("widgetInput");
    widgetInput->setStyleSheet(QString("QWidget#widgetInput{border-radius:1px solid #333333;"
                                       "border-radius: 10px;"
                                       "background-color: #ffffff;}"));
    QHBoxLayout *horLayoutInput = new QHBoxLayout(widgetInput);
    horLayoutInput->setContentsMargins(10, 5, 5, 10);
    horLayoutInput->setSpacing(10);


    m_lineEdit = new QLineEdit(widgetInput);
    m_lineEdit->setContextMenuPolicy(Qt::NoContextMenu);
    connect(m_lineEdit, SIGNAL(returnPressed()), this, SLOT(SltSearcCitys()));
    m_lineEdit->setMinimumHeight(30);
    m_lineEdit->setStyleSheet(QString("QLineEdit{border-radius:none; border-radius: 10px;"
                                      "background-color: #ffffff; font-family: '%1'; "
                                      "color: #333333; font: 16px;}").arg(Skin::m_strAppFontNormal));

    QPushButton *btnSearch = new QPushButton(this);
    btnSearch->setFixedSize(67, 35);
    btnSearch->setText(tr("搜索"));
    connect(btnSearch, SIGNAL(clicked(bool)), this, SLOT(SltSearcCitys()));
    btnSearch->setStyleSheet(QString("QPushButton { border: none; border-radius: 10px; color: #ffffff;"
                                     "background-color: #169bd5;"
                                     "padding-top: 0px; font-family: '%1'; font: 18px;}"
                                     "QPushButton::pressed{padding-top: 2px;}").arg(Skin::m_strAppFontNormal));

    horLayoutInput->addWidget(m_lineEdit);
    horLayoutInput->addWidget(btnSearch);

    m_listCitys = new QtListWidget(this);
    m_listCitys->SetBackground(QColor("#fafafa"));
    m_listCitys->setVisible(false);
    m_listCitys->setMinimumHeight(140);
    m_listCitys->setFont(QFont(Skin::m_strAppFontNormal));
    m_listCitys->setHoriazontal(false);
    m_listCitys->setAlignment(Qt::AlignVCenter);
    m_listCitys->setItemSize(40);
    connect(m_listCitys, SIGNAL(currentItemClicked(QtListWidgetItem*)), this, SLOT(SltCitySelected(QtListWidgetItem*)));

    QVBoxLayout *verLayoutList = new QVBoxLayout();
    verLayoutList->setContentsMargins(0, 0, 0, 0);
    verLayoutList->setSpacing(5);
    verLayoutList->addWidget(widgetInput);
    verLayoutList->addWidget(m_listCitys);

    QVBoxLayout *verLayoutAll = new QVBoxLayout(this);
    verLayoutAll->setContentsMargins(0, 0, 0, 0);
    verLayoutAll->setSpacing(20);
    verLayoutAll->addWidget(widgetTitle);
    verLayoutAll->addLayout(verLayoutList);
    verLayoutAll->addStretch();
}

void CityManagerWidget::SltSearcCitys()
{
    if (m_strCurrentCity == m_lineEdit->text()) return;

    m_strCurrentCity = m_lineEdit->text();
    QStringList strCitys = CityBook::Instance()->searchCitys(m_strCurrentCity);
    QMap<int, QtListWidgetItem*> mapCitys;
    for (int i = 0; i < strCitys.size(); i++) {
        mapCitys.insert(i, new QtListWidgetItem(i, strCitys.at(i)));
    }
    m_listCitys->SetItems(mapCitys);

    int nSize = mapCitys.size();
    if (nSize > 9) {
        m_listCitys->setFixedHeight(9 * 40);
    }
    else if (nSize > 3 && nSize < 10) {
        m_listCitys->setFixedHeight(nSize * 40 + 20);
    }
}

void CityManagerWidget::SltCitySelected(QtListWidgetItem *item)
{
    emit signalCityChanged(item->m_strText);
}

QSize CityManagerWidget::sizeHint() const
{
    return QSize(800, 480);
}

