/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : lyricwidget.h --- LyricWidget
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef LYRICWIDGET_H
#define LYRICWIDGET_H

#include "qtwidgetbase.h"
#include "lyricfactory.h"
#include "netdownlyric.h"

//#define AUTO_DOWNLOAD_LYRIC

class LyricWidget : public QtWidgetBase
{
    Q_OBJECT
public:
    explicit LyricWidget(QWidget *parent = 0);
    ~LyricWidget();

    void LoadLyricFile(const QString &name, const QString &path);
    void ChangePostion(qint64 postion);
    void ShowErrorString();
    void SetLyricPostion(int postion);
signals:

public slots:

private:
    LyricFactory   *m_lyricFactory;
#ifdef AUTO_DOWNLOAD_LYRIC
    NetdownLyric   *m_networkLyric;
#endif

    QStringList     m_strLyricLines;
    QString         m_strSongName;

    qreal           m_lineHeight;

    int             m_nCurrentIndex;
    int             m_nStartIndex;
    QString         m_strLyricPath;

    bool            m_bLyricLoad;
    bool            m_bError;
    int             m_nShowCount;
private slots:
    void SltCurrentIndexChanged(int index);
    void SltLoadNetLyric(const QString &file);

protected:
    void paintEvent(QPaintEvent *);
    void drawLyricLines(QPainter *painter);
};

#endif // LYRICWIDGET_H
