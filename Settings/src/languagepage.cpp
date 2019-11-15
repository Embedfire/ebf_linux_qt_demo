/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : languagepage.cpp --- LanguagePage
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.qtcn.org/bbs/i.php
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "languagepage.h"
#include "skin.h"
#include "appconfig.h"
#include "../qtmessagebox.h"

#include <QApplication>
#include <QPainter>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QProcess>
#include <QApplication>

LanguagePage::LanguagePage(QWidget *parent) : QtListWidget(parent)
{
    m_backgroundColor = Qt::transparent;
    m_nItemSize = 45;
    m_bHorizontal = false;
    m_nBaseWidth = Skin::m_nScreenWidth;
    m_nBaseHeight = 400;

    connect(this, SIGNAL(currentItemClicked(QtListWidgetItem*)), this, SLOT(SltCurrentIndexClicked(QtListWidgetItem*)));

    LoadQmFiles();
}

LanguagePage::~LanguagePage()
{

}

void LanguagePage::LoadQmFiles()
{
    QDir dir(qApp->applicationDirPath() + "/translations");
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QString strTemp = AppConfig::ReadSetting("System", "language", "qt_zh.qm").toString();
    QFileInfoList list = dir.entryInfoList(QStringList() << "*.qm");
    m_nCurrentIndex = 0;
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        if (strTemp == fileInfo.fileName()) m_nCurrentIndex = i;
        m_listItems.insert(i, new QtListWidgetItem(i, fileInfo.fileName()));
    }

    this->update();
}

void LanguagePage::SltCurrentIndexClicked(QtListWidgetItem *item)
{
    AppConfig::SaveSetting("System", "language", item->m_strText);
    int nRet = QtMessageBox::ShowAskMessage(tr("语言设置重启生效，是否立即重启?"), tr("语言设置"));
    if (nRet == QDialog::Accepted)
    {
#ifdef __arm__
        QString strCmd = qApp->applicationDirPath() + "/run.sh";
        QProcess::startDetached(strCmd);
        qApp->quit();
#endif
    }
}

void LanguagePage::drawItemInfo(QPainter *painter, QtListWidgetItem *item)
{
    painter->save();
    painter->setPen(QColor("#797979"));
    painter->drawLine(QPoint(item->m_rect.left() - m_nMargin, item->m_rect.bottom()),
                      QPoint(item->m_rect.right() + m_nMargin, item->m_rect.bottom()));

    QRect rect(item->m_rect.left() + 20, item->m_rect.top(), item->m_rect.width() - 40, item->m_rect.height());
    QFont font(Skin::m_strAppFontNormal);
    font.setPixelSize(24);
    painter->setFont(font);
    painter->setPen(m_nCurrentIndex == item->m_nId ? QColor("#02A7F0") : QColor("#ffffff"));
    painter->drawText(rect, Qt::AlignVCenter, QString("%1. ").arg(item->m_nId + 1, 2, 10, QChar(' ')) + item->m_strText);

    painter->restore();
}
