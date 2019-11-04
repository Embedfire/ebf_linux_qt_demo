/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : gyroscope.cpp ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/5
*******************************************************************/
#include "gyroscope.h"
#include "skin.h"

#include <QPainter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QPushButton>


TextBoardWidget::TextBoardWidget(QWidget *parent) : QWidget(parent)
{
    m_nPitchValue = 0;
    m_nRollValue = 0;
    m_nYawValue = 0;

    m_strTitle = tr("数据面板");

    m_strLabels = QStringList() << "X" << "Y" << "Z";
    m_strUnits = QStringList() << "°/s" << "°/s" << "°/s";
    this->setFixedSize(256, 296);
}

TextBoardWidget::~TextBoardWidget()
{

}

void TextBoardWidget::setValue(int index, qint16 value)
{
    if (0 == index) {
        m_nPitchValue = value;
    } else if (1 == index ) {
        m_nRollValue = value;
    } else if (2 == index) {
        m_nYawValue = value;
    }

    this->update();
}

void TextBoardWidget::setValues(int p, int r, int y)
{
    m_nPitchValue = p;
    m_nRollValue = r;
    m_nYawValue = y;
    this->update();
}

void TextBoardWidget::setTitle(const QString &text)
{
    m_strTitle = text;
    this->update();
}

void TextBoardWidget::setArgumensLabels(const QStringList &labels)
{
    if (labels.size() != 3) return;
    m_strLabels = labels;
}

void TextBoardWidget::setArgumensUnits(const QStringList &units)
{
    if (units.size() != 3) return;
    m_strUnits = units;
}

void TextBoardWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(32);
    painter.setFont(font);

    QRect rectData(this->rect());
    painter.setPen("#aaaaaa");
    painter.setBrush(QColor("#00509b"));
    painter.drawRoundedRect(1, 1, this->width() - 2, this->height() - 2, 6, 6);

    font.setPixelSize(24);
    painter.setFont(font);
    int nHeight = painter.fontMetrics().height();
    painter.setPen("#ffffff");
    // 参数
    QRect rect(rectData.left(), rectData.top() + 10, rectData.width(), nHeight);
    painter.drawText(rect, Qt::AlignCenter, m_strTitle);

    font.setFamily(Skin::m_strAppFontNormal);
    font.setPixelSize(24);
    painter.setFont(font);

    rect = QRect(rect.left() + 64, rect.top(), rect.width() - 80, rect.height());
    rect = QRect(rect.left(), rect.bottom() + 30, rect.width(), rect.height());
    QString strTemp = QString("%1 : %2 %3").arg(m_strLabels.at(0)).arg(m_nPitchValue, 4, 10).arg(m_strUnits.at(0));
    painter.drawText(rect, strTemp);

    rect = QRect(rect.left(), rect.bottom() + 30, rect.width(), rect.height());
    strTemp = QString("%1 : %2 %3").arg(m_strLabels.at(1)).arg(m_nRollValue, 4, 10).arg(m_strUnits.at(1));
    painter.drawText(rect, strTemp);

    rect = QRect(rect.left(), rect.bottom() + 30, rect.width(), rect.height());
    strTemp = QString("%1 : %2 %3").arg(m_strLabels.at(2)).arg(m_nYawValue, 4, 10).arg(m_strUnits.at(2));
    painter.drawText(rect, strTemp);
}

/////////////////////////////////////////////////////////////////////////////
Gyroscope::Gyroscope(QWidget *parent) : QtAnimationWidget(parent)
{
    m_nPitchValue = 0;
    m_nRollValue = 0;
    m_nYawValue = 0;

    InitWidget();

#if 0
    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(SltStartTest()));
    timer->start();
#endif

    // 数据采集
    m_threadTest = new Mpu6050Thread(this);
    connect(m_threadTest, SIGNAL(signalUpdate(int,int,qint16)), this, SLOT(SltUpdateValues(int,int,qint16)));
    m_threadTest->start();
}

