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
#include <QDebug>
#include <QFile>

#define FLASH_FILE_INFO     "/sys/class/mtd/mtd0/size"
#ifndef FLASH_FILE_EMMC
#define FLASH_FILE_EMMC     "/sys/class/mmc_host/mmc1/mmc1:0001/block/mmcblk1/size"
#endif

AboutBoard::AboutBoard(QWidget *parent) : QWidget(parent)
{
    m_strNandSize = "";
    InitBoardInfo();
    InitWidget();
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
    QFile file(FLASH_FILE_INFO);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Read flash size failed";
        return;
    }

    QString strTemp = file.readAll();
    strTemp.remove("\\n");
    quint32 usize = strTemp.toULong();
    usize /= (1024 * 1024);
    m_strNandSize = QString("%1MB NAND").arg(usize);
    file.close();
#endif
}

void AboutBoard::InitWidget()
{
    QVBoxLayout *verLayoutAll = new QVBoxLayout(this);
    verLayoutAll->setContentsMargins(20, 20, 0, 10);
    verLayoutAll->setSpacing(10);

    {
        QWidget *widget = new QWidget(this);
        widget->setObjectName("widgetItem");

        QHBoxLayout *horLayout = new QHBoxLayout(widget);
        horLayout->setContentsMargins(0, 0, 20, 10);

        horLayout->addWidget(new QLabel(tr("硬件版本"), widget));
        horLayout->addStretch();
        horLayout->addWidget(new QLabel(tr("V1.0"), widget));
        verLayoutAll->addWidget(widget);
    }

    {
        QWidget *widget = new QWidget(this);
        widget->setObjectName("widgetItem");

        QHBoxLayout *horLayout = new QHBoxLayout(widget);
        horLayout->setContentsMargins(0, 0, 20, 10);

        horLayout->addWidget(new QLabel(tr("开发板型号"), widget));
        horLayout->addStretch();
        horLayout->addWidget(new QLabel(tr("EBF6UL/6ULL S1 Pro"), widget));
        verLayoutAll->addWidget(widget);
    }

    {
        QWidget *widget = new QWidget(this);
        widget->setObjectName("widgetItem");

        QHBoxLayout *horLayout = new QHBoxLayout(widget);
        horLayout->setContentsMargins(0, 0, 20, 10);

        horLayout->addWidget(new QLabel(tr("存储空间"), widget));
        horLayout->addStretch();
        horLayout->addWidget(new QLabel(m_strNandSize.isEmpty() ? tr("8GB eMMC") : m_strNandSize, widget));
        verLayoutAll->addWidget(widget);
    }

    {
        QWidget *widget = new QWidget(this);
        widget->setObjectName("widgetItem");

        QHBoxLayout *horLayout = new QHBoxLayout(widget);
        horLayout->setContentsMargins(0, 0, 20, 10);

        horLayout->addWidget(new QLabel(tr("内存大小"), widget));
        horLayout->addStretch();
        horLayout->addWidget(new QLabel(tr("512MB"), widget));
        verLayoutAll->addWidget(widget);
    }

    ClickedWidget *widgetUpdate = new ClickedWidget(this);
    widgetUpdate->setIndex(5, tr("关于App"));
    connect(widgetUpdate, SIGNAL(signalClicked(int)), this, SIGNAL(signalChangePage(int)));
    verLayoutAll->addWidget(widgetUpdate);

    this->setStyleSheet(QString("QWidget#widgetItem{border: none; border-bottom: 1px solid #797979; background: none;}"
                                "QLabel{font-family: '%1'; font: 24px; color: #ffffff;}")
                        .arg(Skin::m_strAppFontNormal));
    verLayoutAll->addStretch();
}
