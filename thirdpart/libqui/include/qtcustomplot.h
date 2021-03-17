/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : qtcustomplot.h --- QtCustomPlot
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef QTCUSTOMPLOT_H
#define QTCUSTOMPLOT_H

#include <QWidget>
#include <QList>
#include <QPointF>
#include <QPainterPath>

#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT QtCustomPlot : public QWidget {
#else
class QtCustomPlot : public QWidget {
#endif
    Q_OBJECT
public:
    explicit QtCustomPlot(QWidget *parent = 0);
    ~QtCustomPlot();

    // 添加和设置数据数据
    void addData(double data);
    void setData(QVector<double> data);
    void clearData();

    // 设置范围值及步长
    void setMinValue(double minValue);
    void setMaxValue(double maxValue);
    void setXStep(double xStep);
    void setYStep(double yStep);

    void setLabels(QString strXLabel = "X轴", QString strYLabel = "Y轴");
    void setFont(QFont font);
    void StartTest();

    void setBackgroundColor(QColor color);
signals:

public slots:

private:
    QRectF          m_dataRect;
    QVector<double> m_listData;
    int             m_nStartTime;
    QPainterPath    m_dataCurvePath;

    double      m_nMinValue;
    double      m_nMaxValue;
    double      m_nXStep;
    double      m_nYStep;

    bool        m_bShowGrid;
    bool        m_bDrawPath;

    QString     m_strXLabels;
    QString     m_strYLabels;

    QColor      m_colorBackground;
    QColor      m_colorGridLine;
    QColor      m_colorLineColor;

    QFont       m_font;
private:
    void calcDataBox();
    void updateData();

private slots:
    void SltTestData();

protected:
    void resizeEvent(QResizeEvent *e);
    void paintEvent(QPaintEvent *);
    void drawDataBox(QPainter *painter);
    void drawBoxText(QPainter *painter);
    void drawCurvePath(QPainter *painter);
};

#endif // QTCUSTOMPLOT_H
