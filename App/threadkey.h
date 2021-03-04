/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : threadkey.h --- ThreadKey
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef THREADKEY_H
#define THREADKEY_H

#include <QThread>

class ThreadKey : public QThread
{
    Q_OBJECT
public:
    explicit ThreadKey(QObject *parent = 0, quint8 type = 0);
    ~ThreadKey();
    void Stop();

signals:
    void SltKeyPressed(const quint8 &type);
    void signalKeyPressed(const quint8 &code,const quint8 &value);

public slots:

private:

protected:
    quint8 m_nKeyType;
    quint8 m_nKeyPressed;

    bool m_bRun;
    void run();
};

#endif // THREADKEY_H
