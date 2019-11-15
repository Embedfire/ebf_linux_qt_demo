/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : videowidget.h --- VideoWidget
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef QTVIDEOWIDGET_H
#define QTVIDEOWIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QTimer>

#include "qtplaytoolbar.h"
#include "qtvideowidgetsurface.h"
#include "videoplaylistwidget.h"
#include "qtsliderbar.h"

/////////////////////////////////////////////////////////////////////
/// \brief The VideoWidget class
///
class QtVideoWidget : public QtWidgetBase
{
    Q_OBJECT
public:
    explicit QtVideoWidget(QWidget *parent = 0);
    ~QtVideoWidget();

    void setMedia(const QString &name, int index);

    // 播放列表
    MediaPlayListWidget *m_playList;
signals:

public slots:

private:
    QMediaPlayer    *m_player;
    PlayTitleBarWidget  *m_titleBar;
    PlayerBarWidget *m_playBar;

    QtVideoWidgetSurface *surface;

    qint64      m_nDuration;
    qint64      m_nPostion;
    QUrl        m_urlMedia;

    // 停留自动关闭
    QTimer     *m_timerShow;
    bool        m_bToolBarShow;

    QtSliderBar *m_volumeSlider;
private:
    void ShowToolBar();

private slots:
    void SltAutoCloseToolBar();

    void SltBackClicked();
    void SltBtnPlayClicked(bool bOk);
    void SltPostionChanged(qint64 postion);
    void SltDurationChanged(qint64 duration);
    void SltChangePostion(int postion);

    void SltShowMenuList();
    void SltChangeVolume();
protected:
    void resizeEvent(QResizeEvent *event);

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *);
};

#endif // QTVIDEOWIDGET_H
