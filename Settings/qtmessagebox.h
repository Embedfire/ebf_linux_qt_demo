/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : messagebox.h --- MessageBox
 作 者    : 倪Niyh 华
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    1.0.0.0 1     文件创建
*******************************************************************/
#ifndef QTMESSAGEBOX_H
#define QTMESSAGEBOX_H

#include <QTimer>
#include <QDialog>
#include <QWidget>
#include <QTextDocument>

//////////////////////////////////////////////////////////////////////////////////////
/// \brief The MessageBox class
/// 消息对话框
class QtMessageBox : public QDialog {
    Q_OBJECT
public:
    explicit QtMessageBox(QWidget *parent = 0);
    ~QtMessageBox();

    typedef enum { Msg_Information, Msg_Question, Msg_Warning, Msg_Error } E_MSG_TYPE;

    // 显示提示框
    static void ShowMessage(const QString &text, const QString &title = "系统提示");
    static int  ShowAskMessage(const QString &text, const QString &title = "询问");

    void SetMessages(const QString &text,
                     const QString &title = "系统提示",
                     E_MSG_TYPE type =  Msg_Information);
signals:

private:
    // 支持富文本
    QTextDocument *m_document;

    QString m_strTitle;
    QString m_strMessage;

    // 消息类型
    quint8  m_nMsgType;

    // 定时返回
    QTimer *m_timer;
    // 当前选中按钮
    int     m_nIndexBtn;
    // 倒计时步数统计
    int     m_nSetp;

    // 按钮
    QRect   m_btnOkRect;
    QRect   m_btnCalcelRect;
    QRect   m_rectWinClose;

    // 样式配置
    QString m_strTextColor;
    QString m_strHTextColor;
    QString m_strBackgroundColor;
    QString m_strHighLightColor;

private slots:
    void SltTimeOut();

protected:
    QPoint mousePoint;
    bool   m_mousePressed;

    bool   m_bBtnCalcelHover;
    bool   m_bBtnOkHover;

private:

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
    void leaveEvent(QEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
};

#endif // QTMESSAGEBOX_H
