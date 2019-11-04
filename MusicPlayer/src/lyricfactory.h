/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 :
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef LYRICFACTORY_H
#define LYRICFACTORY_H

#include <QObject>

class LyricLine {

public:
    explicit LyricLine();
    explicit LyricLine(int m, QString t);
    int getmilliseconds() const;
    QString gettext() const;

private:
    int milliseconds;
    QString text;
};


class LyricFactory : public QObject
{
    Q_OBJECT
public:
    explicit LyricFactory(QObject *parent = 0);

    bool LoadLyricFile(const QString &fileName);
    int findIndex(int position);
    void SetIndex(int position);
    void setcurrentIndex(const int & i);
    QString getTextline(int index);

    QStringList getLyricTexts();

signals:
    void currentIndexChanged(int);

public slots:

private:
    void clearData();

    int m_currentIndex;
    QList<LyricLine> lyricData;
};

#endif // LYRICFACTORY_H
