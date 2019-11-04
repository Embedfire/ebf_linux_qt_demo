/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : main.cpp ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/15
*******************************************************************/
#include "filesystemwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("xyinput"));
    QApplication a(argc, argv);
    FileSystemWindow w;
#ifdef __arm__
    w.showFullScreen();
#else
    w.resize(800, 480);
    w.show();
#endif

    return a.exec();
}
