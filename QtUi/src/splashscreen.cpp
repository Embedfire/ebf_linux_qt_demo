/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : splashscreen.cpp --- SplashScreen
 作 者    : 倪Niyh 华
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    1.0.0.0 1     文件创建
*******************************************************************/
#include "splashscreen.h"

#include <QTimer>
#include <QPainter>
#include <QPixmap>
#include <QFileInfo>
#include <QMovie>
#include <QDebug>

SplashScreen::SplashScreen(QWidget *parent, int msec) :
    QWidget(parent),m_nMSecTimeout(msec)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    this->setAttribute(Qt::WA_DeleteOnClose);

    m_strFileName = CheckLogoFile(qApp->applicationDirPath() + "/conf");

    m_movie = NULL;
    m_strMessage = "";
    m_strTextColor = "#34c388";
    m_widgetMain = NULL;
}

SplashScreen::~SplashScreen()
{
    if (NULL != m_movie)
    {
        m_movie->stop();
        delete m_movie;
        m_movie = NULL;
    }
}

/**
 * @brief CheckLogoFile
 *  检查启动logo资源
 * @param path
 * @return
 */
QString SplashScreen::CheckLogoFile(const QString &path)
{
    QString strFile = path + "/logo.gif";
    // 设置为gif优先
    if (QFile::exists(strFile))
    {
        return strFile;
    }

    // 启动图片加载
    strFile = path + "/logo.png";
    if (QFile::exists(strFile))
    {
        return strFile;
    }

    // 启动图片加载
    strFile = path + "/logo.jpg";
    if (QFile::exists(strFile))
    {
        return strFile;
    }

    // 启动图片加载
    strFile = path + "/logo.bmp";
    if (QFile::exists(strFile))
    {
        return strFile;
    }

    // 如果都没有显示默认的启动动画
    return "";
}

void SplashScreen::SetMainWidget(QWidget *widget)
{
    m_widgetMain = widget;
}

void SplashScreen::ShowMessages(const QString &msg, const QString &textClr)
{
    m_strMessage = msg;
    m_strTextColor = textClr;
    this->update();
}

/**
 * @brief SplashScreen::Start
 * 启动
 */
void SplashScreen::Start()
{
    // 文件判断
    if (m_strFileName.endsWith("gif") || m_strFileName.endsWith("GIF"))
    {
        m_movie = new QMovie(this);
        m_movie->setFileName(m_strFileName);
        m_movie->jumpToFrame(0);
//        m_movie->setScaledSize(this->size());
        this->setFixedSize(m_movie->currentPixmap().size());

        connect(m_movie, SIGNAL(finished()), this, SLOT(SltFinished()));
        connect(m_movie, SIGNAL(frameChanged(int)), this, SLOT(SltFramChanged(int)));
    }
    else if (m_strFileName.endsWith("png") ||
             m_strFileName.endsWith("jpg") ||
             m_strFileName.endsWith("bmp"))
    {
        m_pixmap = QPixmap(m_strFileName);
        this->setFixedSize(m_pixmap.size());
    }

    // 如果没有动画，就超时退出
    if ((0 != m_nMSecTimeout) && (NULL == m_movie))
    {
        QTimer::singleShot(m_nMSecTimeout, this, SLOT(SltFinished()));
    }

    // 如果有动画则播放动画
    if (NULL != m_movie)
    {
        m_movie->start();
    }

    this->update();
    this->show();
}

/**
 * @brief SplashScreen::SltFinished
 */
void SplashScreen::SltFinished()
{
    if (NULL != m_widgetMain)
    {
       m_widgetMain->show();
    }

    this->close();
}

/**
 * @brief SplashScreen::SltFramChanged
 */
void SplashScreen::SltFramChanged(int)
{
    m_pixmap = m_movie->currentPixmap();
    this->update();
}

/**/
void SplashScreen::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 没有图片，默认显示白底黑字
    if (m_pixmap.isNull())
    {
        painter.fillRect(this->rect(), QColor("#1d1e24"));
#ifdef Q_OS_WIN32
        QFont font("思源黑体 CN Normal");
#else
        QFont font  = painter.font();
#endif

        font.setPixelSize(24);
        painter.setFont(font);
        painter.setPen(QColor(m_strTextColor));
        painter.drawText(this->rect(), Qt::AlignCenter,
                         m_strMessage.isEmpty() ? QString("程序正在启动中,请稍后...")
                                                : m_strMessage);
    }
    else
    {
        painter.drawPixmap(this->rect(), m_pixmap);
    }
}

QSize SplashScreen::sizeHint() const
{
    return QSize(800, 480);
}
