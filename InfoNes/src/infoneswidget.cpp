/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : infoneswidget.cpp ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/10/19
*******************************************************************/
#include "infoneswidget.h"
#include "skin.h"
#include "appconfig.h"
#include "infoneslistwidget.h"

#include <QApplication>
#include <QPushButton>
#include <QBoxLayout>
#include <QDebug>

InfoNesWidget::InfoNesWidget(QWidget *parent) : QtAnimationWidget(parent)
{
    this->SetBackground(QPixmap(":/images/infones/ic_background.png"));
    InitWidget();
}

InfoNesWidget::~InfoNesWidget()
{

}

void InfoNesWidget::InitWidget()
{
    QtWidgetTitleBar *m_widgetTitle = new QtWidgetTitleBar(this);
    m_widgetTitle->SetScalSize(Skin::m_nScreenWidth, 82);
    m_widgetTitle->SetBackground(Qt::transparent);
    m_widgetTitle->setFont(QFont(Skin::m_strAppFontBold));
    m_widgetTitle->SetTitle(tr("InfoNes 模拟器"), QColor("#ffffff"), 32);
    connect(m_widgetTitle, SIGNAL(signalBackHome()), this, SIGNAL(signalBackHome()));

    InfoNesListWidget *infoListWidget = new InfoNesListWidget(this);
    infoListWidget->LoadNesResource(qApp->applicationDirPath() + "/nes");
    connect(infoListWidget, SIGNAL(currentItemClicked(QtListWidgetItem*)), this, SLOT(SltItemClicked(QtListWidgetItem *)));

    // 全局布局
    QVBoxLayout *verLayoutAll = new QVBoxLayout(this);
    verLayoutAll->setContentsMargins(0, 0, 0, 0);
    verLayoutAll->setSpacing(10);
    verLayoutAll->addWidget(m_widgetTitle, 1);
    verLayoutAll->addWidget(infoListWidget, 5);

    m_gamePannel = new GameWidgetPannel(this);
    m_gamePannel->hide();
}

void InfoNesWidget::SltItemClicked(QtListWidgetItem *item)
{
    m_gamePannel->startGame(item->m_strPath);
}

void InfoNesWidget::resizeEvent(QResizeEvent *e)
{
    m_gamePannel->setGeometry(0, 0, this->width(), this->height());
    QWidget::resizeEvent(e);
}
