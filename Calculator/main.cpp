/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : main.cpp ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/8/31
*******************************************************************/
#include "calculator.h"
#include "skin.h"
#include "calcfunction.h"
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator w;
#ifdef __arm__
    w.showFullScreen();
#else
    Skin::InitSkin();
    w.resize(800, 480);
    w.show();
#endif
    return a.exec();
}
