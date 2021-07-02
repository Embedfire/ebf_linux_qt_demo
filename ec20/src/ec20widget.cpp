/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : EC20Widget.cpp ---
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "ec20widget.h"
#include "cmdprocess.h"
#include "skin.h"


#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QTimer>
#include <QWidget>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QLabel>

#define BAT_DIR         "/home/cat/peripheral/ec20-4g"
#define EC20_DEV        "/dev/ttyUSB2"

EC20Widget::EC20Widget(QWidget *parent) : QtAnimationWidget(parent)
{
    InitButtons();

    strSpeed=tr("180kb/2.3M");
    strDevicename="ppp0";
    strDevicetype="EC20";
    strUsetime="00:00:00";
    strConnecttime="00:00:00";
    strIpaddr="0.0.0.0";
    m_step = StepInit;

    m_cmd = new CmdProcess();
    m_cmd->setWorkdir(BAT_DIR);
    connect(m_cmd,SIGNAL(sendProcessMsg(const QString)),this,SLOT(getProcessMsg(const QString)));

    subwidget = new QWidget(this);
    subwidget->setObjectName("subwidget");
    subwidget->setStyleSheet("QWidget#subwidget{background-color: rgba(85, 85, 85, 0.1);border-radius:5px; color:#ffffff;font-size:20px;}");
    subwidget->setGeometry(0,90,800,250);
    QHBoxLayout *subHLayout = new QHBoxLayout(subwidget);
    subHLayout->setContentsMargins(20, 10, 20, 10);
    subHLayout->setSpacing(10);

    QWidget *m_devicewidget = new QWidget(subwidget);
    m_devicewidget->setObjectName("subdevicewidget");
    m_devicewidget->setStyleSheet("QWidget#subdevicewidget{background-color: rgba(85, 85, 85, 0.3);border-radius:5px;}"
                                        "QWidget{color:#ffffff;font-size:20px;}");
    m_devicewidget->setMinimumWidth(300);

    QVBoxLayout *deviceVLayout = new QVBoxLayout(m_devicewidget);//垂直
    QHBoxLayout *deviceHLayout = new QHBoxLayout();//水平
    deviceHLayout->setContentsMargins(5, 5, 5, 5);
    deviceHLayout->setSpacing(5);
    QVBoxLayout *infoHLayout = new QVBoxLayout();
    QVBoxLayout *pixmapHLayout = new QVBoxLayout();
    QHBoxLayout *btnHLayout = new QHBoxLayout();

    deviceHLayout->addLayout(infoHLayout);
    deviceHLayout->addLayout(pixmapHLayout);

    deviceVLayout->addLayout(deviceHLayout);
    deviceVLayout->addLayout(btnHLayout);


    labdevice = new QLabel(m_devicewidget);
    labdevice->setText(QString("设备名称：%1").arg(strDevicename.toUpper()));
    labinfo = new QLabel(m_devicewidget);
    labinfo->setStyleSheet("font-size:15px;");
    labinfo->setText(QString("当前网速：%1\r\n已连接：%2\r\nIP地址：%3\r\n设备类型：%4\r\n连接时间：%5")
                  .arg(strSpeed)
                  .arg(strUsetime)
                  .arg(strIpaddr)
                  .arg(strDevicetype)
                  .arg(strConnecttime));

    infoHLayout->addWidget(labdevice);
    infoHLayout->addWidget(labinfo);

    QLabel *labpix1 = new QLabel(m_devicewidget);
    labpix1->setPixmap(QPixmap(":/images/ec20/card_1.png").scaled(100,100));
    QLabel *labpix2 = new QLabel(m_devicewidget);
    labpix2->setPixmap(QPixmap(":/images/ec20/card_2.png").scaled(100,100));

    pixmapHLayout->addWidget(labpix1);
    pixmapHLayout->addWidget(labpix2);

    QLabel *labbtn1= new QLabel(m_devicewidget);
    labbtn1->setText("刷新");
    QLabel *labbtn2 = new QLabel(m_devicewidget);
    labbtn2->setText("重连");
    QLabel *labbtn3 = new QLabel(m_devicewidget);
    labbtn3->setText("测速");
    btnHLayout->addWidget(labbtn1);
    btnHLayout->addWidget(labbtn2);
    btnHLayout->addWidget(labbtn3);

    m_infowidget = new QTextEdit(subwidget);
    m_infowidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//水平滚动条
    m_infowidget->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );//垂直滚动条
    m_infowidget->setObjectName("m_infowidget");
    m_infowidget->setStyleSheet("QTextEdit#m_infowidget{background-color: rgba(85, 85, 85, 0.3);color:#ffffff;font-size:20px;}");

    QWidget *m_homewidget = new QWidget(subwidget);
    m_homewidget->setObjectName("m_homewidget");
    m_homewidget->setStyleSheet("QWidget#m_homewidget{background-color: rgba(85, 85, 85, 0.3);border-radius:5px; color:#ffffff;font-size:20px;}");
    m_homewidget->setMinimumWidth(100);

    subHLayout->addWidget(m_devicewidget);
    subHLayout->addWidget(m_infowidget);
    subHLayout->addWidget(m_homewidget);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(handletimeout()));
}

