/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : arecordwidget.h --- ARecordWidget
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/10/10
*******************************************************************/
#ifndef ARECORDWIDGET_H
#define ARECORDWIDGET_H

#include "qtwidgetbase.h"
#include <QTimer>

#ifdef __arm__
#include "wavobject.h"
#endif

class ARecordWidget : public QtWidgetBase
{
    Q_OBJECT
public:
    explicit ARecordWidget(QWidget *parent = 0);
    ~ARecordWidget();

    void setRecodeEnable(bool bOk);
    bool isRecording();

signals:
    void signalRecordFile(const QString &fileName);

public slots:

private:
#ifdef __arm__
    WavObject  *m_wavObject;
#endif

    bool        m_bRecording;
    bool        m_bPause;
    bool        m_bEnable;

    QString     m_strRecordPath;
    QString     m_strRecordFile;

    int         m_nTimeCount;
    QTimer      *m_timer;

    QRect       m_rectStop;
    QRect       m_rectPause;

private:
    QString getTimeString();
    void StartRecording();
    void StopRecording();
    void PauseRecording();

private slots:
    void SltBegingRecord();
    void StopTimer();

protected:
    void paintEvent(QPaintEvent *);
    void drawButtons(QPainter *painter);

    void mousePressEvent(QMouseEvent *);
};

#endif // ARECORDWIDGET_H
