/**********************************************;********************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : cameraconfig.cpp --- CameraConfig
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/16
*******************************************************************/
#include "cameraconfig.h"
#include "skin.h"
#include "qtsliderbar.h"

#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <QBoxLayout>
#include <QDebug>
#include <QPushButton>

ConfigWidget::ConfigWidget(QWidget *parent) : QWidget(parent)
{
    m_nRow = 3;
    m_nIndex = 0;
    m_nItemHeight = 45;
    m_bSelected = true;
    m_strItems = QStringList();
}

ConfigWidget::~ConfigWidget()
{
    m_strItems.clear();
}

void ConfigWidget::setRows(int row)
{
    m_nRow = row;
    this->setFixedHeight(m_nRow * m_nItemHeight + m_nRow + 1);
    this->update();
}

void ConfigWidget::setItems(const QStringList &strItems)
{
    m_strItems = strItems;
    this->setRows(m_strItems.size());
}

void ConfigWidget::setCurrentIndex(const int &index)
{
    m_nIndex = index;
    this->update();
}

void ConfigWidget::setSelectMode(bool bOk)
{
    m_bSelected = bOk;
    this->update();
}

void ConfigWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), QColor("#cc555555"));
    painter.setPen(QColor("#7fdcdcdc"));
    for (int i = 0; i <= m_nRow; i++) {
        painter.drawLine(QPoint(0, i * m_nItemHeight), QPoint(this->width(), i * m_nItemHeight));
    }
    //    painter.drawLine(QPoint(0, this->height() - 2), QPoint(this->width(), this->height() - 2));

    if (!m_strItems.isEmpty()) {
        drawItemInfo(&painter);
    }
}

void ConfigWidget::drawItemInfo(QPainter *painter)
{
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(24);
    painter->setFont(font);

    int nSpace = 15;
    int radius = m_bSelected ? 23 : -nSpace;
    int offset = 8;
    for (int i = 0; i < m_strItems.size(); i++) {
        if (m_bSelected) {
            painter->setPen(QColor("#00ffff"));
            painter->setBrush(QColor("#ffffff"));
            painter->drawEllipse(nSpace, (m_nItemHeight - radius) / 2 + i * m_nItemHeight, radius, radius);
            if (m_nIndex == i) {
                painter->setBrush(QColor("#00ffff"));
                painter->drawEllipse(nSpace + offset / 2, (m_nItemHeight - radius) / 2 + i * m_nItemHeight + offset / 2,
                                     radius - offset, radius - offset);
            }
        }

        QRect rect(nSpace * 2 + radius, i * m_nItemHeight, this->width() - nSpace * 3 + radius, m_nItemHeight);
        painter->setPen(QColor("#ffffff"));
        painter->drawText(rect, Qt::AlignVCenter, m_strItems.at(i));
    }

    painter->restore();
}

void ConfigWidget::mousePressEvent(QMouseEvent *e)
{
    int nY = e->y();
    m_nIndex = (nY / m_nItemHeight);
    this->update();
    emit signalClicked(m_nIndex);
    emit signalItemClicked(m_strItems.at(m_nIndex));
}


//////////////////////////////////////////////////////////////////
CameraConfig::CameraConfig(QWidget *parent) : QtAnimationWidget(parent)
{
    this->SetBackground(Qt::transparent);
    m_photoSize = QSize(800, 480);
    m_strListResolv = QStringList() << "320x240" << "480x272" << tr("800x480(默认)");
    m_strListLight = QStringList() << tr("自动(默认)") << tr("光照") << tr("阴天") << tr("办公室") << tr("室内");
    m_strListEffect = QStringList() << tr("正常(默认)") << tr("冷色") << tr("暖色")
                                    << tr("黑白") << tr("泛黄") << tr("偏绿") << tr("过曝");
    InitWidget();
    InitMainPage();
}

CameraConfig::~CameraConfig()
{

}

QSize CameraConfig::photoSize() const
{
    return m_photoSize;
}

