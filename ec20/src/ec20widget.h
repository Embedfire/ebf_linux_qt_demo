/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : EC20Widget.h ---
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef EC20WIDGET_H
#define EC20WIDGET_H

#include "qtwidgetbase.h"
#include "qtpixmapbutton.h"

#include <QMap>
#include <QResizeEvent>
#include <QDateTime>

class CmdProcess;
class QTextEdit;
class QLabel;

class EC20Widget : public QtAnimationWidget
{
    Q_OBJECT
    //typedef enum {BtnHome, BtnUser, BtnOnOff, BtnKey, BtnLedR, BtnLedG, BtnLedB, BtnCount} E_BTNS;
    typedef enum {BtnBack,BtnUpDown,BtnConnect,BtnReset,BtnHome,BtnDevice,BtnMeasure,BtnLocation,BtnSetting,BtnExit,BtnCount} EC_BTNS;
    typedef enum {StepInit,StepConnect,StepTest,StepDis,StepNone} CMD_STEP;
public:
    EC20Widget(QWidget *parent = 0);
    ~EC20Widget();

public slots:

private slots:
    void getProcessMsg(const QString msg);
    void handletimeout();
    void testConnect();

private:
    void InitButtons();

    void KeyPressed(int index);

    void startConnect();

    void disConnect();
    void updateinfo();

    void  appendinfo(QString msg);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    //void resizeEvent(QResizeEvent *e);

private:
    CmdProcess           *m_cmd;
    QTextEdit            *m_infowidget;
    QWidget              *subwidget;
    QTimer               *timer;
    bool                 connctState=false;
    CMD_STEP             m_step;


    QLabel               *labdevice,*labinfo;

    QDateTime            timeConnect;
    QString              strSpeed,strUsetime,strIpaddr,strConnecttime;
    QString              strDevicename,strDevicetype;
};

#endif // EC20Widget_H
