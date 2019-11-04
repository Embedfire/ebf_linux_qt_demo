#include "v4l2cam.h"

#include <iosfwd>

#include <QDebug>
#include <QTextStream>

V4l2Cam::V4l2Cam(uint videoNum) : fd(-1)
{
    sprintf(cameraaddr,"/dev/video%d",videoNum);
    if ((fd = open(cameraaddr, O_RDWR)) == -1){
        qDebug() << "open failed" << cameraaddr;
        return;
    }
    queryam();
}

V4l2Cam::V4l2Cam()
{

}

V4l2Cam::~V4l2Cam()
{
    if (-1 != fd)
    {
        close(fd);
    }
}

int V4l2Cam::OPenCamera(int videoNum)
{
    sprintf(cameraaddr,"/dev/video%d",videoNum);
    if ((fd = open(cameraaddr, O_RDWR)) == -1){
        qDebug() << "open failed" << cameraaddr;
        return -1;
    }
    queryam();
    return 0;
}

int V4l2Cam::queryam()
{
    struct v4l2_capability cap;
    memset(&cap, 0, sizeof(struct v4l2_capability));
    if (ioctl(fd, VIDIOC_QUERYCAP, &cap) == -1){
        qDebug() << "ERROR:unable Querying Capabilities";
        return -1;
    }
    devName = ((char*)cap.card);

    struct v4l2_fmtdesc fmtdesc;
    struct v4l2_frmsizeenum frmsize;
    fmtdesc.index = 0;
    fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    while(ioctl(fd,VIDIOC_ENUM_FMT,&fmtdesc) != -1)
    {
        formatType type;
        type.index = fmtdesc.index++;
        type.description = ((char*)fmtdesc.description);
        frmsize.pixel_format = fmtdesc.pixelformat;
        frmsize.index = 0;
        while (ioctl(fd, VIDIOC_ENUM_FRAMESIZES, &frmsize) >= 0)
        {
#if 0
            QTextStream ss;
            if(frmsize.type == V4L2_FRMSIZE_TYPE_DISCRETE){
                ss << frmsize.discrete.width << "x" << frmsize.discrete.height;
                type.framesize.push_back(ss.readAll().toLatin1().data());
            }else if(frmsize.type == V4L2_FRMSIZE_TYPE_STEPWISE){
                ss << frmsize.discrete.width << "x" << frmsize.discrete.height;
                type.framesize.push_back(ss.readAll().toLatin1().data());
            }
#endif
            frmsize.index++;
        }
        FormatType.push_back(type);
    }

    return 0;
}

int V4l2Cam::setPixelformat(uint32_t width, uint32_t height, uint32_t format, uint32_t field){
    struct v4l2_format fmt;
    memset(&fmt, 0, sizeof(struct v4l2_format));
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    v4l2img.imgwidth = width;
    v4l2img.imgheight = height;

    fmt.fmt.pix.width = width;
    fmt.fmt.pix.height = height;

    imgWidth = width;
    imgHeight = height;

    Width = fmt.fmt.pix.width;
    Height = fmt.fmt.pix.height;

    fmt.fmt.pix.pixelformat = format;
    fmt.fmt.pix.field = field;
    if (ioctl(fd, VIDIOC_S_FMT, &fmt) == -1){
        qDebug() << "Setting Pixel Format failed [VIDIOC_S_FMT]" << fd;
//        return -1;
    }

    if (ioctl(fd, VIDIOC_G_FMT, &fmt) == -1){
        qDebug() << "Setting Pixel Format failed [VIDIOC_G_FMT]" << fd;
//        return -1;
    }

    qDebug() << "setok " << fd << v4l2img.imgwidth << v4l2img.imgheight;
    return 0;
}

int V4l2Cam::setFps(uint32_t fps, bool HDmode){
    struct v4l2_streamparm str;
    memset(&str, 0, sizeof(struct v4l2_streamparm));
    str.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    str.parm.capture.capability = V4L2_CAP_TIMEPERFRAME;
    if(HDmode)
        str.parm.capture.capturemode = V4L2_MODE_HIGHQUALITY;
    str.parm.capture.timeperframe.numerator = 1;
    str.parm.capture.timeperframe.denominator = fps;
    if (ioctl(fd, VIDIOC_S_PARM, &str) == -1){
        qDebug() << "Setting FPS failed" ;
//        return -1;
    }
    if (ioctl(fd, VIDIOC_G_PARM, &str) == -1){
        qDebug() << "Setting FPS failed" ;
//        return -1;
    }

    Fps = str.parm.capture.timeperframe.denominator;

    return 0;
}

