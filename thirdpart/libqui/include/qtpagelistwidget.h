/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : qtlistwidget.h --- QtListWidget
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/8
*******************************************************************/
#ifndef QTPAGELISTWIDGET_H
#define QTPAGELISTWIDGET_H

#include "qtwidgetbase.h"
#include <QMap>
#include <QTimer>
#include <QPropertyAnimation>
#include <QPixmap>

////////////////////////////////////////////////////////
/// \brief The LauncherItem class

#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT QtPageListWidgetItem {
#else
class QtPageListWidgetItem {
#endif
public:
    QtPageListWidgetItem(int id, const QStringList &args);
    QtPageListWidgetItem(int id, const QString &name);
    QtPageListWidgetItem(int id, const QString &name, const QPixmap &icon);
    QtPageListWidgetItem(int id, const QString &path, const QString &name, const QPixmap &icon);

    int     m_nId;

    QString m_strText;
    QPixmap m_pixmapIcon;
    QString m_strBaseName;
    QString m_strPath;
    QRect   m_rect;

    QStringList m_strMultiParameters;
};

////////////////////////////////////////////////////////
/// \brief The QtListWidget class
#ifdef QtUi
class QTUISHARED_EXPORT QtPageListWidget : public QtWidgetBase {
#else
class QtPageListWidget : public QtWidgetBase {
#endif
    Q_OBJECT
public:
    typedef enum {None, LeftDirection, RightDirection} MoveDirection;
    Q_PROPERTY(int xPos READ Xpos WRITE setXPos)

    explicit QtPageListWidget(QWidget *parent = 0);
    ~QtPageListWidget();

    void AddItem(int id, QtPageListWidgetItem *item);
    void SetItems(const QMap<int, QtPageListWidgetItem *> &items);

    void SetBackground(const QPixmap &pixmap);
    void SetBackground(const QColor &color);

    void SetPageCount(int count);
    void SetItemLayut(int rows, int columns);
    void SetItemLayoutSpace(int row, int col);

    void SetLoopbackChange(bool bOk);

signals:
    void currentItemClicked(QtPageListWidgetItem *item);
    void currentPageChanged(int index);

protected:
    QMap<int, QtPageListWidgetItem *> m_listItems;
    // skin
    QColor      m_backgroundColor;
    QPixmap     m_pixmapWallpaper;

    int         m_nPageCnt;
    int         m_nCurrentPage;
    int         m_nPrevPage;

    int         m_nLayoutRows;
    int         m_nLayoutColumns;

    qreal       m_nItemWidth;
    qreal       m_nItemHeight;

    int         m_nDirection;

    QTimer      *m_timerMove;
    bool        m_bLoopbackChange;
    QPropertyAnimation *m_animationMove;

private:
    bool    m_bPressed;
    QPoint  m_startPos;
    int     m_nStartPos;
    int     m_nMoveEndValue;
    bool    m_bRecovery;

private:
    void setXPos(int nValue);
    int Xpos(){return m_nStartPos;}
    void resizeRect();
private slots:

protected:
    int         m_nCurrentIndex;
    int         m_nHorSpace;
    int         m_nVSpace;
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *e);

    void paintEvent(QPaintEvent *);
    void drawListItem(QPainter *painter, int page, int xOffset = 0);
    virtual void drawItemInfo(QPainter *painter, QtPageListWidgetItem *item);
};

#endif // QTPAGELISTWIDGET_H
