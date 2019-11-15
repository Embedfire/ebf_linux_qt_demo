/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : ebookwidget.cpp ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/8
*******************************************************************/
#include "ebookwidget.h"
#include "skin.h"
#include "qtpixmapbutton.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDir>
#include <QFileInfo>
#include <QTimer>
#include <QApplication>
#include <QFileDialog>
#include <QDebug>

#include <QTextStream>
#include <QTextCodec>
#include <QFile>
#include <QMouseEvent>

TextBrowser::TextBrowser(QWidget *parent) : QTextBrowser(parent)
{
    m_bPressed = false;
    this->setContextMenuPolicy(Qt::NoContextMenu);
    this->setUndoRedoEnabled(false);
    m_scrollbar = this->verticalScrollBar();
}

void TextBrowser::mousePressEvent(QMouseEvent *e)
{
    m_bPressed = true;
    m_startPos = e->pos();
    emit signalClicked();
    QTextBrowser::mousePressEvent(e);
}

void TextBrowser::mouseReleaseEvent(QMouseEvent *e)
{
    m_bPressed = false;
    m_startPos = e->pos();
    QTextBrowser::mouseReleaseEvent(e);
}

void TextBrowser::mouseMoveEvent(QMouseEvent *e)
{
    if (m_bPressed) {
        int nOffset = m_startPos.y() - e->pos().y();
        int nValue = m_scrollbar->value();
        nValue += nOffset;
        if (nValue < 0) nValue = 0;
        m_scrollbar->setValue(nValue);
        m_startPos = e->pos();
    }

//    QTextBrowser::mouseMoveEvent(e);
}

EBookWidget::EBookWidget(QWidget *parent) : QtAnimationWidget(parent)
{
    this->SetBackground(QPixmap(":/images/ebook/ic_background.png"));

    m_strDirPath = qApp->applicationDirPath() + "/ebook/";
    InitWidget();

    m_fileDialog = new QtFileDialog(this);
    m_fileDialog->setRootPath(m_strDirPath);
    m_fileDialog->setVisible(false);
    connect(m_fileDialog, SIGNAL(signalBackHome()), this, SLOT(SltFileDialogClose()));
    connect(m_fileDialog, SIGNAL(signalSelected(QString)), this, SLOT(SltFileSelected(QString)));

    QTimer::singleShot(500, this, SLOT(SltLoadEbooks()));
}

EBookWidget::~EBookWidget()
{

}

void EBookWidget::InitWidget()
{
    m_widgetTitle= new QtWidgetTitleBar(this);
    m_widgetTitle->SetScalSize(Skin::m_nScreenWidth, 60);
    m_widgetTitle->SetBackground(QColor("#f0f0f0"));
    m_widgetTitle->SetBtnHomePixmap(QPixmap(":/images/ebook/menu_icon.png"), QPixmap(":/images/ebook/menu_icon_pressed.png"));
    m_widgetTitle->setFont(QFont(Skin::m_strAppFontBold));
    m_widgetTitle->SetTitle(tr("电子书"), "#333333", 22);
    connect(m_widgetTitle, SIGNAL(signalBtnClicked(int)), this, SLOT(SltToolBtnClicked(int)));

    m_btnBack = new QtPixmapButton(BtnBack, QRect(10, 10, 40, 40), QPixmap(":/images/ebook/ic_back.png"), QPixmap(":/images/ebook/ic_back.png"));
    m_btnBack->setVisible(false);

    m_btnAdd = new QtPixmapButton(BtnAdd, QRect(10, 10, 40, 40), QPixmap(":/images/ebook/ic_add.png"), QPixmap(":/images/ebook/ic_add_pressed.png"));
    m_btnSetting = new QtPixmapButton(BtnSetting, QRect(750, 10, 40, 40), QPixmap(":/images/ebook/ic_setting.png"), QPixmap(":/images/ebook/ic_setting_Press.png"));
    m_btnSetting->setVisible(false);

    QMap<int,QtPixmapButton*> btngroup;
    btngroup.insert(BtnBack, m_btnBack);
    btngroup.insert(BtnAdd, m_btnAdd);
    btngroup.insert(BtnSetting, m_btnSetting);
    m_widgetTitle->SetToolButtons(btngroup);

    //////////////////////////////////////////////////////////////////////////////////////////////////
    m_booksView = new QtEbookList(this);
    m_booksView->SetBackground(Qt::transparent);
    m_booksView->SetPageCount(1);
    connect(m_booksView, SIGNAL(currentItemClicked(QtPageListWidgetItem*)), this, SLOT(SltCurrentItemClicked(QtPageListWidgetItem*)));

    m_textBrowser = new TextBrowser(this);
    m_textBrowser->setVisible(false);
    m_textBrowser->setFont(QFont(Skin::m_strAppFontNormal, 14));
    m_textBrowser->setStyleSheet(QString("QTextBrowser {border: 1px solid #c5c5c5; border-top: none;background-color: #ffffff;}"));
    connect(m_textBrowser, SIGNAL(signalClicked()), this, SLOT(SltClosePalette()));

    QVBoxLayout *verLayout = new QVBoxLayout(this);
    verLayout->setContentsMargins(0, 0, 0, 0);
    verLayout->setSpacing(0);
    verLayout->addWidget(m_widgetTitle, 1);
    verLayout->addWidget(m_booksView, 7);
    verLayout->addWidget(m_textBrowser, 7);

    m_paletteWidget = new QtPaletteWidget(this);
    connect(m_paletteWidget, SIGNAL(signalFontChanged(int)), this, SLOT(SltFontSizeChanged(int)));
    connect(m_paletteWidget, SIGNAL(signalColorChanged(QColor)), this, SLOT(SltColorChanged(QColor)));
}

