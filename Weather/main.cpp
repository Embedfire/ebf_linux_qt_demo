/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : main.cpp ---
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "weatherwidget.h"
#include "appconfig.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("xyinput"));
    QApplication a(argc, argv);
    AppConfig::m_strSettingsFile = a.applicationDirPath() + "/conf/config.ini";
    WeatherWidget w;
#ifdef __arm__
    w.showFullScreen();
#else
    w.resize(800, 480);
    w.show();
#endif

    return a.exec();
}
