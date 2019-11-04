/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : videoplaylistwidget.cpp --- VideoPlayListWidget
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "videoplaylistwidget.h"
#include "skin.h"

#include <QPainter>
#include <QDir>
#include <QFileInfo>
#include <QBoxLayout>
#include <QApplication>

VideoPlayListWidget::VideoPlayListWidget(QWidget *parent) : QtListWidget(parent)
{
    m_bHorizontal = false;
    m_nItemSize = 40;
    m_nMargin = 0;
    m_backgroundColor = Qt::transparent;
    m_nCurrentIndex = 0;
}

VideoPlayListWidget::~VideoPlayListWidget()
{

}

// 绘制列表
void VideoPlayListWidget::drawItemInfo(QPainter *painter, QtListWidgetItem *item)
{
    painter->save();
    QRect rect = item->m_rect;
    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->setPen(QPen(QColor("#797979"), 1));
    painter->drawLine(rect.bottomLeft(), rect.bottomRight());

    painter->setPen(m_nCurrentIndex == item->m_nId ? QColor("#02A7F0") : QColor("#ffffff"));
    QFont font(Skin::m_strAppFontNormal);
    font.setPixelSize(24);
    painter->setFont(font);
    rect = QRect(rect.left() + 10, rect.top(), rect.width() - 10, rect.height());
    painter->drawText(rect, Qt::AlignVCenter, item->m_strBaseName);
    painter->restore();
}

///////////////////////////////////////////////////////////////////////////////////
MediaPlayListWidget::MediaPlayListWidget(QWidget *parent) : QtAnimationWidget(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    m_colorBackground = QColor("#BC182E3A");

    m_labelTitle = new QLabel(this);
    m_labelTitle->setAlignment(Qt::AlignCenter);
    m_labelTitle->setText(tr("播放列表"));
    m_labelTitle->setMinimumHeight(40);

    m_listWidget = new VideoPlayListWidget(this);
    QVBoxLayout *verLayout = new QVBoxLayout(this);
    verLayout->setContentsMargins(0, 10, 0, 10);
    verLayout->setSpacing(0);
    verLayout->addWidget(m_labelTitle);
    verLayout->addWidget(m_listWidget, 1);

    // 播放列表
    m_playList = new QMediaPlaylist(this);
    m_playList->setPlaybackMode(QMediaPlaylist::Loop);
    connect(m_playList, SIGNAL(currentIndexChanged(int)), this, SLOT(SltCurrMediaChanged(int)));
    connect(m_listWidget, SIGNAL(currentIndexClicked(int)), m_playList, SLOT(setCurrentIndex(int)));

    this->setStyleSheet(QString("QLabel{color: #ffffff; font: 24px; font-family: '%1';"
                                "border: none; border-bottom: 1px solid #797979;}").arg(Skin::m_strAppFontNormal));
}

MediaPlayListWidget::~MediaPlayListWidget()
{
    m_playList->clear();
}

void MediaPlayListWidget::setTitle(const QString &title)
{
    m_labelTitle->setText(title);
}

QMediaPlaylist *MediaPlayListWidget::palyList()
{
    return m_playList;
}

QMap<int, QtListWidgetItem *> MediaPlayListWidget::items()
{
    return m_mapItems;
}

void MediaPlayListWidget::ScanDirMedias(const QString &path)
{
    QDir dir(path);
    if (!dir.exists()) return;
    dir.setFilter(QDir::Dirs| QDir::Files);
    dir.setSorting(QDir::DirsFirst);
    QFileInfoList list = dir.entryInfoList();
    int index = m_mapItems.size();
    for (int i = 0; i < list.size(); i++) {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.fileName() == "."|| fileInfo.fileName() == "..") { continue; }

        if (fileInfo.isDir()) {
            ScanDirMedias(fileInfo.filePath());
        }
        else if (fileInfo.suffix() == "mp4") {
            QString strName = fileInfo.baseName().toLocal8Bit().constData();
            QString strPath = fileInfo.absoluteFilePath().toLocal8Bit().constData();
            m_playList->addMedia(QUrl::fromLocalFile(strPath));
            m_mapItems.insert(index, new QtListWidgetItem(index, strPath, strName, QPixmap(":/images/video/ic_video_preview.png")));
            index++;
        }
    }
}

void MediaPlayListWidget::LoadLocalFiles(const QString &path)
{
    // 扫描sdk目录
    ScanDirMedias(path);

    // 如果sdk没文件，加载本地
    if (m_mapItems.isEmpty() && m_playList->isEmpty()) {
        ScanDirMedias(qApp->applicationDirPath() + "/video/");
    }

    // 如果扫描到文件，刷新列表
    if (!m_mapItems.isEmpty() && !m_playList->isEmpty()) {
        m_playList->setCurrentIndex(0);
        m_listWidget->SetItems(m_mapItems);
        emit signalMediaChanged(m_mapItems.value(0)->m_strBaseName);
    }

    this->update();
}

void MediaPlayListWidget::SltCurrMediaChanged(int index)
{
    m_listWidget->setCurrentIndex(index);
    QtListWidgetItem *item = m_listWidget->currentItem();
    if (NULL != item) {
        emit signalMediaChanged(item->m_strBaseName);
    }
}

void MediaPlayListWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_colorBackground);
    painter.drawRoundedRect(0, 0, this->width() + 5, this->height(), 10, 10);
}
