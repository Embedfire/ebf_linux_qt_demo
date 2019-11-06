/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : notepadwidget.cpp ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/8
*******************************************************************/
#include "notepadwidget.h"
#include "skin.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QFile>
#include <QTextCodec>
#include <QTextStream>

#include <QApplication>
#include <QMessageBox>
#include <QFileInfo>
#include <QMouseEvent>

TextEdit::TextEdit(QWidget *parent) : QTextEdit(parent)
{
    m_bPressed = false;
    m_scrollbar = this->verticalScrollBar();
    this->setContextMenuPolicy(Qt::NoContextMenu);
}

void TextEdit::mousePressEvent(QMouseEvent *e)
{
    m_bPressed = true;
    m_startPos = e->pos();
    emit signalClicked();
    QTextEdit::mousePressEvent(e);
}

void TextEdit::mouseReleaseEvent(QMouseEvent *e)
{
    m_bPressed = false;
    m_startPos = e->pos();
    QTextEdit::mouseReleaseEvent(e);
}

void TextEdit::mouseMoveEvent(QMouseEvent *e)
{
    if (m_bPressed) {
        int nOffset = m_startPos.y() - e->pos().y();
        int nValue = m_scrollbar->value();
        nValue += nOffset;
        if (nValue < 0) nValue = 0;
        m_scrollbar->setValue(nValue);
        m_startPos = e->pos();
    }

    QTextEdit::mouseMoveEvent(e);
}

/////////////////////////////////////////////////////////////////////////////////
NotePadWidget::NotePadWidget(QWidget *parent) : QtAnimationWidget(parent)
{
    this->SetBackground(QPixmap(":/images/notepad/ic_background.png"));

    InitWidget();

    m_fileDialog = new QtFileDialog(this);
    m_fileDialog->setRootPath(qApp->applicationDirPath() + "/notepad");
    m_fileDialog->setVisible(false);
    connect(m_fileDialog, SIGNAL(signalBackHome()), this, SLOT(SltFileDialogClose()));
    connect(m_fileDialog, SIGNAL(signalSelected(QString)), this, SLOT(SltFileSelected(QString)));
}

NotePadWidget::~NotePadWidget()
{

}

void NotePadWidget::OpenDocument(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        m_textEdit->setText(tr("打开文件失败"));
        return;
    }

    QTextStream read(&file);
    read.setCodec(QTextCodec::codecForName("GB18030"));
    m_textEdit->setText(read.readAll());
    QFileInfo fileInfo(fileName);
    m_widgetTitle->SetTitle(fileInfo.fileName());
    file.close();
}

void NotePadWidget::SaveDocument(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(this, tr("告警"), tr("保存文件失败！！！"));
        return;
    }

    QTextStream write(&file);
    write.setCodec(QTextCodec::codecForName("GB18030"));
    write << m_textEdit->toPlainText();
    file.close();

    qDebug() << fileName;
}

void NotePadWidget::InitWidget()
{
    m_widgetTitle= new QtWidgetTitleBar(this);
    m_widgetTitle->setFixedHeight(44);
    m_widgetTitle->SetBackground(Qt::transparent);
    m_widgetTitle->setFont(QFont(Skin::m_strAppFontNormal));
    m_widgetTitle->SetTitle("记事本", "#333333", 18);

    QPushButton *btnMenu = new QPushButton(m_widgetTitle);
    btnMenu->setFixedSize(30, 30);
    btnMenu->setStyleSheet(QString("QPushButton {border-image: url(:/images/notepad/ic_file.png);}"
                                   "QPushButton::menu-indicator {width: 0px; height: 0px;}"));

    QMenu *menuFile = new QMenu(this);
    QAction *actionNew = new QAction(tr("新建"), this);
    actionNew->setShortcut(QKeySequence(QKeySequence::New));
    menuFile->addAction(actionNew);

    QAction *actionOpen = new QAction(tr("打开"), this);
    actionOpen->setShortcut(QKeySequence(QKeySequence::Open));
    menuFile->addAction(actionOpen);

    QAction *actionSave = new QAction(tr("保存"), this);
    actionSave->setShortcut(QKeySequence(QKeySequence::Save));
    menuFile->addAction(actionSave);

    QAction *actionExit = new QAction(tr("退出"), this);
    actionExit->setShortcut(QKeySequence(QKeySequence::Close));
    menuFile->addAction(actionExit);
    btnMenu->setMenu(menuFile);
    connect(menuFile, SIGNAL(triggered(QAction*)), this, SLOT(SltActionTriggered(QAction*)));

    //////////////////////////////////////////////////////////////
    QPushButton *btnSetting = new QPushButton(m_widgetTitle);
    btnSetting->setFixedSize(30, 30);
    btnSetting->setStyleSheet(QString("QPushButton {border-image: url(:/images/notepad/ic_setting.png);}"
                                      "QPushButton:pressed {border-image: url(:/images/notepad/ic_setting_Press.png);}"));
    connect(btnSetting, SIGNAL(clicked(bool)), this, SLOT(SltSetPaletteConfig()));

    QPushButton *btnHome = new QPushButton(m_widgetTitle);
    btnHome->setFixedSize(44, 44);
    connect(btnHome, SIGNAL(clicked(bool)), this, SLOT(SltBackHome()));
    btnHome->setStyleSheet(QString("QPushButton {border-image: url(:/images/notepad/menu_icon.png);}"
                                   "QPushButton:pressed {border-image: url(:/images/notepad/menu_icon_pressed.png);}"));

    QHBoxLayout *horLayoutTitle = new QHBoxLayout(m_widgetTitle);
    horLayoutTitle->setContentsMargins(9, 0, 10, 0);
    horLayoutTitle->setSpacing(18);
    horLayoutTitle->addWidget(btnMenu);
    horLayoutTitle->addWidget(btnSetting);
    horLayoutTitle->addStretch();
    horLayoutTitle->addWidget(btnHome);

    m_textEdit = new TextEdit(this);
    m_textEdit->setFont(QFont(Skin::m_strAppFontNormal, 14));
    m_textEdit->setStyleSheet(QString("QTextEdit {border: 1px solid #c5c5c5; border-top: none;"
                                      "background-color: #ffffff;}"));
    connect(m_textEdit, SIGNAL(signalClicked()), this, SLOT(SltClosePalette()));

    QVBoxLayout *verLayout = new QVBoxLayout(this);
    verLayout->setContentsMargins(0, 0, 0, 0);
    verLayout->setSpacing(0);
    verLayout->addWidget(m_widgetTitle);
    verLayout->addWidget(m_textEdit, 1);

    m_paletteWidget = new QtPaletteWidget(this);
    connect(m_paletteWidget, SIGNAL(signalFontChanged(int)), this, SLOT(SltFontSizeChanged(int)));
    connect(m_paletteWidget, SIGNAL(signalColorChanged(QColor)), this, SLOT(SltColorChanged(QColor)));
}

