#include "statusbarwidget.h"
#include "unit.h"
#include "skin.h"

#include <QPainter>
#include <QMouseEvent>

StatusBarWidget::StatusBarWidget(QWidget *parent) : QWidget(parent)
{
    this->setMinimumHeight(STATUSBAR_HEIGHT);
}

StatusBarWidget::~StatusBarWidget()
{

}

void StatusBarWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap(":/images/mainwindow/statusbar_bg.png"));
}

void StatusBarWidget::mousePressEvent(QMouseEvent *e)
{
    emit signalAboutClicked();
    QWidget::mousePressEvent(e);
}
