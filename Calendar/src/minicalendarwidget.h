/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : minicalendarwidget.h --- MiniCalendarWidget
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/6
*******************************************************************/
#ifndef MINICALENDARWIDGET_H
#define MINICALENDARWIDGET_H

#include "qtwidgetbase.h"

class MiniCalendarWidget : public QtWidgetBase
{
    Q_OBJECT
public:
    explicit MiniCalendarWidget(QWidget *parent = 0);
    ~MiniCalendarWidget();

    void SetBackground(const QPixmap &pixmap);
signals:
    void changeCurrentPage(int index, int direction);

public slots:


private:
    QPixmap     m_pixmapBackground;

private:
    // 获取星期
    QString getCurrendDayOfWeek();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
};

#endif // MINICALENDARWIDGET_H
