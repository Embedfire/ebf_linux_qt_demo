/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : main.cpp ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/6
*******************************************************************/
#include "calendarwidget.h"
#include "appconfig.h"
#include "skin.h"

#include <QApplication>
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    AppConfig::m_strSettingsFile = a.applicationDirPath() + "/conf/config.ini";
    a.setFont(QFont(Skin::m_strAppFontNormal));

    CalendarWidget w;
#ifdef __arm__
    w.showFullScreen();
#else
    w.resize(800, 480);
    w.show();
#endif

    return a.exec();
}


