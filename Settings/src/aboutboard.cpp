/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : aboutboard.cpp --- AboutBoard
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "aboutboard.h"
#include "unit.h"
#include "skin.h"
#include "clickedwidget.h"

#include <QLabel>
#include <QBoxLayout>
#include <QPainter>
#include <QDebug>
#include <QFile>

#define FLASH_FILE_PART     4
#define FLASH_FILE_INFO     "/sys/class/mtd/mtd%1/size"
#ifndef FLASH_FILE_EMMC
#define FLASH_FILE_EMMC     "/sys/class/mmc_host/mmc1/mmc1:0001/block/mmcblk1/size"
#endif

AboutBoard::AboutBoard(QWidget *parent) : QtListWidget(parent)
{
    m_backgroundColor = Qt::transparent;
    m_nItemSize = 45;
    m_bHorizontal = false;
    m_nBaseWidth = Skin::m_nScreenWidth;
    m_nBaseHeight = 400;

    m_strNandSize = "";
    InitBoardInfo();
    InitWidget();
    connect(this, SIGNAL(currentIndexClicked(int)), this, SLOT(SltCurrentIndexClicked(int)));
}

AboutBoard::~AboutBoard()
{

}

// 512MB NAND / 8GB eMMC
void AboutBoard::InitBoardInfo()
{
#ifdef __arm__
    // emmc设备检测
    if (QFile::exists(FLASH_FILE_EMMC)) {
        m_strNandSize = "";
        return;
    }

    // nand容量读取
    quint32 usize, i;
    QString flash_file;
    for (i = 0; i < FLASH_FILE_PART; i++) {
        flash_file = QString(FLASH_FILE_INFO).arg(i);

        QFile file(flash_file);
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Read flash size failed";
            return;
        }

        QString strTemp = file.readAll();
        strTemp.remove("\\n");
        usize += strTemp.toULong();
        file.close();
    }

    usize /= (1024 * 1024);
    m_strNandSize = QString("%1MB NAND").arg(usize);

#endif
}

void AboutBoard::InitWidget()
{
    int index = 0;
    m_listItems.insert(index, new QtListWidgetItem(index, tr("硬件版本"),  tr("V1.0"), QPixmap())); index++;
    m_listItems.insert(index, new QtListWidgetItem(index, tr("开发板型号"),  tr("EBF6UL/6ULL S1 Pro"), QPixmap())); index++;
    m_strNandSize = m_strNandSize.isEmpty() ? tr("8GB eMMC") : m_strNandSize;
    m_listItems.insert(index, new QtListWidgetItem(index, tr("存储空间"),  m_strNandSize, QPixmap())); index++;
    m_listItems.insert(index, new QtListWidgetItem(index, tr("内存大小"),  tr("512MB"), QPixmap())); index++;
    m_listItems.insert(index, new QtListWidgetItem(index, tr("关于App"),  tr(""), QPixmap(":/images/setting/ic_next.png")));
}

void AboutBoard::SltCurrentIndexClicked(int index)
{
    if (4 == index) {
        emit signalChangePage(6);
    }
}

void AboutBoard::drawItemInfo(QPainter *painter, QtListWidgetItem *item)
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
    painter->restore();
}