void CameraConfig::InitWidget()
{
    m_widgetTitle = new QtWidgetTitleBar(this);
    m_widgetTitle->SetBackground(QColor("#000000"));
    m_widgetTitle->SetScalSize(400, 45);
    m_widgetTitle->setFont(Skin::m_strAppFontBold);
    m_widgetTitle->SetTitle(tr("参数设置"), "#ffffff", 24);

    m_btnBack = new QPushButton(m_widgetTitle);
    connect(m_btnBack, SIGNAL(clicked(bool)), this, SLOT(SltBackClicked()));
    m_btnBack->setFixedSize(40, 40);
    m_btnBack->setVisible(false);
    m_btnBack->setStyleSheet(QString("QPushButton{border-image: url(:/images/camera/ic_back.png);}"
                                     "QPushButton:pressed{border-image: url(:/images/camera/ic_back_pre.png);}"));
    QHBoxLayout *horLayoutTitle = new QHBoxLayout(m_widgetTitle);
    horLayoutTitle->setContentsMargins(10, 0, 10, 0);
    horLayoutTitle->setSpacing(10);
    horLayoutTitle->addWidget(m_btnBack);
    horLayoutTitle->addStretch();

    m_stackedWidget = new QtStackedWidget(this);
    m_stackedWidget->setPressMove(false);
    m_stackedWidget->SetBackground(Qt::transparent);
    m_stackedWidget->setCurrentIndex(0);

    m_configMain = new ConfigWidget(m_stackedWidget);
#if 0
    m_configMain->setItems(QStringList() << tr("自动对焦") << tr("亮度") << tr("饱和度") << tr("对比度")
                           << tr("分辨率") << tr("光线模式") << tr("特殊效果"));
#endif
    m_configMain->setSelectMode(false);
    m_configMain->setRows(7);
    m_stackedWidget->addWidget(0, m_configMain);
    connect(m_configMain, SIGNAL(signalClicked(int)), this, SLOT(SltChangePage(int)));

    m_configResolv = new ConfigWidget(m_stackedWidget);
    m_configResolv->setItems(m_strListResolv);
    m_configResolv->setCurrentIndex(2);
    m_stackedWidget->addWidget(1, m_configResolv);
    connect(m_configResolv, SIGNAL(signalClicked(int)), this, SLOT(SltPhotoSize(int)));

    m_configLight = new ConfigWidget(m_stackedWidget);
    m_configLight->setItems(m_strListLight);
    m_stackedWidget->addWidget(2, m_configLight);

    m_configEffect = new ConfigWidget(m_stackedWidget);
    m_configEffect->setItems(m_strListEffect);
    m_stackedWidget->addWidget(3, m_configEffect);

    QVBoxLayout *verLayout = new QVBoxLayout(this);
    verLayout->setContentsMargins(0, 0, 0, 0);
    verLayout->setSpacing(0);
    verLayout->addWidget(m_widgetTitle);
    verLayout->addWidget(m_stackedWidget, 1);
}

