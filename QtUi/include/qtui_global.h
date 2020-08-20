/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : qtui_global.h ---
 作 者    : Niyh(lynnhua)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef QTUI_GLOBAL_H
#define QTUI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTUI_LIBRARY)
#  define QTUISHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTUISHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QTUI_GLOBAL_H
