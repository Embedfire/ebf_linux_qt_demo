/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : beepwidget.cpp ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/28
*******************************************************************/
#include "beepwidget.h"
#include "skin.h"

#include <QDir>
#include <QFile>
#include <QBoxLayout>
#include <QPainter>
#include <QMouseEvent>
#include <QProcess>
#include <QDebug>

BeepWidget::BeepWidget(QWidget *parent) : QtAnimationWidget(parent),m_nIndex(3)
{
    m_btnHome = QtPixmapButton(QPixmap(":/images/beep/menu_icon.png"), QPixmap(":/images/beep/menu_icon_pressed.png"));
    m_pixmapHandle = QPixmap(":/images/beep/ic_slider.png");
    m_pixmapHorn = QPixmap(":/images/beep/ic_horn.png");

    m_bLeftSwitch = false;
    m_bRightSwitch = false;
    m_nSwitchIndex = 0;
    m_bPwmBeep = false;

    m_timer = new QTimer(this);
    m_timer->setInterval(500);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(SltLongPressed()));

    m_animationMove = new QPropertyAnimation(this, "switchRect");
    m_animationMove->setEasingCurve(QEasingCurve::OutCirc);
    m_animationMove->setDuration(300);

    // 初始化控件位置
    InitDataRect();

    // 检查设备
    CheckDevice();
}

BeepWidget::~BeepWidget()
{
    setBeepState(0);
}

QRect BeepWidget::switchRect() const
{
    return m_rectLeftSwitch;
}

void BeepWidget::setSwitchRect(const QRect &value)
{
    if (0 == m_nSwitchIndex) {
        m_rectLeftSwitch = value;
    } else if (1 == m_nSwitchIndex){
        m_rectRightSwitch = value;
    }
    this->update();
}

void BeepWidget::InitDataRect()
{
    m_btnHome.setRect(QRect(736, 3, 54, 54));
    m_rectHorn = QRect(228, 82, 344, 344);
    m_rectLeftSwitch = QRect(80, m_bLeftSwitch ? 263 : 181, 65, 65);
    m_rectRightSwitch = QRect(657, m_bRightSwitch ? 263 : 181, 65, 65);
}

void BeepWidget::CheckDevice()
{
#ifdef __arm__
    QString strDevice = "/sys/class/gpio/gpio19";
    QDir dir(strDevice);
    if (!dir.exists()) {
        system("echo 19 > /sys/class/gpio/export");
        system("echo 'out' > /sys/class/gpio/gpio19/direction");
        qDebug() << "check beep gpio" << dir.exists();
    }
#endif
}

void BeepWidget::setBeepState(int on)
{
#ifdef __arm__
    QString strFile = "/sys/class/gpio/gpio19/value";
    QFile file(strFile);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        qDebug() << "/sys/class/gpio/gpio19 export failed!";
        return;
    }

    file.write(1 == on ? "1" : "0");
    file.close();
#else
    qDebug() << "state" << on;
#endif
}

void BeepWidget::StopTimer()
{
    if (m_timer->isActive()) {
        m_timer->stop();
    }

    m_nIndex = 3;
    setBeepState(0);
    this->update();
}

void BeepWidget::SltLongPressed()
{
    m_nIndex += 1;
    if (m_nIndex > 3) m_nIndex = 1;
    static bool on = false;
    on = !on;
    this->setBeepState(on ? 1 : 0);
    this->update();
}

void BeepWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // 设置放大倍数
    painter.scale(m_scaleX, m_scaleY);

    // 绘制背景
    painter.drawPixmap(0, 0, QPixmap(":/images/beep/ic_background.png"));

    // 绘制标题栏
    drawTitle(&painter);

    // 绘制左边开关
    drawSwitch(&painter);

    // 绘制音量按钮
    drawHorn(&painter);

    // 绘制右边开关
    drawSwitch(&painter, false);
}

void BeepWidget::drawTitle(QPainter *painter)
{
    painter->save();
    painter->drawPixmap(m_btnHome.rect(), m_btnHome.pixmap());

    QFont font(Skin::m_strAppFontBold);
    font.setPixelSize(32);
    painter->setFont(font);
    painter->setPen(QColor("#333333"));
    painter->drawText(0, 0, Skin::m_nScreenWidth, 60, Qt::AlignCenter, tr("蜂鸣器控制"));
    painter->restore();
}

