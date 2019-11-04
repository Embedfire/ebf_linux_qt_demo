/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : qtwidgetbase.h --- QtWidgetBase
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef QTWIDGETBASE_H
#define QTWIDGETBASE_H

#include "QtUi"

#ifdef QtUi
class QTUISHARED_EXPORT QtWidgetBase : public QWidget {
#else
class QtWidgetBase : public QWidget {
#endif
    Q_OBJECT
public:
    explicit QtWidgetBase(QWidget *parent = 0);
    ~QtWidgetBase();

signals:

public slots:

};

////////////////////////////////////////////////////////////////////
// 专用标题栏
#ifdef QtUi
class QTUISHARED_EXPORT QtWidgetTitleBar : public QWidget {
#else
class QtWidgetTitleBar : public QWidget {
#endif
    Q_OBJECT
public:
    explicit QtWidgetTitleBar(QWidget *parent = 0);
    QtWidgetTitleBar(const QString &title, QWidget *parent  = 0);

    ~QtWidgetTitleBar();

    void SetBackground(const QColor &color);
    void SetBackground(const QPixmap &pixmap);

    void SetTitle(const QString &title, const QColor &textClr, const int &fontSize = 18);
signals:
    void signalBack();
    void signalHome();

private:
    QPixmap     m_pixmapBackground;
    QColor      m_colorBackground;
    QColor      m_colorText;

    QString     m_strTitle;
    int         m_nFontSize;
protected:
    void paintEvent(QPaintEvent *);
};

#endif // QTWIDGETBASE_H
