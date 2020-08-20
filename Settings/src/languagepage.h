/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : languagepage.h --- LanguagePage
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.qtcn.org/bbs/i.php
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef LANGUAGEPAGE_H
#define LANGUAGEPAGE_H

#include "qtlistwidget.h"

class LanguagePage : public QtListWidget
{
    Q_OBJECT
public:
    explicit LanguagePage(QWidget *parent = 0);
    ~LanguagePage();

signals:
    void signalChangeLanguage(const QString &qmFile);

private:
    void LoadQmFiles();

private slots:
    void SltCurrentIndexClicked(QtListWidgetItem *item);

protected:
    void drawItemInfo(QPainter *painter, QtListWidgetItem *item);
};

#endif // LANGUAGEPAGE_H