Gyroscope::~Gyroscope()
{
    m_threadTest->Stop();
}

void Gyroscope::InitWidget()
{
    QPushButton *btnHome = new QPushButton(this);
    btnHome->setFixedSize(54, 54);
    connect(btnHome, SIGNAL(clicked(bool)), this, SIGNAL(signalBackHome()));
    btnHome->setStyleSheet(QString("QPushButton {border-image: url(:/images/music/menu_icon.png);}"
                                   "QPushButton:pressed {border-image: url(:/images/music/menu_icon_pressed.png);}"));

    m_textBoardLeft = new TextBoardWidget(this);
    m_textBoardLeft->setTitle(tr("加速度"));
    m_textBoardLeft->setArgumensUnits(QStringList() << "m/s²" << "m/s²" << "m/s²");

#ifdef USE_TEXT_BOARD
    m_textBoardRight = new TextBoardWidget(this);
    m_textBoardRight->setTitle(tr("角速度"));
#else
    m_widgetDisplay = new GyroscopeWidget(this);
    m_widgetDisplay->SetFont(QFont(Skin::m_strAppFontNormal));
    m_widgetDisplay->setYawValue(m_nYawValue);
    m_widgetDisplay->setFixedSize(344, 344);
    m_widgetDisplay->setRollValue(m_nRollValue);
    m_widgetDisplay->setPitchValue(m_nPitchValue);
#endif

    QHBoxLayout *horLayout = new QHBoxLayout();
    horLayout->setContentsMargins(10, 10, 10, 10);
    horLayout->addWidget(m_textBoardLeft, 1, Qt::AlignCenter);
#ifdef USE_TEXT_BOARD
    horLayout->addWidget(m_textBoardRight, 1, Qt::AlignCenter);
#else
    horLayout->addWidget(m_widgetDisplay, 1, Qt::AlignCenter);
#endif

    QVBoxLayout *verLayout = new QVBoxLayout(this);
    verLayout->setContentsMargins(10, 10, 10, 10);
    verLayout->setSpacing(20);
    verLayout->addWidget(btnHome, 0, Qt::AlignRight | Qt::AlignTop);
    verLayout->addLayout(horLayout, 1);
}

void Gyroscope::SltStartTest()
{
    int nDirection = qrand() % 2;
    m_nYawValue = (qrand() % 80 + 100)  * (1 == nDirection ? 1 : -1);

    nDirection = qrand() % 2;
    m_nRollValue = (qrand() % 30 + 60)  * (1 == nDirection ? 1 : -1);

    nDirection = qrand() % 2;
    m_nPitchValue = (qrand() % 80 + 100)  * (1 == nDirection ? 1 : -1);

    m_textBoardLeft->setValues(m_nPitchValue, m_nRollValue, m_nYawValue);
#ifdef USE_TEXT_BOARD
    m_textBoardRight->setValues(m_nPitchValue, m_nRollValue, m_nYawValue);
#else
    m_widgetDisplay->setYawValue(m_nYawValue);
    m_widgetDisplay->setRollValue(m_nRollValue);
    m_widgetDisplay->setPitchValue(m_nPitchValue);
#endif

    this->update();
}

void Gyroscope::SltUpdateValues(int type, int index, qint16 value)
{
    if (0 == type) {
        m_textBoardLeft->setValue(index, value);
    } else {
#ifdef USE_TEXT_BOARD
        m_textBoardRight->setValue(index, value);
#endif
    }
}

void Gyroscope::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::TextAntialiasing | QPainter::Antialiasing);
    painter.drawPixmap(this->rect(), QPixmap(":/images/gry/background.png"));

    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(32);
    painter.setFont(font);
    painter.setPen("#ffffff");
    painter.drawText(0, 0, this->width(), 100, Qt::AlignCenter, QString("陀螺仪"));
}

