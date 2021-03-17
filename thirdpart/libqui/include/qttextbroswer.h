/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : qttextbroswer.h --- QtTextBroswer
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef QTTEXTBROSWER_H
#define QTTEXTBROSWER_H

#include <QWidget>

#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT QtTextBroswer : public QWidget {
#else
class QtTextBroswer : public QWidget {
#endif
    Q_OBJECT
public:
    explicit QtTextBroswer(QWidget *parent = 0);
    ~QtTextBroswer();

    void setAlignment(Qt::Alignment align);

    void setText(const QString &text);
    QString text() const;

    void append(const QString &text);

signals:

public slots:

private:
    Qt::Alignment  m_align;

    int     m_nOffset;
    bool    m_bPressed;
    QPoint  m_startPos;
    int     m_nTextHeight;

    QColor  m_colorText;
    QString m_strText;
protected:
    void resizeEvent(QResizeEvent *e);
    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);

    void moveStep(int offset, bool wheel = false);
};

#endif // QTTEXTBROSWER_H
