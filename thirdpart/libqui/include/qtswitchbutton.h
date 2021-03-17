/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : qtswitchbutton.h --- QtSwitchButton
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/15
*******************************************************************/
#ifndef QTSWITCHBUTTON_H
#define QTSWITCHBUTTON_H

#include <QWidget>

#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT QtSwitchButton : public QWidget {
#else
class QtSwitchButton : public QWidget {
#endif
    Q_OBJECT
public:
    explicit QtSwitchButton(QWidget *parent = 0);
    ~QtSwitchButton();

    void setHorizontal(bool bOk);

    bool isChecked();
    void setChecked(bool bOk);

    void setBackgroundColor(const QColor &color);
    void setHandleColor(const QColor &color);

signals:
    void buttonChecked(bool bOk);

public slots:

private:
    bool m_bHorizontal;
    QColor m_colorBackground;
    QColor m_colorHandle;
    bool   m_bChecked;

protected:
    QSize sizeHint() const;

    void paintEvent(QPaintEvent *);
    void drawRandStyle(QPainter *painter);
    void mousePressEvent(QMouseEvent *);
};

#endif // QTSWITCHBUTTON_H
