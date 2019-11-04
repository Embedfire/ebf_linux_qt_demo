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
#include "lyricfactory.h"

#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QDebug>

//////////////////////////////////////////
LyricLine::LyricLine() {
    milliseconds = INT_MAX;
    text = " ";
}

LyricLine::LyricLine(int m, QString t) {
    milliseconds = m;
    text = t;
}

int LyricLine::getmilliseconds() const {
    return milliseconds;
}

QString LyricLine::gettext() const {
    return text;
}

/////////////////////////////////////////
/// \brief LyricFactoory::LyricFactoory
/// \param parent
/////////////////////////////////////////////

LyricFactory::LyricFactory(QObject *parent) :
    QObject(parent)
{
    m_currentIndex = 0;
}

bool LyricFactory::LoadLyricFile(const QString &fileName)
{
    clearData();
    setcurrentIndex(0);
    QFile flyric(fileName);
    if (!flyric.open(QIODevice::ReadOnly | QIODevice::Text)) {        
        lyricData.clear();
        return false;
    }
    bool ok;
    QString textLine;
    QTextStream sin(& flyric);
    sin.setCodec("GB18030");

    int milliseconds;
    while (! sin.atEnd()) {
        textLine = sin.readLine();
        textLine.mid(1,1).toInt(& ok, 10);
        if (! ok) {
            continue;
        }
        milliseconds = (textLine.mid(1,2).toInt(& ok) * 60 +
                        textLine.mid(4,2).toInt(& ok)) * 1000 +
                textLine.mid(7,2).toInt(& ok) * 10;
        textLine = textLine.mid(10);
        lyricData.append(LyricLine(milliseconds, textLine));
    }
    flyric.close();
    return true;
}

int LyricFactory::findIndex(int position)
{
    if (lyricData.isEmpty()) return 0;

    //bug fix
    if (position == 0) {
        setcurrentIndex(0);
        return 0;
    }

    //bug fix end
    int countless = lyricData.count() - 1, mid = lyricData.count() / 2, diff = mid / 2;
    while (1) {
        if (lyricData.at(mid).getmilliseconds() <= position) {
            if (mid < countless && lyricData.at(mid + 1).getmilliseconds() > position) {
                break;
            } else {
                mid += diff;
            }
        } else {
            mid -= diff;
        }
        diff /= 2;
        if (diff == 0) {
            break;
        }
    }
    setcurrentIndex(mid);
    return mid;
}

void LyricFactory::SetIndex(int position)
{
    // 计算该行停留时间
    if (m_currentIndex + 1 < lyricData.count()) {
        int millSec = lyricData.at(m_currentIndex + 1).getmilliseconds() / 1000;
        if (millSec <= position) {
            m_currentIndex ++;
            emit currentIndexChanged(m_currentIndex);
        }
    }
}

void LyricFactory::setcurrentIndex(const int &i)
{
    if ((i >= 0 && (i < lyricData.count())) && m_currentIndex != i) {
        m_currentIndex = i;
        emit currentIndexChanged(m_currentIndex);
    }
}

QString LyricFactory::getTextline(int index)
{
    if ((index + 1) < lyricData.count()) {
        return lyricData.at(index).gettext();
    }

    return "";
}

QStringList LyricFactory::getLyricTexts()
{
    QStringList strLyrics;
    foreach (LyricLine line, lyricData) {
        strLyrics.append(line.gettext());
    }

    return strLyrics;
}

void LyricFactory::clearData()
{
    lyricData.clear();
    m_currentIndex = 0;
}
