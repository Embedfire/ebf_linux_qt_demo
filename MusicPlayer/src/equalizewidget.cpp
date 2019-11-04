/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : equalizewidget.cpp --- EqualizeWidget
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/8/31
*******************************************************************/
#include "equalizewidget.h"
#include "skin.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QPainter>

QtEqualizeSliderBar::QtEqualizeSliderBar(int id, QWidget *parent) :
    QtSliderBar(parent),m_nId(id)
{
    connect(this, SIGNAL(currentValueChanged(int)), this, SLOT(SltCurrentValueChanged(int)));
}

QtEqualizeSliderBar::~QtEqualizeSliderBar()
{

}

void QtEqualizeSliderBar::SltCurrentValueChanged(int value)
{
    emit currentValueChanged(m_nId, value);
}


///////////////////////////////////////////////////////////////////////////////////////
EqualizeWidget::EqualizeWidget(QWidget *parent) : QtAnimationWidget(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setMinimumSize(405, 355);
    m_nYPos = 60;
    InitWidget();
}

EqualizeWidget::~EqualizeWidget()
{

}

void EqualizeWidget::StartAutoMove(bool bShow, int width)
{
    this->SetAnimationCurve(bShow ? QEasingCurve::OutBounce : QEasingCurve::Linear);
    if (!this->isVisible()) this->setVisible(true);
    QPoint startPos = QPoint(width, m_nYPos);
    QPoint endPos = QPoint(width - this->width(), m_nYPos);
    this->StartAnimation(bShow ? startPos : endPos, !bShow ? startPos : endPos, 300, bShow);
}

void EqualizeWidget::InitWidget()
{
    QLabel *labelTitle = new QLabel(this);
    labelTitle->setObjectName("labelTitle");
    labelTitle->setText(QStringLiteral("均衡器"));
    labelTitle->setAlignment(Qt::AlignCenter);

    QStringList strLabels = QStringList() << "31" << "62" << "125" << "250" << "500"
                                          << "1K" << "2K" << "4K" << "8K" << "16K";
    QHBoxLayout *horLayoutSlider = new QHBoxLayout();
    horLayoutSlider->setContentsMargins(0, 0, 0, 0);
    horLayoutSlider->setSpacing(10);
    for (int i = 0; i < 10; i++) {
        QVBoxLayout *verLayoutSlider = new QVBoxLayout();
        verLayoutSlider->setContentsMargins(0, 0, 0, 0);
        verLayoutSlider->setSpacing(0);

        m_sliderBar[i] = new QtEqualizeSliderBar(i + 1, this);
        m_sliderBar[i]->SetHorizontal(false);
        m_sliderBar[i]->SetSliderSize(4, 32);
        m_sliderBar[i]->setFixedSize(32, 236);
        connect(m_sliderBar[i], SIGNAL(currentValueChanged(int,int)), this, SLOT(SltEqualizeClicked(int,int)));

        QLabel *labelText = new QLabel(strLabels.at(i), this);
        labelText->setAlignment(Qt::AlignCenter);

        verLayoutSlider->addWidget(m_sliderBar[i], 1);
        verLayoutSlider->addWidget(labelText, 1, Qt::AlignVCenter);
        horLayoutSlider->addLayout(verLayoutSlider, 1);
    }

    QVBoxLayout *verLayoutAll = new QVBoxLayout(this);
    verLayoutAll->setContentsMargins(10, 10, 10, 30);
    verLayoutAll->setSpacing(10);
    verLayoutAll->addWidget(labelTitle);
    verLayoutAll->addLayout(horLayoutSlider);
    verLayoutAll->addStretch();

    this->setStyleSheet(QString("QLabel{font-family:'%1'; color: #333333; font: bold 18px;}"
                                "QLabel#labelTitle {color: #ffffff; font: bold 24px;}").arg(Skin::m_strAppFontBold));
}

QSize EqualizeWidget::minimumSize() const
{
    return QSize(405, 355);
}

QSize EqualizeWidget::sizeHint() const
{
    return QSize(405, 355);
}

void EqualizeWidget::SltEqualizeClicked(int index, int value)
{
    qDebug() << "SltEqualizeClicked" << index << value;
}

void EqualizeWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor("#5362b5"));
    painter.drawRoundedRect(0, 0, this->width() + 10, this->height(), 6, 6);
}
