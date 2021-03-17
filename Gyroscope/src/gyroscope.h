/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : gyroscope.h ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/5
*******************************************************************/
#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include "qtwidgetbase.h"
#include "mpu6050thread.h"
#include "gyroscopewidget.h"
#include "qtwidgetbase.h"
#include "qtpixmapbutton.h"

#ifndef USE_TEXT_BOARD
#define USE_TEXT_BOARD
#endif

class TextBoardWidget : public QtWidgetBase
{
    Q_OBJECT
public:
    TextBoardWidget(QWidget *parent = 0);
    ~TextBoardWidget();

    void setValue(int index, qint16 value);
    void setValue(int index, double value);
    void setValues(int p, int r, int y);
    void setValues(double p, double r, double y);

    void setTitle(const QString &text);
    void setArgumensLabels(const QStringList &labels);
    void setArgumensUnits(const QStringList &units);

private:
    double m_nPitchValue;
    double m_nRollValue;
    double m_nYawValue;

    QString     m_strTitle;
    QStringList m_strLabels;
    QStringList m_strUnits;

protected:
    void paintEvent(QPaintEvent *);
};

class Gyroscope : public QtAnimationWidget
{
    Q_OBJECT

public:
    Gyroscope(QWidget *parent = 0);
    ~Gyroscope();

private:
    int m_nPitchValue;
    int m_nRollValue;
    int m_nYawValue;

    int m_nPitchValue_1;
    int m_nRollValue_1;
    int m_nYawValue_1;

    TextBoardWidget     *m_textBoardLeft;
#ifdef USE_TEXT_BOARD
    TextBoardWidget     *m_textBoardRight;
#else
    GyroscopeWidget     *m_widgetDisplay;
#endif

    Mpu6050Thread       *m_threadTest;
    QtPixmapButton      *m_btnHome;

private:
    void InitWidget();
    QString CheckMPU6050Device();

private slots:
    void SltStartTest();
    void SltUpdateValues(int type, int index, qint16 value);
    void SltUpdateValues(int type, int index, double value);
protected:
    void resizeEvent(QResizeEvent *e);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // GYROSCOPE_H