void CameraConfig::InitMainPage()
{
    QVBoxLayout *verLayoutAll = new QVBoxLayout(m_configMain);
    verLayoutAll->setContentsMargins(0, 0, 0, 0);
    verLayoutAll->setSpacing(0);

    {
        QHBoxLayout *horLayout = new QHBoxLayout();
        horLayout->setContentsMargins(10, 0, 10, 0);
        horLayout->addWidget(new QLabel(tr("自动对焦"), m_configMain));
        verLayoutAll->addLayout(horLayout);

        QtSwitchButton *switchBtn = new QtSwitchButton(m_configMain);
        switchBtn->setFixedSize(51, 25);
        horLayout->addStretch();
        horLayout->addWidget(switchBtn);
    }

    {
        QHBoxLayout *horLayout = new QHBoxLayout();
        horLayout->setContentsMargins(10, 0, 0, 0);
        horLayout->addWidget(new QLabel(tr("亮度"), m_configMain));
        verLayoutAll->addLayout(horLayout);

        QtSliderBar *sliderLight = new QtSliderBar(m_configMain);
        sliderLight->SetMaxValue(100);
        sliderLight->setFixedSize(200, 45);
        sliderLight->SetHorizontal(true);
        sliderLight->ShowHandleBackground(false);
        sliderLight->SetHandleColor(QColor("#00ffff"));
        sliderLight->SetSliderSize(3, 30);
        horLayout->addStretch();
        horLayout->addWidget(sliderLight);
    }

    {
        QHBoxLayout *horLayout = new QHBoxLayout();
        horLayout->setContentsMargins(10, 0, 0, 0);
        horLayout->addWidget(new QLabel(tr("饱和度"), m_configMain));
        verLayoutAll->addLayout(horLayout);

        QtSliderBar *sliderSaturation = new QtSliderBar(m_configMain);
        sliderSaturation->SetMaxValue(100);
        sliderSaturation->setFixedSize(200, 45);
        sliderSaturation->SetHorizontal(true);
        sliderSaturation->ShowHandleBackground(false);
        sliderSaturation->SetHandleColor(QColor("#00ffff"));
        sliderSaturation->SetSliderSize(3, 30);
        horLayout->addStretch();
        horLayout->addWidget(sliderSaturation);
    }

    {
        QHBoxLayout *horLayout = new QHBoxLayout();
        horLayout->setContentsMargins(10, 0, 0, 0);
        horLayout->addWidget(new QLabel(tr("对比对"), m_configMain));
        verLayoutAll->addLayout(horLayout);

        QtSliderBar *sliderContrastratio = new QtSliderBar(m_configMain);
        sliderContrastratio->SetMaxValue(100);
        sliderContrastratio->setFixedSize(200, 45);
        sliderContrastratio->SetHorizontal(true);
        sliderContrastratio->ShowHandleBackground(false);
        sliderContrastratio->SetHandleColor(QColor("#00ffff"));
        sliderContrastratio->SetSliderSize(3, 30);
        horLayout->addStretch();
        horLayout->addWidget(sliderContrastratio);
    }

    {
        QHBoxLayout *horLayout = new QHBoxLayout();
        horLayout->addWidget(new QLabel(tr("分辨率"), m_configMain));
        horLayout->setContentsMargins(10, 0, 10, 0);
        horLayout->setSpacing(0);
        verLayoutAll->addLayout(horLayout);

        m_labelResolv = new QLabel(m_configMain);
        m_labelResolv->setText(m_strListResolv.at(2));
        connect(m_configResolv, SIGNAL(signalItemClicked(QString)), m_labelResolv, SLOT(setText(QString)));

        horLayout->addStretch();
        horLayout->addWidget(m_labelResolv);

        QLabel *labelNext = new QLabel(m_configMain);
        labelNext->setFixedSize(27, 27);
        labelNext->setPixmap(QPixmap(":/images/camera/ic_next.png"));
        horLayout->addWidget(labelNext, 0, Qt::AlignVCenter);
    }

    {
        QHBoxLayout *horLayout = new QHBoxLayout();
        horLayout->addWidget(new QLabel(tr("光线模式"), m_configMain));
        horLayout->setContentsMargins(10, 0, 10, 0);
        horLayout->setSpacing(0);
        verLayoutAll->addLayout(horLayout);

        m_labelLight = new QLabel(m_configMain);
        m_labelLight->setText(m_strListLight.at(0));
        connect(m_configLight, SIGNAL(signalItemClicked(QString)), m_labelLight, SLOT(setText(QString)));

        horLayout->addStretch();
        horLayout->addWidget(m_labelLight);

        QLabel *labelNext = new QLabel(m_configMain);
        labelNext->setFixedSize(27, 27);
        labelNext->setPixmap(QPixmap(":/images/camera/ic_next.png"));
        horLayout->addWidget(labelNext, 0, Qt::AlignVCenter);
    }

    {
        QHBoxLayout *horLayout = new QHBoxLayout();
        horLayout->addWidget(new QLabel(tr("特殊效果"), m_configMain));
        horLayout->setContentsMargins(10, 0, 10, 0);
        horLayout->setSpacing(0);
        verLayoutAll->addLayout(horLayout);

        m_labelEffect = new QLabel(m_configMain);
        m_labelEffect->setText(m_strListEffect.at(0));
        connect(m_configEffect, SIGNAL(signalItemClicked(QString)), m_labelEffect, SLOT(setText(QString)));

        horLayout->addStretch();
        horLayout->addWidget(m_labelEffect);

        QLabel *labelNext = new QLabel(m_configMain);
        labelNext->setFixedSize(27, 27);
        labelNext->setPixmap(QPixmap(":/images/camera/ic_next.png"));
        horLayout->addWidget(labelNext, 0, Qt::AlignVCenter);
    }
    verLayoutAll->addStretch();

    this->setStyleSheet(QString("QLabel{font-family: '%1'; font: 24px; color: #ffffff; min-height: 45px;}").arg(Skin::m_strAppFontBold));
}

void CameraConfig::SltBackClicked()
{
    m_btnBack->setVisible(false);
    m_stackedWidget->setCurrentIndex(0, QtStackedWidget::LeftDirection, 315);
    this->resize(this->width(), 360);
}

void CameraConfig::SltChangePage(int index)
{
    if (index < 3) return;

    m_btnBack->setVisible(index > 3);
    int nRow = 3;
    if (4 == index) nRow = 3;
    else if (5 == index) nRow = 5;
    else if (6 == index) nRow = 7;
    m_stackedWidget->setCurrentIndex(index - 3, QtStackedWidget::UpDirection, nRow * 45);
    this->resize(this->width(), (nRow + 1) * 45);
}

void CameraConfig::SltPhotoSize(int index)
{
    if (0 == index) m_photoSize = QSize(320, 240);
    else if (1 == index) m_photoSize = QSize(480, 272);
    else if (2 == index) m_photoSize = QSize(800, 480);
}

void CameraConfig::showEvent(QShowEvent *e)
{
    m_btnBack->setVisible(false);
    m_stackedWidget->setCurrentIndex(0);
    this->resize(this->width(), 360);
    QWidget::showEvent(e);
}

