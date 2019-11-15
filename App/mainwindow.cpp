/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : mainwindow.cpp ---
 作 者    : Niyh(lynnhua)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "mainwindow.h"
#include "statusbarwidget.h"
#include "unit.h"
#include "skin.h"
#include "appconfig.h"

#include "musicplayer.h"
#include "beepwidget.h"
#include "rgblightmonitor.h"
#include "backlightwidget.h"
#include "calendarwidget.h"
#include "calculator.h"
#include "camerawidget.h"
#include "carmeterwidget.h"
#include "adcviewer.h"
#include "dhtcollection.h"
#include "ebookwidget.h"
#include "filesystemwindow.h"
#include "gyroscope.h"
#include "notepadwidget.h"
#include "photosview.h"
#include "recorderwidget.h"
#include "settingwidget.h"
#include "videoplayer.h"
#include "weatherwidget.h"
#include "keypresswidget.h"
#include "infoneswidget.h"
#include "nessimulator.h"

#ifdef BUILD_WITH_WEBVIEW
#include "browserwindow.h"
#endif

#include <QPainter>
#include <QBoxLayout>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QTimerEvent>
#include <QRegExp>

#define MOUSE_DEV_PATH       "/dev/input/by-path"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
#ifdef __arm__
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);

    // 启动检测鼠标是否接入系统
    AppConfig::m_bMouseInsert = CheckMouseInsert();
    bool bOn = AppConfig::ReadSetting("System", "mouse", true).toBool();
    this->setCursor((bOn || AppConfig::m_bMouseInsert) ? Qt::ArrowCursor : Qt::BlankCursor);
#endif

    m_widgetWorkSpace = NULL;
    m_musicWidget = NULL;
    m_nCurrentIndex = -1;
    m_bStartApp = false;

    InitWidget();
    InitDesktop();
    InitThreads();

#ifdef CHECK_MOUSE_BY_TIMER
    m_nMouseCheckId = startTimer(3000);
#endif
}

MainWindow::~MainWindow()
{
#ifdef CHECK_MOUSE_BY_TIMER
    killTimer(m_nMouseCheckId);
#endif

    delete m_aboutUs;
    m_aboutUs = NULL;

    if (NULL != m_widgetWorkSpace) {
        delete m_widgetWorkSpace;
        m_widgetWorkSpace = NULL;
    }
}

void MainWindow::InitWidget() {
    QVBoxLayout *verLayout = new QVBoxLayout(this);
    verLayout->setContentsMargins(0, 0, 0, 0);
    verLayout->setSpacing(0);

    m_launcherWidget = new LauncherWidget(this);
    m_launcherWidget->SetWallpaper(QPixmap(":/images/mainwindow/background.png"));
    connect(m_launcherWidget, SIGNAL(currentItemClicked(int)), this, SLOT(SltCurrentAppChanged(int)));
    verLayout->addWidget(m_launcherWidget, 1);

    // 广告
    m_aboutUs = new AboutUs(this);
    m_aboutUs->hide();
    connect(m_launcherWidget, SIGNAL(signalAboutClicked()), m_aboutUs, SLOT(SltStartMove()));

#if 0
    if (NULL == m_musicWidget) {
        m_musicWidget = new MusicPlayer(this);
        connect(m_musicWidget, SIGNAL(signalBackHome()), this, SLOT(SltBackHome()));
        connect(m_musicWidget, SIGNAL(signalAnimationFinished()), this, SLOT(SltAppStartOk()));
    }
#endif
}

