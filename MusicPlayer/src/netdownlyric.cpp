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
#include "netdownlyric.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>

#include <QDebug>
#include <QApplication>
#include <QTextCodec>

NetdownLyric::NetdownLyric(QObject *parent) :
    QObject(parent)
{
    initNetwork();
    m_uchType = REQ_SEARCH;
}

NetdownLyric::~NetdownLyric()
{
}

// 查询
void NetdownLyric::searchNetLyric(const QString &songname, const QString &artist)
{
    QString strUrl = "http://geci.me/api/lyric/" + songname;
    m_strSongName = artist;
    qDebug() << "search lyric" << strUrl;
    m_uchType = REQ_SEARCH;
    m_network->get(QNetworkRequest(QUrl(strUrl)));
}

void NetdownLyric::initNetwork()
{
    m_network = new QNetworkAccessManager(this);
    m_reply   = NULL;

    connect(m_network, SIGNAL(finished(QNetworkReply*)), this, SLOT(sltNetworkFinished(QNetworkReply *)));
}

void NetdownLyric::parseLyricUrl(QByteArray jsonData)
{
    QString strTemp = "";
    QString strUrl = "";

    QJsonParseError jsonError;
    QJsonDocument json = QJsonDocument::fromJson(jsonData, &jsonError);
    if (jsonError.error == QJsonParseError::NoError) {
        // 解析数据
        if (json.isObject()) {
            QJsonObject jsonObj = json.object();
            QJsonArray jsonArray = jsonObj["result"].toArray();

            for (int i = 0; i < jsonArray.count(); i++)
            {
                // 转换数组
                jsonObj = jsonArray.at(i).toObject();
                strUrl = jsonObj.value("lrc").toString();
                if (!strUrl.isEmpty()) {
                    strTemp = jsonObj.value("song").toString();
                    QString strSongName = qApp->applicationDirPath() + "/lrc/" + m_strSongName + ".lrc";

                    localFile.setFileName(strSongName);
                    if (!localFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)) {
                        qDebug() << "open lrc file failed" << strSongName;
                        return;
                    }

                    in.setDevice(&localFile);
                    in.setCodec("GB18030");

                    // 发送请求
                    m_uchType = REQ_DOWNLOAD;
                    m_reply = m_network->get(QNetworkRequest(QUrl(strUrl)));
                    connect(m_reply, SIGNAL(finished()), this, SLOT(sltDownLoadFinished()));
                    return;
                }

            }
        }
    }
}

void NetdownLyric::parseLyricData(QByteArray jsonData)
{
    in << jsonData;
}

void NetdownLyric::sltNetworkFinished(QNetworkReply *reply)
{
    switch (m_uchType) {
    case REQ_SEARCH:
        parseLyricUrl(reply->readAll());
        break;
    case REQ_DOWNLOAD:
        parseLyricData(reply->readAll());
        break;
    default:
        break;
    }
}

void NetdownLyric::sltDownLoadFinished()
{
    localFile.close();
    m_reply->deleteLater();
    emit signalDownFinished(m_strSongName);
}
