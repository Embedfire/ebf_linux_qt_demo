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
#ifndef QTLISTWIDGET_H
#define QTLISTWIDGET_H

#include "qtwidgetbase.h"
#include <QMap>
#include <QTimer>
#include <QPropertyAnimation>
#include <QPixmap>

//////////////////////////////////////////////////////////
///// \brief The LauncherItem class

#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT QtListWidgetItem {
#else
class QtListWidgetItem {
#endif
public:
    QtListWidgetItem(int id, const QStringList &args);
    QtListWidgetItem(int id, const QString &name);
    QtListWidgetItem(int id, const QString &name, const QPixmap &icon);
    QtListWidgetItem(int id, const QString &path, const QString &name, const QPixmap &icon);

    int     m_nId;

    QString m_strText;
    QPixmap m_pixmapIcon;
    QString m_strBaseName;
    QString m_strPath;
    QRect   m_rect;

    QStringList m_strMultiParameters;
    bool    m_bPressed;
};

////////////////////////////////////////////////////////
/// \brief The QtListWidget class
#ifdef QtUi
class QTUISHARED_EXPORT QtListWidget : public QtWidgetBase {
#else
class QtListWidget : public QtWidgetBase {
#endif
    Q_OBJECT
public:
    typedef enum {None, LeftDirection, RightDirection, UpDirection, DownDirection} MoveDirection;
    Q_PROPERTY(int xPos READ movePos WRITE setMovePos)

    explicit QtListWidget(QWidget *parent = 0);
    ~QtListWidget();

    QtListWidgetItem *currentItem();
    void AddItem(int id, QtListWidgetItem *item);
    void SetItems(const QMap<int, QtListWidgetItem *> &items);

    void SetBackground(const QPixmap &pixmap);
    void SetBackground(const QColor &color);

    void setItemSize(int size);
    void setHoriazontal(bool bOk);

    void setAlignment(Qt::Alignment aligns);
    void setScaleSize(int w, int h);

public slots:
    void setPrevIndex();
    void setCurrentIndex(int index);
    void setNexIndex();

signals:
    void currentItemClicked(QtListWidgetItem *item);
    void currentIndexClicked(int index);

private:
    void setMovePos(int nValue);
    int  movePos(){return m_nStartPos;}
    void ClearItems();

private:
    bool    m_bPressed;
    QPoint  m_startPos;
    int     m_nStartPos;
    int     m_nMoveEndValue;
    bool    m_bRecovery;

protected:
    QMap<int, QtListWidgetItem *> m_listItems;
    int         m_alignment;

    QColor      m_backgroundColor;
    QPixmap     m_pixmapWallpaper;
    QColor      m_colorText;

    int         m_nStartIndex;
    int         m_nCurrentIndex;

    int         m_nMargin;
    int         m_nSpace;

    int         m_nItemShowCnt;
    int         m_nItemSize;
    bool        m_bHorizontal;

    QPropertyAnimation *m_animationMove;
    int         m_nDirection;

protected:
    QSize sizeHint() const;

    void resizeEvent(QResizeEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *e);

    void paintEvent(QPaintEvent *);
    void drawHorizontalItem(QPainter *painter);
    void drawVerticalItem(QPainter *painter);
    virtual void drawItemInfo(QPainter *painter, QtListWidgetItem *item);
};

#endif // QTLISTWIDGET_H
