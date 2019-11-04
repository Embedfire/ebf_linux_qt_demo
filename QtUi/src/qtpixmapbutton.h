/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : qtpixmapbutton.h --- QtPixmapButton
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef QTPIXMAPBUTTON_H
#define QTPIXMAPBUTTON_H

#include <QObject>
#include <QWidget>

#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT QtPixmapButton {
#else
class QtPixmapButton  {
#endif
public:
    QtPixmapButton() {}
    QtPixmapButton(QPixmap pixmapNormal, QPixmap pixmapPressed);
    QtPixmapButton(int id, QRect rect, QPixmap pixmapNormal, QPixmap pixmapPressed);

    int id();

    QRect rect();
    void setRect(QRect rect);

    QPixmap pixmap();

    QString text();
    void setText(const QString &text);

    void setPressed(bool bOk);
    bool isPressed();

    QSize size() const;

private:
    int m_nId;
    QRect m_rect;

    QPixmap m_pixmapNormal;
    QPixmap m_pixmapPressed;

    QString m_strText;

    bool  m_bPressed;
};

#endif // QTPIXMAPBUTTON_H
