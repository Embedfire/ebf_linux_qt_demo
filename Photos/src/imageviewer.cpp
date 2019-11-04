/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : imageviewer.cpp --- ImageViewer
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/8
*******************************************************************/
#include "imageviewer.h"
#include "skin.h"
#include <QPainter>
#include <QMouseEvent>

#include <QFileInfo>
#include <QButtonGroup>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

#define BTN_SIZE        50


//////////////////////////////////////////////////////////////////////////////////////
TitleBarWidget::TitleBarWidget(QWidget *parent) : QtToolBar(parent)
{
    m_strText = "";
    this->setFixedHeight(50);
    m_rectBack = QRect(20, 10, 30, 30);
}

TitleBarWidget::~TitleBarWidget()
{

}

void TitleBarWidget::SetText(const QString &text)
{
    m_strText = text;
    this->update();
}

void TitleBarWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), QColor("#b2ededed"));

    painter.drawPixmap(m_rectBack, QPixmap(":/images/photos/toolbar/ic_back.png"));

    painter.setPen("#333333");
    painter.setFont(QFont(Skin::m_strAppFontNormal, 18));
    painter.drawText(this->rect(), Qt::AlignCenter, m_strText);
    painter.setPen("#cacaca");
    painter.drawLine(this->rect().bottomLeft(), this->rect().bottomRight());
}

void TitleBarWidget::mousePressEvent(QMouseEvent *e)
{
    if (m_rectBack.contains(e->pos())) {
        emit signalBack();
    }
    QWidget::mousePressEvent(e);
}

//////////////////////////////////////////////////////////////////////////////////////
BottomBarWidget::BottomBarWidget(QWidget *parent) : QtToolBar(parent)
{
    this->setFixedHeight(50);
    InitWidget();
}

BottomBarWidget::~BottomBarWidget()
{

}

void BottomBarWidget::Stop()
{
    m_btnPlay->setChecked(false);
}

void BottomBarWidget::InitWidget()
{
    QButtonGroup *btnGroup = new QButtonGroup(this);
    QHBoxLayout *horLayout = new QHBoxLayout(this);
    horLayout->setContentsMargins(10, 10, 10, 10);
    horLayout->setSpacing(84);
    horLayout->addStretch();

    QPushButton *btnPlus = new QPushButton(this);
    btnPlus->setStyleSheet(QString("QPushButton {border-image: url(:/images/photos/toolbar/ic_add.png);}"
                                   "QPushButton:pressed {border-image: url(:/images/photos/toolbar/ic_add_press.png);}"));
    btnGroup->addButton(btnPlus, 1);
    horLayout->addWidget(btnPlus);

    QPushButton *btnMins = new QPushButton(this);
    btnMins->setStyleSheet(QString("QPushButton {border-image: url(:/images/photos/toolbar/ic_mins.png);}"
                                   "QPushButton:pressed {border-image: url(:/images/photos/toolbar/ic_mins_press.png);}"));
    btnGroup->addButton(btnMins, 2);
    horLayout->addWidget(btnMins);

    m_btnPlay = new QPushButton(this);
    connect(m_btnPlay, SIGNAL(clicked(bool)), this, SIGNAL(signalPlay(bool)));
    m_btnPlay->setCheckable(true);
    m_btnPlay->setChecked(false);
    m_btnPlay->setStyleSheet(QString("QPushButton {border-image: url(:/images/photos/toolbar/play.png);}"
                                   "QPushButton:checked {border-image: url(:/images/photos/toolbar/pause.png);}"));
    horLayout->addWidget(m_btnPlay);

    QPushButton *btnLeftRotate = new QPushButton(this);
    btnLeftRotate->setStyleSheet(QString("QPushButton {border-image: url(:/images/photos/toolbar/left_rotate.png);}"
                                         "QPushButton:pressed {border-image: url(:/images/photos/toolbar/left_rotate_pressed.png);}"));
    btnGroup->addButton(btnLeftRotate, 4);
    horLayout->addWidget(btnLeftRotate);

    QPushButton *btnRightRotate = new QPushButton(this);
    btnRightRotate->setStyleSheet(QString("QPushButton {border-image: url(:/images/photos/toolbar/right_rotate.png);}"
                                          "QPushButton:pressed {border-image: url(:/images/photos/toolbar/right_rotate_pressed.png);}"));
    btnGroup->addButton(btnRightRotate, 5);
    horLayout->addWidget(btnRightRotate);
    horLayout->addStretch();

    this->setStyleSheet(QString("QPushButton {min-width: 30px; min-height: 30px;}"));
    connect(btnGroup, SIGNAL(buttonClicked(int)), this, SIGNAL(buttonClicked(int)));
}

void BottomBarWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), QColor("#b2ededed"));
    painter.setPen("#cacaca");
    painter.drawLine(this->rect().topLeft(), this->rect().topRight());
}

void BottomBarWidget::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
}

//////////////////////////////////////////////////////////////////////////////////////
ImageViewer::ImageViewer(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_DeleteOnClose);

    m_bPressed = false;
    m_nScaleFactor = 100;
    m_nRotate = 0;
    m_bToolBtnShow = false;

    m_btnPrev = new QPushButton(this);
    connect(m_btnPrev, SIGNAL(clicked(bool)), this, SLOT(SltShowPrevImage()));
    m_btnPrev->setVisible(false);
    m_btnPrev->setStyleSheet(QString("QPushButton {border-image: url(:/images/photos/toolbar/ic_left.png);}"
                                     "QPushButton:pressed {border-image: url(:/images/photos/toolbar/ic_left_pressed.png);}"
                                     "QPushButton:!enabled {border-image: url(:/images/photos/toolbar/ic_left_pressed.png);}"));

    m_btnNext = new QPushButton(this);
    connect(m_btnNext, SIGNAL(clicked(bool)), this, SLOT(SltShowNextImage()));
    m_btnNext->setVisible(false);
    m_btnNext->setStyleSheet(QString("QPushButton {border-image: url(:/images/photos/toolbar/ic_right.png);}"
                                     "QPushButton:pressed {border-image: url(:/images/photos/toolbar/ic_right_pressed.png);}"
                                     "QPushButton:!enabled {border-image: url(:/images/photos/toolbar/ic_right_pressed.png);}"));


    m_titleBar = new TitleBarWidget(this);
    connect(m_titleBar, SIGNAL(signalBack()), this, SLOT(close()));

    m_bottomBar = new BottomBarWidget(this);
    connect(m_bottomBar, SIGNAL(buttonClicked(int)), this, SLOT(SltToolButtonClicked(int)));
    connect(m_bottomBar,SIGNAL(signalPlay(bool)), this, SLOT(SltAutoPlay(bool)));

    m_opacity = 1.0;
    m_timer = new QTimer(this);
    m_timer->setInterval(50);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(SltSetOpacity()));

    m_timerSlide = new QTimer(this);
    m_timerSlide->setInterval(3000);
    connect(m_timerSlide, SIGNAL(timeout()), this, SLOT(SltPlaySlide()));
}

ImageViewer::~ImageViewer()
{

}

void ImageViewer::SetPixmap(int id, QMap<int, QtPageListWidgetItem*> pixmaps)
{
    m_listPixmaps.clear();
    m_listPixmaps = pixmaps;
    SetCurrentIndex(id);
    this->show();
}

void ImageViewer::SetCurrentIndex(int index)
{
    m_nIndex = index;
    m_btnPrev->setEnabled(m_nIndex > 0);
    m_btnNext->setEnabled(m_nIndex < (m_listPixmaps.size() - 1));

    QString strFile = m_listPixmaps.value(m_nIndex)->m_strText;
    QFileInfo fileInfo(strFile);
    m_titleBar->SetText(fileInfo.fileName());

    m_pixmap = QPixmap(strFile);
    m_pixmapTemp = QPixmap(strFile);

    if (m_pixmap.width() > this->width() || m_pixmap.height() > this->height()) {
        if (m_pixmap.width() > this->width()) {
            m_nScaleFactor = this->width() * 100.0 / m_pixmap.width();
        } else {
            m_nScaleFactor = this->height() * 100.0 / m_pixmap.height();
        }
        m_pixmapTemp = m_pixmap.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    } else {
        m_nScaleFactor = 100;
    }

    int nX = this->rect().center().x() - m_pixmapTemp.width() / 2;
    int nY = this->rect().center().y() - m_pixmapTemp.height() / 2;
    m_rectPixmap = QRect(nX, nY, m_pixmapTemp.width(), m_pixmapTemp.height());

    this->update();
}


void ImageViewer::SltToolButtonClicked(int index)
{
    if (1 == index) {
        m_nScaleFactor += 10;
        if (m_nScaleFactor >= 120) {
            m_nScaleFactor = 120;
        }
        scalePixmap();
    } else if (2 == index) {
        m_nScaleFactor -= 10;
        if (m_rectPixmap.width() < (this->width() / 2)) {
            m_nScaleFactor += 10;
        }
        scalePixmap();
    } else if (4 == index) {
        m_nRotate -= 90;
        if (m_nRotate <= -360) {
            m_nRotate = 0;
        }
    } else if (5 == index) {
        m_nRotate += 90;
        if (m_nRotate >= 360) {
            m_nRotate = 0;
        }
    }

    this->update();
}

