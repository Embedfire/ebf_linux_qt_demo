/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : videoplayer.cpp ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/7
*******************************************************************/
#include "videoplayer.h"
#include "skin.h"

#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDir>
#include <QFileInfo>
#include <QTimer>

#ifndef FLASH_FILE_EMMC
#define FLASH_FILE_EMMC     "/sys/class/mmc_host/mmc1/mmc1:0001/block/mmcblk1/size"
#endif

VideoPlayer::VideoPlayer(QWidget *parent) : QtAnimationWidget(parent)
{
    this->SetBackground(QPixmap(":/images/video/ic_background.png"));

    InitWidget();
    QTimer::singleShot(500, this, SLOT(LoadMedias()));
}

VideoPlayer::~VideoPlayer()
{

}

void VideoPlayer::InitWidget()
{
    QtWidgetTitleBar *m_widgetTitle = new QtWidgetTitleBar(this);
    m_widgetTitle->SetScalSize(Skin::m_nScreenWidth, 80);
    m_widgetTitle->SetBackground(Qt::transparent);
    m_widgetTitle->setFont(QFont(Skin::m_strAppFontNormal));
    m_widgetTitle->SetTitle(tr("视频播放器"), "#ffffff", 32);
    connect(m_widgetTitle, SIGNAL(signalBackHome()), this, SIGNAL(signalBackHome()));

    QVBoxLayout *verLayoutCentor = new QVBoxLayout(this);
    verLayoutCentor->setContentsMargins(0, 0, 0, 0);
    verLayoutCentor->setSpacing(0);
    verLayoutCentor->addWidget(m_widgetTitle, 1);

    m_videosList = new VideoListViewer(this);
    m_videosList->SetBackground(Qt::transparent);
    connect(m_videosList, SIGNAL(currentItemClicked(QtPageListWidgetItem*)), this, SLOT(SltItemClicked(QtPageListWidgetItem *)));
    verLayoutCentor->addWidget(m_videosList, 5);

    m_videoWidget = new QtVideoWidget(this);
    m_videoWidget->hide();
}

void VideoPlayer::LoadMedias()
{
    m_videoWidget->m_playList->LoadLocalFiles("/run/media/");
    QMap<int, QtPageListWidgetItem *> items;
    foreach (QtListWidgetItem *item, m_videoWidget->m_playList->items()) {
        items.insert(item->m_nId, new QtPageListWidgetItem(item->m_nId, item->m_strPath, item->m_strBaseName, QPixmap(":/images/video/ic_video_preview.png")));
    }
    m_videosList->SetItems(items);
}

void VideoPlayer::SltItemClicked(QtPageListWidgetItem *item)
{
    QFileInfo fileInfo(item->m_strPath);
    m_videoWidget->setMedia(fileInfo.fileName(), item->m_nId);
    m_videoWidget->setGeometry(0, 0, this->width(), this->height());
    m_videoWidget->show();
}

void VideoPlayer::resizeEvent(QResizeEvent *e)
{
    if (NULL != m_videoWidget) {
        m_videoWidget->setGeometry(0, 0, this->width(), this->height());
    }
    QWidget::resizeEvent(e);
}

