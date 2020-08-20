#include "browserwindow.h"
#include "skin.h"

#include <QAction>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

BrowserWindow::BrowserWindow(QWidget *parent) : QtAnimationWidget(parent)
{
    this->setFixedSize(800, 480);
    this->SetBackground(QPixmap(":/images/browser/background.png"));
    InitWidget();
}

BrowserWindow::~BrowserWindow()
{
}

void BrowserWindow::InitWidget()
{
    QWidget *widgetTitle = new QWidget(this);
    widgetTitle->setMinimumHeight(60);
    widgetTitle->setStyleSheet("QPushButton{min-width: 38px; min-height: 38px;}");

    QHBoxLayout *horLayoutTitle = new QHBoxLayout(widgetTitle);
    horLayoutTitle->setContentsMargins(10, 10, 10, 10);
    horLayoutTitle->setSpacing(10);

    QPushButton *btnPrev = new QPushButton(widgetTitle);
    btnPrev->setFocusPolicy(Qt::NoFocus);
    horLayoutTitle->addWidget(btnPrev);
    btnPrev->setStyleSheet(QString("QPushButton {border-image: url(:/images/browser/ic_prev.png);}"
                                   "QPushButton:pressed {border-image: url(:/images/browser/ic_prev_pre.png);}"));

    QPushButton *btnHome = new QPushButton(widgetTitle);
    btnHome->setFocusPolicy(Qt::NoFocus);
    horLayoutTitle->addWidget(btnHome);
    btnHome->setStyleSheet(QString("QPushButton {border-image: url(:/images/browser/ic_home.png);}"));

    QPushButton *btnNext = new QPushButton(widgetTitle);
    btnNext->setFocusPolicy(Qt::NoFocus);
    horLayoutTitle->addWidget(btnNext);
    btnNext->setStyleSheet(QString("QPushButton {border-image: url(:/images/browser/ic_next.png);}"
                                   "QPushButton:pressed {border-image: url(:/images/browser/ic_next_pre.png);}"));

    QPushButton *btnRefresh = new QPushButton(widgetTitle);
    btnRefresh->setFocusPolicy(Qt::NoFocus);
    horLayoutTitle->addWidget(btnRefresh);
    btnRefresh->setStyleSheet(QString("QPushButton {border-image: url(:/images/browser/ic_refresh.png);}"));

    QWidget *widgetAddress = new QWidget(this);
    widgetAddress->setObjectName("widgetAddress");
    widgetAddress->setFixedSize(476, 36);
    QHBoxLayout *horLayoutAddr = new QHBoxLayout(widgetAddress);
    horLayoutAddr->setContentsMargins(10, 0, 0, 0);
    horLayoutAddr->setSpacing(0);

    m_lineEditHostAddr = new QLineEdit(this);
    m_lineEditHostAddr->setText("http://www.firebbs.cn");
    horLayoutAddr->addWidget(m_lineEditHostAddr);

    QPushButton *btnGo = new QPushButton(this);
    connect(btnGo, SIGNAL(clicked(bool)), this, SLOT(SltGotoHostAddr()));
    btnGo->setFocusPolicy(Qt::NoFocus);
    btnGo->setFixedSize(36, 36);
    horLayoutAddr->addWidget(btnGo);
    btnGo->setStyleSheet(QString("QPushButton {border-image: url(:/images/browser/ic_go.png);}"));

    horLayoutTitle->addWidget(widgetAddress, 1);
    horLayoutTitle->addStretch();
    widgetAddress->setStyleSheet(QString("#widgetAddress {background-color: #ffffff; "
                                         "border: 1px solid #bfbfbf; border-radius: 18px;}"
                                         "QLineEdit {font-family: '%1'; font: 20px; color: #333333;border:none;}")
                                 .arg(Skin::m_strAppFontNormal));

    QPushButton *btnBackHome = new QPushButton(widgetTitle);
    btnBackHome->setFixedSize(54, 54);
    btnBackHome->setFocusPolicy(Qt::NoFocus);
    horLayoutTitle->addWidget(btnBackHome);
    connect(btnBackHome, SIGNAL(clicked(bool)), this, SIGNAL(signalBackHome()));
    btnBackHome->setStyleSheet(QString("QPushButton {border-image: url(:/images/browser/menu_icon.png);}"
                                       "QPushButton:pressed {border-image: url(:/images/browser/menu_icon_pressed.png);}"));

    m_webView = new QWebEngineView(this);
    QVBoxLayout *verLayout = new QVBoxLayout(this);
    verLayout->setContentsMargins(0, 0, 0, 0);
    verLayout->setSpacing(0);
    verLayout->addWidget(widgetTitle);
    verLayout->addWidget(m_webView);

    connect(btnPrev, SIGNAL(clicked(bool)), m_webView, SLOT(back()));
    connect(btnNext, SIGNAL(clicked(bool)), m_webView, SLOT(forward()));
    connect(btnHome, SIGNAL(clicked(bool)), this, SLOT(SltGoToHome()));
    connect(btnRefresh, SIGNAL(clicked(bool)), m_webView, SLOT(reload()));

    // load html
    SltGoToHome();
}

void BrowserWindow::SltGotoHostAddr()
{
    QUrl url = QUrl::fromUserInput(m_lineEditHostAddr->text());
    m_webView->load(url);
    m_webView->setFocus();
}

void BrowserWindow::SltGoToHome()
{
    m_webView->load(QUrl::fromUserInput("www.firebbs.cn"));
}

