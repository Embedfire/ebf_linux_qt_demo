#include "nesscreenwidget.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "InfoNES_System.h"
#include "InfoNES.h"
#include "InfoNES_pAPU.h"

#include <QMutexLocker>
#include <QPainter>
#include <QPoint>
#include <QThread>
#include <QDebug>

//NesScreenWidget::NesScreenWidget(QWidget *parent) : QOpenGLWidget(parent)
NesScreenWidget::NesScreenWidget(QWidget *parent) : QWidget(parent)
{
    image = QImage((uchar *)WorkFrame, NES_DISP_WIDTH, NES_DISP_HEIGHT, QImage::Format_RGB16);
}

NesScreenWidget::~NesScreenWidget()
{
}

void NesScreenWidget::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(this->rect(), image);
    painter.end();
}

void NesScreenWidget::loadFrame()
{
    QMutexLocker locker(&mutex);
    image = QImage((uchar *)WorkFrame, NES_DISP_WIDTH, NES_DISP_HEIGHT, QImage::Format_RGB16);
    this->update();
}
