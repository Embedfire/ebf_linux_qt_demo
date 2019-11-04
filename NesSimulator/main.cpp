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
#include "nessimulator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NesSimulator w;
#ifdef __arm__
    w.showFullScreen();
#else
    w.setFixedSize(800, 480);
    w.show();
#endif

    return a.exec();
}