void MainWindow::InitDesktop()
{
    bool bMiniBoard = AppConfig::ReadSetting("System", "mini", false).toBool();
#if 1
    // 第一页
    int nPage = 0;
    m_launchItems.insert(0, new LauncherItem(0, nPage, tr("文件管理"), QPixmap(":/images/mainwindow/ic_file.png")));
    m_launchItems.insert(3, new LauncherItem(3, nPage, tr("相册"), QPixmap(":/images/mainwindow/ic_photos.png")));
    m_launchItems.insert(5, new LauncherItem(5, nPage, tr("天气"), QPixmap(":/images/mainwindow/ic_weather.png")));
    m_launchItems.insert(6, new LauncherItem(6, nPage, tr("记事本"), QPixmap(":/images/mainwindow/ic_notepad.png")));
    m_launchItems.insert(7, new LauncherItem(7, nPage, tr("时钟"), QPixmap(":/images/mainwindow/ic_clock.png")));
    m_launchItems.insert(8, new LauncherItem(8, nPage, tr("电子书"), QPixmap(":/images/mainwindow/ic_ebook.png")));
    m_launchItems.insert(10, new LauncherItem(10, nPage, tr("计算器"), QPixmap(":/images/mainwindow/ic_calc.png")));

    // mini板卡取消功能
    if (!bMiniBoard) {
        m_launchItems.insert(1, new LauncherItem(1, nPage, tr("视频播放"), QPixmap(":/images/mainwindow/ic_video.png")));
        m_launchItems.insert(2, new LauncherItem(2, nPage, tr("ADC"), QPixmap(":/images/mainwindow/ic_adc.png")));
        m_launchItems.insert(4, new LauncherItem(4, nPage, tr("相机"), QPixmap(":/images/mainwindow/ic_camera.png")));
        m_launchItems.insert(9, new LauncherItem(9, nPage, tr("温湿度"), QPixmap(":/images/mainwindow/ic_temp.png")));
        m_launchItems.insert(11, new LauncherItem(11, nPage, tr("音乐播放"), QPixmap(":/images/mainwindow/ic_music.png")));
    }

    // 第二页
    nPage++;
    m_launchItems.insert(12, new LauncherItem(12, nPage, tr("RGB彩灯"), QPixmap(":/images/mainwindow/ic_light.png")));
#ifdef BUILD_WITH_WEBVIEW
    m_launchItems.insert(14, new LauncherItem(14, nPage, tr("网络浏览器"), QPixmap(":/images/mainwindow/ic_webview.png")));
#endif
    m_launchItems.insert(15, new LauncherItem(15, nPage, tr("汽车仪表"), QPixmap(":/images/mainwindow/ic_car.png")));
    m_launchItems.insert(16, new LauncherItem(16, nPage, tr("背光调节"), QPixmap(":/images/mainwindow/ic_backlight.png")));
    m_launchItems.insert(19, new LauncherItem(19, nPage, tr("按键测试"), QPixmap(":/images/mainwindow/ic_key.png")));
    m_launchItems.insert(23, new LauncherItem(23, nPage, tr("系统设置"), QPixmap(":/images/mainwindow/ic_setting.png")));

    // mini板卡取消功能
    if (!bMiniBoard) {
        m_launchItems.insert(13, new LauncherItem(13, nPage, tr("陀螺仪"), QPixmap(":/images/mainwindow/ic_gyroscope.png")));
        m_launchItems.insert(17, new LauncherItem(17, nPage, tr("蜂鸣器"), QPixmap(":/images/mainwindow/ic_beep.png")));
        m_launchItems.insert(18, new LauncherItem(18, nPage, tr("录音"), QPixmap(":/images/mainwindow/ic_record.png")));
    }

    // 第三页
    nPage++;
    m_launchItems.insert(24, new LauncherItem(24, nPage, tr("InfoNES模拟器"), QPixmap(":/images/mainwindow/ic_game.png")));

    m_launcherWidget->SetItems(m_launchItems);
#endif
}

void MainWindow::InitThreads()
{
    m_threadUsbInsert = new ThreadMouseCheck(this);
    connect(m_threadUsbInsert, SIGNAL(signalMouseInsert(bool)), this, SLOT(SltMouseInsert(bool)));
#ifdef __arm__
    m_threadUsbInsert->start();
#endif

    m_threadPowerKey = new ThreadKey(this);
    m_threadKey = new ThreadKey(this, 1);

    m_threadPowerKey->start();
    m_threadKey->start();
}

