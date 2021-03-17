/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : qtaddressbar.h --- QtAddressBar
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/15
*******************************************************************/
#ifndef QTADDRESSBAR_H
#define QTADDRESSBAR_H

#include "qtwidgetbase.h"
#include <QMap>

class AddressItem {
public:
    AddressItem():m_nId(0) {}
    AddressItem(int id, QString addr, QRect rect) :
        m_nId(id),m_strAddress(addr),m_rect(rect),m_bPressed(false)
    {

    }

    int id() {return m_nId;}
    QRect rect() {return m_rect;}
    void setRect(QRect rect) {m_rect = rect;}

    QString address() {return m_strAddress;}
    void setAddress(QString addr) {m_strAddress = addr;}

private:
    int m_nId;
    QString m_strAddress;
    QRect   m_rect;
    bool m_bPressed;
};

/////////////////////////////////////////////////////////////////////////////////
class AddressLineEdit : public QtWidgetBase {
    Q_OBJECT
public:
    explicit AddressLineEdit(QWidget *parent = 0);
    ~AddressLineEdit();

    void setAddress(const QString &addr);
    QString getAddress();

    void appendDir(const QString &dir);

signals:
    void signalAddress(const QString &strAddr);

public slots:
    void SltBackAddress();
    void SltNextAddress();

private:
    QMap<int,AddressItem*>  m_addressItems;
    QFont   m_font;
    int     m_nSplitWidth;
    int     m_nIndex;
    QString m_strAddrPath;
    int     m_nMargin;

private:
    void ClearItem(int startId = 0);
    void CurrentPathChanged(int index);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
};

/////////////////////////////////////////////////////////////////////////////////
#ifdef QtUi
class QTUISHARED_EXPORT QtAddressBar : public QtWidgetTitleBar {
#else
class QtAddressBar : public QtWidgetTitleBar {
#endif
    Q_OBJECT
public:
    explicit QtAddressBar(QWidget *parent = 0);
    ~QtAddressBar();

    void setAddress(const QString &addr);
    QString getAddress();

signals:
    void signalBackHome();
    void signalAddress(const QString &strAddr);

protected:
    void SltBtnClicked(int index);

private:
    AddressLineEdit *m_addrLineEdit;

private:
    void InitWidget();

protected:
    void resizeEvent(QResizeEvent *e);
};

#endif // QTADDRESSBAR_H
