/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : qtwidgetbase.h --- QtWaitWidget
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef QTWAITWIDGET_H
#define QTWAITWIDGET_H

#include "qtwidgetbase.h"
#include <QTimer>

class QtWaitWidget : public QtWidgetBase
{
    Q_OBJECT
public:
    explicit QtWaitWidget(QWidget *parent = 0);
    ~QtWaitWidget();

    void SetPixmap(const QPixmap &pixmap);

    void Start(int interval);
    void SetText(const QString &text);
signals:

private:
    qreal   m_rotate;
    qreal   m_step;

    QString m_strText;

    QTimer *m_timer;
    QPixmap m_pixmap;
    int     m_nInterval;

private slots:
    void SltBeginToRefresh();

protected:

    void paintEvent(QPaintEvent *);
};

#endif // QTWAITWIDGET_H