void MainWindow::SltCurrentAppChanged(int index)
{
    if (m_bStartApp) return;
    m_launcherWidget->setEnabled(false);
    m_bStartApp = true;

    if (NULL != m_widgetWorkSpace ) {
        if (m_nCurrentIndex != index) {
            disconnect(m_widgetWorkSpace, SIGNAL(signalBackHome()), this, SLOT(SltBackHome()));
            delete m_widgetWorkSpace;
            m_widgetWorkSpace = NULL;
        } else {
            m_widgetWorkSpace->setVisible(true);
            m_widgetWorkSpace->StartAnimation(QPoint(this->width(), this->height()), QPoint(0, 0), 300, true);
            return;
        }
    }

    switch (index) {
    case 0: {
        m_widgetWorkSpace = new FileSystemWindow(this);
    }
        break;
    case 1: {
        if (NULL != m_musicWidget) {
            m_musicWidget->StopMusic();
        }
        //
        m_widgetWorkSpace = new VideoPlayer(this);
    }
        break;
    case 2: {
        m_widgetWorkSpace = new AdcViewer(this);
    }
        break;
    case 3: {
        m_widgetWorkSpace = new PhotosView(this);
    }
        break;
    case 4: {
        m_widgetWorkSpace = new CameraWidget(this);
    }
        break;
    case 5: {
        m_widgetWorkSpace = new WeatherWidget(this);
    }
        break;
    case 6: {
        m_widgetWorkSpace = new NotePadWidget(this);
    }
        break;
    case 7: {
        m_widgetWorkSpace = new CalendarWidget(this);
    }
        break;
    case 8: {
        m_widgetWorkSpace = new EBookWidget(this);
    }
        break;
    case 9: {
        m_widgetWorkSpace = new DhtCollection(this);
    }
        break;
    case 10: {
        m_widgetWorkSpace = new Calculator(this);
    }
        break;
    case 11: {
        //        m_widgetWorkSpace = new MusicPlayer(this);
        m_nCurrentIndex = index;
        if (NULL == m_musicWidget) {
            m_musicWidget = new MusicPlayer(this);
            connect(m_musicWidget, SIGNAL(signalBackHome()), this, SLOT(SltBackHome()));
            connect(m_musicWidget, SIGNAL(signalAnimationFinished()), this, SLOT(SltAppStartOk()));
        }

        m_musicWidget->resize(this->size());
        m_musicWidget->setVisible(true);
        m_musicWidget->StartAnimation(QPoint(this->width(), this->height()), QPoint(0, 0), 300, true);
        return;
    }
        break;
    case 12: {
        m_widgetWorkSpace = new RgbLightMonitor(this);
    }
        break;
    case 13: {
        m_widgetWorkSpace = new Gyroscope(this);
    }
        break;
    case 14: {
#ifdef BUILD_WITH_WEBVIEW
        m_widgetWorkSpace = new BrowserWindow(this);
#endif
    }
        break;
    case 15: {
        m_widgetWorkSpace = new CarMeterWidget(this);
    }
        break;
    case 16: {
        m_widgetWorkSpace = new BackLightWidget(this);
    }
        break;
    case 17: {
        m_widgetWorkSpace = new BeepWidget(this);
    }
        break;
    case 18: {
        m_widgetWorkSpace = new RecorderWidget(this);
    }
        break;
    case 19: {
        m_widgetWorkSpace = new KeyPressWidget(this);
        connect(m_threadPowerKey, SIGNAL(signalKeyPressed(quint8)), (KeyPressWidget *)m_widgetWorkSpace, SLOT(SltKeyPressed(quint8)));
        connect(m_threadKey, SIGNAL(signalKeyPressed(quint8)), (KeyPressWidget *)m_widgetWorkSpace, SLOT(SltKeyPressed(quint8)));
    }
        break;
    case 23: {
        m_widgetWorkSpace = new SettingWidget(this);
        connect((SettingWidget *)m_widgetWorkSpace, SIGNAL(signalChangeCursorShape(Qt::CursorShape)),
                this, SLOT(SltChangeCursorShap(Qt::CursorShape)));
    }
        break;
    case 24: {
        // 关闭音乐
        if (NULL != m_musicWidget) {
            m_musicWidget->StopMusic();
        }

#if 1
        m_widgetWorkSpace = new InfoNesWidget(this);
#else
        m_widgetWorkSpace = new NesSimulator(this);
#endif
    }
        break;

    default:
        m_nCurrentIndex = -1;
        break;
    }

    if (NULL != m_widgetWorkSpace) {
        m_widgetWorkSpace->resize(this->size());
        connect(m_widgetWorkSpace, SIGNAL(signalBackHome()), this, SLOT(SltBackHome()));
        connect(m_widgetWorkSpace, SIGNAL(signalAnimationFinished()), this, SLOT(SltAppStartOk()));

        m_nCurrentIndex = index;
        m_widgetWorkSpace->setVisible(true);
        m_widgetWorkSpace->StartAnimation(QPoint(this->width(), this->height()), QPoint(0, 0), 300, true);
    }
}