void BeepWidget::drawSwitch(QPainter *painter, bool left)
{
    painter->save();

    QFont font = painter->font();
    font.setPixelSize(24);
    painter->setFont(font);
    painter->setPen(QColor("#78DF26"));

    if (left) {
        QRect rect(81, 184, 60, 50);
        painter->drawText(rect, Qt::AlignCenter, QString("ON"));
        rect = QRect(81, 275, 60, 40);
        painter->drawText(rect, Qt::AlignCenter, QString("OFF"));
        painter->drawPixmap(m_rectLeftSwitch, m_pixmapHandle);
        painter->setPen(QColor("#000000"));
        painter->drawText(m_rectLeftSwitch, Qt::AlignCenter, tr("滴答"));
    }
    else {
        QRect rect(657, 184, 65, 50);
        painter->drawText(rect, Qt::AlignCenter, QString("ON"));
        rect = QRect(657, 275, 65, 40);
        painter->drawText(rect, Qt::AlignCenter, QString("OFF"));
        painter->drawPixmap(m_rectRightSwitch, m_pixmapHandle);
        painter->setPen(QColor("#000000"));
        painter->drawText(m_rectRightSwitch, Qt::AlignCenter, tr("长鸣"));
    }
    painter->restore();
}

void BeepWidget::drawHorn(QPainter *painter)
{
    painter->save();

    painter->drawPixmap(m_rectHorn.left() + 54, m_rectHorn.top() + 77, m_pixmapHorn);
    for (int i = 0; i < m_nIndex; i++) {
        QPixmap pixmap(QString(":/images/beep/ic_horn_%1.png").arg(i + 1));
        int nY = (m_rectHorn.center().y() - pixmap.height() / 2);
        int nX = m_rectHorn.left() + 174 + i * 13;
        painter->drawPixmap(nX, nY, pixmap);
    }
    painter->restore();
}

void BeepWidget::mousePressEvent(QMouseEvent *e)
{
    QRect rect;
    ScaleRect(rect, m_btnHome.rect());
    if (rect.contains(e->pos())) {
        m_btnHome.setPressed(true);
        this->update();
    }

    ScaleRect(rect, m_rectLeftSwitch);
    if (rect.contains(e->pos())) {
        m_bLeftSwitch = !m_bLeftSwitch;
        m_nSwitchIndex = 0;
        m_animationMove->setStartValue(QRect(80, m_bLeftSwitch ? 181 : 263, 65, 65));
        m_animationMove->setEndValue(QRect(80, m_bLeftSwitch ? 263 : 181, 65, 65));
        m_animationMove->start();
        m_bPwmBeep = m_bLeftSwitch;

        if (m_bLeftSwitch) {
            m_timer->start();
            m_bRightSwitch = false;
            m_rectRightSwitch = QRect(657, m_bRightSwitch ? 263 : 181, 65, 65);
        } else {
            setBeepState(0);
        }
        return;
    }

    ScaleRect(rect, m_rectRightSwitch);
    if (rect.contains(e->pos())) {
        m_bRightSwitch = !m_bRightSwitch;
        m_nSwitchIndex = 1;
        m_animationMove->setStartValue(QRect(657, m_bRightSwitch ? 181 : 263, 65, 65));
        m_animationMove->setEndValue(QRect(657, m_bRightSwitch ? 263 : 181, 65, 65));
        m_animationMove->start();

        if (m_bLeftSwitch) {
            m_bLeftSwitch = false;
            m_rectLeftSwitch = QRect(80, m_bLeftSwitch ? 263 : 181, 65, 65);
        }

        if (m_bRightSwitch) {
            StopTimer();
        }
        // 控制蜂鸣器
        setBeepState(m_bRightSwitch ? 1 : 0);
        return;
    }

    ScaleRect(rect, m_rectHorn);
    if (rect.contains(e->pos())) {
        if (m_bLeftSwitch) {
            m_bLeftSwitch = false;
            m_rectLeftSwitch = QRect(80, m_bLeftSwitch ? 263 : 181, 65, 65);
        }

        if (m_bRightSwitch) {
            m_bRightSwitch = false;
            m_rectRightSwitch = QRect(657, m_bRightSwitch ? 263 : 181, 65, 65);
        }

        m_timer->start();
        setBeepState(1);
    }
}

void BeepWidget::mouseReleaseEvent(QMouseEvent *e)
{
    QRect rect;
    ScaleRect(rect, m_btnHome.rect());
    if (m_btnHome.isPressed()) {
        m_btnHome.setPressed(false);
        if (rect.contains(e->pos())) {
            emit signalBackHome();
        }
        this->update();
    }

    // 处理定时器
    if (!m_bPwmBeep && m_timer->isActive()) {
        StopTimer();
    }
}