EC20Widget::~EC20Widget()
{

}

void EC20Widget::InitButtons()
{
    m_btns.insert(BtnConnect, new QtPixmapButton(BtnConnect, QRect(10, 10, 100, 50), QPixmap(":/images/ec20/btn001.png"), QPixmap(":/images/ec20/btn001_1.png")));
    m_btns.insert(BtnReset, new QtPixmapButton(BtnReset, QRect(120, 10, 100, 50), QPixmap(":/images/ec20/btn002.png"), QPixmap(":/images/ec20/btn002_1.png")));

    //m_btns.insert(BtnBack, new QtPixmapButton(BtnBack, QRect(736, 10, 54, 54), QPixmap(":/images/keyled/menu_icon.png"), QPixmap(":/images/keyled/menu_icon_pressed.png")));
    m_btns.insert(BtnUpDown, new QtPixmapButton(BtnUpDown, QRect(736, 10, 54, 54), QPixmap(":/images/ec20/updown.png"), QPixmap(":/images/ec20/updown.png")));
    m_btns.insert(BtnHome, new QtPixmapButton(BtnHome, QRect(430, 370, 50, 50), QPixmap(":/images/ec20/ic_home.png"), QPixmap(":/images/ec20/ic_home_1.png")));
    m_btns.insert(BtnDevice, new QtPixmapButton(BtnDevice, QRect(490, 370, 50, 50), QPixmap(":/images/ec20/ic_device.png"), QPixmap(":/images/ec20/ic_device_1.png")));
    m_btns.insert(BtnMeasure, new QtPixmapButton(BtnMeasure, QRect(550, 370, 50, 50), QPixmap(":/images/ec20/ic_measure.png"), QPixmap(":/images/ec20/ic_measure_1.png")));

    m_btns.insert(BtnLocation, new QtPixmapButton(BtnLocation, QRect(610, 370, 50, 50), QPixmap(":/images/ec20/ic_location.png"), QPixmap(":/images/ec20/ic_location_1.png")));
    m_btns.insert(BtnSetting, new QtPixmapButton(BtnSetting, QRect(670, 370, 50, 50), QPixmap(":/images/ec20/ic_setting.png"), QPixmap(":/images/ec20/ic_setting_1.png")));
    m_btns.insert(BtnExit, new QtPixmapButton(BtnExit, QRect(730, 370, 50, 50), QPixmap(":/images/ec20/ic_exit.png"), QPixmap(":/images/ec20/ic_exit_1.png")));

    m_btns.value(BtnConnect)->setText("连接");
    m_btns.value(BtnReset)->setText("测试");
}

void EC20Widget::KeyPressed(int index)
{
    switch (index) {
    case BtnExit: emit signalBackHome(); break;
    case BtnBack: emit signalBackHome(); break;
    case BtnUpDown:{};break;
    case BtnConnect:
    {
        connctState=!connctState;
        if(connctState){
            startConnect();
        }
        else{
            disConnect();
        }
    }
        break;
    case BtnReset:
    {
        testConnect();
    }
        break;
    case BtnHome:
    {
    }
        break;
    case BtnDevice:
    {
    }
        break;
    case BtnMeasure:
    {
    }
        break;
    case BtnLocation:
    {
    }
        break;
    case BtnSetting:
    {
    }
        break;
    default:
        break;
    }
}
/*
ppp0: flags=4305<UP,POINTOPOINT,RUNNING,NOARP,MULTICAST>  mtu 1500
        inet 10.12.251.75  netmask 255.255.255.255  destination 10.64.64.64
        ppp  txqueuelen 3  (Point-to-Point Protocol)
        RX packets 4  bytes 52 (52.0 B)
        RX errors 0  dropped 0  overruns 0  frame 0
        TX packets 4  bytes 58 (58.0 B)
        TX errors 0  dropped 0 overruns 0  carrier 0  collisions 0
*/
void  EC20Widget::appendinfo(QString msg)
{

}
void EC20Widget::getProcessMsg(const QString msg)
{
#ifdef __arm__

    if(msg.contains("ppp0: flags="))
    {
        m_infowidget->append(QDateTime::currentDateTime().toString("yy-MM-dd mm:hh:ss"));

        QStringList msglist=msg.split("\n");
        foreach(QString str,msglist)
        {
            if(str.contains("inet"))
            {
                QStringList ipinfolist = str.split(" ");

                for(int i =0; i<ipinfolist.count();i++)
                {
                    QString str=ipinfolist.at(i);
                    if(!str.isEmpty())
                    {
                        if(str.contains("inet"))
                        {
                            strIpaddr=ipinfolist.at(i+1);
                        }
                        m_infowidget->append(str);
                    }
                }
            }
        }

        if(m_step==StepConnect)
        {
            m_infowidget->append("connect ok");
            m_step=StepNone;
        }
        else if(m_step==StepTest)
        {
            m_infowidget->append("connect ok");
            m_step=StepNone;
        }
        m_infowidget->moveCursor(QTextCursor::End);
    }
    else if(msg.contains("ppp0: error fetching interface information: Device not found"))
    {
        m_infowidget->append("connect fail");
        m_step=StepNone;
    }
#else
    qDebug()<<msg;
#endif
}
void EC20Widget::startConnect()
{
    m_step=StepConnect;
    m_btns.value(BtnConnect)->setText("断开");
    timeConnect=QDateTime::currentDateTime();
    strConnecttime = timeConnect.toString("hh:mm:ss");
    timer->start(1000);
#ifdef __arm__
    m_cmd->startCmd("sudo /home/cat/peripheral/ec20-4g/ppp-on.sh");
    QTimer::singleShot(2000, this, SLOT(testConnect()));
#else
    qDebug()<<"start connet";
#endif
}
void EC20Widget::testConnect()
{
    m_step=StepTest;
#ifdef __arm__
    m_cmd->startCmd(QString("ifconfig %1").arg(strDevicename));
#else
    qDebug()<<"test connet";
#endif
}
void EC20Widget::disConnect()
{
    m_step=StepDis;
    m_btns.value(BtnConnect)->setText("连接");
    timer->stop();
#ifdef __arm__
    m_cmd->startCmd("pkill pppd");
#else
    qDebug()<<"dis connet";
#endif
}
void EC20Widget::updateinfo()
{
    labdevice->setText(QString("设备名称：%1").arg(strDevicename.toUpper()));
    labinfo->setText(QString("当前网速：%1\r\n已连接：%2\r\nIP地址：%3\r\n设备类型：%4\r\n连接时间：%5")
                  .arg(strSpeed)
                  .arg(strUsetime)
                  .arg(strIpaddr)
                  .arg(strDevicetype)
                  .arg(strConnecttime));
}
void EC20Widget::handletimeout()
{
    strUsetime =QDateTime::fromMSecsSinceEpoch(QDateTime::currentDateTime().toMSecsSinceEpoch() - timeConnect.toMSecsSinceEpoch()).toUTC().toString("hh:mm:ss");
    updateinfo();
}
void EC20Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

