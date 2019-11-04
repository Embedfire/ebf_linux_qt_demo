/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : mp3infoobject.cpp --- Mp3InfoObject
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "mp3infoobject.h"

#include <QFile>
#include <QTextCodec>
#include <QDebug>

QString Mp3InfoObject::getArtistInfo(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "open failed";
        return "";
    }

    QTextCodec *textCodec = QTextCodec::codecForName("GB18030");
    // 把文件的最后128字节信息读给pbuf数组
    long seekPos = 128;
    file.seek(file.size() - seekPos);

    char pbuf[128];
    memset(pbuf, 0, sizeof(pbuf));
    file.read(pbuf, 128);

    // 获取标签信息
    QString strTemp = textCodec->toUnicode(pbuf, 3);
    // 获得tag,如果不是tag，那么就返回
    if (!strTemp.compare("tag"))
    {
        file.close();
        return "";
    }

    // 获取专辑信息
    QString strAristInfo = getUnicodeString(pbuf + 3, 30);
    if (strAristInfo.isEmpty()) return strAristInfo;
    strAristInfo.append("-");
    strAristInfo += getUnicodeString(pbuf + 33, 30);
    file.close();
    return strAristInfo;
}

QString Mp3InfoObject::getUnicodeString(char *buffer, int len)
{
    QByteArray temp(buffer, len);
    while (temp.length() > 0)
    {
        if (0x00 == (uchar)temp[temp.length() - 1])
        {
            temp.remove(temp.length() - 1, 1);
        }
        else break;
    }

    QTextCodec *textCodec = QTextCodec::codecForName("GB18030");
    return textCodec->toUnicode(temp);
}
