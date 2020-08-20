/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : qtcustomplot.cpp --- QtCustomPlot
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "qtcustomplot.h"

#include <QFontMetrics>
#include <QPainter>
#include <QDebug>

#include <QTimer>

class SmoothCurveCreator {
public:
    /**
     * 传入曲线上的点的 list，创建平滑曲线
     * @param points - 曲线上的点
     * @return - 返回使用给定的点创建的 QPainterPath 表示的平滑曲线
     */
    static QPainterPath createSmoothCurve(const QList<QPointF> &points);

private:
    /**
     * Solves a tridiagonal system for one of coordinates (x or y)
     * of first Bezier control points.
     * @param result - Solution vector.
     * @param rhs - Right hand side vector.
     * @param n - Size of rhs.
     */
    static void calculateFirstControlPoints(double * &result, const double *rhs, int n);

    /**
     * Calculate control points of the smooth curve using the given knots.
     * @param knots - Points of the given curve.
     * @param firstControlPoints - Store the generated first control points.
     * @param secondControlPoints - Store the generated second control points.
     */
    static void calculateControlPoints(const QList<QPointF> &knots,
                                       QList<QPointF> *firstControlPoints,
                                       QList<QPointF> *secondControlPoints);
};


QPainterPath SmoothCurveCreator::createSmoothCurve(const QList<QPointF> &points) {
    QPainterPath path;
    int len = points.size();

    if (len < 2) {
        return path;
    }

    QList<QPointF> firstControlPoints;
    QList<QPointF> secondControlPoints;
    calculateControlPoints(points, &firstControlPoints, &secondControlPoints);

    path.moveTo(points[0].x(), points[0].y());

    // Using bezier curve to generate a smooth curve.
    for (int i = 0; i < len - 1; ++i) {
        path.cubicTo(firstControlPoints[i], secondControlPoints[i], points[i+1]);
    }

    return path;
}

void SmoothCurveCreator::calculateFirstControlPoints(double *&result,
                                                     const double *rhs,
                                                     int n) {
    result = new double[n];
    double *tmp = new double[n];
    double b = 2.0;
    result[0] = rhs[0] / b;

    // Decomposition and forward substitution.
    for (int i = 1; i < n; i++) {
        tmp[i] = 1 / b;
        b = (i < n - 1 ? 4.0 : 3.5) - tmp[i];
        result[i] = (rhs[i] - result[i - 1]) / b;
    }

    for (int i = 1; i < n; i++) {
        result[n - i - 1] -= tmp[n - i] * result[n - i]; // Backsubstitution.
    }

    delete tmp;
}

void SmoothCurveCreator::calculateControlPoints(const QList<QPointF> &knots,
                                                QList<QPointF> *firstControlPoints,
                                                QList<QPointF> *secondControlPoints) {
    int n = knots.size() - 1;

    for (int i = 0; i < n; ++i) {
        firstControlPoints->append(QPointF());
        secondControlPoints->append(QPointF());
    }

    if (n == 1) {
        // Special case: Bezier curve should be a straight line.
        // P1 = (2P0 + P3) / 3
        (*firstControlPoints)[0].rx() = (2 * knots[0].x() + knots[1].x()) / 3;
        (*firstControlPoints)[0].ry() = (2 * knots[0].y() + knots[1].y()) / 3;

        // P2 = 2P1 – P0
        (*secondControlPoints)[0].rx() = 2 * (*firstControlPoints)[0].x() - knots[0].x();
        (*secondControlPoints)[0].ry() = 2 * (*firstControlPoints)[0].y() - knots[0].y();

        return;
    }

    // Calculate first Bezier control points
    double *xs = 0;
    double *ys = 0;
    double *rhsx = new double[n]; // Right hand side vector
    double *rhsy = new double[n]; // Right hand side vector

    // Set right hand side values
    for (int i = 1; i < n - 1; ++i) {
        rhsx[i] = 4 * knots[i].x() + 2 * knots[i + 1].x();
        rhsy[i] = 4 * knots[i].y() + 2 * knots[i + 1].y();
    }
    rhsx[0] = knots[0].x() + 2 * knots[1].x();
    rhsx[n - 1] = (8 * knots[n - 1].x() + knots[n].x()) / 2.0;
    rhsy[0] = knots[0].y() + 2 * knots[1].y();
    rhsy[n - 1] = (8 * knots[n - 1].y() + knots[n].y()) / 2.0;

    // Calculate first control points coordinates
    calculateFirstControlPoints(xs, rhsx, n);
    calculateFirstControlPoints(ys, rhsy, n);

    // Fill output control points.
    for (int i = 0; i < n; ++i) {
        (*firstControlPoints)[i].rx() = xs[i];
        (*firstControlPoints)[i].ry() = ys[i];

        if (i < n - 1) {
            (*secondControlPoints)[i].rx() = 2 * knots[i + 1].x() - xs[i + 1];
            (*secondControlPoints)[i].ry() = 2 * knots[i + 1].y() - ys[i + 1];
        } else {
            (*secondControlPoints)[i].rx() = (knots[n].x() + xs[n - 1]) / 2;
            (*secondControlPoints)[i].ry() = (knots[n].y() + ys[n - 1]) / 2;
        }
    }

    delete xs;
    delete ys;
    delete rhsx;
    delete rhsy;
}

