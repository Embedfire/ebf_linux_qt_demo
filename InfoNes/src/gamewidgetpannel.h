/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : gamewidgetpannel.h --- GameWidgetPannel
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/10/25
*******************************************************************/
#ifndef GAMEWIDGETPANNEL_H
#define GAMEWIDGETPANNEL_H

#include "qtwidgetbase.h"
#include <QProcess>
#include <QTimer>

class GameWidgetPannel : public QtWidgetBase
{
    Q_OBJECT
public:
    explicit GameWidgetPannel(QWidget *parent = 0);
    ~GameWidgetPannel();

    void startGame(const QString &fileName);
    bool isRunning();

signals:
    void signalGameQuit();

private slots:

private:
    QProcess *m_cmd;
    bool      m_bEngineError;
    bool      m_bQuit;

    QTimer   *m_timer;
protected:
    QString CheckKeyboardInsert();

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
};

#endif // GAMEWIDGETPANNEL_H
