/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : qtrefreshbutton.h --- QtRefreshButton
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef QTREFRESHBUTTON_H
#define QTREFRESHBUTTON_H

#include <QWidget>
#include <QTimer>

class QtRefreshButton : public QWidget
{
    Q_OBJECT
public:
    explicit QtRefreshButton(QWidget *parent = 0);
    ~QtRefreshButton();

    void SetPixmap(const QPixmap &pixmap);

    void Start(int interval);

signals:

private:
    qreal   m_rotate;
    qreal   m_step;

    QTimer *m_timer;
    QPixmap m_pixmap;
    int     m_nInterval;

private slots:
    void SltBeginToRefresh();

protected:
    QSize sizeHint() const;
    void paintEvent(QPaintEvent *);
};

#endif // QTREFRESHBUTTON_H
