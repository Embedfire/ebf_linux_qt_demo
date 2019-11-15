/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 :
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "musicplaylistwidget.h"
#include "skin.h"

#include <QDir>
#include <QFileInfo>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QApplication>
#include <QBoxLayout>
#include <QTextCodec>

#define TO_GB18030_CODEC(str)      QTextCodec::codecForName("GB18030")->toUnicode(str)

PlayListWidget::PlayListWidget(QWidget *parent) : QtListWidget(parent)
{
    m_bHorizontal = false;
    m_nItemSize = 40;
    m_nMargin = 0;
    m_backgroundColor = Qt::transparent;
    m_nCurrentIndex = 0;

    m_nBaseWidth = 405;
    m_nBaseHeight = 360;
}

PlayListWidget::~PlayListWidget()
{

}

// 绘制列表
void PlayListWidget::drawItemInfo(QPainter *painter, QtListWidgetItem *item)
{
    painter->save();
    QRect rect = item->m_rect;
    painter->setPen(QPen(QColor("#797979"), 1));
    painter->drawLine(rect.bottomLeft(), rect.bottomRight());

    painter->setPen(m_nCurrentIndex == item->m_nId ? QColor("#02A7F0") : QColor("#ffffff"));
    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(20);
    painter->setFont(font);
    rect = QRect(rect.left() + 10, rect.top(), rect.width() - 10, rect.height());
    painter->drawText(rect, Qt::AlignVCenter, item->m_strBaseName);
    painter->restore();
}

///////////////////////////////////////////////////////////////////////////////////
MusicPlayListWidget::MusicPlayListWidget(QWidget *parent) : QtAnimationWidget(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    m_colorBackground = QColor("#5362b5");
    m_nBaseWidth  = 405;
    m_nBaseHeight = 350;
    m_nYPos = 60;

    m_listWidget = new PlayListWidget(this);
    QVBoxLayout *verLayout = new QVBoxLayout(this);
    verLayout->setContentsMargins(0, 10, 0, 10);
    verLayout->setSpacing(0);
    verLayout->addStretch(1);
    verLayout->addWidget(m_listWidget, 9);

    // 播放列表
    m_playList = new QMediaPlaylist(this);
    m_playList->setPlaybackMode(QMediaPlaylist::Loop);
    connect(m_playList, SIGNAL(currentIndexChanged(int)), this, SLOT(SltCurrMediaChanged(int)));
    connect(m_listWidget, SIGNAL(currentIndexClicked(int)), m_playList, SLOT(setCurrentIndex(int)));
}

MusicPlayListWidget::~MusicPlayListWidget()
{
    m_playList->clear();
}

void MusicPlayListWidget::setTitle(const QString &title)
{
    m_strTitle = title;
}

QMediaPlaylist *MusicPlayListWidget::playList()
{
    return m_playList;
}

void MusicPlayListWidget::LoadLocalFiles(const QString &path)
{
    // 扫描sdk目录
    ScanDirMedias(path);

    // 如果sdk没文件，加载本地
    if (m_mapItems.isEmpty() && m_playList->isEmpty()) {
        ScanDirMedias(qApp->applicationDirPath() + "/music/");
    }

    // 如果扫描到文件，刷新列表
    if (!m_mapItems.isEmpty() && !m_playList->isEmpty()) {
        m_playList->setCurrentIndex(0);
        m_listWidget->SetItems(m_mapItems);
        QtListWidgetItem *item = m_mapItems.value(0);
        emit signalMediaChanged(item->m_strBaseName, item->m_strPath);
    }

    this->update();
}

void MusicPlayListWidget::StartAutoMove(bool bShow, int width)
{
    this->SetAnimationCurve(bShow ? QEasingCurve::OutBounce : QEasingCurve::Linear);
    if (!this->isVisible()) this->setVisible(true);
    QPoint startPos = QPoint(width, m_nYPos);
    QPoint endPos = QPoint(width - this->width(), m_nYPos);
    this->StartAnimation(bShow ? startPos : endPos, !bShow ? startPos : endPos, 300, bShow);
}

void MusicPlayListWidget::ScanDirMedias(const QString &path)
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
        else if (fileInfo.suffix() == "mp3") {
            QString strName = fileInfo.baseName().toLocal8Bit().constData();
            QString strPath = fileInfo.absoluteFilePath().toLocal8Bit().constData();
            m_playList->addMedia(QUrl::fromLocalFile(strPath));
            m_mapItems.insert(index, new QtListWidgetItem(index, strPath, strName, QPixmap()));
            index++;
        }
    }
}

void MusicPlayListWidget::SltCurrMediaChanged(int index)
{
    m_listWidget->setCurrentIndex(index);
    QtListWidgetItem *item = m_listWidget->currentItem();
    if (NULL != item) {
        emit signalMediaChanged(item->m_strBaseName, item->m_strPath);
    }
}

void MusicPlayListWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.scale(m_scaleX, m_scaleY);
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_colorBackground);
    painter.drawRoundedRect(0, 0, m_nBaseWidth + 5,m_nBaseHeight, 10, 10);

    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(24);
    painter.setPen(Qt::white);
    painter.drawText(0, 0, m_nBaseWidth, 40, Qt::AlignCenter, tr("播放列表"));

    painter.setPen(QColor("#797979"));
    painter.drawLine(QPoint(0, 40), QPoint(m_nBaseWidth, 40));
}
