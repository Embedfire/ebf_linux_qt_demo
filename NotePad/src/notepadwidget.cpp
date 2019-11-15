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
    this->setUndoRedoEnabled(false);
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
    m_widgetTitle->SetScalSize(Skin::m_nScreenWidth, 48);
    m_widgetTitle->SetBackground(Qt::transparent);
    m_widgetTitle->setFont(QFont(Skin::m_strAppFontBold));
    m_widgetTitle->SetTitle(tr("记事本"), "#333333", 20);
    m_widgetTitle->SetBtnHomePixmap(QPixmap(":/images/notepad/menu_icon.png"), QPixmap(":/images/notepad/menu_icon_pressed.png"));

    QtPixmapButton *btnMenu = new QtPixmapButton(1, QRect(10, 2, 40, 40), QPixmap(":/images/notepad/ic_file.png"), QPixmap(":/images/notepad/ic_file.png"));
    QtPixmapButton *btnSetting = new QtPixmapButton(2, QRect(60, 2, 40, 40), QPixmap(":/images/notepad/ic_setting.png"), QPixmap(":/images/notepad/ic_setting_Press.png"));
    QMap<int,QtPixmapButton *> btns;
    btns.insert(1, btnMenu);
    btns.insert(2, btnSetting);
    m_widgetTitle->SetToolButtons(btns);
    connect(m_widgetTitle, SIGNAL(signalBtnClicked(int)), this, SLOT(SltToolBtnClicked(int)));

    m_menuFile = new QMenu(this);
    QAction *actionNew = new QAction(tr("新建"), this);
    actionNew->setShortcut(QKeySequence(QKeySequence::New));
    m_menuFile->addAction(actionNew);
    connect(actionNew, SIGNAL(triggered(bool)), this, SLOT(NewDocument()));

    QAction *actionOpen = new QAction(tr("打开"), this);
    actionOpen->setShortcut(QKeySequence(QKeySequence::Open));
    connect(actionOpen, SIGNAL(triggered(bool)), this, SLOT(ActionOpen()));
    m_menuFile->addAction(actionOpen);

    QAction *actionSave = new QAction(tr("保存"), this);
    actionSave->setShortcut(QKeySequence(QKeySequence::Save));
    connect(actionSave, SIGNAL(triggered(bool)), this, SLOT(SaveDocument()));
    m_menuFile->addAction(actionSave);

    QAction *actionExit = new QAction(tr("退出"), this);
    actionExit->setShortcut(QKeySequence(QKeySequence::Close));
    m_menuFile->addAction(actionExit);
    connect(actionExit, SIGNAL(triggered(bool)), this, SIGNAL(signalBackHome()));
//    connect(m_menuFile, SIGNAL(triggered(QAction*)), this, SLOT(SltActionTriggered(QAction*)));

    //////////////////////////////////////////////////////////////
    m_textEdit = new TextEdit(this);
    m_textEdit->setFont(QFont(Skin::m_strAppFontNormal, 14));
    m_textEdit->setStyleSheet(QString("QTextEdit {border: 1px solid #c5c5c5; border-top: none;"
                                      "background-color: #ffffff;}"));
    connect(m_textEdit, SIGNAL(signalClicked()), this, SLOT(SltClosePalette()));

    QVBoxLayout *verLayout = new QVBoxLayout(this);
    verLayout->setContentsMargins(0, 0, 0, 0);
    verLayout->setSpacing(0);
    verLayout->addWidget(m_widgetTitle, 1);
    verLayout->addWidget(m_textEdit, 9);

    m_paletteWidget = new QtPaletteWidget(this);
    connect(m_paletteWidget, SIGNAL(signalFontChanged(int)), this, SLOT(SltFontSizeChanged(int)));
    connect(m_paletteWidget, SIGNAL(signalColorChanged(QColor)), this, SLOT(SltColorChanged(QColor)));
}

void NotePadWidget::ActionOpen()
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
        m_paletteWidget->setGeometry(this->width(), m_widgetTitle->geometry().bottom(), 436 * m_scaleX, 432 * m_scaleY);
    }
    emit signalBackHome();
}

void NotePadWidget::SltActionTriggered(QAction *action)
{
    if (action->text() == "新建") {
        NewDocument();
    } else if (action->text() == "打开") {
        ActionOpen();
    } else if (action->text() == "保存") {
        SaveDocument();
    } else if (action->text() == "退出") {
        emit signalBackHome();
    }
}

void NotePadWidget::SltSetPaletteConfig()
{
    if (m_paletteWidget->pos().x() > (this->width() / 2)) {
        m_paletteWidget->StartAnimation(QPoint(this->width(), m_widgetTitle->rect().bottom()),
                                        QPoint(this->width() - m_paletteWidget->width(), m_widgetTitle->rect().bottom()), 200, true);
    } else {
        m_paletteWidget->StartAnimation(QPoint(this->width() - m_paletteWidget->width(), m_widgetTitle->rect().bottom()),
                                        QPoint(this->width(), m_widgetTitle->rect().bottom()), 200, true);
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
        m_paletteWidget->StartAnimation(QPoint(this->width() - m_paletteWidget->width(), m_widgetTitle->rect().bottom()),
                                        QPoint(this->width(), m_widgetTitle->rect().bottom()), 200, true);
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

void NotePadWidget::SltToolBtnClicked(int index)
{
    if (0 == index) {
        emit signalBackHome();
    } else if (1 == index) {
        QPoint pos = m_widgetTitle->geometry().bottomLeft();
        pos = this->mapToGlobal(pos);
        m_menuFile->exec(QPoint(pos.x() + 2, pos.y() + 2));
    } else if (2 == index) {
        SltSetPaletteConfig();
    }

    m_textEdit->clearFocus();
}

void NotePadWidget::resizeEvent(QResizeEvent *e)
{
    m_scaleX = (this->width() * 1.0) / m_nBaseWidth;
    m_scaleY = (this->height() * 1.0) / m_nBaseHeight;

    m_paletteWidget->setGeometry(this->width(), m_widgetTitle->rect().bottom(), 436 * m_scaleX, 432 * m_scaleY);
    m_fileDialog->setFixedSize(this->size());
    QWidget::resizeEvent(e);
}

