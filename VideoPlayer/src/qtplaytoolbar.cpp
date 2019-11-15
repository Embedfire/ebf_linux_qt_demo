/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : qtplaytoolbar.cpp --- QtPlayToolBar
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/14
*******************************************************************/
#include "qtplaytoolbar.h"
#include "skin.h"

#include <QPainter>
#include <QMouseEvent>
#include <QButtonGroup>

//////////////////////////////////////////////////////////////////////////////////////
PlayTitleBarWidget::PlayTitleBarWidget(QWidget *parent) : QtToolBar(parent)
{
    m_strText = "";
    m_nBaseWidth = Skin::m_nScreenWidth;
    m_nBaseHeight = 50;

    m_rectBack = QRect(20, 10, 40, 40);
}

PlayTitleBarWidget::~PlayTitleBarWidget()
{

}

void PlayTitleBarWidget::SetText(const QString &text)
{
    m_strText = text;
    this->update();
}

void PlayTitleBarWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.scale(m_scaleX, m_scaleY);
    painter.fillRect(0, 0, m_nBaseWidth, m_nBaseHeight, QColor("#7f182E3A"));

    painter.drawPixmap(m_rectBack.topLeft(), QPixmap(":/images/photos/toolbar/ic_back.png"));

    painter.setPen("#ffffff");
    painter.setFont(QFont(Skin::m_strAppFontNormal, 18));
    painter.drawText(0, 0, m_nBaseWidth, m_nBaseHeight, Qt::AlignCenter, m_strText);
}

void PlayTitleBarWidget::mousePressEvent(QMouseEvent *e)
{
    QRect rect;
    ScaleRect(rect, m_rectBack);
    if (rect.contains(e->pos())) {
        emit signalBack();
    }
    QWidget::mousePressEvent(e);
}


//////////////////////////////////////////////////////////////////////////////////////
PlayerBarWidget::PlayerBarWidget(QWidget *parent) : QtToolBar(parent)
{
    m_nBaseWidth = Skin::m_nScreenWidth;
    m_nBaseHeight = 102;

    m_strCurrTime = "00:00";
    m_strDuration = "00:00";

    InitWidget();
    connect(this, SIGNAL(signalBtnClicked(int)), this, SLOT(SltBtnClicked(int)));
}

PlayerBarWidget::~PlayerBarWidget()
{

}

void PlayerBarWidget::setPlayState(bool bOk)
{
    m_btns.value(1)->setChecked(bOk);
}

void PlayerBarWidget::setPostion(int postion)
{
    m_progressBar->SetValue(postion);
    m_strCurrTime = QString("%1:%2").arg(postion / 60, 2, 10, QChar('0')).arg(postion % 60, 2, 10, QChar('0'));
    this->update();
}

void PlayerBarWidget::setDuration(int duration)
{
    m_progressBar->SetMaxValue(duration);
    m_strDuration = QString("%1:%2").arg(duration / 60, 2, 10, QChar('0')).arg(duration % 60, 2, 10, QChar('0'));
    this->update();
}

void PlayerBarWidget::InitWidget()
{
    m_btns.insert(0, new QtPixmapButton(0, QRect(295, 40, 60, 60), QPixmap(":/images/video/ic_prev.png"), QPixmap(":/images/video/ic_prev_pre.png")));
    m_btns.insert(1, new QtPixmapButton(1, QRect(375, 40, 60, 60), QPixmap(":/images/video/ic_play.png"), QPixmap(":/images/video/ic_pause.png")));
    m_btns.insert(2, new QtPixmapButton(2, QRect(465, 40, 60, 60), QPixmap(":/images/video/ic_next.png"), QPixmap(":/images/video/ic_next_pre.png")));
    m_btns.insert(3, new QtPixmapButton(3, QRect(655, 40, 60, 60), QPixmap(":/images/video/ic_volume.png"), QPixmap(":/images/video/ic_volume_pre.png")));
    m_btns.insert(4, new QtPixmapButton(4, QRect(728, 40, 60, 60), QPixmap(":/images/video/ic_menu_list.png"), QPixmap(":/images/video/ic_menu_list_pre.png")));
    m_btns.value(1)->setCheckAble(true);

    // 进度条
    m_progressBar = new QtSliderBar(this);
    m_progressBar->SetHorizontal(true);
    m_progressBar->SetSliderSize(2, 40);
    connect(m_progressBar, SIGNAL(currentValueChanged(int)), this, SIGNAL(currentPostionChanged(int)));
}

void PlayerBarWidget::SltBtnClicked(int index)
{
    if (0 == index) {
        emit signalPrev();
    } else if (1 == index) {
        QtPixmapButton *btn = m_btns.value(1);
        emit signalPlay(btn->isChecked());
    } else if (2 == index) {
        emit signalNext();
    } else if (3 == index) {
        emit signalVolume();
    } else if (4 == index) {
        emit signalMuenList();
    }
}

void PlayerBarWidget::resizeEvent(QResizeEvent *e)
{
    SetScaleValue();
    m_progressBar->SetSliderSize(2, 40 * m_scaleY);
    m_progressBar->resize(675 * m_scaleX, 40 * m_scaleY);
    m_progressBar->move(60 * m_scaleX, 1);
    m_progressBar->SetValue(m_progressBar->value());
    QWidget::resizeEvent(e);
}

void PlayerBarWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.scale(m_scaleX, m_scaleY);
    QLinearGradient linearGradient(QPoint(0, 0), QPoint(0, this->height()));
    linearGradient.setColorAt(0, QColor("#00aaaaaa"));
    linearGradient.setColorAt(1, QColor("#d0aaaaaa"));
    painter.setPen(Qt::NoPen);
    painter.setBrush(linearGradient);
    painter.drawRect(0, 0, m_nBaseWidth, m_nBaseHeight);

    painter.setPen(QColor("#ffffff"));
    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(18);
    painter.setFont(font);
    painter.drawText(QRect(4, 0, 60, 40), Qt::AlignCenter, m_strCurrTime);
    painter.drawText(QRect(740, 0, 60, 40), Qt::AlignCenter, m_strDuration);

    foreach (QtPixmapButton *btn, m_btns) {
        int nX = btn->rect().left() + (btn->rect().width() - btn->pixmap().width()) / 2;
        int nY = btn->rect().top() + (btn->rect().height() - btn->pixmap().height()) / 2;
        painter.drawPixmap(nX, nY, btn->pixmap());
    }
}

