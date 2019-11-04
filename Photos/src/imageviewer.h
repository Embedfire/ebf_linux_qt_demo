/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : imageviewer.h --- ImageViewer
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/8
*******************************************************************/
#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QMap>
#include <QTimer>
#include <QPushButton>

#include "qttoolbar.h"
#include "qtpagelistwidget.h"

class TitleBarWidget : public QtToolBar
{
    Q_OBJECT
public:
    explicit TitleBarWidget(QWidget *parent = 0);
    ~TitleBarWidget();

    void SetText(const QString &text);
signals:
    void signalBack();

private:
    QString m_strText;
    QRect   m_rectBack;
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
};

class BottomBarWidget : public QtToolBar
{
    Q_OBJECT
public:
    explicit BottomBarWidget(QWidget *parent = 0);
    ~BottomBarWidget();
    void Stop();

signals:
    void buttonClicked(int index);
    void signalPlay(bool bOk);

private:
    QPushButton *m_btnPlay;
    void InitWidget();

protected:
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *e);
};

class ImageViewer : public QWidget
{
    Q_OBJECT
public:
    explicit ImageViewer(QWidget *parent = 0);
    ~ImageViewer();

    void SetPixmap(int id, QMap<int, QtPageListWidgetItem*> pixmaps);
    void SetCurrentIndex(int index);

signals:
    void signalBack();

public slots:

private slots:
    void SltToolButtonClicked(int index);

private:
    QMap<int, QtPageListWidgetItem*> m_listPixmaps;

    QPixmap     m_pixmap;
    QPixmap     m_pixmapTemp;

    QRect       m_rectPixmap;
    int         m_nIndex;

    bool        m_bPressed;
    QPoint      m_startPos;

    int         m_nScaleFactor;
    double      m_nRotate;
    double      m_opacity;

    TitleBarWidget  *m_titleBar;
    BottomBarWidget *m_bottomBar;
    QPushButton     *m_btnPrev;
    QPushButton     *m_btnNext;
    QTimer          *m_timer;
    // 幻灯片
    QTimer          *m_timerSlide;
    bool             m_bToolBtnShow;

private:
    void setToolBarVisible(bool bOk);
    void scalePixmap();

private slots:
    void SltSetOpacity();
    void SltShowPrevImage();
    void SltShowNextImage();
    void SltAutoPlay(bool bOk);
    void SltPlaySlide();
protected:
    void resizeEvent(QResizeEvent *e);

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
};

#endif // IMAGEVIEWER_H
