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
#include <QPushButton>

#include "launcherwidget.h"
#include "qtwidgetbase.h"
#include "aboutus.h"
#include "threadkey.h"

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

    QPushButton         *m_btnPrevPage;
    QPushButton         *m_btnNextPage;

    AboutUs             *m_aboutUs;
    QtAnimationWidget   *m_widgetWorkSpace;
    MusicPlayer         *m_musicWidget;

    int                  m_nCurrentIndex;
    bool                 m_bStartApp;

    ThreadKey       *m_threadPowerKey;
    ThreadKey       *m_threadKey;
private:
    void InitWidget();
    void InitDesktop();
    void InitKeyThread();
private slots:
    void SltCurrentPageChanged(int index);
    void SltCurrentAppChanged(int index);

    void SltBackHome();
    void SltChangeCursorShap(Qt::CursorShape shape);
    void SltAppStartOk();

protected:
    void resizeEvent(QResizeEvent *e);
    void paintEvent(QPaintEvent *);
#ifdef Q_OS_WIN32
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
#endif
};

#endif // MAINWINDOW_H
