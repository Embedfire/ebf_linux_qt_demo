/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : appconfig.cpp --- AppConfig
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/25
*******************************************************************/
#include "appconfig.h"
#include <QSettings>
#include <QApplication>

QString AppConfig::m_strSettingsFile = "conf/config.ini";
void AppConfig::SaveSetting(const QString &group, const QString &name, const QVariant &value)
{
    QSettings settings(m_strSettingsFile, QSettings::IniFormat);
    settings.beginGroup(group);
    settings.setValue(name, value);
    settings.endGroup();
}

QVariant AppConfig::ReadSetting(const QString &group, const QString &name, const QVariant &value)
{
    QSettings settings(m_strSettingsFile, QSettings::IniFormat);
    settings.beginGroup(group);
    QVariant keyValue = settings.value(name, value);
    settings.endGroup();

    return keyValue;
}
