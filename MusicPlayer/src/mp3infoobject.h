/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : mp3infoobject.h --- Mp3InfoObject
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef MP3INFOOBJECT_H
#define MP3INFOOBJECT_H

#include <QObject>

class Mp3InfoObject
{
public:
    static QString getArtistInfo(const QString &fileName);

private:
    static QString getUnicodeString(char *buffer, int len);
};

#endif // MP3INFOOBJECT_H
