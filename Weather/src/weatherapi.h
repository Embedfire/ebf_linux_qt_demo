/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : WeatherApi.h ---
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef WEATHERAPI_H
#define WEATHERAPI_H

#include <QWidget>

#include <QNetworkAccessManager>
#include <QNetworkReply>

class WeatherApi : public QObject
{
    Q_OBJECT

public:
    WeatherApi(QObject *parent = 0);
    ~WeatherApi();

    void QueryCityWeather(const QString &cityCode);
signals:
    void signalResult(const QByteArray &jsonData);

private:
    QString GetSignText(QString text);
    QNetworkAccessManager *manager;

private slots:
    void replyFinished(QNetworkReply* reply);
};

#endif // WEATHERAPI_H
