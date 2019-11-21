/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : appconfig.h --- AppConfig
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/25
*******************************************************************/
#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QVariant>

class AppConfig
{
public:
    static QString m_strSettingsFile;
    static void SaveSetting(const QString &group, const QString &name, const QVariant &value);
    static QVariant ReadSetting(const QString &group, const QString &name, const QVariant &value = QVariant());
    static bool m_bMouseInsert;
    static bool m_bPlayVideo;
    static QSize GetDesktopSize();
};

#endif // APPCONFIG_H
