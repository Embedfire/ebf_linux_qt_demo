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

#ifdef __arm__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <linux/fb.h>
#endif

QString AppConfig::m_strSettingsFile = "conf/config.ini";
bool    AppConfig::m_bMouseInsert = false;
bool    AppConfig::m_bPlayVideo = false;

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


QSize AppConfig::GetDesktopSize() {
#ifdef __arm__
    int fb_fd = open("/dev/fb0", O_RDWR);
    int lcd_width, lcd_height;
    static struct fb_var_screeninfo var;

    if(-1 == fb_fd)
    {
        printf("cat't open /dev/fb0 \n");
        return QSize(0, 0);
    }
    //获取屏幕参数
    if(-1 == ioctl(fb_fd, FBIOGET_VSCREENINFO, &var))
    {
        close(fb_fd);
        printf("cat't ioctl /dev/fb0 \n");
        return QSize(0, 0);
    }

    // 计算参数
    lcd_width    = var.xres;
    lcd_height   = var.yres;

    printf("fb width:%d height:%d \n", lcd_width, lcd_height);
    close(fb_fd);

    return QSize(lcd_width, lcd_height);
#else
//    return QSize(480, 272);
    return QSize(800, 480);
#endif
}
