/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : mainwindow.h ---
 作 者    : Niyh(lynnhua)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include "launcherwidget.h"
#include "qtwidgetbase.h"
#include "aboutus.h"
#include "threadkey.h"
#include "threadmousecheck.h"

// 声卡
#define VOICE_DEV       "/dev/snd/pcmC0D0p"
// ADC
#define ADC_DEV         "/sys/bus/iio/devices/iio:device0/in_voltage3_raw"
// 摄像头
#define CAMERA_DEV      "/dev/video0"
// DHT11
#define DHT11_DEV       "/dev/dht11"
// RGB彩灯
#define RGB_DEV         "/sys/class/leds/red"
// RGB-红
#define RGB_RED_DEV     "/sys/class/leds/red/brightness"
// RGB-绿
#define RGB_GREEN_DEV   "/sys/class/leds/green/brightness"
// RGB-蓝
#define RGB_BLUE_DEV    "/sys/class/leds/blue/brightness"
// 陀螺仪MPU6050
#define MPU6050_DEV     "/sys/bus/iio/devices/iio\:device1"
// 背光
#define BKLIGHT_DEV     "/sys/class/backlight/backlight/brightness"
// 蜂鸣器
#define BEEP_DEV        "/sys/class/gpio/gpio19"
// keyboard
#define KEY_DEV         "/dev/input/by-path/platform-sgpio-keys-event"
// switch
#define POWER_DEV       "/dev/input/by-path/platform-20cc000.snvs:snvs-powerkey-event"

class MusicPlayer;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    LauncherWidget      *m_launcherWidget;
    QMap<int, LauncherItem*> m_launchItems;

    AboutUs             *m_aboutUs;
    QtAnimationWidget   *m_widgetWorkSpace;
    MusicPlayer         *m_musicWidget;

    int                  m_nCurrentIndex;
    bool                 m_bStartApp;

    ThreadMouseCheck    *m_threadUsbInsert;
    ThreadKey           *m_threadPowerKey;
    ThreadKey           *m_threadKey;

#ifdef CHECK_MOUSE_BY_TIMER
    int              m_nMouseCheckId;
#endif
private:
    void InitWidget();
    void InitDesktop();
    void InitThreads();

    bool CheckDevice(QString device);
private slots:
    void SltCurrentAppChanged(int index);

    void SltBackHome();
    void SltChangeCursorShap(Qt::CursorShape shape);
    void SltAppStartOk();

    void SltMouseInsert(bool bOk);

protected:
    void resizeEvent(QResizeEvent *e);
#ifdef BUILD_WIN_NES
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
#endif

    // 新增鼠标检测
    bool CheckMouseInsert();

#if CHECK_MOUSE_BY_TIMER
    void timerEvent(QTimerEvent *e);
#endif
};

#endif // MAINWINDOW_H
