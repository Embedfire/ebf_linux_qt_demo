/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : main.cpp ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/10/10
*******************************************************************/
#include "recorderwidget.h"
#include "skin.h"
#include <QTextCodec>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Skin::InitSkin();
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    a.setApplicationName("录音机");
    RecorderWidget w;
#ifdef __arm__
    w.showFullScreen();
#else
    w.resize(800, 480);
    w.show();
#endif

    return a.exec();
}
