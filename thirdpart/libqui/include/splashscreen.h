/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : splashscreen.h --- SplashScreen
 作 者    : 倪Niyh 华
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    1.0.0.0 1     文件创建
使用方法：
    // 启动界面
    SplashScreen *splash = new SplashScreen();
    a.processEvents();

    // 启动主程序
    splash->setFixedSize(QSize(APP_SIZE_WIDGET, APP_SIZE_HEIGHT));
    splash->SetMainWidget(new MainWindow);
    splash->Start();
*******************************************************************/
#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QWidget>

#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT SplashScreen : public QWidget {
#else
class SplashScreen : public QWidget {
#endif
    Q_OBJECT
public:
    explicit SplashScreen(QWidget *parent = 0, int msec = 2000);
    ~SplashScreen();

    void SetMainWidget(QWidget *widget);

    // 显示的消息
    void ShowMessages(const QString &msg, const QString &tetClr = "#ffffff");
    void Start();

signals:
    void signalFinished();

public slots:


private:
    // 需要启动的widget
    QWidget *m_widgetMain;

    /**
     * @brief m_strMessage
     * 如果没有图片相关资源，直接绘制启动文字
     * 同样，如果有图片，如果设置了文字显示，也会显示
     */
    QString m_strMessage;

    // 文字颜色，默认为黑底白字
    QString m_strTextColor;

    // 文件名
    QString m_strFileName;
    // 启动静态图画
    QPixmap m_pixmap;
    // 超时时间
    int     m_nMSecTimeout;

    // 播放动画
    QMovie *m_movie;

private:
    QString CheckLogoFile(const QString &path);

private slots:
    void SltFinished();
    void SltFramChanged(int);

protected:
    void paintEvent(QPaintEvent *);
    QSize sizeHint() const;
};

#endif // SPLASHSCREEN_H