int V4l2Cam::memsetCam()
{
    struct v4l2_requestbuffers req;
    req.count = 1;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;
    if (ioctl(fd, VIDIOC_REQBUFS, &req) == -1)
    {
        qDebug() << "Requesting Buffer error";
        return -1;
    }

    v4l2img.addr = (uchar*)malloc(req.count * sizeof(*v4l2img.addr));
    if(!v4l2img.addr){
        qDebug() << "Out of memory";
        return -1;
    }
    for(uint32_t n_buffers = 0;n_buffers < req.count; n_buffers++)
    {
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = n_buffers;
        if(ioctl(fd, VIDIOC_QUERYBUF, &buf) == -1){
            qDebug() << "Querying Buffer error";
            return -1;
        }

        v4l2img.addr = (uchar*)mmap (NULL, buf.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, buf.m.offset);
        if(v4l2img.addr == MAP_FAILED){
            qDebug() << "Buffer map error";
            return -1;
        }
    }

    for (uint32_t n_buffers = 0; n_buffers < req.count; n_buffers++)
    {
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = n_buffers;
        if (ioctl(fd, VIDIOC_QBUF, &buf) == -1)
        {
            qDebug() << "Querying Buffer error";
            return -1;
        }
    }

    enum v4l2_buf_type type;
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if (ioctl(fd,VIDIOC_STREAMON,&type) == -1){
        qDebug() << "Stream on error" ;
        return -1;
    }

    Camera_Read();
    return 0;
}

int V4l2Cam::getBrightness()
{
    struct v4l2_control ctrl;
    int ret;
    ctrl.id = V4L2_CID_BRIGHTNESS;
    ret = ioctl(fd, VIDIOC_G_CTRL, &ctrl);
    if(ret != 0) return -255;
    return ctrl.value;
}

int V4l2Cam::getContrast()
{
    struct v4l2_control ctrl;
    int ret;
    ctrl.id = V4L2_CID_CONTRAST;
    ret = ioctl(fd, VIDIOC_G_CTRL, &ctrl);
    if(ret != 0) return -255;
    return ctrl.value;
}

int V4l2Cam::getHUE()
{
    struct v4l2_control ctrl;
    int ret;
    ctrl.id = V4L2_CID_HUE;
    ret = ioctl(fd, VIDIOC_G_CTRL, &ctrl);
    if(ret != 0) return -255;
    return ctrl.value;
}

int V4l2Cam::getSaturation()
{
    struct v4l2_control ctrl;
    int ret;
    ctrl.id = V4L2_CID_SATURATION;
    ret = ioctl(fd, VIDIOC_G_CTRL, &ctrl);
    if(ret != 0) return -255;
    return ctrl.value;
}

int V4l2Cam::getGAMMA()
{
    struct v4l2_control ctrl;
    int ret;
    ctrl.id = V4L2_CID_GAMMA;
    ret = ioctl(fd, VIDIOC_G_CTRL, &ctrl);
    if(ret != 0) return -255;
    return ctrl.value;
}

int V4l2Cam::getWhiteBalance()
{
    struct v4l2_control ctrl;
    int ret;
    ctrl.id = V4L2_CID_WHITENESS;
    ret = ioctl(fd, VIDIOC_G_CTRL, &ctrl);
    if(ret != 0) return -255;
    return ctrl.value;
}

int V4l2Cam::getAutoWhiteBalance()
{
    struct v4l2_control ctrl;
    int ret;
    ctrl.id = V4L2_CID_AUTO_WHITE_BALANCE;
    ret = ioctl(fd, VIDIOC_G_CTRL, &ctrl);
    if(ret != 0) return -255;
    return (bool)ctrl.value;
}

int V4l2Cam::getGain()
{
    struct v4l2_control ctrl;
    int ret;
    ctrl.id = V4L2_CID_GAIN;
    ret = ioctl(fd, VIDIOC_G_CTRL, &ctrl);
    if(ret != 0) return -255;
    return ctrl.value;
}

int V4l2Cam::getAutoGain()
{
    struct v4l2_control ctrl;
    int ret;
    ctrl.id = V4L2_CID_AUTOGAIN;
    ret = ioctl(fd, VIDIOC_G_CTRL, &ctrl);
    if(ret != 0) return -255;
    return (bool)ctrl.value;
}

int V4l2Cam::getExposure()
{
    struct v4l2_control ctrl;
    int ret;
    ctrl.id = V4L2_CID_EXPOSURE;
    ret = ioctl(fd, VIDIOC_G_CTRL, &ctrl);
    if(ret != 0) return -255;
    return ctrl.value;
}

