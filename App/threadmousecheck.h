/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : threadmousecheck.h --- ThreadMouseCheck
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.qtcn.org/bbs/i.php
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef THREADMOUSECHECK_H
#define THREADMOUSECHECK_H

#include <QThread>

class ThreadMouseCheck : public QThread
{
    Q_OBJECT
public:
    explicit ThreadMouseCheck(QObject *parent = 0);
    ~ThreadMouseCheck();

signals:
    void signalMouseInsert(bool bOk);

public slots:

protected:
    bool m_bRun;
    void run();
};

#endif // THREADMOUSECHECK_H
