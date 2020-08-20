#include "gamewidget.h"

#include <QPainter>
#include <QImage>
#include <QDebug>

#ifdef Q_OS_WIN32
NesGamePannel::NesGamePannel(QWidget *parent) : QOpenGLWidget(parent) {
#else
NesGamePannel::NesGamePannel(QWidget *parent) : QWidget(parent) {
#endif

    m_nKeyMap = 0;
    m_bInit = false;

    memset(m_nImageData, 0x00, sizeof(uint32_t) * 256 * 240);
    m_imageBuff = new QImage((uchar*)m_nImageData, 256, 240, QImage::Format_ARGB32);
    m_imageDisplay = *m_imageBuff;

    m_timer = new QTimer(this);
    m_timer->setInterval(1);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(SltStart()));
}

NesGamePannel::~NesGamePannel()
{
    m_timer->stop();
    delete m_timer;
    m_timer = NULL;
}

void NesGamePannel::LoadGame(const QString &fileName)
{
    if (m_timer->isActive()) m_timer->stop();

    m_bInit = load_file(fileName.toStdString().c_str());
    if (m_bInit) {
        fce_init();
        setFlag(A);
        m_timer->start();
    }

    this->update();
}

void NesGamePannel::Stop()
{
    m_nKeyMap = 0;
    m_imageBuff->loadFromData((uchar*)m_nImageData, 256 * 240);
    m_imageDisplay = QImage();
    this->update();
}

void NesGamePannel::clearBackground(int c)
{
    pal rgb = pale[c];
    m_imageBuff->fill(QColor(rgb.r, rgb.g, rgb.b, 255));
}

void NesGamePannel::addPoint(int x, int y, int c)
{
    if( x <0 || x >= 256 || y < 0 || y >= 240) return;
    pal rgb = pale[c];
    m_imageBuff->setPixelColor(x,y, QColor(rgb.r,rgb.g,rgb.b));
}

void NesGamePannel::display()
{
    // 缩放image
    m_imageDisplay = m_imageBuff->scaled(this->size());
    update();
}

void NesGamePannel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if (m_bInit) {
        painter.drawImage(0, 0, m_imageDisplay);
    }
    else {
        painter.fillRect(this->rect(), Qt::black);
        QFont font = painter.font();
        font.setPixelSize(32);
        painter.setFont(font);
        painter.setPen(Qt::white);
        painter.drawText(this->rect(), Qt::AlignCenter, QString("Loading Game..."));

        // 绘制备注信息
        font.setPixelSize(18);
        painter.setFont(font);
        painter.setPen(QColor("#ffc700"));
        QRect rect(0, this->height() / 2, this->width(), this->height() / 2);
        QString strMask = "A,S,W,D 控制方向移动，\nI/开始(B), J/跳(C), K/开火(D)";
        QTextOption option;
        option.setAlignment(Qt::AlignCenter);
        option.setWrapMode(QTextOption::WordWrap);
        painter.drawText(rect, strMask, option);
    }
}

void NesGamePannel::setFlag(Flags flag)
{
    m_nKeyMap |= flag;
}

void NesGamePannel::removeFlag(Flags flag)
{
    m_nKeyMap &= ~flag;
}

bool NesGamePannel::testFlag(Flags flag)
{
    return m_nKeyMap & flag;
}

void NesGamePannel::SltStart()
{
    fce_run();
}
