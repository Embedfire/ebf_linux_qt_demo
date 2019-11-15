/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : cameraconfig.h --- CameraConfig
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/16
*******************************************************************/
#ifndef CAMERACONFIG_H
#define CAMERACONFIG_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>

#include "qtwidgetbase.h"
#include "qtswitchbutton.h"
#include "qtstackedwidget.h"

class ConfigWidget : public QWidget{
    Q_OBJECT
public:
    explicit ConfigWidget(QWidget *parent = 0);
    ~ConfigWidget();

    int  rowCount() {return m_nRow;}
    void setRows(int row);

    void setItems(const QStringList &strItems);
    void setCurrentIndex(const int &index);
    void setSelectMode(bool bOk);

signals:
    void signalClicked(int index);
    void signalItemClicked(const QString &text);
private:

private:
    int     m_nRow;
    int     m_nIndex;
    int     m_nItemHeight;

    QStringList m_strItems;
    bool    m_bSelected;

protected:
    void paintEvent(QPaintEvent *);
    void drawItemInfo(QPainter *painter);

    void mousePressEvent(QMouseEvent *e);
};

class CameraConfig : public QtAnimationWidget
{
    Q_OBJECT
public:
    explicit CameraConfig(QWidget *parent = 0);
    ~CameraConfig();

    QSize photoSize() const;

signals:

public slots:

private:
    QtWidgetTitleBar *m_widgetTitle;
    QPushButton      *m_btnBack;

    QtStackedWidget  *m_stackedWidget;

    ConfigWidget     *m_configMain;
    ConfigWidget     *m_configResolv;
    ConfigWidget     *m_configLight;
    ConfigWidget     *m_configEffect;

    QStringList      m_strListResolv;
    QStringList      m_strListLight;
    QStringList      m_strListEffect;

    QLabel          *m_labelResolv;
    QLabel          *m_labelLight;
    QLabel          *m_labelEffect;

    QSize           m_photoSize;
private:
    void InitWidget();
    void InitMainPage();

private slots:
    void SltBackClicked();
    void SltChangePage(int index);
    void SltPhotoSize(int index);

protected:
    void showEvent(QShowEvent *e);
};

#endif // CAMERACONFIG_H
