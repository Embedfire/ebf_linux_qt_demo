/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : filedialog.cpp --- FileDialog
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/21
*******************************************************************/
#include "qtfiledialog.h"

#include <QButtonGroup>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QBoxLayout>

#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QApplication>

#define FONT_FAMILY "思源黑体 CN Normal"

QtFileDialog::QtFileDialog(QWidget *parent) : QtAnimationWidget(parent)
{
    if (NULL != parent) {
        this->resize(parent->size());
        this->setAttribute(Qt::WA_DeleteOnClose);
    } else {
        this->setFixedSize(800, 480);
    }

    m_bShow = true;
    m_bSaveFile = false;
    m_keyboard = NULL;
    m_strListFilter = QStringList() << "*.txt";
    m_strRootPath = qApp->applicationDirPath() + "/";
    InitWidget();
    InitModel();
}

QtFileDialog::~QtFileDialog()
{

}

void QtFileDialog::setSaveFileMode(bool bOk)
{
    m_bSaveFile = bOk;
    m_lineEditPath->setReadOnly(!bOk);
    m_lineEditPath->clear();
}

void QtFileDialog::setRootPath(const QString &path)
{
    m_strRootPath = path;
    m_addressBar->setAddress(path);
}

bool QtFileDialog::isSaveFileMode()
{
    return m_bSaveFile;
}

void QtFileDialog::InitWidget()
{
    m_addressBar = new QtAddressBar(this);
    connect(m_addressBar, SIGNAL(signalBackHome()), this, SIGNAL(signalBackHome()));
    connect(m_addressBar, SIGNAL(signalAddress(QString)), this, SLOT(SltAddressChanged(QString)));
    m_addressBar->setAddress(m_strRootPath);

    QHBoxLayout *horLayoutRight = new QHBoxLayout();
    horLayoutRight->setContentsMargins(0, 0, 0, 0);
    horLayoutRight->setSpacing(0);

    //////////////////////////////////////////////////////////////////////////////////////////
    QWidget *widgetRecent = new QWidget(this);
    widgetRecent->setObjectName("widgetRecent");
    widgetRecent->setStyleSheet(QString("QWidget#widgetRecent{background-color: #605d53;}"
                                        "QPushButton{border:none; border-bottom: 1px solid #aaaaaa;"
                                        "background-color: none; font-family:'%1';"
                                        "font: 18px; color: #ffffff; min-height: 30px; padding-left: 10px}"
                                        "QPushButton:pressed{background-color: #f17a49;}").arg(FONT_FAMILY));
    horLayoutRight->addWidget(widgetRecent, 1);


    QVBoxLayout *verLayoutRecent = new QVBoxLayout(widgetRecent);
    verLayoutRecent->setContentsMargins(0, 0, 0, 0);
    verLayoutRecent->setSpacing(0);
    QButtonGroup *btnGroup = new QButtonGroup(this);
    QPushButton *btnHome = new QPushButton(widgetRecent);
    btnGroup->addButton(btnHome, 0);
    btnHome->setText("home");
    verLayoutRecent->addWidget(btnHome);

    QPushButton *btnRoot = new QPushButton(widgetRecent);
    btnRoot->setText("root");
    btnGroup->addButton(btnHome, 1);
    verLayoutRecent->addWidget(btnRoot);

    verLayoutRecent->addStretch();
    connect(btnGroup, SIGNAL(buttonClicked(int)), this, SLOT(SltBtnRecentClicked(int)));

    //////////////////////////////////////////////////////////////////////////////////////////
    // file list
    m_listView = new QtPressMoveListView(this);
    m_listView->SetIconMode();
    m_listView->setDragDropMode(QListView::NoDragDrop);

    QHBoxLayout *horLayoutLineEdit = new QHBoxLayout();
    horLayoutLineEdit->setContentsMargins(10, 8, 10, 8);
    horLayoutLineEdit->setSpacing(10);
    horLayoutLineEdit->addWidget(new QLabel(tr("文件名："), this));

    m_lineEditPath = new LineEdit(this);
    m_lineEditPath->setReadOnly(m_bSaveFile);
    m_lineEditPath->setStyleSheet(QString("QLineEdit{border: 1px solid #5b5b5b; color:#333333; min-height: 24px;}"
                                          "QLineEdit::focus{border: 1px solid #0078d7;}"));
    horLayoutLineEdit->addWidget(m_lineEditPath, 1);
    connect(m_lineEditPath, SIGNAL(signalFocus(bool)), this, SLOT(SltTextFocusChanged(bool)));

    QPushButton *btnOpen = new QPushButton(this);
    btnOpen->setStyleSheet(QString("QPushButton {border: 1px solid #5b5b5b; border-radius: 2px; "
                                   "min-width: 80px; min-height: 24px;color: #333333; }"
                                   "QPushButton:pressed {border: 1px solid #0078d7;}"));
    btnOpen->setText(tr("确  定"));
    connect(btnOpen, SIGNAL(clicked(bool)), this, SLOT(SltBtnOkClicked()));
    horLayoutLineEdit->addWidget(btnOpen);


    QVBoxLayout *verLayoutFiles =  new QVBoxLayout();
    verLayoutFiles->setContentsMargins(0, 0, 0, 0);
    verLayoutFiles->setSpacing(0);
    verLayoutFiles->addWidget(m_listView, 9);
    verLayoutFiles->addLayout(horLayoutLineEdit, 1);

#ifdef __arm__
    m_keyboard = new QLabel(this);
    m_keyboard->setFixedHeight(221);
    m_keyboard->setVisible(false);
    verLayoutFiles->addWidget(m_keyboard);
#endif

    horLayoutRight->addLayout(verLayoutFiles, 5);
    //////////////////////////////////////////////////////////////////////////////////////////
    QVBoxLayout *verLayoutAll = new QVBoxLayout(this);
    verLayoutAll->setContentsMargins(0, 0, 0, 0);
    verLayoutAll->setSpacing(0);
    verLayoutAll->addWidget(m_addressBar, 1);
    verLayoutAll->addLayout(horLayoutRight, 7);
}

