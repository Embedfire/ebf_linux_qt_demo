/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : camerawidget.cpp ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/15
           2021/2/22
*******************************************************************/
#include "camerawidget.h"
#include "skin.h"

#include <QDateTime>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QMouseEvent>
#include <QApplication>
#include <QCameraInfo>
#include <QHBoxLayout>

#include <QCoreApplication>

#include "qtswitchbutton.h"

#ifdef __arm__
#define DEFAULT_DEVICE      1
#else
#define DEFAULT_DEVICE      0
#endif

CameraWidget::CameraWidget(QWidget *parent) : QtAnimationWidget(parent)
{
    m_strPhotoPath = qApp->applicationDirPath() + "/photos/";
    m_pixmapMenu = QPixmap(":/images/camera/menu_icon.png");

    m_bPhotoPressed = false;
    m_bConfigPressed = false;
    m_bMenuPressed = false;
    m_bOpenDevice = false;

#if TEST_PROCESS_CAMERA
    m_cmd = new QProcess(this);
#endif

    //m_camera = NULL;
    surface = NULL;

    m_rectMenu = QRect(m_nBaseWidth - 10 - m_pixmapMenu.width(), 2, m_pixmapMenu.width(), m_pixmapMenu.height());
#ifndef __arm__
    m_rectConfig = QRect(m_nBaseWidth - 50 - 80, m_nBaseHeight - 64, 80, 20);
#endif

    m_configWidget = new CameraConfig(this);

#if !TEST_PROCESS_CAMERA
    QTimer::singleShot(500, this, SLOT(InitCamera()));
#endif
}

CameraWidget::~CameraWidget()
{
#if TEST_PROCESS_CAMERA
    if  (m_cmd->state() != QProcess::NotRunning) {
        m_cmd->kill();
        qDebug() << "kill";
    }
#endif
}

void CameraWidget::TakePhotos()
{
    m_strInfoMsg = QString("照相失败！");
    if (NULL != m_camera) {
        QString strFileName = m_strPhotoPath + "Img_";
        strFileName += QDateTime::currentDateTime().toString("yyyyMMddhhmss");
        strFileName += ".png";
//        if (surface->takePhoto(strFileName, m_configWidget->photoSize())) {
//            m_strInfoMsg = QString("相片保存：%1").arg(strFileName);
//        }
    }

    this->update();
    QTimer::singleShot(1000, this, SLOT(SltClearMessage()));
}

void CameraWidget::InitCamera()
{
#if TEST_PROCESS_CAMERA
    m_cmd->start("gst-launch-1.0 imxv4l2src device=/dev/video1 ! imxv4l2sink");
#else
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    foreach (const QCameraInfo &cameraInfo, cameras) {

//        m_camera = new QCamera(cameraInfo);
        if (cameraInfo == QCameraInfo::defaultCamera())
        {
            qDebug() << cameraInfo.deviceName();
            m_camera.reset(new QCamera(cameraInfo));
            //m_camera= new QCamera(cameraInfo);
            break;
        }
    }

    if (NULL != m_camera) {
//        surface = new QtVideoWidgetSurface(this);
//        surface = new QCameraViewfinder(this);

        m_imageCapture.reset(new QCameraImageCapture(m_camera.data()));

        connect(m_imageCapture.data(), &QCameraImageCapture::readyForCaptureChanged, this, &CameraWidget::readyForCapture);
        connect(m_imageCapture.data(), &QCameraImageCapture::imageCaptured, this, &CameraWidget::processCapturedImage);
        connect(m_imageCapture.data(), &QCameraImageCapture::imageSaved, this, &CameraWidget::imageSaved);
        connect(m_imageCapture.data(), QOverload<int, QCameraImageCapture::Error, const QString &>::of(&QCameraImageCapture::error),
                this, &CameraWidget::displayCaptureError);


        surface = new QtViewFinder(this);
        connect(surface,SIGNAL(returnbtn_clicked_signal()),this, SLOT(on_clieckBackhome()));
        connect(surface,SIGNAL(take_picture_signal()),this, SLOT(on_takePicture()));
        surface->setGeometry(0,0,this->width(),this->height());
        surface->setEnabledTake(false);

        m_camera->setViewfinder(surface);

        QCameraViewfinderSettings set;
        set.setResolution(1280, 720);
        m_camera->setViewfinderSettings(set);


//        m_mediaRecorder.reset(new QMediaRecorder(m_camera.data()));
//        m_imageCapture.reset(new QCameraImageCapture(m_camera.data()));
//        m_mediaRecorder->setMetaData(QMediaMetaData::Title, QVariant(QLatin1String("Test Title")));

//        QHBoxLayout *mainlayout = new QHBoxLayout;
//        this->setLayout(mainlayout);
//        mainlayout->addWidget(surface);

        surface->show();
        //qDebug()<<surface->width()<<surface->height();
        surface->setSize(surface->width(),surface->height());


        m_camera->start();


        //m_configWidget->show();
    }
#endif
}
void CameraWidget::on_clieckBackhome()
{
    m_camera->stop();
    emit signalBackHome();
}


