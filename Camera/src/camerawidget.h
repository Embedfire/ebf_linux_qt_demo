/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : camerawidget.h ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/15
*******************************************************************/
#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include "qtwidgetbase.h"
#include "cameraconfig.h"
#include "qtvideowidgetsurface.h"
#include <QCamera>

#include <QTimer>
#include <QProcess>

#ifdef __arm__
#define TEST_PROCESS_CAMERA     1
#else
#define TEST_PROCESS_CAMERA     0
#endif

class CameraWidget : public QtAnimationWidget
{
    Q_OBJECT

public:
    CameraWidget(QWidget *parent = 0);
    ~CameraWidget();


private:
#if TEST_PROCESS_CAMERA
    QProcess *m_cmd;
#endif
    QCamera *m_camera;
    QtVideoWidgetSurface *surface;


protected:
    QImage   m_imagePhoto;
    bool     m_bOpenDevice;

    QRect   m_rectPhoto;
    bool    m_bPhotoPressed;

    QRect   m_rectConfig;
    bool    m_bConfigPressed;

    QPixmap m_pixmapMenu;
    QRect   m_rectMenu;
    bool    m_bMenuPressed;

    QString m_strPhotoPath;
    QString m_strInfoMsg;

private:
    CameraConfig    *m_configWidget;

    void TakePhotos();

private slots:
    void InitCamera();
    void SltClearMessage();

protected:
    void showEvent(QShowEvent *e);

    void resizeEvent(QResizeEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    void paintEvent(QPaintEvent *);
    void drawToolButton(QPainter *painter);
};

#endif // CAMERAWIDGET_H
