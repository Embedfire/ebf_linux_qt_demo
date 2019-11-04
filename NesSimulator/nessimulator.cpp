/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : nessimulator.cpp ---
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "nessimulator.h"
#include "skin.h"

#include <QPainter>
#include <QMouseEvent>

#include <QKeyEvent>
#include <QApplication>
#include <QFile>
#include <QDebug>

//////////////////////////////////////////////////////////////////////////////////////
SimulatorTitleBar::SimulatorTitleBar(QWidget *parent) : QtToolBar(parent)
{
    m_strText = "";
    this->setFixedHeight(50);
    m_rectBack = QRect(20, 10, 40, 40);
}

SimulatorTitleBar::~SimulatorTitleBar()
{

}

void SimulatorTitleBar::SetText(const QString &text)
{
    m_strText = text;
    this->update();
}

void SimulatorTitleBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), QColor("#7f182E3A"));

    painter.drawPixmap(m_rectBack.topLeft(), QPixmap(":/images/photos/toolbar/ic_back.png"));

    painter.setPen("#ffffff");
    painter.setFont(QFont(Skin::m_strAppFontNormal, 18));
    painter.drawText(this->rect(), Qt::AlignCenter, m_strText);
}

void SimulatorTitleBar::mousePressEvent(QMouseEvent *e)
{
    if (m_rectBack.contains(e->pos())) {
        emit signalBack();
    }
    QWidget::mousePressEvent(e);
}

//////////////////////////////////////////////////////////////////////////////////////
NesGamePannel *s_gameWidgetPannel = NULL;
NesSimulator::NesSimulator(QWidget *parent) : QtAnimationWidget(parent)
{

    s_gameWidgetPannel = new NesGamePannel(this);

    m_titleBar = new SimulatorTitleBar(this);
    connect(m_titleBar, SIGNAL(signalBack()), this, SIGNAL(signalBackHome()));

    QString strFile = qApp->applicationDirPath() + "/nes/SuperMarie.nes";
    if (QFile::exists(strFile))
    {
        s_gameWidgetPannel->LoadGame(strFile);
        m_titleBar->SetText("SuperMarie.nes");
    }
}

NesSimulator::~NesSimulator()
{
    delete s_gameWidgetPannel;
    s_gameWidgetPannel = NULL;
}

void NesSimulator::resizeEvent(QResizeEvent *e)
{
    s_gameWidgetPannel->resize(this->size());
    s_gameWidgetPannel->move(0, 0);

    m_titleBar->setGeometry(0, -m_titleBar->height(), this->width(), m_titleBar->height());
    QWidget::resizeEvent(e);
}

void NesSimulator::sendKeyPressed(QKeyEvent *event)
{
    keyPressEvent(event);
}

void NesSimulator::sendKeyReleased(QKeyEvent *event)
{
    keyReleaseEvent(event);
}

void NesSimulator::mousePressEvent(QMouseEvent *)
{
    static bool bToolBarShow = false;
    bToolBarShow = !bToolBarShow;
    if (bToolBarShow) {
        m_titleBar->SetAnimation(QPoint(0, -m_titleBar->height()), QPoint(0, 0));
    } else {
        m_titleBar->SetAnimation(QPoint(0, 0), QPoint(0, -m_titleBar->height()));
    }
}

void NesSimulator::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_W:
        s_gameWidgetPannel->setFlag(UP);
        break;
    case Qt::Key_S:
        s_gameWidgetPannel->setFlag(DOWN);
        break;
    case Qt::Key_A:
        s_gameWidgetPannel->setFlag(LEFT);
        break;
    case Qt::Key_D:
        s_gameWidgetPannel->setFlag(RIGHT);
        break;
    case Qt::Key_U:
        s_gameWidgetPannel->setFlag(A);
        break;
    case Qt::Key_I:
        s_gameWidgetPannel->setFlag(B);
        break;
    case Qt::Key_J:
        s_gameWidgetPannel->setFlag(C);
        break;
    case Qt::Key_K:
    case Qt::Key_Space:
        s_gameWidgetPannel->setFlag(D);
        break;
    }
}

void NesSimulator::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_W:
        s_gameWidgetPannel->removeFlag(UP);
        break;
    case Qt::Key_S:
        s_gameWidgetPannel->removeFlag(DOWN);
        break;
    case Qt::Key_A:
        s_gameWidgetPannel->removeFlag(LEFT);
        break;
    case Qt::Key_D:
        s_gameWidgetPannel->removeFlag(RIGHT);
        break;
    case Qt::Key_U:
        s_gameWidgetPannel->removeFlag(A);
        break;
    case Qt::Key_I:
        s_gameWidgetPannel->removeFlag(B);
        break;
    case Qt::Key_J:
        s_gameWidgetPannel->removeFlag(C);
        break;
    case Qt::Key_K:
    case Qt::Key_Space:
        s_gameWidgetPannel->removeFlag(D);
        break;
    }
}
