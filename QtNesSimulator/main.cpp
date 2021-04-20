/********************************************************************************
 * Copyright (C) 2020 - All Rights Reserved by xiaomutech
 * date: 2020/7/24
 * auth: yhni lynnhua@163.com QQ:393320854
 * desc:
 ********************************************************************************/
#include "nesemulatewindow.h"
#include "controlhandlewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if 1
    NesEmulateWindow w;
#else
    ControlHandleWidget w;
#endif
    w.show();

    return a.exec();
}