void CameraWidget::on_takePicture()
{
    qDebug()<<"takepicture";

    //获取程序当前运行目录
    QString filepath = QCoreApplication::applicationDirPath();
    filepath+="/photos/";
    qDebug()<<filepath;
    m_imageCapture->capture(filepath);
}
void CameraWidget::readyForCapture(bool ready)
{
    qDebug()<<"ready:"<<ready;
    //ui->takeImageButton->setEnabled(ready);
    surface->setEnabledTake(ready);
}
void CameraWidget::imageSaved(int id, const QString &fileName)
{
    qDebug()<<"id:"<<id<<"fileName:"<<fileName;

    Q_UNUSED(id);
//    ui->statusbar->showMessage(tr("Captured \"%1\"").arg(QDir::toNativeSeparators(fileName)));

//    m_isCapturingImage = false;
//    if (m_applicationExiting)
//        close();
    surface->loadImage(fileName);
}
void CameraWidget::processCapturedImage(int requestId, const QImage& img)
{
    qDebug()<<"requestId:"<<requestId;

    Q_UNUSED(requestId);
    QImage scaledImage = img.scaled(surface->size(),
                                    Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation);

    //ui->lastImagePreviewLabel->setPixmap(QPixmap::fromImage(scaledImage));

    //Display captured image for 4 seconds.
    //displayCapturedImage();
    //QTimer::singleShot(4000, this, &Camera::displayViewfinder);
}
void CameraWidget::displayCaptureError(int id, const QCameraImageCapture::Error error, const QString &errorString)
{
    qDebug()<<"id:"<<id<<"error:"<<error<<"errorString:"<<errorString;

    Q_UNUSED(id);
    Q_UNUSED(error);
    //QMessageBox::warning(this, tr("Image Capture Error"), errorString);
    //m_isCapturingImage = false;
}



void CameraWidget::SltClearMessage()
{
    m_strInfoMsg.clear();
    this->update();
}

void CameraWidget::showEvent(QShowEvent *e)
{
#if TEST_PROCESS_CAMERA
    if  (m_cmd->state() == QProcess::NotRunning) {
        m_cmd->start("gst-launch-1.0 imxv4l2src device=/dev/video1 ! imxv4l2sink");
    }
#endif
    QWidget::showEvent(e);
}

void CameraWidget::resizeEvent(QResizeEvent *e)
{
    SetScaleValue();
    m_configWidget->setFixedSize(434 * m_scaleX, 360 * m_scaleY);
    m_configWidget->move((this->width() - m_configWidget->width()) / 2, -m_configWidget->height());
    QWidget::resizeEvent(e);
}