#ifdef BUILD_WITH_HDMI
    // 设置放大倍数
    painter.scale(m_scaleX, m_scaleY);
#endif

    painter.drawPixmap(0, 0, QPixmap(":/images/ec20/bg004.png"));

    painter.setPen(QColor("#ffffff"));
    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(32);
    painter.setFont(font);
    painter.drawText(0, 0, Skin::m_nScreenWidth, 70, Qt::AlignCenter, tr("EBF_GSM_EC20"));

    painter.setPen(QColor("#1395da"));
    font.setPixelSize(26);
    painter.setFont(font);
    painter.drawText(Skin::m_nScreenWidth/5*3, 0, Skin::m_nScreenWidth/5*2, 70, Qt::AlignCenter, strSpeed);
    font.setPixelSize(32);
    painter.setFont(font);
    painter.setPen(QColor("#ffffff"));

    font.setFamily(Skin::m_strAppFontRegular);
    font.setPixelSize(30);
    painter.setFont(font);

    foreach (QtPixmapButton *btn, m_btns) {
        painter.drawPixmap(btn->rect(), btn->pixmap());
        if (!btn->text().isEmpty()) {
            painter.drawText(btn->rect(), Qt::AlignCenter, btn->text());
        }
    }

    //subwidget->setGeometry(0,Skin::m_nScreenHeight/480*80,Skin::m_nScreenWidth,Skin::m_nScreenHeight/480*250);

    subwidget->move(0,Skin::m_nScreenHeight/480*80);
    subwidget->resize(Skin::m_nScreenWidth,Skin::m_nScreenHeight/480*250);

//    for (int i = BtnHome; i < BtnCount; i++) {
//        QRect rect = m_btns.value(i)->rect();
//        rect = QRect(rect.left(), rect.bottom() + 10, rect.width(), 40);
//        painter.drawText(rect, Qt::AlignCenter, pchLedText[i - BtnLedR]);
//    }
}
//void EC20Widget::resizeEvent(QResizeEvent *e)
//{
//    this->setGeometry(0,0,Skin::m_nScreenWidth,Skin::m_nScreenHeight);
//    subwidget->setGeometry(0,Skin::m_nScreenHeight/480*80,Skin::m_nScreenWidth,Skin::m_nScreenHeight/480*250);

//    QWidget::resizeEvent(e);
//}
void EC20Widget::mousePressEvent(QMouseEvent *e)
{
    foreach (QtPixmapButton *btn, m_btns) {
        //if (btn->id() > BtnBack) break;

        QRect rect;
        ScaleRect(rect, btn->rect());

        if (rect.contains(e->pos())) {
            btn->setPressed(true);
            this->update();
            break;
        }
    }
}

void EC20Widget::mouseReleaseEvent(QMouseEvent *e)
{
    foreach (QtPixmapButton *btn, m_btns) {
        if (btn->isPressed()) {
            btn->setPressed(false);
            KeyPressed(btn->id());
        }
    }

    this->update();
    QWidget::mouseReleaseEvent(e);
}


