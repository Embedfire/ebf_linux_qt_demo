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
#ifndef NETDOWNLYRIC_H
#define NETDOWNLYRIC_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QFile>
#include <QTextStream>

class NetdownLyric : public QObject
{
    Q_OBJECT
public:
    explicit NetdownLyric(QObject *parent = 0);
    ~NetdownLyric();

    typedef enum {
        REQ_SEARCH,
        REQ_DOWNLOAD,
    } E_REQUEST;

    void searchNetLyric(const QString &songname, const QString &artist = "");
signals:
    void signalDownFinished(const QString &songName);
public slots:

private:
    QNetworkAccessManager *m_network;
    QNetworkReply         *m_reply;

    uchar m_uchType;

    QFile localFile;
    QTextStream in;
    QString m_strSongName;

private:
    void initNetwork();


    void parseLyricUrl(QByteArray json);
    void parseLyricData(QByteArray jsonData);

    Q_SLOT void sltNetworkFinished(QNetworkReply *reply);
    Q_SLOT void sltDownLoadFinished();
};

#endif // NETDOWNLYRIC_H
