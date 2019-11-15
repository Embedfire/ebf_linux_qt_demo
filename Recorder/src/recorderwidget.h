/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : recorderwidget.h ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/10/10
*******************************************************************/
#ifndef RECORDERWIDGET_H
#define RECORDERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QMediaPlayer>
#include <QPushButton>

#include "qtwidgetbase.h"
#include "arecordwidget.h"
#include "qtsliderbar.h"
#include "wavplaylistwidget.h"
#include "qtpixmapbutton.h"

class RecorderWidget : public QtAnimationWidget
{
    Q_OBJECT
public:
    RecorderWidget(QWidget *parent = 0);
    ~RecorderWidget();

private:
    void InitWidget();
    QTime GetTimeByPostion(int postion);

private slots:
    void InitPlayList();
    void SltBtnPlayClicked();

    void SltDurationChanged(qint64 duration);
    void SltPostionChanged(qint64 postion);
    void stateChanged(QMediaPlayer::State newState);
    void SltChangePostion(int postion);

    void SltBtnClicked(int index);

private:
    ARecordWidget       *m_recordWidget;
    WavPlayListWidget   *m_playlistWidget;

    QtSliderBar         *m_progressBar;
    QtSliderBar         *m_sliderVolume;

    QString             m_strCurrTime;
    QString             m_strDuration;

    QMediaPlayer    *m_player;
protected:
    void resizeEvent(QResizeEvent *e);
    void paintEvent(QPaintEvent *);
};

#endif // RECORDERWIDGET_H
