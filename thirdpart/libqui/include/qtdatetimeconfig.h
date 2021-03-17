/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : qtdatetimeconfig.h --- QtDateTimeConfig
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef QTDATETIMECONFIG_H
#define QTDATETIMECONFIG_H

#include "qtwidgetbase.h"
#include <QLabel>

class NumberSelected : public QtWidgetBase {

    Q_OBJECT
public:
    explicit NumberSelected(QWidget *parent = 0);
    ~NumberSelected();

    typedef enum {None, UpDirection, DownDirection} Direction;
    void setItmes(const QStringList &items);

    void setMinValue(int value);
    void setMaxValue(int value);
    void setCurrentIndex(int index);
    int  currentIndex();

signals:
    void signalIndexChanged();

private:
    QColor  m_colorBackground;
    QColor  m_colorText;
    QColor  m_colorBackroundSelected;
    QColor  m_colorTextSelected;

    int     m_nItemHeight;

    QStringList m_strListItems;

    bool m_bPressed;
    QPoint m_startPos;

    int m_nStartIndex;
    int m_nIndex;
    int m_nOffset;
    int m_nDirection;
    int m_nMinValue;
    int m_nMaxValue;
private:
    void setCurrentValue();

protected:
    void paintEvent(QPaintEvent *);
    void drawListItem(QPainter *painter);

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
    void moveStep(int nOffset);
};

#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT QtDateTimeConfig : public QtWidgetBase {
#else
class QtDateTimeConfig : public QtWidgetBase {
#endif
    Q_OBJECT
public:
    explicit QtDateTimeConfig(QWidget *parent = 0);
    ~QtDateTimeConfig();

    typedef enum {DateFormat, TimeFormat} ConfigFromat;
    void setConfigFormat(QtDateTimeConfig::ConfigFromat format);
    QtDateTimeConfig::ConfigFromat getFormat();

    void SetFont(QFont font);

    QDate getCurrentDate();
    QTime getCurrentTime();

private:
    ConfigFromat m_format;
    QString      m_strText;
    NumberSelected *m_numberSelected[3];

private:
    void InitWidget();
    int getCurrentMonthDays(int year, int month);

private slots:
    void SltNumberChanged();

protected:
    void paintEvent(QPaintEvent *);
};

#endif // QTDATETIMECONFIG_H
