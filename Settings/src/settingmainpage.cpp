/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : settingmainpage.cpp --- SettingMainPage
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "settingmainpage.h"
#include "qtswitchbutton.h"
#include "appconfig.h"
#include "clickedwidget.h"
#include "skin.h"

#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <QDebug>
#include <QApplication>
#include <QCursor>
#include <QPainter>

/////////////////////////////////////////////////////////////////////////////
SettingMainPage::SettingMainPage(QWidget *parent) : QtListWidget(parent)
{
    m_backgroundColor = Qt::transparent;
    m_nItemSize = 45;
    m_bHorizontal = false;
    m_nBaseWidth = Skin::m_nScreenWidth;
    m_nBaseHeight = 400;

    InitWidget();
    connect(this, SIGNAL(currentIndexClicked(int)), this, SLOT(SltCurrentIndexClicked(int)));
}

SettingMainPage::~SettingMainPage()
{

}

void SettingMainPage::SltSwitchClicked(bool on)
{
    AppConfig::SaveSetting("System", "mouse", on);
    if (AppConfig::m_bMouseInsert) return;
    emit signalChangeCursorShape(on ? Qt::ArrowCursor : Qt::BlankCursor);
}

void SettingMainPage::InitWidget()
{
    m_btnSwitch = new QtSwitchButton(this);
    m_btnSwitch->setBackgroundColor(QColor("#0199ff"));
    m_btnSwitch->setHandleColor(QColor("#ffffff"));
    m_btnSwitch->setChecked(AppConfig::ReadSetting("System", "mouse", true).toBool());
    connect(m_btnSwitch, SIGNAL(buttonChecked(bool)), this, SLOT(SltSwitchClicked(bool)));

    int index = 1;
    m_listItems.insert(index, new QtListWidgetItem(index, tr("关于开发板"),  tr(""), QPixmap(":/images/setting/ic_next.png"))); index++;
    m_listItems.insert(index, new QtListWidgetItem(index, tr("显示/隐藏鼠标"),  tr(""), QPixmap())); index++;
    m_listItems.insert(index, new QtListWidgetItem(index, tr("背光调节"),  tr(""), QPixmap(":/images/setting/ic_next.png"))); index++;
    m_listItems.insert(index, new QtListWidgetItem(index, tr("时间设置"),  tr(""), QPixmap(":/images/setting/ic_next.png"))); index++;
    m_listItems.insert(index, new QtListWidgetItem(index, tr("日期设置"),  tr(""), QPixmap(":/images/setting/ic_next.png"))); index++;
    m_listItems.insert(index, new QtListWidgetItem(index, tr("语言设置(重启生效)"),  tr(""), QPixmap(":/images/setting/ic_next.png")));
}

void SettingMainPage::SltCurrentIndexClicked(int index)
{
    if (2 == index) {
        m_btnSwitch->setChecked(!m_btnSwitch->isChecked());
    } else {
        emit signalChangePage(index < 2 ? 1 : (index - 1));
    }
}

void SettingMainPage::resizeEvent(QResizeEvent *e)
{
    m_nItemShowCnt = m_bHorizontal ? ((m_nBaseWidth - m_nMargin * 2) / m_nItemSize) :
                                     ((m_nBaseHeight - m_nMargin * 2) / m_nItemSize);
    SetScaleValue();
    m_btnSwitch->setFixedSize(60 * m_scaleX, 30 * m_scaleY);
    QWidget::resizeEvent(e);
}

void SettingMainPage::drawItemInfo(QPainter *painter, QtListWidgetItem *item)
{
    painter->save();
    painter->setPen(QColor("#797979"));
    painter->drawLine(QPoint(item->m_rect.left() - m_nMargin, item->m_rect.bottom()),
                      QPoint(item->m_rect.right() + m_nMargin, item->m_rect.bottom()));

    QRect rect(item->m_rect.left() + 20, item->m_rect.top(), item->m_rect.width() - 40, item->m_rect.height());
    QFont font(Skin::m_strAppFontNormal);
    font.setPixelSize(24);
    painter->setFont(font);
    painter->setPen(QColor("#ffffff"));
    painter->drawText(rect, Qt::AlignVCenter, item->m_strText);

    QPixmap pixmap = item->m_pixmapIcon;
    if (pixmap.isNull()) {
        int nW = painter->fontMetrics().width(item->m_strBaseName);
        painter->drawText(QRect(m_nBaseWidth - nW - 20, rect.top(), nW, rect.height()), Qt::AlignCenter, item->m_strBaseName);
    } else {
        painter->drawPixmap(m_nBaseWidth - pixmap.width() - 20, rect.top() + (rect.height() - pixmap.height()) / 2, pixmap);
    }

    if (2 == item->m_nId) {
        int nX = (item->m_rect.right() - 60 - m_nMargin) * m_scaleX;
        int nY = (item->m_rect.height() - 30) / 2 + item->m_rect.top();
        m_btnSwitch->move(nX, nY * m_scaleY);
    }

    painter->restore();
}


