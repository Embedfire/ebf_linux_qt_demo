#ifndef QTMESSAGE233_H
#define QTMESSAGE233_H

#include "qtwidgetbase.h"
#include <QDialog>
#include <QFrame>


//MyFrame 为了实现圆角效果
class MyFrame : public QFrame {
    Q_OBJECT
public:
    explicit MyFrame(QWidget *parent = 0);
    ~MyFrame();
    void setText(QString title,QString message,QString accept,QString reject);
signals:

private:
    QString message;
    QString message_title;
    QString accept_text;
    QString reject_text;

    bool accept_hover;
    bool reject_hover;
protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *event);
};

#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT QtMessage : public QDialog {
#else
class QtMessage : public QDialog {
#endif
    Q_OBJECT

public:
    explicit QtMessage(QWidget *parent = 0);
    //QtMessage(QWidget *parent = 0,QString title=tr("提示"),QString msg=tr("未知错误"),QString accept=tr("确认"),QString reject=tr("取消"));
    ~QtMessage();

    void setMessage(QString Message);

signals:

private slots:
    void acceptOperate();
    void rejectOperate();
private:
    MyFrame* frame;
protected:
    void mousePressEvent( QMouseEvent * event );
    void mouseReleaseEvent( QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *event);

};


#endif // QTMESSAGE_H
