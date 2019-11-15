/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : versionupdatepage.cpp --- VersionUpdatePage
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "versionupdatepage.h"
#include "appconfig.h"
#include "unit.h"
#include "skin.h"

#include <QFile>
#include <QFileInfo>
#include <QApplication>
#include <QDebug>
#include <QBoxLayout>
#include <QProcess>
#include <QLabel>

VersionUpdatePage::VersionUpdatePage(QWidget *parent) : QWidget(parent)
{
    m_strAppName = "fire";

    m_download = new DownloadNetworkManager(this);
    connect(m_download, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(SltDownloadProgress(qint64,qint64)));
    connect(m_download, SIGNAL(signalVersionInfo(QString,QString)), this, SLOT(SltVersionInfo(QString,QString)));
    connect(m_download, SIGNAL(signalDownFinish(QString)), this, SLOT(SltDownloadOk(QString)));

    m_textBrowserInfo = new QtTextBroswer(this);
    m_textBrowserInfo->setText(tr("当前版本： V%1 build at %2 %3 .").arg(APP_STR_VERSION).arg(APP_BUILD_DATE).arg(__TIME__));

    QHBoxLayout *horLayoutBtn = new QHBoxLayout();
    horLayoutBtn->setContentsMargins(0, 0, 0, 0);
    horLayoutBtn->setSpacing(20);

    m_labelUpdateLogo = new QLabel(this);
    horLayoutBtn->addWidget(m_labelUpdateLogo);

    horLayoutBtn->addStretch();

    m_btnCheckVersion = new QPushButton(this);
    m_btnCheckVersion->setText(tr("检查更新"));
    horLayoutBtn->addWidget(m_btnCheckVersion);

    m_btnDownload = new QPushButton(this);
    m_btnDownload->setText(tr("下载该版本"));
    m_btnDownload->setEnabled(false);
    horLayoutBtn->addWidget(m_btnDownload);

    m_progressBar = new QProgressBar(this);
    m_progressBar->setTextVisible(false);
    m_progressBar->setMaximumHeight(10);
    m_progressBar->setStyleSheet(QString("QProgressBar{border: none; border-radius: 5px; background-color: #ffffff;}"
                                         "QProgressBar::chunk{border: none; border-radius: 5px;background-color: #008000;}"));

    QVBoxLayout *verLayout = new QVBoxLayout(this);
    verLayout->setContentsMargins(10, 10, 10, 10);
    verLayout->setSpacing(10);
    verLayout->addWidget(m_textBrowserInfo, 1);
    verLayout->addWidget(m_progressBar);
    verLayout->addLayout(horLayoutBtn);

    connect(m_btnCheckVersion, SIGNAL(clicked(bool)), this, SLOT(SltCheckAppVersion()));
    connect(m_btnDownload, SIGNAL(clicked(bool)), this, SLOT(SltDownloadNewApp()));

    this->setStyleSheet(QString("QPushButton{border: 1px solid #c6c6c6; border-radius: 5px; min-height: 25px; min-width: 80px;"
                                "background-color: #f0f0f0; color: #333333;}"
                                "QPushButton:!enabled{color: #aaaaaa;}"
                                "QLabel{color: #ffffff;}"));
}

VersionUpdatePage::~VersionUpdatePage()
{

}

/**
 * @brief MainWindow::GetServerConf
 * @param cmd
 * @param app
 * @return
 */
QString VersionUpdatePage::GetServerConf(const QString &cmd, const QString &app)
{
    QString strUrl = "http://";
    QString strSetting = AppConfig::ReadSetting("Update", "host", "106.15.178.227").toString();
    strUrl += strSetting;
    strUrl += ":";
    strSetting = AppConfig::ReadSetting("Update", "port", "11086").toString();
    strUrl += strSetting;
    strUrl += "/";
    strUrl += cmd;
    strUrl += "/";
    strUrl += app;

    return strUrl;
}

bool VersionUpdatePage::CheckNewVersion(QString oldVersion, QString newVersion)
{
    return (GetVersionVal(newVersion) > GetVersionVal(oldVersion));
}

