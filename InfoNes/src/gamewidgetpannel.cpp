/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : gamewidgetpannel.cpp --- GameWidgetPannel
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/10/25
*******************************************************************/
#include "gamewidgetpannel.h"
#include "skin.h"
#include "appconfig.h"

#include <QApplication>
#include <QPainter>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

GameWidgetPannel::GameWidgetPannel(QWidget *parent) : QtWidgetBase(parent)
{
    m_bEngineError = false;
    m_bQuit = false;

    m_cmd = new QProcess(this);

    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    m_timer->setSingleShot(true);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(hide()));
}

GameWidgetPannel::~GameWidgetPannel()
{
    if (isRunning()) {
        m_cmd->kill();
    }
}

void GameWidgetPannel::startGame(const QString &fileName)
{
    if (isRunning()) return;
    if (m_timer->isActive()) m_timer->stop();

    QString strCmd = qApp->applicationDirPath() + "/InfoNes";
    if (QFile::exists(strCmd)) {
        m_bEngineError = false;
        m_bQuit = false;

        strCmd += " ";
        strCmd += fileName;
        strCmd += " ";
        strCmd += CheckKeyboardInsert();

#ifdef __arm__
        // 关闭鼠标显示
        this->setCursor(Qt::BlankCursor);
        m_cmd->start(strCmd);
#endif
    }
    else {
        m_bQuit = false;
        m_bEngineError = true;
    }

    this->show();
}

bool GameWidgetPannel::isRunning()
{
    return (m_cmd->state() != QProcess::NotRunning);
}

void GameWidgetPannel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.scale(m_scaleX, m_scaleY);
    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(24);
    painter.setFont(font);

    QRect rect(0, 0, m_nBaseWidth, m_nBaseHeight);
    painter.fillRect(rect, Qt::black);
    painter.setPen(QColor("#aaaaaa"));
    if (m_bQuit) {
        painter.drawText(rect, Qt::AlignCenter, tr("正在退出游戏...."));
    }
    else {
        painter.drawText(rect, Qt::AlignCenter, m_bEngineError ? tr("游戏引擎错误，请联系管理员！") : tr("正在启动...."));
    }
}

QString GameWidgetPannel::CheckKeyboardInsert()
{
    QDir dir("/dev/input/by-path/");
    if (!dir.exists()) return "";

    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); i++) {
        QFileInfo fileInfo = list.at(i);
        if (fileInfo.fileName().contains("kbd")) {
            return fileInfo.absoluteFilePath();
        }
    }

    return "";
}

void GameWidgetPannel::mousePressEvent(QMouseEvent *)
{
    if (m_timer->isActive()) return;

    m_bQuit = true;

#ifdef __arm__
    if (isRunning()) {
        m_cmd->kill();
        m_cmd->waitForFinished(1000);
    }

    // 打开/关闭鼠标显示
    bool bOn = AppConfig::ReadSetting("System", "mouse", true).toBool();
    this->setCursor(bOn ? Qt::ArrowCursor : Qt::BlankCursor);
    this->update();
#endif

    m_timer->start();
}
