#ifndef V4L2CAM_H
#define V4L2CAM_H

#include <QObject>

#ifdef Q_OS_UNIX
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#endif

#include <QVector>
#include <iostream>
#include <sstream>
#include <errno.h>
#include <fcntl.h>

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <string>

#include <unistd.h>

#include <malloc.h>

#ifdef QtV4l2
#if defined(V4L2CAM_LIBRARY)
#  define V4L2CAMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define V4L2CAMSHARED_EXPORT Q_DECL_IMPORT
#endif
#endif


typedef struct {
    int exposureType;
    int exposure;
    int gain;
    int whiteBalance;
    int brightness;
    int saturation;
    int contrast;
} v4l2Set;

typedef struct {
    int index;
    char* description;
    QVector<char *> framesize;
} formatType;

typedef struct {
    int imgwidth;
    int imgheight;
    uchar* addr;
} v4l2pic;

#ifdef QtV4l2
class V4L2CAMSHARED_EXPORT V4l2Cam {
#else
class V4l2Cam {
#endif
public:
    V4l2Cam(uint videoNum);
    V4l2Cam();
    ~V4l2Cam();

    int OPenCamera(int videoNum);
    v4l2pic *Camera_Read();
    v4l2pic pic2send;
    char * devName;
    void Camera_Set(v4l2Set set);

    uint32_t Width, Height, Fps;
    QVector<formatType> FormatType;

    int setPixelformat(uint32_t width = 800, uint32_t height = 480,
                       uint32_t format = V4L2_PIX_FMT_JPEG,
                       uint32_t field = V4L2_FIELD_NONE);

    int setFps(uint32_t fps = 60, bool HDmode = false);
    int memsetCam();
    int queryam();
    int releaseMen();
    void CloseDev();

    int setBrightness(int value);
    int setContrast(int value);
    int setHUE(int value);
    int setSaturation(int value);
    int setGAMMA(int value);
    int setWhiteBalance(int value);
    int setAutoWhiteBalance(bool value);
    int setGain(int value);
    int setAutoGain(bool value);
    int setExposure(int value);
    int setAutoExposure(bool value);

    int getBrightness();
    int getContrast();
    int getHUE();
    int getSaturation();
    int getGAMMA();
    int getWhiteBalance();
    int getAutoWhiteBalance();
    int getGain();
    int getAutoGain();
    int getExposure();
    int getAutoExposure();

private:
    char cameraaddr[15];
    int fd;
    struct v4l2_buffer buf;
    v4l2pic v4l2img;
    uint32_t imgWidth, imgHeight;
};

#endif // V4L2CAM_H