quint32 VersionUpdatePage::GetVersionVal(QString &verNum)
{
    QStringList verList = verNum.split(".");
    // 如果不是4段表示当前版本是最新的版本，忽略升级
    if (4 != verList.size())
    {
        return 0;
    }

    // 计算版本信息
    quint32 ullVersion = 0;
    QString strTemp = "";
    for (int i = 0; i < 4; i++)
    {
        strTemp = verList.at(i);
        ullVersion |= (strTemp.toInt() << ((3 - i) * 8));
    }

    return ullVersion;
}

QString VersionUpdatePage::CalcFileSize(quint64 size)
{
    return QString("%1 Mb").arg(size * 1.0 / (1024 * 1024), 0, 'f', 2, QChar('0'));
}

/**
 * @brief MainWindow::SltDownloadProgress
 * @param bytesReceived
 * @param bytesTotal
 */
void VersionUpdatePage::SltDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    m_progressBar->setValue(bytesReceived);
    m_progressBar->setMaximum(bytesTotal);
    m_labelUpdateLogo->setText(QString("已下载 %1 MB,总大小 %2 MB。")
                               .arg(bytesReceived * 1.0 / (1024 * 1024), 0, 'f', 2, QChar('0'))
                               .arg(bytesTotal * 1.0 / (1024 * 1024), 0, 'f', 2, QChar('0')));
}

/**
 * @brief MainWindow::SltDownloadOk
 * 下载完成，开始解压
 * @param name
 */
void VersionUpdatePage::SltDownloadOk(const QString &name)
{
    QFileInfo fileInfo(name);
    if (!QString::compare("zip", fileInfo.completeSuffix()))
    {
#if 0
        QStringList strFiles = JlCompress::getFileList(name);
        if (strFiles.isEmpty()) return;

        // 解压文件
        foreach (QString fileName, strFiles) {
            m_strExtractFile = fileName;
            JlCompress::extractFile(name, fileName, qApp->applicationDirPath() + "/" + fileName);
        }
#endif
    }
    else if (!QString::compare("exe", fileInfo.completeSuffix()))
    {

    }
    else if (!QString::compare("tar.bz2", fileInfo.completeSuffix()))
    {
        m_labelUpdateLogo->setText(tr("正在解压升级包，请勿断电或重启设备..."));
#ifdef __arm__
        QProcess cmd;
        cmd.start("tar", QStringList() << "-jxvf" << name << "-C" << qApp->applicationDirPath());
        cmd.waitForFinished();
        QProcess::execute("reboot");
#endif
    }

    m_btnCheckVersion->setEnabled(true);
}

/**
 * @brief MainWindow::SltVersionInfo
 * @param verNum
 * @param verInfo
 */
void VersionUpdatePage::SltVersionInfo(const QString &verNum, const QString &verInfo)
{
    bool bError = (!QString::compare("err", verNum));
    m_btnDownload->setEnabled(false);

    if (!bError && CheckNewVersion(APP_STR_VERSION, verNum))
    {
        m_btnDownload->setEnabled(true);
        QString strText = QString("发现新版本[ %1 ] \n\n").arg(verNum);
        m_textBrowserInfo->setText(strText + verInfo);
    }
    else {
        m_textBrowserInfo->setText(bError ? tr("版本更新发生异常...") :
                                             tr("恭喜你！当前为最新版本，不用更新。"));
        if (!bError) {
            m_textBrowserInfo->append(verInfo);
        }
    }

    this->update();
}

void VersionUpdatePage::SltCheckAppVersion()
{
    m_download->checkVersion(GetServerConf("cv", m_strAppName));
}

void VersionUpdatePage::SltDownloadNewApp()
{
    m_download->downloadFile(GetServerConf("up", m_strAppName));
    m_btnDownload->setEnabled(false);
    m_btnCheckVersion->setEnabled(false);
}

void VersionUpdatePage::resizeEvent(QResizeEvent *e)
{
    QFont font(Skin::m_strAppFontNormal);
    if (this->height() < 400) {
        font.setPixelSize(14);
    } else {
        font.setPixelSize(20);
    }

    m_textBrowserInfo->setFont(font);
    m_textBrowserInfo->setText(m_textBrowserInfo->text());

    QWidget::resizeEvent(e);
}

void VersionUpdatePage::showEvent(QShowEvent *e)
{
    QWidget::showEvent(e);
}