////////////////////////////////////////////////////////////////////////////////////
QtCustomPlot::QtCustomPlot(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);

    m_nMinValue = 0;
    m_nMaxValue = 100;
    m_nStartTime = 0;

    m_nXStep = 24;
    m_nYStep = 10;

    m_bShowGrid = true;
    m_bDrawPath = true;

    m_strXLabels = "时间/S";
    m_strYLabels = "温度/℃";

    m_colorBackground = QColor("#1d252c");
    m_colorGridLine = QColor("#ffffff");
    m_colorLineColor = QColor("#02a7f0");

    m_font.setFamily("Microsoft Yahei");
    m_font.setPixelSize(14);
}

QtCustomPlot::~QtCustomPlot()
{

}

void QtCustomPlot::addData(double data)
{
    if (data > m_nMaxValue) data = m_nMaxValue;
    m_listData.push_back(data);
    updateData();
}

void QtCustomPlot::setData(QVector<double> data)
{
    m_listData = data;
    updateData();
}

void QtCustomPlot::clearData()
{
    m_listData.clear();
    update();
}

void QtCustomPlot::setMinValue(double minValue)
{
    if (this->m_nMinValue != minValue) {
        this->m_nMinValue = minValue;
        this->update();
    }
}

void QtCustomPlot::setMaxValue(double maxValue)
{
    if (this->m_nMaxValue != maxValue) {
        this->m_nMaxValue = maxValue;
        this->update();
    }
}

void QtCustomPlot::setXStep(double xStep)
{
    if (this->m_nXStep != xStep) {
        this->m_nXStep = xStep;
        this->update();
    }
}

void QtCustomPlot::setYStep(double yStep)
{
    if (this->m_nYStep != yStep) {
        this->m_nYStep = yStep;
        this->update();
    }
}

void QtCustomPlot::setLabels(QString strXLabel, QString strYLabel)
{
    m_strXLabels = strXLabel;
    m_strYLabels = strYLabel;
    calcDataBox();
    this->update();
}

void QtCustomPlot::setFont(QFont font)
{
    m_font = font;
    calcDataBox();
}

void QtCustomPlot::StartTest()
{
    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(SltTestData()));
    timer->start();
}

void QtCustomPlot::setBackgroundColor(QColor color)
{
    if (!color.isValid()) return;
    m_colorBackground = color;
    this->update();
}

void QtCustomPlot::calcDataBox()
{
    QFontMetrics fm(m_font);
    int nYoffset = QFontMetrics(fm).width(m_strYLabels);
    int nXoffset = fm.height();
    m_dataRect = QRect(nYoffset + 10, 30, this->width() - nYoffset - 40,
                       this->height() - 40 - nXoffset);

    updateData();
}

void QtCustomPlot::updateData()
{
    int i = m_listData.count() - m_nXStep;

    if (i > 0) {
        m_listData.remove(0, i);
        m_nStartTime += i;
    }

    if (m_listData.size() < 2) return;

    QList<QPointF> points;
    qreal nWidth = m_dataRect.width() * 1.0 / m_nXStep;
    int index = 0;
    foreach (double value, m_listData) {
        qreal yOffset = (1 - value / m_nMaxValue) * m_dataRect.height();
        points << QPointF(m_dataRect.left() + nWidth * index, yOffset);
        index++;
    }

    m_dataCurvePath = SmoothCurveCreator::createSmoothCurve(points);
    m_dataCurvePath.setFillRule(Qt::WindingFill);
    // 设置闭环
    QPointF lastPos = points.last();
    QPointF firstPos = points.first();
    m_dataCurvePath.lineTo(lastPos.x(), m_dataRect.bottom());
    m_dataCurvePath.lineTo(m_dataRect.left(), m_dataRect.bottom());
    m_dataCurvePath.lineTo(m_dataRect.left(), firstPos.y());
    // 计算当前值
    this->update();
}

void QtCustomPlot::SltTestData()
{
    int nValue = (qrand() % 20) + (m_nMaxValue / 2);
    this->addData(nValue * 1.0);
}

void QtCustomPlot::resizeEvent(QResizeEvent *e)
{
    calcDataBox();
    QWidget::resizeEvent(e);
}

