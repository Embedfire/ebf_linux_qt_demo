/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : aboutboard.h --- AboutBoard
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef ABOUTBOARD_H
#define ABOUTBOARD_H

#include <QWidget>

class AboutBoard : public QWidget
{
    Q_OBJECT
public:
    explicit AboutBoard(QWidget *parent = 0);
    ~AboutBoard();

signals:
    void signalChangePage(int index);

public slots:

private:
    void InitBoardInfo();
    void InitWidget();

private:
    QString m_strNandSize;
};

#endif // ABOUTBOARD_H
