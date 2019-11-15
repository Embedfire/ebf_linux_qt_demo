/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : versionupdatepage.h --- VersionUpdatePage
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef VERSIONUPDATEPAGE_H
#define VERSIONUPDATEPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>

#include "downloadnetworkmanager.h"
#include "qttextbroswer.h"

class VersionUpdatePage : public QWidget
{
    Q_OBJECT
public:
    explicit VersionUpdatePage(QWidget *parent = 0);
    ~VersionUpdatePage();

signals:

public slots:

private:
    DownloadNetworkManager  *m_download;

    QString     m_strAppName;
    QString     m_strExecName;

    // 解压文件
    QString     m_strExtractFile;

    QtTextBroswer *m_textBrowserInfo;

    QPushButton   *m_btnCheckVersion;
    QPushButton   *m_btnDownload;
    QProgressBar  *m_progressBar;

    QLabel        *m_labelUpdateLogo;
private:
    QString GetServerConf(const QString &cmd, const QString &app);
    bool    CheckNewVersion(QString oldVersion, QString newVersion);
    quint32 GetVersionVal(QString &verNum);
    QString CalcFileSize(quint64 size);

private slots:
    void SltDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void SltDownloadOk(const QString &name);
    void SltVersionInfo(const QString &verNum, const QString &verInfo);

    void SltCheckAppVersion();
    void SltDownloadNewApp();

protected:
    void resizeEvent(QResizeEvent *e);
    void showEvent(QShowEvent *e);
};

#endif // VERSIONUPDATEPAGE_H
