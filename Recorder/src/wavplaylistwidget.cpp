/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : wavplaylistwidget.cpp --- WavPlayListWidget
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "wavplaylistwidget.h"
#include "skin.h"

#include <QPainter>
#include <QDir>
#include <QFileInfo>

WavPlayListWidget::WavPlayListWidget(QWidget *parent) : QtListWidget(parent)
{
    m_nBaseWidth = 500;
    m_nBaseHeight = 300;

    m_bHorizontal = false;
    m_nItemSize = 37;
    m_backgroundColor = Qt::transparent;
    m_nCurrentIndex = 0;

    m_playList = new QMediaPlaylist(this);
    m_playList->setPlaybackMode(QMediaPlaylist::Loop);
    connect(m_playList, SIGNAL(currentIndexChanged(int)), this, SLOT(setCurrentIndex(int)));
    connect(this, SIGNAL(currentIndexClicked(int)), m_playList, SLOT(setCurrentIndex(int)));
}

WavPlayListWidget::~WavPlayListWidget()
{
    m_playList->clear();
}

void WavPlayListWidget::LoadLocalFiles(const QString &path)
{
    QDir dir(path);
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QFileInfoList list = dir.entryInfoList(QStringList() << "*.wav");
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        m_playList->addMedia(QUrl::fromLocalFile(fileInfo.absoluteFilePath()));
        m_listItems.insert(i, new QtListWidgetItem(i, fileInfo.fileName(), fileInfo.absoluteFilePath()));
    }

    m_playList->setCurrentIndex(0);
    this->update();
}

QMediaPlaylist *WavPlayListWidget::palyList()
{
    return m_playList;
}

// 录音完成
void WavPlayListWidget::SltAddWavFile(const QString &file)
{
    QFileInfo fileInfo(file);
    m_playList->addMedia(QUrl::fromLocalFile(fileInfo.absoluteFilePath()));
    int nId = m_listItems.size();
    m_listItems.insert(nId, new QtListWidgetItem(nId, fileInfo.fileName(), fileInfo.absoluteFilePath()));
    this->update();
}

// 绘制列表
void WavPlayListWidget::drawItemInfo(QPainter *painter, QtListWidgetItem *item)
{
    painter->save();
    QRect rect = QRect(item->m_rect.left() + 20, item->m_rect.top(), item->m_rect.width() - 90, item->m_rect.height());
    painter->setPen(QPen(QColor("#797979"), 1));
    painter->drawLine(rect.bottomLeft(), rect.bottomRight());
    // 设置选中画笔
    painter->setPen(m_nCurrentIndex == item->m_nId ? QColor("#02A7F0") : QColor("#333333"));
    QFont font(Skin::m_strAppFontRegular);
    font.setPixelSize(24);
    painter->setFont(font);
    if (item->m_nId == m_nCurrentIndex){
        QPixmap pixmapIco(":/images/music/music.png");
        painter->drawPixmap(rect.left(), rect.top() + pixmapIco.height() / 2, pixmapIco);
        int nOffset = 10 + pixmapIco.width();
        rect = QRect(rect.left() + nOffset, rect.top(), rect.width() - nOffset, rect.height());
    }

    painter->drawText(rect, Qt::AlignVCenter, item->m_strText);
    painter->restore();
}
