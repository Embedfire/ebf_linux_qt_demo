/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : threadmousecheck.cpp --- ThreadMouseCheck
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.qtcn.org/bbs/i.php
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "threadmousecheck.h"

#ifdef __arm__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#endif

#define UEVENT_BUFFER_SIZE 2048

ThreadMouseCheck::ThreadMouseCheck(QObject *parent) : QThread(parent),
    m_bRun(false)
{

}

ThreadMouseCheck::~ThreadMouseCheck()
{
    m_bRun = false;
    this->wait(2000);
}

void ThreadMouseCheck::run()
{
#ifdef __arm__
    struct sockaddr_nl client;
    struct timeval tv;
    int usb_dev, rcvlen, ret;
    fd_set fds;
    int buffersize = 1024;

    char buf[UEVENT_BUFFER_SIZE] = { 0 };

    usb_dev = socket(AF_NETLINK, SOCK_RAW, NETLINK_KOBJECT_UEVENT);

    memset(&client, 0, sizeof(client));

    client.nl_family = AF_NETLINK;
    client.nl_pid = getpid();
    client.nl_groups = 1;

    setsockopt(usb_dev, SOL_SOCKET, SO_RCVBUF, &buffersize, sizeof(buffersize));

    bind(usb_dev, (struct sockaddr*)&client, sizeof(client));

    m_bRun = true;
    while (m_bRun) {
        FD_ZERO(&fds);
        FD_SET(usb_dev, &fds);

        tv.tv_sec = 1;
        tv.tv_usec = 100 * 1000;
        ret = select(usb_dev + 1, &fds, NULL, NULL, &tv);

        if(ret < 0)
            continue;
        if(!(ret > 0 && FD_ISSET(usb_dev, &fds)))
            continue;

        /* receive data */
        rcvlen = recv(usb_dev, &buf, sizeof(buf), 0);

        if (rcvlen > 0) {
            if (strstr(buf, "mouse")) {
                if (strstr(buf,"add")) {
                    emit signalMouseInsert(true);
                }
                else {
                    emit signalMouseInsert(false);
                }
            }
        }
    }

    close(usb_dev);
#endif
}
