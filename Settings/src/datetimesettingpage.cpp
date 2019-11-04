/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : timesettingpage.cpp --- TimeSettingPage
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "datetimesettingpage.h"
#include "skin.h"

#include <QDateTime>
#include <QProcess>
#include <QBoxLayout>
#include <QPushButton>

#include <QDebug>

DateTimeSettingPage::DateTimeSettingPage(QWidget *parent,
                                         QtDateTimeConfig::ConfigFromat format) :
    QWidget(parent)
{
    m_timeConfig = new QtDateTimeConfig(this);
    m_timeConfig->setFixedSize(375, 241);
    m_timeConfig->SetFont(Skin::m_strAppFontNormal);
    m_timeConfig->setConfigFormat(format);
    m_timeConfig->setStyleSheet(QString("QWidget{background-color: #ffffff; border: none; border-radius: 10px;}"
                                        "QLabel{ font-family: '%1'; font: 24px; color: #333333; border-radius: 0px;}")
                                .arg(Skin::m_strAppFontBold));

    QPushButton *btnConfig = new QPushButton(this);
    btnConfig->setText(tr("确定"));
    btnConfig->setFixedSize(166, 70);
    connect(btnConfig, SIGNAL(clicked(bool)), this, SLOT(SetSystemDatetime()));
    btnConfig->setStyleSheet(QString("QPushButton{ border-image: url(:/images/calendar/ic_btn.png);"
                                     "color: #ffffff; font: 30px; font-family:'%1';}"
                                     "QPushButton::pressed{border-image: url(:/images/calendar/ic_btn_pre.png);}").arg(Skin::m_strAppFontBold));

    QVBoxLayout *verLayout = new QVBoxLayout(this);
    verLayout->setContentsMargins(20, 20, 20, 20);
    verLayout->setSpacing(50);
    verLayout->addWidget(m_timeConfig, 0, Qt::AlignHCenter);
    verLayout->addWidget(btnConfig, 0, Qt::AlignHCenter);
}

DateTimeSettingPage::~DateTimeSettingPage()
{

}

void DateTimeSettingPage::SetSystemDatetime()
{
    if (QtDateTimeConfig::TimeFormat == m_timeConfig->getFormat()) {
#ifdef __arm__
        QTime time = m_timeConfig->getCurrentTime();
        QProcess cmd;
        cmd.start("date", QStringList() << "-s" << time.toString("hh:mm:ss"));
        cmd.waitForFinished(500);
        cmd.execute("hwclock -w");
        cmd.waitForFinished(500);
#endif
    }
    else {
#ifdef __arm__
        QDate date = m_timeConfig->getCurrentDate();
        QProcess cmd;
        cmd.start("date", QStringList() << "-s" << date.toString("yyyy-MM-dd"));
        cmd.waitForFinished(500);
        cmd.execute("hwclock -w");
        cmd.waitForFinished(500);
#endif
    }

    emit signalFinished();
}
