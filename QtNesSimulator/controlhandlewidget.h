/********************************************************************************
 * Copyright (C) 2020 - All Rights Reserved by xiaomutech
 * date: 2020/7/24
 * auth: yhni lynnhua@163.com QQ:393320854
 * desc:
 ********************************************************************************/
#ifndef CONTROLHANDLEWIDGET_H
#define CONTROLHANDLEWIDGET_H

#include <QWidget>

class ControlHandleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlHandleWidget(QWidget *parent = nullptr);
    ~ControlHandleWidget();

signals:

private:
    int  m_nDirection;
    qreal m_value;
private:
    QSize sizeHint() const override;
    void paintEvent(QPaintEvent *) override;
    void drawBMWLogo(QPainter *painter);
    void drawDirectionCtrl(QPainter *painter);

    void mouseMoveEvent(QMouseEvent *e) override;
};

#endif // CONTROLHANDLEWIDGET_H
