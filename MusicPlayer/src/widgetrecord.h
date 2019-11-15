/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : widgetrecord.h --- WidgetRecord
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef WIDGETRECORD_H
#define WIDGETRECORD_H

#include "qtwidgetbase.h"
#include <QTimer>
#include <QPropertyAnimation>

class PixmapItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int ratote READ ratote WRITE setRatote)
public:
    PixmapItem(const QPixmap &pix, QObject *parent = 0) :
        QObject(parent),m_nRatote(0),m_pixmap(pix)
    {
    }

    int ratote() {return m_nRatote;}
    void setRatote(int value) {m_nRatote = value;}
    QPixmap pixmap() {return m_pixmap;}
private:
    int m_nRatote;
    QPixmap m_pixmap;
};

class WidgetRecord : public QtWidgetBase
{
    Q_OBJECT
public:
    explicit WidgetRecord(QWidget *parent = 0);
    ~WidgetRecord();

    void SetImage(const QImage &image);
    void Start();
    void Stop();

signals:

public slots:

private:
    PixmapItem *m_handlePixmap;
    QPixmap     m_pixmapRecord;
    QPixmap     m_pixmapArtist;

    int         m_nRotateCD;
    int         m_nRotateHandle;

    QTimer     *m_timer;
    bool        m_bPlay;

    QPropertyAnimation  *m_animationHandle;

private slots:
    void SltCicleRun();
    void SltHandleMove(const QVariant &);

protected:
    void paintEvent(QPaintEvent *);
};

#endif // WIDGETRECORD_H
