/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : qtvideowidgetsurface.h --- QtVideoWidgetSurface
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/22
*******************************************************************/
#ifndef QTVIDEOWIDGETSURFACE_H
#define QTVIDEOWIDGETSURFACE_H

#include <QWidget>
#include <QImage>

#include <QtMultimedia/QAbstractVideoSurface>
#include <QtMultimedia/QVideoSurfaceFormat>

//////////////////////////////////////////////////////////////////
/// \brief The VideoWidgetSurface class
/// 视频帧解析
#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT QtVideoWidgetSurface : public QAbstractVideoSurface {
#else
class QtVideoWidgetSurface : public QAbstractVideoSurface {
#endif
    Q_OBJECT
public:
    QtVideoWidgetSurface(QWidget *widget, QObject *parent = 0);

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;
    bool isFormatSupported(const QVideoSurfaceFormat &format) const;

    bool start(const QVideoSurfaceFormat &format);
    void stop();

    bool present(const QVideoFrame &frame);

    QRect videoRect() const { return targetRect; }
    void updateVideoRect();

    void paint(QPainter *painter);

    bool takePhoto(const QString &fileName, const QSize &size = QSize(800, 480));
private:
    QWidget *widget;
    QImage::Format imageFormat;
    QRect targetRect;
    QSize imageSize;
    QRect sourceRect;
    QVideoFrame currentFrame;
};

/////////////////////////////////////////////////////////////////////


#endif // QTVIDEOWIDGETSURFACE_H