int V4l2Cam::getAutoExposure()
{
    struct v4l2_control ctrl;
    int ret;
    ctrl.id = V4L2_CID_EXPOSURE_AUTO;
    ret = ioctl(fd, VIDIOC_G_CTRL, &ctrl);
    if(ret != 0) return -255;
    if(ctrl.value == 1)
        return false;
    else
        return true;
}


int V4l2Cam::setBrightness(int value)
{
    struct v4l2_control ctrl;
    int ret;
    ctrl.id = V4L2_CID_BRIGHTNESS;
    ctrl.value = value;
    ret = ioctl(fd, VIDIOC_S_CTRL, &ctrl);
    if(ret != 0) return -1;
    return 0;
}

int V4l2Cam::setContrast(int value)
{
    struct v4l2_control ctrl;
    int ret;
    ctrl.id = V4L2_CID_CONTRAST;
    ctrl.value = value;
    ret = ioctl(fd, VIDIOC_S_CTRL, &ctrl);
    if(ret != 0) return -1;
    return 0;
}

int V4l2Cam::setHUE(int value)
{
    struct v4l2_control ctrl;
    int ret;
    ctrl.id = V4L2_CID_HUE;
    ctrl.value = value;
    ret = ioctl(fd, VIDIOC_S_CTRL, &ctrl);
    if(ret != 0) return -1;
    return 0;
}

int V4l2Cam::setSaturation(int value)
{
    struct v4l2_control ctrl;
    int ret;
    ctrl.id = V4L2_CID_SATURATION;
    ctrl.value = value;
    ret = ioctl(fd, VIDIOC_S_CTRL, &ctrl);
    if(ret != 0) return -1;
    return 0;
}

int V4l2Cam::setGAMMA(int value)
{
    struct v4l2_control ctrl;
    int ret;
    ctrl.id = V4L2_CID_GAMMA;
    ctrl.value = value;
    ret = ioctl(fd, VIDIOC_S_CTRL, &ctrl);
    if(ret != 0) return -1;
    return 0;
}

int V4l2Cam::setWhiteBalance(int value)
{
    struct v4l2_control ctrl;
    int ret;
    ctrl.id = V4L2_CID_WHITENESS;
    ctrl.value = value;
    ret = ioctl(fd, VIDIOC_S_CTRL, &ctrl);
    if(ret != 0) return -1;
    return 0;
}

int V4l2Cam::setAutoWhiteBalance(bool value)
{
    struct v4l2_control ctrl;
    int ret;
    ctrl.id = V4L2_CID_AUTO_WHITE_BALANCE;
    ctrl.value = value;
    ret = ioctl(fd, VIDIOC_S_CTRL, &ctrl);
    if(ret != 0) return -1;
    return 0;
}

int V4l2Cam::setGain(int value)
{
    struct v4l2_control ctrl;
    int ret;
    ctrl.id = V4L2_CID_GAIN;
    ctrl.value = value;
    ret = ioctl(fd, VIDIOC_S_CTRL, &ctrl);
    if(ret != 0) return -1;
    return 0;
}

int V4l2Cam::setAutoGain(bool value)
{
    struct v4l2_control ctrl;
    int ret;
    ctrl.id = V4L2_CID_AUTOGAIN;
    ctrl.value = value;
    ret = ioctl(fd, VIDIOC_S_CTRL, &ctrl);
    if(ret != 0) return -1;
    return 0;
}

int V4l2Cam::setExposure(int value)
{
    struct v4l2_control ctrl;
    int ret;
    ctrl.id = V4L2_CID_EXPOSURE;
    ctrl.value = value;
    ret = ioctl(fd, VIDIOC_S_CTRL, &ctrl);
    if(ret != 0) return -1;
    return 0;
}

int V4l2Cam::setAutoExposure(bool value)
{
    struct v4l2_control ctrl;
    int ret;
    ctrl.id = V4L2_CID_EXPOSURE_AUTO_PRIORITY;
    ctrl.value = value;
    ret = ioctl(fd, VIDIOC_S_CTRL, &ctrl);
    if(ret != 0) return -1;
    return 0;
}

v4l2pic* V4l2Cam::Camera_Read()
{
    ioctl(fd,VIDIOC_DQBUF,&buf);
    buf.index = 0;
    memcpy(&pic2send, &v4l2img, sizeof(v4l2img));
    ioctl(fd, VIDIOC_QBUF, &buf);
    return &pic2send;
}

int V4l2Cam::releaseMen()
{
    if(buf.length > 1)
    {
        munmap(v4l2img.addr, buf.length);
        close(fd);
        return 0;
    }
    else
        return -1;
}

void V4l2Cam::CloseDev()
{
    munmap(v4l2img.addr, buf.length);
    close(fd);
    fd = -1;
}
