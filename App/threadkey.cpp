/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : threadkey.cpp --- ThreadKey
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "threadkey.h"
#include <QDebug>

#ifdef __arm__
#include <stdio.h>
#include <linux/input.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#endif

// keyboard
#define KEY_DEV     "/dev/input/by-path/platform-gpio-keys-event"
// switch
#define POWER_DEV   "/dev/input/by-path/platform-20cc000.snvs:snvs-powerkey-event"

#define KEY1        11
#define KEY2        2
#define WAKE_UP     28

ThreadKey::ThreadKey(QObject *parent, quint8 type) : QThread(parent),
    m_nKeyType(type),m_nKeyPressed(0),m_bRun(false)
{
}

ThreadKey::~ThreadKey()
{
    Stop();
}

void ThreadKey::Stop()
{
    m_bRun = false;
    this->wait(3000);
}

void ThreadKey::run()
{
#ifdef __arm__
    int fd = 0;
    struct input_event inmyself;
    //fd = open(0 == m_nKeyType ? POWER_DEV : KEY_DEV, O_RDONLY);
    fd = open(KEY_DEV, O_RDONLY);
    if (fd < 0)
    {
        printf("Open keyboard failed .\n");
        return;
    }

    m_bRun = true;
    while (m_bRun)
    {


        if (read(fd, &inmyself, sizeof(inmyself)) < 0) {
            m_bRun = false;
            break;
        }
        else {
            qDebug()<<inmyself.code<<inmyself.type<<inmyself.value;
            emit signalKeyPressed(inmyself.code,inmyself.value);
        }
    }

    close(fd);
#endif
}
