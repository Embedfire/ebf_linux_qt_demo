/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : qtaddressbar.cpp --- QtAddressBar
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/15
*******************************************************************/
#include "qtaddressbar.h"

#include <QFont>
#include <QMouseEvent>
#include <QPainter>
#include <QFontMetrics>
#include <QPushButton>
#include <QBoxLayout>
#include <QDebug>

AddressLineEdit::AddressLineEdit(QWidget *parent) : QWidget(parent)
{
    m_font = this->font();
    m_font.setPixelSize(18);
    m_nMargin = 10;

    QFontMetrics fm(m_font);
    m_nSplitWidth = fm.width("/") ;
    m_nIndex = -1;
}

AddressLineEdit::~AddressLineEdit()
{

}

void AddressLineEdit::setAddress(const QString &addr)
{
    m_strAddrPath = addr;
    QStringList strAddress = addr.split("/");
    ClearItem();
    QFontMetrics fm(m_font);

    QRect rect(0, 0, m_nMargin, this->height());

    for (int i = 0; i < strAddress.size(); i++) {
        QString strAddr = strAddress.at(i);
        int nWidth = fm.width(strAddr, strAddr.length());
        rect = QRect(rect.right()+ 2, rect.top(), nWidth + m_nSplitWidth, rect.height());
        m_addressItems.insert(i, new AddressItem(i, strAddr, rect));
    }

    m_nIndex = m_addressItems.size() - 1;
    this->update();
}

QString AddressLineEdit::getAddress()
{
    QString strPath = "";
    for (int i = 0; i < m_addressItems.size(); i++) {
        if (i > m_nIndex) break;
        strPath += m_addressItems.value(i)->address();
        strPath.append("/");
    }

    return strPath;
}

void AddressLineEdit::appendDir(const QString &dir)
{
    Q_UNUSED(dir);
}

void AddressLineEdit::SltBackAddress()
{
    if (m_nIndex > 0) {
        CurrentPathChanged(m_nIndex - 1);
    }
}

void AddressLineEdit::SltNextAddress()
{
    if (m_nIndex < (m_addressItems.size() - 1)) {
        CurrentPathChanged(m_nIndex + 1);
    }
}

void AddressLineEdit::ClearItem(int startId)
{
    foreach (AddressItem *item, m_addressItems) {
        if (item->id() >= startId) {
            m_addressItems.remove(item->id());
            delete item;
            item = NULL;
        }
    }
}

void AddressLineEdit::CurrentPathChanged(int index)
{
    if (index == m_nIndex) return;
    m_nIndex = index;
    QString strPath = getAddress();
    this->update();
    emit signalAddress(strPath);
}

void AddressLineEdit::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#fafafa"));
    painter.drawRoundedRect(this->rect(), 8, 8);

    painter.setFont(m_font);
#if 1
    painter.setBrush(Qt::NoBrush);
    foreach (AddressItem *item, m_addressItems) {
        painter.setPen(m_nIndex == item->id() ? QColor("#00ff00") : QColor("#3c3c3c"));
        painter.drawText(item->rect(), Qt::AlignCenter, item->address());

        if (item->id() < (m_addressItems.size() - 1)) {
            painter.drawText(QRect(item->rect().right(), item->rect().top(), m_nSplitWidth, this->height()),
                             Qt::AlignCenter, "/");
        }
    }
#else
    QRect rectText(m_nMargin, 0, this->width() - m_nMargin * 2, this->height());
    painter.drawText(rectText, Qt::AlignVCenter, m_strAddrPath);
#endif
}

void AddressLineEdit::mousePressEvent(QMouseEvent *e)
{
    foreach (AddressItem *item, m_addressItems) {
        if (item->rect().contains(e->pos())) {
            CurrentPathChanged(item->id());
            this->update();
            break;
        }
    }
}


/////////////////////////////////////////////////////////////////////////////////
QtAddressBar::QtAddressBar(QWidget *parent) : QWidget(parent)
{
    this->setFixedHeight(60);
    InitWidget();
}

QtAddressBar::~QtAddressBar()
{

}

void QtAddressBar::setAddress(const QString &addr)
{
    m_addrLineEdit->setAddress(addr);
}

QString QtAddressBar::getAddress()
{
    return m_addrLineEdit->getAddress();
}

void QtAddressBar::InitWidget()
{
    QHBoxLayout *horLayout = new QHBoxLayout(this);
    horLayout->setContentsMargins(3, 3, 3, 3);
    horLayout->setSpacing(10);

    QPushButton *btnPrev = new QPushButton(this);
    horLayout->addWidget(btnPrev);
    btnPrev->setFixedSize(30, 30);
    btnPrev->setStyleSheet(QString("QPushButton {border-image: url(:/images/file/ic_prev.png);}"
                                   "QPushButton:pressed {border-image: url(:/images/file/ic_prev_pre.png);}"));


    QPushButton *btnNext = new QPushButton(this);
    btnNext->setFixedSize(30, 30);
    horLayout->addWidget(btnNext);
    btnNext->setStyleSheet(QString("QPushButton {border-image: url(:/images/file/ic_next.png);}"
                                   "QPushButton:pressed {border-image: url(:/images/file/ic_next_pre.png);}"));

    m_addrLineEdit = new AddressLineEdit(this);
    m_addrLineEdit->setFixedHeight(36);
    horLayout->addWidget(m_addrLineEdit, 1);
    connect(btnPrev, SIGNAL(clicked(bool)), m_addrLineEdit, SLOT(SltBackAddress()));
    connect(btnNext, SIGNAL(clicked(bool)), m_addrLineEdit, SLOT(SltNextAddress()));
    connect(m_addrLineEdit, SIGNAL(signalAddress(QString)), this, SIGNAL(signalAddress(QString)));

    QPushButton *btnHome = new QPushButton(this);
    horLayout->addWidget(btnHome, 1);

    btnHome->setFixedSize(54, 54);
    connect(btnHome, SIGNAL(clicked(bool)), this, SIGNAL(signalBackHome()));
    btnHome->setStyleSheet(QString("QPushButton {border-image: url(:/images/file/menu_icon.png);}"
                                   "QPushButton:pressed {border-image: url(:/images/file/menu_icon_pressed.png);}"));
}

void QtAddressBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), QColor("#474540"));
}


