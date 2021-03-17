#include "qtmessage.h"
#include <QPainter>
#include <QMouseEvent>

//#include <QDebug>

MyFrame::MyFrame(QWidget *parent) : QFrame(parent)
{
    this->resize(320, 160);

    message_title="提示";
    //message="没有检测到温湿度传感器，请连接检查";
    accept_text="确认";
    reject_text="取消";
}
MyFrame::~MyFrame()
{

}
void MyFrame::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    QBrush brush;

    QRect title_rect(0,0,this->width(),this->height()/6);
    QRect message_rect(0,this->height()/6,this->width(),this->height()/2);
    QRect accept_rect(0,this->height()/3*2,this->width()/2,this->height()/3);
    QRect reject_rect(this->width()/2,this->height()/3*2,this->width()/2-1,this->height()/3);

//    //绘制按钮背景
//    if(accept_hover)
//        brush.setColor(QColor(255,0,0,255));
//    else
//        brush.setColor(QColor(0,0,0,255));

//    painter.setBrush(brush);
//    painter.drawRect(accept_rect);

//    if(reject_hover)
//        brush.setColor(QColor(255,0,0,255));
//    else
//        brush.setColor(QColor(0,0,0,255));

//    painter.setBrush(brush);
//    painter.drawRect(reject_rect);

    //绘制文字
    QFont font = painter.font();
    font.setPixelSize(16);
    painter.setFont(font);
    painter.setPen(Qt::black);
    painter.drawText(accept_rect,Qt::AlignCenter,accept_text);
    painter.drawText(reject_rect,Qt::AlignCenter,reject_text);
    painter.drawText(title_rect,Qt::AlignCenter,message_title);

    font.setPixelSize(14);
    painter.setFont(font);
    painter.drawText(message_rect,Qt::AlignCenter,message);
    //绘制线条
    painter.drawLine(0,this->height()/3*2,this->width(),this->height()/3*2);
    painter.drawLine(this->width()/2,this->height()/3*2,this->width()/2,this->height());
}
void MyFrame::setText(QString title,QString message,QString accept,QString reject)
{
    this->message_title=title;
    this->message=message;
    this->accept_text=accept;
    this->reject_text=reject;
}
//通过鼠标事件来更新悬停效果
void MyFrame::mouseMoveEvent(QMouseEvent *event)
{
//    if(event->pos().y()>this->height()/3*2)
//    {
//        if(event->pos().x()>this->width()/2)
//        {
//            accept_hover=false;
//            reject_hover=!accept_hover;
//        }
//        else
//        {
//            reject_hover=false;
//            accept_hover=!reject_hover;
//        }

//    }
//    this->update();
}




QtMessage::QtMessage(QWidget *parent) : QDialog(parent)
{
    this->setModal(true);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->resize(320, 160);

    frame = new MyFrame(this);
    frame->setText("提示","没有检测到温湿度传感器，请连接检查","确认","取消");
    frame->setStyleSheet("background-color:#f2f2f2;border-radius:5px;");
    frame->show();
}
//QtMessage::QtMessage(QWidget *parent,QString title,QString msg,QString accept,QString reject) : QDialog(parent)
//{
//    this->setModal(true);

//    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
//    this->setAttribute(Qt::WA_TranslucentBackground);
//    this->resize(320, 160);

//    frame = new MyFrame(this);
//    frame->setText(title,msg,accept,reject);
//    frame->setStyleSheet("background-color:#f2f2f2;border-radius:5px;");
//    frame->show();
//}

QtMessage::~QtMessage()
{

}
void QtMessage::setMessage(QString Message)
{
    frame->setText("提示",Message,"确认","取消");
}
void QtMessage::mouseReleaseEvent( QMouseEvent *)
{
}
void QtMessage::mousePressEvent( QMouseEvent * event )
{
    if(event->pos().y()>this->height()/3*2)
    {
        if(event->pos().x()>this->width()/2)
        {
            //qDebug()<<"cancle";
            rejectOperate();
        }
        else
        {
            //qDebug()<<"ok";
            acceptOperate();
        }
    }
    this->update();
}
void QtMessage::mouseMoveEvent(QMouseEvent *event)
{
}
//确认操作
void QtMessage::acceptOperate()
{
    this->accept();
}

//取消操作
void QtMessage::rejectOperate()
{
    this->reject();
}