void QtFileDialog::InitModel()
{
    m_model = new QFileSystemModel(this);
    m_model->setFilter(QDir::Dirs | QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);

    m_listView->setModel(m_model);
#ifdef __arm__
    connect(m_listView, SIGNAL(clicked(QModelIndex)), this, SLOT(SltItemClicked(QModelIndex)));
#else
    connect(m_listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(SltItemClicked(QModelIndex)));
#endif
}

void QtFileDialog::SltAnimationFinished()
{
    this->setVisible(m_bShow);
    if (m_bShow) {
        m_model->setRootPath(m_strRootPath);
        m_listView->setRootIndex(m_model->index(m_strRootPath));
    }
}

void QtFileDialog::SltTextFocusChanged(bool bOk)
{
    if (NULL != m_keyboard) {
        m_keyboard->setVisible(bOk);
    }
}

void QtFileDialog::SltBtnOkClicked()
{
    QString strFile = m_lineEditPath->text();
    if (!strFile.isEmpty()) {
        if (!strFile.endsWith(".txt")) {
            strFile.append(".txt");
        }

        if (!strFile.contains(m_strRootPath)) {
            strFile = m_strRootPath + "/" + strFile;
        }
        emit signalSelected(strFile);
    } else if (!m_bSaveFile) {
        emit signalBackHome();
    }
}

void QtFileDialog::SltItemClicked(const QModelIndex &index)
{
    if (m_model->isDir(index)) {
        m_strRootPath = m_model->filePath(index);
        m_addressBar->setAddress(m_strRootPath);
        m_listView->setRootIndex(m_model->index(m_strRootPath));
    } else {
        QFileInfo fileInfo(m_model->filePath(index));
        if (fileInfo.isFile() && (fileInfo.suffix() == "txt"))
        {
            m_lineEditPath->setText(m_model->filePath(index));
        }
    }
}

void QtFileDialog::SltItemFileClicked(const QModelIndex &index)
{
    if (!m_model->isDir(index)) {
        QFileInfo fileInfo(m_model->filePath(index));
        if (fileInfo.isFile() && (fileInfo.suffix() == "txt"))
        {
            m_lineEditPath->setText(m_model->filePath(index));
        }
    }
}

void QtFileDialog::SltAddressChanged(const QString &addr)
{
    m_listView->setRootIndex(m_model->index(addr));
}

void QtFileDialog::SltBtnRecentClicked(int index)
{
    if (0 == index) {
        m_listView->setRootIndex(m_model->index("/home/"));
    } else {
        m_listView->setRootIndex(m_model->index("/root/"));
    }
}

void QtFileDialog::resizeEvent(QResizeEvent *e)
{
    SetScaleValue();
    m_listView->setIconSize(QSize(60 * m_scaleX, 60 * m_scaleY));
    m_listView->setGridSize(QSize(100 * m_scaleX, 100 * m_scaleY));
    QWidget::resizeEvent(e);
}