void CameraWidget::mousePressEvent(QMouseEvent *e)
{
    QRect rect;
    ScaleRect(rect, m_rectPhoto);
    if (rect.contains(e->pos())) {
        m_bPhotoPressed = true;
        this->update();
        return;
    }

    ScaleRect(rect, m_rectMenu);
    if (rect.contains(e->pos())) {
        m_bMenuPressed = true;
        m_pixmapMenu = QPixmap(":/images/camera/menu_icon_pressed.png");
        this->update();
        return;
    }

    ScaleRect(rect, m_rectConfig);
    if (rect.contains(e->pos())) {
        m_bConfigPressed = true;
        this->update();
        return;
    }
#if TEST_PROCESS_CAMERA
    if  (m_cmd->state() != QProcess::NotRunning) {
        m_cmd->kill();
    }
    emit signalBackHome();
#endif
}

void CameraWidget::mouseReleaseEvent(QMouseEvent *e)
{
//    if (m_bPhotoPressed) {
//        m_bPhotoPressed = false;
//        TakePhotos();
//    } else if (m_bMenuPressed) {
//        m_bMenuPressed = false;
//        m_pixmapMenu = QPixmap(":/images/camera/menu_icon.png");
//        this->update();
//        emit signalBackHome();
//    } else if (m_bConfigPressed) {
//        m_bConfigPressed = false;
//        this->update();

//        int nX = (this->width() - m_configWidget->width()) / 2;
//        if (m_configWidget->y() < 0) {
//            m_configWidget->StartAnimation(QPoint(nX, -m_configWidget->height()), QPoint(nX, 0), 200, true);
//        }
//        else {
//            m_configWidget->StartAnimation(QPoint(nX, 0), QPoint(nX, -m_configWidget->height()), 200, false);
//        }
//    }

    QWidget::mouseReleaseEvent(e);
}

void CameraWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.scale(m_scaleX, m_scaleY);
    painter.fillRect(QRect(0, 0, m_nBaseWidth, m_nBaseHeight), QColor("#000000"));

#ifndef __arm__
    if (!m_strInfoMsg.isEmpty()) {
        painter.setPen(Qt::white);
        painter.drawText(10, 10, m_nBaseWidth - 20, 30, Qt::AlignVCenter, m_strInfoMsg);
    }

    if (NULL  != m_camera) {
        if (surface->isActive()) {
            surface->paint(&painter);
        }
    } else {
        painter.setPen(Qt::white);
        QFont font = painter.font();
        font.setPixelSize(28);
        painter.setFont(font);
        painter.drawText(QRect(0, 0, m_nBaseWidth, m_nBaseHeight), Qt::AlignCenter, tr("照相机打开失败！"));
    }
#endif

    // 绘制按钮
    //drawToolButton(&painter);
}

void CameraWidget::drawToolButton(QPainter *painter)
{
    painter->save();
    painter->drawPixmap(m_rectMenu, m_pixmapMenu);
#ifndef __arm__
    // draw big
    int radius = 80;
    int nX = (m_nBaseWidth - radius) / 2;
    int nY = m_nBaseHeight - radius - 24;
    painter->setPen(QPen(QColor("#ffffff"), 4));
    painter->drawArc(nX, nY, radius, radius, 0, 360 * 16);
    m_rectPhoto = QRect(nX, nY, radius, radius);

    radius = 60;
    nX = (m_nBaseWidth - radius) / 2;
    nY += 10;
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_bPhotoPressed ? QColor("#02a7f0") : QColor("#ffffff"));
    painter->drawEllipse(nX, nY, radius, radius);

    painter->setBrush(m_bConfigPressed ? QColor("#02a7f0") : QColor("#ffffff"));
    radius = 20;
    nX = m_rectConfig.left();
    nY = m_rectConfig.top();
    painter->drawEllipse(nX, nY, radius, radius);
    painter->drawEllipse(nX + 30, nY, radius, radius);
    painter->drawEllipse(nX + 60, nY, radius, radius);
#endif
    painter->restore();
}

