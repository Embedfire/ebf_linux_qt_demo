#include "qtviewfinder.h"
#include <QLabel>
#include <QToolButton>
#include <QPushButton>
#include <QTimer>

#include "qtpixmapbutton.h"

#include <QDebug>

QtViewFinder::QtViewFinder(QWidget *parent):QCameraViewfinder(parent),
    m_bZoom(true),m_scaleX(1.0),m_scaleY(1.0),m_nBaseWidth(800),m_nBaseHeight(480)
{
    this->setGeometry(0,0,m_nBaseWidth,m_nBaseHeight);

    this->setStyleSheet("QWidget:focus{outline: none;}");

    m_pixmapMenu = QPixmap(":/images/camera/menu_icon.png");

    m_returnbtn = new QPushButton(this);
    connect(m_returnbtn, SIGNAL(clicked(bool)), this, SIGNAL(returnbtn_clicked_signal()));
    m_returnbtn->setStyleSheet(QString("QPushButton {border-image: url(:/images/camera/menu_icon.png);}"
                                   "QPushButton:pressed {border-image: url(:/images/camera/menu_icon_pressed.png);}"));

    take_picture = new QPushButton(this);
    connect(take_picture, SIGNAL(clicked(bool)), this, SIGNAL(take_picture_signal()));
    take_picture->setStyleSheet(QString("QPushButton {border-image: url(:/images/camera/take.png);}"
                                   "QPushButton:pressed {border-image: url(:/images/camera/take_pressed.png);}"));

    show_config = new QToolButton(this);
    show_config->setCheckable(true);
    connect(show_config, SIGNAL(clicked(bool)), this, SLOT(on_show_config()));
    show_config->setStyleSheet(QString("QToolButton {border-image: url(:/images/camera/tool.png);}"
                                   "QToolButton:pressed {border-image: url(:/images/camera/tool_pressed.png);}"
                                    "QToolButton:checked {border-image: url(:/images/camera/tool_pressed.png);}"));

    show_image = new QLabel(this);
    show_image->hide();

    config=new CameraConfig(this);
    config->hide();

    timer_hide = new QTimer();
    connect(timer_hide,SIGNAL(timeout()),this,SLOT(on_hide_image()));

    m_returnbtn->setGeometry(m_nBaseWidth - 10 - m_pixmapMenu.width(),2,m_pixmapMenu.width(),m_pixmapMenu.height());
    take_picture->setGeometry(m_nBaseWidth/2-25,m_nBaseHeight/5*4,80,80);
    show_config->setGeometry(m_nBaseWidth-100,m_nBaseHeight/5*4+30,74,20);
    show_image->setGeometry(10,m_nBaseHeight-200, 300,200);
    config->setGeometry(50,20,430,360);
}

QtViewFinder::~QtViewFinder()
{

}

void QtViewFinder::on_returnbtn_clicked(bool clicked)
{
    if(clicked)
        emit returnbtn_clicked_signal();
}

void QtViewFinder::on_take_picture()
{
    emit take_picture_signal();
}

void QtViewFinder::on_show_config()
{
    if(show_config->isChecked())
    {
        config->show();
    }
    else
    {
        config->hide();
    }
    //qDebug()<<config->width()<<config->height();
}

void QtViewFinder::setSize(int width, int height)
{
    m_nBaseWidth=width;
    m_nBaseHeight=height;

    m_returnbtn->setGeometry(m_nBaseWidth - 10 - m_pixmapMenu.width(),2,m_pixmapMenu.width(),m_pixmapMenu.height());
    take_picture->setGeometry(m_nBaseWidth/2-25,m_nBaseHeight/5*4,80,80);
    show_config->setGeometry(m_nBaseWidth-100,m_nBaseHeight/5*4+30,74,20);
    show_image->setGeometry(10,m_nBaseHeight-200, 300,200);
    config->setGeometry(50,20,430,360);
}

void QtViewFinder::loadImage(QString image_path)
{
    show_image->setPixmap(QPixmap(image_path).scaled(show_image->width(),show_image->height()));
    show_image->show();
    timer_hide->start(3000);
}

void QtViewFinder::on_hide_image()
{
    show_image->hide();
    timer_hide->stop();
}

void QtViewFinder::setEnabledTake(bool enable)
{
    take_picture->setEnabled(enable);
}
