/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : skin.h --- Skin
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/8/31
*******************************************************************/
#ifndef SKIN_H
#define SKIN_H

#include <QObject>

#ifdef QtSkin
#if defined(SKIN_LIBRARY)
#  define SKINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SKINSHARED_EXPORT Q_DECL_IMPORT
#endif
class SKINSHARED_EXPORT Skin {
#else
class Skin {
#endif
public:
    Skin();
    static void InitSkin();

    static QString m_strAppFontNormal;
    static QString m_strAppFontRegular;
    static QString m_strAppFontBold;
    static QString m_strAppFontMedium;

    static int     m_nScreenWidth;
    static int     m_nScreenHeight;
};

#endif // SKIN_H