void MainWindow::SltBackHome()
{
    if (NULL != m_widgetWorkSpace) {
        m_widgetWorkSpace->StartAnimation(QPoint(0, 0), QPoint(-this->width(), -this->height()), 300, false);
    }
    else if (NULL != m_musicWidget) {
        m_musicWidget->StartAnimation(QPoint(0, 0), QPoint(-this->width(), -this->height()), 300, false);
    }
}

void MainWindow::SltChangeCursorShap(Qt::CursorShape shape)
{
    this->setCursor(shape);
}

void MainWindow::SltAppStartOk()
{
    m_bStartApp = false;
    m_launcherWidget->setEnabled(true);
    if (11 == m_nCurrentIndex) {
        if (NULL != m_musicWidget && m_musicWidget->isVisible()) {
            m_musicWidget->InitPlayList();
        }
    }

    if (19 == m_nCurrentIndex && (NULL != m_widgetWorkSpace) && !m_widgetWorkSpace->isVisible()) {
        disconnect(m_widgetWorkSpace, SIGNAL(signalBackHome()), this, SLOT(SltBackHome()));
        delete m_widgetWorkSpace;
        m_widgetWorkSpace = NULL;
    }
}

void MainWindow::SltMouseInsert(bool bOk)
{
    AppConfig::m_bMouseInsert = bOk;
    if (this->cursor().shape() == Qt::BlankCursor &&
            !AppConfig::m_bPlayVideo &&
            AppConfig::m_bMouseInsert)
    {
        this->setCursor(Qt::ArrowCursor);
        return;
    }

    bool bOn = AppConfig::ReadSetting("System", "mouse", true).toBool();
    if (!bOk && !AppConfig::m_bPlayVideo) {
        this->setCursor(bOn ? Qt::ArrowCursor : Qt::BlankCursor);
    }
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    m_aboutUs->resize(this->size());

    if (NULL != m_widgetWorkSpace) {
        m_widgetWorkSpace->resize(this->size());
    }

    if (NULL != m_musicWidget) {
        m_musicWidget->resize(this->size());
    }
    QWidget::resizeEvent(e);
}

#ifdef Q_OS_WIN32
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (24 == m_nCurrentIndex && NULL != m_widgetWorkSpace) {
        NesSimulator *simulator = (NesSimulator *)m_widgetWorkSpace;
        simulator->sendKeyPressed(event);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (24 == m_nCurrentIndex && NULL != m_widgetWorkSpace) {
        NesSimulator *simulator = (NesSimulator *)m_widgetWorkSpace;
        simulator->sendKeyReleased(event);
    }
}
#endif


bool MainWindow::CheckMouseInsert()
{
    QDir dir(MOUSE_DEV_PATH);
    if (!dir.exists()) return false;

    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); i++) {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.fileName().contains("mouse")) {
            return true;
        }
    }

    return false;
}

#if CHECK_MOUSE_BY_TIMER
void MainWindow::timerEvent(QTimerEvent *e)
{
    if (m_nMouseCheckId == e->timerId()) {
        AppConfig::m_bMouseInsert = CheckMouseInsert();
        if (this->cursor().shape() == Qt::BlankCursor &&
                !AppConfig::m_bPlayVideo &&
                AppConfig::m_bMouseInsert)
        {
            this->setCursor(Qt::ArrowCursor);
        }
    }
}
#endif


