/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : boardlogowidget.h --- BoardLogoWidget
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/1
*******************************************************************/
#ifndef BOARDLOGOWIDGET_H
#define BOARDLOGOWIDGET_H

#include <QWidget>

class BoardLogoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BoardLogoWidget(QWidget *parent = 0);
    ~BoardLogoWidget();

signals:

public slots:

private:
    QPixmap     m_pixmap;

protected:
    void paintEvent(QPaintEvent *);
    void drawPointLine(QPainter *painter);
};

#endif // BOARDLOGOWIDGET_H