void NotePadWidget::actionOpen()
{
    m_fileDialog->setSaveFileMode(false);
    m_fileDialog->StartAnimation(QPoint(0, this->height()), QPoint(0, 0), 200, true);
}

void NotePadWidget::NewDocument()
{
    m_textEdit->clear();
    m_widgetTitle->SetTitle("untitled.txt");
}

void NotePadWidget::SaveDocument()
{
    if (m_textEdit->toPlainText().isEmpty()) return;

    m_fileDialog->setSaveFileMode(true);
    m_fileDialog->StartAnimation(QPoint(0, this->height()), QPoint(0, 0), 200, true);
}

void NotePadWidget::SltBackHome()
{
    if (m_paletteWidget->pos().x() < this->width()) {
        m_paletteWidget->setGeometry(this->width(), m_widgetTitle->geometry().bottom(), 436, 432);
    }
    emit signalBackHome();
}

void NotePadWidget::SltActionTriggered(QAction *action)
{
    if (action->text() == "新建") {
        NewDocument();
    } else if (action->text() == "打开") {
        actionOpen();
    } else if (action->text() == "保存") {
        SaveDocument();
    } else if (action->text() == "退出") {
        emit signalBackHome();
    }
}

void NotePadWidget::SltSetPaletteConfig()
{
    if (m_paletteWidget->pos().x() > (this->width() / 2)) {
        m_paletteWidget->StartAnimation(QPoint(this->width(), 44), QPoint(this->width() - m_paletteWidget->width(), 44), 200, true);
    } else {
        m_paletteWidget->StartAnimation(QPoint(this->width() - m_paletteWidget->width(), 44), QPoint(this->width(), 44), 200, true);
    }
}

void NotePadWidget::SltFontSizeChanged(int size)
{
    QFont font = m_textEdit->font();
    font.setPixelSize(size);
    m_textEdit->setFont(font);
}

void NotePadWidget::SltColorChanged(const QColor &color)
{
    if (!color.isValid()) return;
    m_textEdit->setStyleSheet(QString("QTextEdit {color: %1;}").arg(color.name()));
}

void NotePadWidget::SltClosePalette()
{
    if (m_paletteWidget->pos().x() < (this->width() / 2)) {
        m_paletteWidget->StartAnimation(QPoint(this->width() - m_paletteWidget->width(), 58), QPoint(this->width(), 58), 200, true);
    }
}

void NotePadWidget::SltFileSelected(const QString &fileName)
{
    if (m_fileDialog->isSaveFileMode()) {
        SaveDocument(fileName);
    }
    else {
        OpenDocument(fileName);
    }

    SltFileDialogClose();
}

void NotePadWidget::SltFileDialogClose()
{
    m_fileDialog->StartAnimation(QPoint(0, 0), QPoint(0, -this->height()), 200, false);
}

void NotePadWidget::resizeEvent(QResizeEvent *e)
{
    m_paletteWidget->setGeometry(this->width(), m_widgetTitle->geometry().bottom(), 436, 432);
    m_fileDialog->setFixedSize(this->size());
    qDebug() << m_fileDialog->size();
    QWidget::resizeEvent(e);
}

