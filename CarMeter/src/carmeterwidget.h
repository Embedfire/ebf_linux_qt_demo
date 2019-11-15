/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : CarMeterWidget.h --- CarMeterWidget
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/7
*******************************************************************/
#ifndef CARMETERWIDGET_H
#define CARMETERWIDGET_H

#include <QWidget>
#include "qtwidgetbase.h"
#include <QTimer>
#include <QMap>
#include <QDebug>

class MarkIcon {
public:
    MarkIcon(int id, QRect rect, QStringList pixmaps, bool m_bFicker = false) :
        m_nId(id),m_nState(0),m_rect(rect),m_pixmaps(pixmaps),
        m_bFickerAble(m_bFicker),m_bChecked(false),m_bFicker(false)
    {

    }

    QPixmap pixmap() {
        int index = m_bFickerAble ? (m_bChecked ? 1 : 0) : m_nState;
        if (index >= m_pixmaps.size()) return QPixmap();
        return m_pixmaps.at(index);
    }

    void ChangeState() {
        m_nState += 1;
        if (m_nState >= m_pixmaps.size()) {
            m_nState = 0;
        }
    }

    int m_nId;
    int m_nState;
    QRect  m_rect;
    QStringList m_pixmaps;

    bool    m_bFickerAble;
    bool    m_bChecked;
    bool    m_bFicker;
};

class CarMeterWidget : public QtAnimationWidget
{
    Q_OBJECT
public:
    explicit CarMeterWidget(QWidget *parent = 0);
    ~CarMeterWidget();

signals:

public slots:

private slots:
    void SltChangValue();
    void SltChangeMarkState();

private:
    int m_nSpeed;
    int m_nLeftPower;
    int m_nRightPower;

    QTimer *m_timer;
    bool bDown;
private:
    bool  m_bHomePressed;
    QRect m_rectHome;

    bool m_bPressed;
    QPoint m_startPos;
    QRect  m_rectLeftValue;
    QRect  m_rectRightValue;
    // 提示标志
    QMap<int, MarkIcon *> m_markSgin;

    QTimer   *m_timerMark;

private:
    void InitData();

protected:
    void paintEvent(QPaintEvent *);
    void drawRects(QPainter *painter);
    void drawMarIcons(QPainter *painter);
    void drawValue(QPainter *painter);

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);
};

#endif // CARMETERWIDGET_H