void QtCustomPlot::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.fillRect(this->rect(), m_colorBackground);
    painter.setFont(m_font);

    // 绘制区域
    drawDataBox(&painter);
    // 绘制文字
    drawBoxText(&painter);
    // 绘制数据
    drawCurvePath(&painter);
}

void QtCustomPlot::drawDataBox(QPainter *painter)
{
    painter->setPen(QPen(QColor("#ffffff"), 1));
    painter->setBrush(m_colorGridLine);

    // 绘制Y轴
    QPointF pointsY[3] = {
        QPointF(m_dataRect.left(), 10),
        QPointF(m_dataRect.left() - 6, 20),
        QPointF(m_dataRect.left() + 6, 20)
    };

    QPointF pointsX[3] = {
        QPointF(m_dataRect.right() + 20,  m_dataRect.bottom()),
        QPointF(m_dataRect.right() + 10, m_dataRect.bottom() - 6),
        QPointF(m_dataRect.right() + 10, m_dataRect.bottom() + 6)
    };

    painter->drawConvexPolygon(pointsY, 3);
    painter->drawConvexPolygon(pointsX, 3);

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->drawLine(QPoint(m_dataRect.left(), 10), m_dataRect.bottomLeft());
    painter->drawLine(m_dataRect.topLeft(), m_dataRect.topRight());
    painter->drawLine(m_dataRect.topRight(), m_dataRect.bottomRight());
    painter->drawLine(m_dataRect.bottomLeft(), QPoint(m_dataRect.right() + 20, m_dataRect.bottom()));


    qreal offset = (m_dataRect.height() * 1.0 / 20);
    int nW = painter->fontMetrics().width("0000");
    int nH = painter->fontMetrics().height();
    QRect rect(m_dataRect.left() - nW, m_dataRect.top(), nW, nH);
    QString strTemp = QString("%1").arg(m_nMaxValue, 0, 'f', 0);
    painter->drawText(rect, Qt::AlignLeft, strTemp);
    int nCnt = (20 / m_nYStep);
    for (int i = 1; i < 20; i++) {
        int nY = m_dataRect.top() + i * offset;
        painter->drawLine(QPoint(m_dataRect.left(), nY), QPoint(m_dataRect.right(), nY));
        if (0 == (i % nCnt) && ((i / nCnt) != m_nYStep)) {
            rect = QRect(m_dataRect.left() - nW, nY, nW, nH);
            strTemp = QString("%1").arg((m_nMaxValue - (i / nCnt) * 10), 0, 'f', 0);
            painter->drawText(rect, Qt::AlignLeft, strTemp);
        }
    }

    offset = m_dataRect.width() * 1.0 / 24;
    rect = QRect(m_dataRect.left(), m_dataRect.bottom(), offset, nH);
    painter->drawText(rect, Qt::AlignLeft, QString("%1").arg(m_nStartTime));
    QString strValue = "";
    for (int i = 1; i < 24; i++) {
        int nX = m_dataRect.left() + i * offset;
        painter->drawLine(QPoint(nX, m_dataRect.top()), QPoint(nX, m_dataRect.bottom()));
        strValue = QString("%1").arg(m_nStartTime + i);
        int nW = painter->fontMetrics().width(strValue);
        if (nW > offset) {
            if ((0 != (i % 5))) continue;
            rect = QRect(nX, m_dataRect.bottom(), nW, nH);
            painter->drawText(rect, Qt::AlignLeft, QString("%1").arg(m_nStartTime + i));
        } else {
            rect = QRect(nX, m_dataRect.bottom(), offset, nH);
            painter->drawText(rect, Qt::AlignLeft, QString("%1").arg(m_nStartTime + i));
        }
    }


    painter->restore();
}

void QtCustomPlot::drawBoxText(QPainter *painter)
{
    painter->save();
    painter->setPen(m_colorGridLine);
    int nTextW = painter->fontMetrics().width(m_strYLabels);
    int nTextH = painter->fontMetrics().height();
    painter->drawText(1, 1, nTextW, nTextH, Qt::AlignCenter, m_strYLabels);


    nTextW = painter->fontMetrics().width(m_strXLabels);
    painter->drawText(this->width() - nTextW - 1, this->height() - nTextH,
                      nTextW, nTextH, Qt::AlignCenter, m_strXLabels);

    // 绘制x轴时间标签
    //    int nXoffset = (rect().width() - 20 )
    painter->restore();
}

void QtCustomPlot::drawCurvePath(QPainter *painter)
{
    if (m_listData.size() < 2) return;

    painter->save();
    QLinearGradient linearGradient(0, 0, 0, m_dataRect.bottom());
    linearGradient.setColorAt(0, QColor(2, 167, 240, 255));
    linearGradient.setColorAt(1, QColor(2, 167, 240, 0));
    painter->setPen(Qt::NoPen);
    painter->setBrush(linearGradient);
    painter->drawPath(m_dataCurvePath);
    painter->restore();
}