void EBookWidget::LoadFileToBrowser(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        m_textBrowser->setText(tr("打开文件失败"));
        return;
    }

    QTextStream read(&file);
    read.setCodec(QTextCodec::codecForName("GB18030"));
    m_textBrowser->setText(read.readAll());
    QFileInfo fileInfo(fileName);
    m_widgetTitle->SetTitle(fileInfo.fileName());
    file.close();
}

void EBookWidget::ChangePage(int index)
{
    m_btnAdd->setVisible(0 == index);
    m_widgetTitle->SetBtnVisible(0 == index);
    m_btnBack->setVisible(1 == index);
    m_btnSetting->setVisible(1 == index);

    m_booksView->setVisible(0 == index);
    m_textBrowser->setVisible(1 == index);
}

void EBookWidget::SltBtnBack()
{
    ChangePage(0);
    m_widgetTitle->SetTitle(tr("电子书"));
    if (m_paletteWidget->pos().x() < this->width()) {
        m_paletteWidget->setGeometry(this->width(), m_widgetTitle->geometry().bottom(), 436, 432);
    }
}

void EBookWidget::SltLoadEbooks()
{
    QMap<int, QtPageListWidgetItem*> listItems;
    QDir dir(m_strDirPath);
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        listItems.insert(i, new QtPageListWidgetItem(i, fileInfo.absoluteFilePath(), QPixmap("")));
    }
    m_booksView->SetItems(listItems);
}

void EBookWidget::SltAddEbool()
{
    m_fileDialog->setSaveFileMode(false);
    m_fileDialog->StartAnimation(QPoint(0, this->height()), QPoint(0, 0), 200, true);
}


void EBookWidget::SltCurrentItemClicked(QtPageListWidgetItem *item)
{
    ChangePage(1);
    LoadFileToBrowser(item->m_strText);
}

void EBookWidget::SltFontSizeChanged(int size)
{
    QFont font = m_textBrowser->font();
    font.setPixelSize(size);
    m_textBrowser->setFont(font);
}

void EBookWidget::SltColorChanged(const QColor &color)
{
    if (!color.isValid()) return;
    m_textBrowser->setStyleSheet(QString("QTextBrowser {color: %1;}").arg(color.name()));
}

void EBookWidget::SltClosePalette()
{
    if (m_paletteWidget->pos().x() < (this->width() / 2)) {
        m_paletteWidget->StartAnimation(QPoint(this->width() - m_paletteWidget->width(), 58 * m_scaleY), QPoint(this->width(), 58 * m_scaleY), 200, true);
    }
}

void EBookWidget::SltFileSelected(const QString &fileName)
{
    QFileInfo fileInfo(fileName);
    QString strNewFile = QString("%1%2").arg(m_strDirPath).arg(fileInfo.fileName());
    if (QFile::exists(strNewFile)){
        qDebug() << "the same file" << strNewFile;
        SltFileDialogClose();
        return;
    }

    QFile::copy(fileInfo.absoluteFilePath(), strNewFile);
    // 重新扫描
    SltLoadEbooks();
}

void EBookWidget::SltFileDialogClose()
{
    m_fileDialog->StartAnimation(QPoint(0, 0), QPoint(0, -this->height()), 200, false);
}

void EBookWidget::SltToolBtnClicked(int index)
{
    if (BtnHome == index) {
        emit signalBackHome();
    } else if (BtnBack == index) {
        ChangePage(0);
        m_widgetTitle->SetTitle(tr("电子书"));
        if (m_paletteWidget->pos().x() < this->width()) {
            m_paletteWidget->setGeometry(this->width(), m_widgetTitle->geometry().bottom(), 436, 432);
        }
    } else if (BtnAdd == index) {
        m_fileDialog->setSaveFileMode(false);
        m_fileDialog->StartAnimation(QPoint(0, this->height()), QPoint(0, 0), 200, true);
    } else if (BtnSetting == index) {
        if (m_paletteWidget->pos().x() > (this->width() / 2)) {
            m_paletteWidget->StartAnimation(QPoint(this->width(), 58 * m_scaleY), QPoint(this->width() - m_paletteWidget->width(), 58 * m_scaleY), 200, true);
        } else {
            m_paletteWidget->StartAnimation(QPoint(this->width() - m_paletteWidget->width(), 58 * m_scaleY), QPoint(this->width(), 58 * m_scaleY), 200, true);
        }
    }
}

void EBookWidget::resizeEvent(QResizeEvent *e)
{
    m_fileDialog->resize(this->size());
    m_scaleX = (this->width() * 1.0) / m_nBaseWidth;
    m_scaleY = (this->height() * 1.0) / m_nBaseHeight;

    m_paletteWidget->setGeometry(this->width(), m_widgetTitle->geometry().bottom(), 436 * m_scaleX, 432 * m_scaleY);
    QWidget::resizeEvent(e);
}

void EBookWidget::mousePressEvent(QMouseEvent *)
{
    if (m_paletteWidget->pos().x() < this->width() / 2) {
        m_paletteWidget->StartAnimation(QPoint(this->width() - m_paletteWidget->width(), 58 * m_scaleY),
                                        QPoint(this->width(), 58 * m_scaleY), 200, true);
    }
}

