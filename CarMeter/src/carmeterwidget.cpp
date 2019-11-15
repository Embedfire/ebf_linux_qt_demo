/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : CarMeterWidget.cpp --- CarMeterWidget
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/7
*******************************************************************/
#include "carmeterwidget.h"
#include "skin.h"
#include <QPainter>
#include <QMatrix>
#include <QMouseEvent>
#include <QDebug>

static QPointF s_leftPoint[] = {
    QPointF(56, 351), QPointF(55, 327), QPointF(55, 303), QPointF(56, 280), QPointF(57, 257), QPointF(61, 233),
    QPointF(67, 210), QPointF(75, 187), QPointF(85, 163), QPointF(100, 140), QPointF(115, 116)
};

static QPointF s_rightPoint[] = {
    QPointF(658, 351), QPointF(671, 327), QPointF(678, 303), QPointF(683, 280), QPointF(684, 257), QPointF(682, 233),
    QPointF(678, 210), QPointF(671, 187), QPointF(662, 163), QPointF(648, 140), QPointF(630, 116)
};

CarMeterWidget::CarMeterWidget(QWidget *parent) : QtAnimationWidget(parent)
{
//    this->setFixedSize(Skin::m_nScreenWidth, Skin::m_nScreenHeight);
    InitData();

    m_timer = new QTimer(this);
    m_timer->setInterval(10);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(SltChangValue()));

    m_timerMark = new QTimer(this);
    m_timerMark->setInterval(500);
    connect(m_timerMark, SIGNAL(timeout()), this, SLOT(SltChangeMarkState()));
    m_timerMark->start();
}

CarMeterWidget::~CarMeterWidget()
{
    m_markSgin.clear();
}

void CarMeterWidget::SltChangValue()
{
    if (bDown) m_nSpeed -= 1;
    else m_nSpeed += 1;

    if (m_nSpeed <= 0) {
        bDown = false;
    } else if (m_nSpeed >= 180) {
        bDown = true;
    }

    this->update();
}

void CarMeterWidget::SltChangeMarkState()
{
    bool bOk = false;
    foreach (MarkIcon *icon, m_markSgin) {
        if (icon->m_bFickerAble && icon->m_bFicker) {
            icon->m_bChecked = !icon->m_bChecked;
            bOk = true;
        }
    }

    if (bOk) this->update();
}

void CarMeterWidget::InitData()
{
    m_nSpeed = 0;
    m_nLeftPower = 2;
    m_nRightPower = 4;

    bDown = true;

    m_bHomePressed = false;
    m_rectHome = QRect(739, 4, 54, 54);
    m_rectLeftValue = QRect(20, 115, 160, 260);
    m_rectRightValue = QRect(630, 115, 160, 260);

    m_markSgin.insert(1, new MarkIcon(1, QRect(100, 9, 40, 40), QStringList() << ":/images/car/mark/turn_left_on.png" << ":/images/car/mark/turn_left_off.png", true));
    m_markSgin.insert(2, new MarkIcon(2, QRect(180, 9, 60, 40), QStringList() << ":/images/car/mark/headlamp_on.png" << ":/images/car/mark/highbeam.png" << ":/images/car/mark/headamp_off.png"));
    m_markSgin.insert(3, new MarkIcon(3, QRect(260, 9, 45, 40), QStringList() << ":/images/car/mark/fog_lamp_on.png" << ":/images/car/mark/fog_lamp_off.png"));
    m_markSgin.insert(4, new MarkIcon(4, QRect(379, 9, 40, 40), QStringList() << ":/images/car/mark/door_open.png" << ":/images/car/mark/car.png"));
    m_markSgin.insert(5, new MarkIcon(5, QRect(497, 9, 49, 40), QStringList() << ":/images/car/mark/parking_on.png" << ":/images/car/mark/parking_off.png"));
    m_markSgin.insert(6, new MarkIcon(6, QRect(577, 9, 40, 40), QStringList() << ":/images/car/mark/safety_belt_on.png" << ":/images/car/mark/safety_belt_off.png"));
    m_markSgin.insert(7, new MarkIcon(7, QRect(660, 9, 40, 40), QStringList() << ":/images/car/mark/turn_right_on.png" << ":/images/car/mark/turn_right_off.png", true));

    m_markSgin.insert(8, new MarkIcon(8, QRect(93, 431, 54, 40), QStringList() << ":/images/car/mark/abs_on.png" << ":/images/car/mark/abs_off.png"));
    m_markSgin.insert(9, new MarkIcon(9, QRect(178, 431, 40, 40), QStringList() << ":/images/car/mark/emergency_lamp_on.png" << ":/images/car/mark/emergency_lamp_off.png"));
    m_markSgin.insert(10, new MarkIcon(10, QRect(558, 431, 40, 40),QStringList() << ":/images/car/mark/engine_on.png" << ":/images/car/mark/engine_off.png" << ":/images/car/mark/engine_error.png"));
    m_markSgin.insert(11, new MarkIcon(11, QRect(643, 431, 56, 40), QStringList() << ":/images/car/mark/enginoil_on.png" << ":/images/car/mark/enginoil_off.png"));
}


void CarMeterWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
    painter.drawPixmap(this->rect(), QPixmap(":/images/car/ic_background.png"));

    drawRects(&painter);
    drawMarIcons(&painter);
    drawValue(&painter);
}

void CarMeterWidget::drawRects(QPainter *painter)
{
    painter->save();
    // 设置放大倍数
    painter->scale(m_scaleX, m_scaleY);

    if (m_bHomePressed) painter->drawPixmap(m_rectHome, QPixmap(":/images/car/menu_icon_pressed.png"));
    for (int i = 0; i < m_nLeftPower; i++) {
        painter->drawPixmap(s_leftPoint[i], QPixmap(QString(":/images/car/left/left_value_%1.png").arg(i)));
    }
    for (int i = 0; i < m_nRightPower; i++) {
        painter->drawPixmap(s_rightPoint[i], QPixmap(QString(":/images/car/right/right_value_%1.png").arg(i)));
    }
    painter->restore();
}

void CarMeterWidget::drawMarIcons(QPainter *painter)
{
    painter->save();
    // 设置放大倍数
    painter->scale(m_scaleX, m_scaleY);

    foreach (MarkIcon *icon, m_markSgin) {
        painter->drawPixmap(icon->m_rect.topLeft(), icon->pixmap());
    }
    painter->restore();
}

void CarMeterWidget::drawValue(QPainter *painter)
{
    painter->save();
    // 设置放大倍数
    painter->scale(m_scaleX, m_scaleY);

    QPixmap pixmap(":/images/car/point_hand.png");
    painter->translate(m_nBaseWidth / 2, m_nBaseHeight / 2);

    int nWidth = 306;
    QRectF rectangle(-nWidth / 2 + 1.2, -nWidth / 2 - 5.6, nWidth, nWidth);
    qreal rotate = (m_nSpeed * 1.0) / 180 * 270;
    QLinearGradient linear;
    linear.setStart(-nWidth / 2, -nWidth / 2);
    linear.setFinalStop(nWidth / 2, nWidth / 2);
    linear.setColorAt(0, QColor(0, 255, 255, 0));
    linear.setColorAt(1, QColor(0, 255, 255, 255));
    painter->setPen(Qt::NoPen);
    painter->setBrush(linear);
    painter->drawPie(rectangle, 225 * 16, -(rotate + (m_nSpeed * 1.0) / 180 * 1) * 16);
    painter->rotate(-135);
    painter->rotate(rotate);
    painter->drawPixmap(-pixmap.width() / 2, -pixmap.height() + 17, pixmap);
    painter->restore();

    painter->save();
    // 设置放大倍数
    painter->scale(m_scaleX, m_scaleY);

    painter->setPen(QColor("#ffffff"));
    //  绘制速度
    QFont font(Skin::m_strAppFontBold);
    font.setBold(true);
    font.setPixelSize(66);
    painter->setFont(font);
    painter->drawText(321, 333, 120, 92, Qt::AlignCenter, QString::number(m_nSpeed));

    font.setPixelSize(29);
    painter->setFont(font);
    painter->drawText(251, 422, 285, 49, Qt::AlignCenter, tr("总里程：546546 km"));
    painter->restore();
}

void CarMeterWidget::mousePressEvent(QMouseEvent *e)
{
    foreach (MarkIcon *icon, m_markSgin) {
        QRect rect;
        ScaleRect(rect, icon->m_rect);

        if (rect.contains(e->pos())) {
            if (icon->m_bFickerAble) {
                icon->m_bFicker = !icon->m_bFicker;
                if (!icon->m_bFicker) icon->m_bChecked = true;
            } else {
                icon->ChangeState();
            }

            this->update();
            break;
        }
    }

    QRect rect;
    ScaleRect(rect, m_rectHome);
    if (rect.contains(e->pos())) {
        m_bHomePressed = true;
        this->update();
    }
    else {
        m_bPressed = true;
        m_startPos = e->pos();
    }

    QWidget::mousePressEvent(e);
}

void CarMeterWidget::mouseReleaseEvent(QMouseEvent *e)
{
    m_bPressed = false;
    if (m_bHomePressed) {
        m_bHomePressed = false;
        this->update();
        emit signalBackHome();
    }
    QWidget::mouseReleaseEvent(e);
}

void CarMeterWidget::mouseMoveEvent(QMouseEvent *e)
{
    QRect rect;
    ScaleRect(rect, m_rectLeftValue);
    if (m_bPressed && rect.contains(e->pos())) {
        int nValue = rect.bottom() - e->y();
        m_nLeftPower = (nValue * 1.0) / rect.height() * 11;
        if (e->y() < 120 * m_scaleY) m_nLeftPower = 11;
        this->update();
    }

    ScaleRect(rect, m_rectRightValue);
    if (rect.contains(e->pos())) {
        int nValue = rect.bottom() - e->y();
        m_nRightPower = (nValue * 1.0) / rect.height() * 11;
        if (e->y() < 120 * m_scaleY) m_nRightPower = 11;
        this->update();
    }
}

void CarMeterWidget::showEvent(QShowEvent *e)
{
    m_timer->start();
    QWidget::showEvent(e);
}

void CarMeterWidget::hideEvent(QHideEvent *e)
{
    m_timer->stop();
    QWidget::hideEvent(e);
}
