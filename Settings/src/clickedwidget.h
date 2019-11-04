/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : clickedwidget.h --- ClickedWidget
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef CLICKEDWIDGET_H
#define CLICKEDWIDGET_H

#include <QWidget>

class ClickedWidget : public QWidget{
    Q_OBJECT
public:
    explicit ClickedWidget(QWidget *parent = 0);
    ~ClickedWidget();

    void setIndex(int index, const QString &text = "");
signals:
    void signalClicked(int index);

private:
    int m_nIndex;
    QString m_strText;
protected:
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);
};

#endif // CLICKEDWIDGET_H
