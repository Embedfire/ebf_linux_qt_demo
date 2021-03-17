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
#include "qtviewfinder.h"

#include <QCamera>
#include <QCameraImageCapture>
#include <QMediaRecorder>
#include <QScopedPointer>
#include <QCameraViewfinder>
#include <QCameraViewfinderSettings>
#include <QMediaMetaData>

#include <QTimer>
#include <QProcess>


//#define GST_COMMAND_CAMERA
//#define SURFACE_CAMERA
//#define VIEWFINDER_CAMERA


//arm 直接用gst命令显示摄像头
//其他情况则使用qt库控制摄像头
//qt库又分QAbstractVideoSurface QCameraViewfinder两种方式

#ifdef __arm__
    #define GST_COMMAND_CAMERA     1
#endif

#ifndef GST_COMMAND_CAMERA
    #define SURFACE_OR_VIEWFINDER  1
#endif

class CameraWidget : public QtAnimationWidget
{
    Q_OBJECT

public:
    CameraWidget(QWidget *parent = 0);
    ~CameraWidget();

private slots:
    void on_timeout();
protected:
    void showEvent(QShowEvent *e);

    void resizeEvent(QResizeEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    void paintEvent(QPaintEvent *);
    void drawToolButton(QPainter *painter);

#if GST_COMMAND_CAMERA
private:
    QProcess *m_cmd;
    void InitCamera();
#else
    #if SURFACE_OR_VIEWFINDER
private:
    void InitCamera(const QCameraInfo &cameraInfo);
private:
    QtViewFinder *surface;
    QScopedPointer<QCamera> m_camera;
    QScopedPointer<QCameraImageCapture> m_imageCapture;
    QScopedPointer<QMediaRecorder> m_mediaRecorder;

private slots:
    void on_takePicture();
    void on_clieckBackhome();

    void readyForCapture(bool ready);
    void imageSaved(int id, const QString &fileName);
    void processCapturedImage(int requestId, const QImage& img);
    void displayCaptureError(int id, const QCameraImageCapture::Error error, const QString &errorString);
    void displayCameraError();
    #else
private:
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

    #endif
#endif
};

#endif // CAMERAWIDGET_H
