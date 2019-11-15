/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : weatherwidget.h --- WeatherWidget
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef WEATHERWIDGET_H
#define WEATHERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QMap>
#include <QTimer>

#include "qtwidgetbase.h"
#include "qtpagelistwidget.h"
#include "qtwaitwidget.h"
#include "weatherapi.h"
#include "citymanagerwidget.h"
#include "qtpixmapbutton.h"

class WeatherView : public QtWidgetBase
{
    Q_OBJECT
public:
    explicit WeatherView(QWidget *parent = 0);
    ~WeatherView();

    void setWeatherData(const QStringList &weatherData);
    void startRefresh();
    void showErrorMessage(const QString &text);

signals:
    void signalToolBtnClicked(int index);

private:
    bool    m_bPressed;
    QPoint  m_startPos;

    int     m_nYOffset;
    QRect   m_rectCenter;

    QtWaitWidget    *m_widgetRefresh;
    bool            m_bRefresh;

    QPixmap         m_pixmapWeatherType;
    QStringList     m_strWeatherDatas;

    QPixmap         m_pixmapWeatherBackground;

    QString         m_strErrorMsg;

private:
    QString getTodayOfWeek();

private slots:
    void SltResetWidget();

protected:
    void resizeEvent(QResizeEvent *e);

    void paintEvent(QPaintEvent *);
    void drawWeatherInfo(QPainter *painter);
    void drawStatusBar(QPainter *painter);

    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
};

///////////////////////////////////////////////////////////////////////
class WeatherReport : public QtListWidget {
    Q_OBJECT
public:
    explicit WeatherReport(QWidget *parent = 0);
    ~WeatherReport();

private:
    QPixmap getPixmap(const QString &type);

protected:
    void drawItemInfo(QPainter *painter, QtListWidgetItem *item);
};

///////////////////////////////////////////////////////////////////////
class WeatherWidget : public QtAnimationWidget
{
    Q_OBJECT
public:
    explicit WeatherWidget(QWidget *parent = 0);
    ~WeatherWidget();

signals:

public slots:

private:
    WeatherView     *m_weatherView;
    WeatherReport   *m_weatherReport;
    QLabel          *m_labelDate;

    WeatherApi      *m_weatherApi;
    QString          m_strCityCode;

    QMap<int, QtListWidgetItem *> m_weatherItems;

    CityManagerWidget *m_cityManager;

private:
    void InitWidget();

    QString getTemperature(const QString &high, const QString &low);

private slots:
    void SltCityManagerBack();
    void SltCityChanged(const QString &city);

private slots:
    void InitWeather();
    void SltToolBtnClicked(int index);
    void SltWeatherReply(const QByteArray &jsonData);

protected:
    void resizeEvent(QResizeEvent *e);
};

#endif // WEATHERWIDGET_H
