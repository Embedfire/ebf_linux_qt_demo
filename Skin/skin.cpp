/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : skin.cpp --- Skin
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/8/31
*******************************************************************/
#include "skin.h"
#include <QDebug>


QString Skin::m_strAppFontNormal = "思源黑体 CN Normal";
QString Skin::m_strAppFontRegular = "思源黑体 CN Regular";
QString Skin::m_strAppFontBold = "思源黑体 CN Bold";
QString Skin::m_strAppFontMedium = "思源黑体 CN Medium";

int     Skin::m_nScreenWidth = 800;
int     Skin::m_nScreenHeight = 480;

Skin::Skin()
{

}

void Skin::InitSkin()
{
    qDebug() << "Skin InitOk: build at " << __DATE__ << __TIME__;
}
