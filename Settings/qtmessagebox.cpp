/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : messagebox.cpp --- MessageBox
 作 者    : 倪Niyh 华
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    1.0.0.0 1     文件创建
*******************************************************************/
#include "qtmessagebox.h"

#include <QCursor>
#include <QMutex>
#include <QMouseEvent>
#include <QTextDocument>
#include <QPainter>
#include <QDebug>

#define TITLE_HEIGHT    40
#define PADDING_SIZE    20
#define SHOW_ITEM_CNT   3
#define BUTTON_WIDTH    150
#define BUTTON_HEIGHT   40

typedef enum
{
    Message_Info,
    Message_Error,

} E_MESSAGE_TYPE;


//////////////////////////////////////////////////////////////////////////////////////
/// \brief MessageBox::self
/// 消息对话框，需要人为处理
QtMessageBox::QtMessageBox(QWidget *parent) : QDialog(parent)
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool | Qt::FramelessWindowHint);
    this->setFixedSize(400, 220);
    this->setFocusPolicy(Qt::NoFocus);
    this->setAttribute(Qt::WA_DeleteOnClose);

    m_bBtnOkHover = false;
    m_bBtnCalcelHover = false;
    m_nMsgType = Msg_Information;

    m_strBackgroundColor = "#ffffff";
    m_strTextColor = "#333333";
    m_strHTextColor = "#000000";
    m_strHighLightColor = "#fafafa";

    QTextOption txoption;
    txoption.setAlignment(Qt::AlignVCenter);
    txoption.setWrapMode(QTextOption::WordWrap);
    m_document = new QTextDocument(this);
    m_document->setDefaultTextOption(txoption);
    m_document->setDocumentMargin(1);
    m_document->setDefaultStyleSheet(QString("*{color: %1;} a{color: #0000ee;}").arg(m_strTextColor));

    this->setMouseTracking(true);
}

QtMessageBox::~QtMessageBox()
{
}

/**
 * @brief MessageBox::ShowMessage
 * @param text
 * @param title
 */
void QtMessageBox::ShowMessage(const QString &text, const QString &title)
{
    QtMessageBox *msgBox = new QtMessageBox();
    msgBox->SetMessages(text, title, Msg_Information);
    msgBox->exec();
}

int QtMessageBox::ShowAskMessage(const QString &text, const QString &title)
{
    QtMessageBox *msgBox = new QtMessageBox();
    msgBox->SetMessages(text, title, Msg_Question);
    return msgBox->exec();
}

void QtMessageBox::SetMessages(const QString &text, const QString &title, E_MSG_TYPE type)
{
    m_document->setHtml(QString("<p>%1</p>").arg(text));
    m_strTitle = title;
    m_nMsgType = type;
    this->update();
}

/**
 * @brief MessageBox::SltTimeOut
 * 倒计时退出提示
 */
void QtMessageBox::SltTimeOut()
{

}

/**
 * @brief MessageBox::paintEvent
 * 绘制界面
 */
void QtMessageBox::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(m_strHighLightColor);
    painter.setBrush(QColor(m_strBackgroundColor));
    painter.drawRect(1, 1, this->width() - 2, this->height() - 2);

    QFont font("Microsoft YaHei");
    font.setPixelSize(18);
    painter.setFont(font);

    // 绘制标题栏
    QRect rect(1, 1, this->width() - 2, TITLE_HEIGHT - 1);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(m_strHighLightColor));
    painter.drawRect(rect);
    painter.setPen(m_strHTextColor);
    painter.drawText(rect, Qt::AlignCenter, m_strTitle);

    // 绘制消息框
    font.setPixelSize(16);
    painter.setFont(font);

    // 文字显示区域
    rect = QRect(PADDING_SIZE, TITLE_HEIGHT, this->width() - PADDING_SIZE * 2,
                 this->height() - TITLE_HEIGHT - BUTTON_HEIGHT - 30);

    m_document->setDefaultFont(font);
    if (m_document->size().width() > rect.width()) {
        m_document->setTextWidth(rect.width());
    }
    QSizeF txtSize = m_document->size();

    // 绘制图标
    painter.save();
    painter.translate(PADDING_SIZE + (rect.width() - txtSize.width()) / 2,
                      (rect.height() - txtSize.height()) / 2 + rect.top());
    m_document->drawContents(&painter);
    painter.restore();

    // --- 绘制按钮 --- //
    if (Msg_Information == m_nMsgType) {
        int nOffset = (this->width() - BUTTON_WIDTH) / 2;
        m_btnOkRect = QRect(nOffset, rect.bottom() + 15, BUTTON_WIDTH, BUTTON_HEIGHT);
    }
    else {
        m_btnOkRect = QRect(PADDING_SIZE, rect.bottom() + 15, BUTTON_WIDTH, BUTTON_HEIGHT);
        m_btnCalcelRect = QRect(this->width() - PADDING_SIZE - BUTTON_WIDTH, m_btnOkRect.top(), BUTTON_WIDTH, BUTTON_HEIGHT);

        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#eeeeee"));
        painter.drawRoundedRect(m_btnCalcelRect, 2, 2);
        painter.setPen("#333333");
        painter.drawText(m_btnCalcelRect, Qt::AlignCenter, tr("取消"));
    }

    // 确认按钮
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#eeeeee"));
    painter.drawRoundedRect(m_btnOkRect, 2, 2);
    painter.setPen("#333333");
    painter.drawText(m_btnOkRect, Qt::AlignCenter, tr("确定"));

}

/**
 * @brief MessageBox::mousePressEvent
 * @param e
 */
void QtMessageBox::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        if (m_btnCalcelRect.contains(e->pos()))
        {
            this->reject();
        }
        else if (m_btnOkRect.contains(e->pos()))
        {
            this->accept();
        }
        else if (m_rectWinClose.contains(e->pos())) {
            this->reject();
        }
        else
        {
            m_mousePressed = true;
            mousePoint = e->globalPos() - this->pos();
        }
    }
}

/* 鼠标拖动处理 */
void QtMessageBox::mouseMoveEvent(QMouseEvent *e)
{
    if (m_mousePressed && (e->buttons() && Qt::LeftButton))
    {
        this->move(e->globalPos() - mousePoint);
    }
    else
    {
        m_bBtnCalcelHover = m_btnCalcelRect.contains(e->pos());
        m_bBtnOkHover = m_btnOkRect.contains(e->pos());
        bool bClose = m_rectWinClose.contains(e->pos());
        this->setCursor((m_bBtnCalcelHover || m_bBtnOkHover | bClose) ? Qt::PointingHandCursor : Qt::ArrowCursor);
        this->update();
    }
}

void QtMessageBox::mouseReleaseEvent(QMouseEvent *)
{
    m_mousePressed = false;
}

void QtMessageBox::leaveEvent(QEvent *)
{
    m_bBtnOkHover = false;
    m_bBtnCalcelHover = false;
    this->update();
}

void QtMessageBox::keyPressEvent(QKeyEvent *)
{

}

void QtMessageBox::keyReleaseEvent(QKeyEvent *)
{

}