void ImageViewer::setToolBarVisible(bool bOk)
{
    m_btnPrev->setVisible(bOk);
    m_btnNext->setVisible(bOk);
    m_bToolBtnShow = bOk;
    this->update();

    if (bOk)  {
        m_titleBar->SetAnimation(QPoint(0, -50), QPoint(0, 0));
        m_bottomBar->SetAnimation(QPoint(0, this->height()), QPoint(0, this->height() - 50));
    } else {
        m_titleBar->SetAnimation(QPoint(0, 0), QPoint(0, -50));
        m_bottomBar->SetAnimation(QPoint(0, this->height() - 50), QPoint(0, this->height()));
    }
}

void ImageViewer::scalePixmap()
{
    double factor = m_nScaleFactor * 1.0 / 100;
    m_pixmapTemp = m_pixmap.scaled(m_pixmap.width() * factor, m_pixmap.height() * factor, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    int nX = this->rect().center().x() - m_pixmapTemp.width() / 2;
    int nY = this->rect().center().y() - m_pixmapTemp.height() / 2;
    m_rectPixmap = QRect(nX, nY, m_pixmapTemp.width(), m_pixmapTemp.height());
}

void ImageViewer::SltSetOpacity()
{
    m_opacity += 0.2;

    if (m_opacity > 1.0) {
        m_opacity = 1.0;
        m_timer->stop();
    }

    this->update();
}

void ImageViewer::SltShowPrevImage()
{
    if (m_listPixmaps.contains(m_nIndex - 1)) {
        m_opacity = 0;
        m_nRotate = 0.0;
        m_timer->start();
        SetCurrentIndex(m_nIndex - 1);
    }
}

void ImageViewer::SltShowNextImage()
{
    if (m_listPixmaps.contains(m_nIndex + 1)) {
        m_opacity = 0;
        m_nRotate = 0.0;
        m_timer->start();
        SetCurrentIndex(m_nIndex + 1);
    }
}

void ImageViewer::SltAutoPlay(bool bOk)
{
    if (!bOk) {
        m_timerSlide->stop();
    } else {
        m_timerSlide->start();
        setToolBarVisible(false);
    }
}

void ImageViewer::SltPlaySlide()
{
    int index = m_nIndex + 1;
    if (m_listPixmaps.contains(index)) {
        SltShowNextImage();
    } else {
        m_nIndex = -1;
        SltPlaySlide();
    }
}

void ImageViewer::resizeEvent(QResizeEvent *e)
{
    m_titleBar->setGeometry(0, -50, this->width(), 50);
    m_bottomBar->setGeometry(0, this->height(), this->width(), 50);
    m_btnPrev->setGeometry(10, (this->height() - BTN_SIZE) / 2, BTN_SIZE, BTN_SIZE);
    m_btnNext->setGeometry(this->width() - 10 - BTN_SIZE, (this->height() - BTN_SIZE) / 2, BTN_SIZE, BTN_SIZE);
    QWidget::resizeEvent(e);
}

void ImageViewer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(this->rect(), m_bToolBtnShow ? QColor("#f3f3f3") : QColor("#000000"));

    painter.save();
    painter.setOpacity(m_opacity);
    painter.translate(m_rectPixmap.left() + m_pixmapTemp.width() / 2, m_rectPixmap.top() + m_pixmapTemp.height() / 2);
    painter.rotate(m_nRotate);
    painter.translate(-m_rectPixmap.left() - m_pixmapTemp.width() / 2, -m_rectPixmap.top() - m_pixmapTemp.height() / 2);
    painter.drawPixmap(m_rectPixmap, m_pixmapTemp);
    painter.restore();
}

void ImageViewer::mousePressEvent(QMouseEvent *e)
{
    m_bPressed = true;
    m_startPos = e->pos();
}

void ImageViewer::mouseReleaseEvent(QMouseEvent *e)
{
    if (m_rectPixmap.width() <= this->width() && m_rectPixmap.height() <= this->height())
    {
        setToolBarVisible(m_titleBar->y() < 0);
    }

    m_bPressed = false;
    m_startPos = e->pos();
}

void ImageViewer::mouseMoveEvent(QMouseEvent *e)
{
    if (m_bPressed) {
        QPoint pos =  e->pos() - m_startPos;
        m_rectPixmap = QRect(m_rectPixmap.left() + pos.x(), m_rectPixmap.top() + pos.y(), m_rectPixmap.width(), m_rectPixmap.height());
        this->update();
        m_startPos = e->pos();
    }
}



