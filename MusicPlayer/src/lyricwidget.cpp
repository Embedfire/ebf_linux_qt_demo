/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : lyricwidget.cpp --- LyricWidget
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "lyricwidget.h"
#include "skin.h"

#include <QApplication>
#include <QPainter>
#include <QDebug>

#define LYRIC_LINE_HEIGHT       40

LyricWidget::LyricWidget(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    m_nShowCount = 7;
    m_bLyricLoad = true;
    m_bError = false;

    m_strSongName = "加载中...";
    m_nCurrentIndex = 0;

    // 歌词处理
    m_lyricFactory = new LyricFactory(this);
    connect(m_lyricFactory, SIGNAL(currentIndexChanged(int)), this, SLOT(SltCurrentIndexChanged(int)));
#ifdef AUTO_DOWNLOAD_LYRIC
    // 网络更新歌词
    m_networkLyric = new NetdownLyric(this);
    connect(m_networkLyric, SIGNAL(signalDownFinished(QString)), this, SLOT(SltLoadNetLyric(QString)));
#endif
}

LyricWidget::~LyricWidget()
{

}

void LyricWidget::LoadLyricFile(const QString &name, const QString &path)
{
    m_strSongName = name;
    m_strLyricPath = path;
    m_strLyricPath.remove(m_strLyricPath.length() - 4, 4);
    m_strLyricPath.append(".lrc");

    m_strLyricLines.clear();
    m_nStartIndex = 0;
    m_nCurrentIndex = 0;
    m_bLyricLoad = m_lyricFactory->LoadLyricFile(m_strLyricPath);
    qDebug() << "load lrc" << m_bLyricLoad << m_strSongName << m_strLyricPath;
    if (m_bLyricLoad)
    {
        m_bError = false;
        m_strLyricLines = m_lyricFactory->getLyricTexts();
    }
    else {
        QString strSong = name;;
        if (m_strSongName.contains("-")) {
            QStringList strConfig = m_strSongName.split("-");
            strSong = strConfig.at(0);
        }

        strSong.remove(" ");
#ifdef AUTO_DOWNLOAD_LYRIC
        m_networkLyric->searchNetLyric(strSong, name);
#endif
    }
    this->update();
}

void LyricWidget::ChangePostion(qint64 postion)
{
    m_lyricFactory->SetIndex(postion / 1000);
}

void LyricWidget::ShowErrorString()
{
   m_strLyricLines.clear();
   m_bError = true;
}

void LyricWidget::SetLyricPostion(int postion)
{
    if (!m_bLyricLoad) return;
    m_lyricFactory->findIndex(postion);
}

void LyricWidget::SltCurrentIndexChanged(int index)
{
    m_nStartIndex = (index < (m_nShowCount / 2)) ? 0 : (index - (m_nShowCount / 2));
    m_nCurrentIndex = index;
    this->update();
}

void LyricWidget::SltLoadNetLyric(const QString &file)
{
    qDebug() << "file" << file;
    m_strLyricLines.clear();
    m_nStartIndex = 0;
    m_nCurrentIndex = 0;
    m_bLyricLoad = m_lyricFactory->LoadLyricFile(m_strLyricPath + file + ".lrc");
    if (m_bLyricLoad)
    {
        m_bError = false;
        m_strLyricLines = m_lyricFactory->getLyricTexts();
    }
    this->update();
}

void LyricWidget::resizeEvent(QResizeEvent *e)
{
    m_nShowCount = (this->height()  - 50) / LYRIC_LINE_HEIGHT;
    QWidget::resizeEvent(e);
}

void LyricWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.fillRect(this->rect(), Qt::transparent);

    QFont font(Skin::m_strAppFontNormal);
    font.setPixelSize(20);
    font.setBold(true);
    painter.setFont(font);
    painter.setPen("#80FFFF");
    painter.drawText(0, 0, this->width(), 60, Qt::AlignCenter, m_strSongName);

    font.setPixelSize(18);
    font.setBold(false);
    painter.setFont(font);
    if (m_strLyricLines.isEmpty()) {
        painter.setPen("#ffffff");
        QRect rect(0, 60, this->width(), this->height() - 60);
        if (m_bError) {
            painter.drawText(rect, Qt::AlignCenter, QStringLiteral("音乐文件格式解析错误"));
        } else {
            painter.drawText(rect, Qt::AlignCenter,
                             m_bLyricLoad ? QStringLiteral("正在加载歌曲...") :
                                            QStringLiteral("未找到歌词文件"));
        }
    }
    else {
        drawLyricLines(&painter);
    }
}

void LyricWidget::drawLyricLines(QPainter *painter)
{
    painter->save();
    QTextOption option;
    option.setWrapMode(QTextOption::WordWrap);
    option.setAlignment(Qt::AlignCenter);

    QRect rect(0, 0, this->width(), 60);
    int index = 0;
    for (int i = 0; i < m_nShowCount; i++) {
        rect = QRect(rect.left(), rect.bottom(), rect.width(), LYRIC_LINE_HEIGHT);
        index = m_nStartIndex + i;
        QString strText = index < m_strLyricLines.size() ? m_strLyricLines.at(index) : "";
        painter->setPen(index == m_nCurrentIndex ? Qt::white : Qt::black);
        painter->drawText(rect, strText, option);
    }
    painter->restore();
}
