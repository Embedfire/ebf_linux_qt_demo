/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : citybook.cpp --- CityBook
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "citybook.h"
#include <QFile>
#include <QTime>
#include <QElapsedTimer>
#include <QDebug>

//{
//  "id": 37,
//  "pid": 3400,
//  "city_code": "101220105",
//  "city_name": "巢湖市",
//  "post_code": "238000",
//  "area_code": "0551",
//  "ctime": "2019-07-11 17:03:40"
//},
City::City(QtJson::JsonObject jsonObj)
{
    m_nId = jsonObj.value("id").toInt();
    m_nPid = jsonObj.value("pid").toInt();

    m_strCityCode = jsonObj.value("city_code").toString();
    m_strCityName = jsonObj.value("city_name").toString();
    m_strPostCode = jsonObj.value("post_code").toString();
    m_strrAreaCode = jsonObj.value("area_code").toString();
}


///////////////////////////////////////////////////////////////
CityBook *CityBook::self = 0;
CityBook::CityBook()
{

}

CityBook::~CityBook()
{

}

CityBook *CityBook::Instance()
{
    if (0 == self) {
        self = new CityBook();
    }

    return self;
}

QString CityBook::GetCityId(const QString &cityName)
{
    foreach (City city, m_cityBook) {
        if (!QString::compare(city.m_strCityName, cityName)) {
            return city.m_strCityCode;
        }
    }
    return "101010100";
}

void CityBook::LoadConfig(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    bool bOk = false;
    QtJson::JsonArray result = QtJson::parse(file.readAll(), bOk).toList();
    file.close();

    if (bOk) {
        for (int i = 0; i < result.size(); i++) {
            QtJson::JsonObject jsonObj = result.value(i).toMap();
            if (jsonObj.value("city_code").toString().isEmpty()) continue;
            m_cityBook.insert(jsonObj.value("id").toInt(), City(jsonObj));
        }
    }
}

QStringList CityBook::searchCitys(const QString &name)
{
    QStringList strCitys;
    foreach (City city, m_cityBook) {
        if (city.m_strCityName.contains(name)) {
            strCitys << city.m_strCityName;
        }
    }
    return strCitys;
}
