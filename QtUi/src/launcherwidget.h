/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : launcherwidget.h --- LauncherWidget
 作 者    : Niyh(lynnhua)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef LAUNCHERWIDGET_H
#define LAUNCHERWIDGET_H

#include <QWidget>
#include <QMap>
#include <QTimer>
#include <QPropertyAnimation>

////////////////////////////////////////////////////////
/// \brief The LauncherItem class

#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT LauncherItem {
#else
class LauncherItem {
#endif
public:
    LauncherItem(int id, int index, const QString &name, const QPixmap &icon);

    int     m_nAppId;
    int     m_nPageIndex;

    QString m_strAppName;
    QPixmap m_pixmapIcon;
    QString m_strClassName;
    QRect   m_rect;
};

////////////////////////////////////////////////////////
/// \brief The LauncherWidget class
#ifdef QtUi
class QTUISHARED_EXPORT LauncherWidget : public QWidget {
#else
class LauncherWidget : public QWidget {
#endif
    Q_OBJECT
public:
    typedef enum {None, LeftDirection, RightDirection} MoveDirection;
    Q_PROPERTY(int xPos READ Xpos WRITE setXPos)

    explicit LauncherWidget(QWidget *parent = 0);
    ~LauncherWidget();

    void AddItem(int id, LauncherItem *item);
    void SetItems(QMap<int, LauncherItem *> items);

    void SetWallpaper(const QPixmap &pixmap);
    void SetWallpaper(const QColor &color);

    void SetPageCount(int count);
    void SetItemLayut(int rows, int columns);

    void SetLoopbackChange(bool bOk);

signals:
    void currentItemClicked(int index);
    void currentPageChanged(int index);

public slots:
    void SltShowNextPage();
    void SltShowPrevPage();

private:
    QMap<int, LauncherItem *> m_itemApps;
    QMap<int, QRect>          m_rectPageSpot;

    // skin
    QColor      m_backgroundColor;
    QPixmap     m_pixmapWallpaper;

    int         m_nPageCnt;
    int         m_nCurrentPage;
    int         m_nPrevPage;

    int         m_nCurrentIndex;

    int         m_nLayoutRows;
    int         m_nLayoutColumns;

    qreal       m_nItemWidth;
    qreal       m_nItemHeight;

    int         m_nDirection;

    QTimer      *m_timerMove;
    bool        m_bLoopbackChange;
    QPropertyAnimation *m_animation;
private:
    bool    m_bPressed;
    QPoint  m_startPos;
    int     m_nStartPos;
    int     m_nMoveEndValue;
    bool    m_bRecovery;
private:
    void setXPos(int nValue);
    int Xpos(){return m_nStartPos;}

private slots:
    void SltChangePage();

protected:
    void resizeEvent(QResizeEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

    void paintEvent(QPaintEvent *);
    void drawAppItem(QPainter *painter, int page, int xOffset = 0);
    void drawItemSpot(QPainter *painter);
    void drawAppInfo(QPainter *painter, QRect rect, LauncherItem *item);
};

#endif // LAUNCHERWIDGET_H
