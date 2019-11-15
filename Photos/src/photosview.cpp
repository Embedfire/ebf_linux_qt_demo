/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : photosview.cpp ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/8
*******************************************************************/
#include "photosview.h"
#include "skin.h"
#include "imageviewer.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>
#include <QDebug>
#include <QTimer>
#include <QDir>

PhotosView::PhotosView(QWidget *parent) : QtAnimationWidget(parent)
{
    this->SetBackground(QColor("#ffffff"));

    m_strDirPath = qApp->applicationDirPath() + "/photos/";
    InitWidget();

    QTimer::singleShot(500, this, SLOT(SltLoadPhotos()));
}

PhotosView::~PhotosView()
{
}

void PhotosView::InitWidget()
{
    QtWidgetTitleBar *widgetTitle = new QtWidgetTitleBar(this);
    widgetTitle->SetScalSize(Skin::m_nScreenWidth, 60);
    widgetTitle->SetBackground(QColor("#f0f0f0"));
    widgetTitle->SetTitle(tr("相册"), "#333333", 25);
    widgetTitle->SetBtnHomePixmap(QPixmap(":/images/photos/menu_icon.png"), QPixmap(":/images/photos/menu_icon_pressed.png"));

    connect(widgetTitle, SIGNAL(signalBackHome()), this, SIGNAL(signalBackHome()));

    m_photoListView = new PhotoListView(this);
    m_photoListView->SetBackground(QColor("#ffffff"));
    connect(m_photoListView, SIGNAL(currentItemClicked(QtPageListWidgetItem*)), this, SLOT(SltCurrentItemClicked(QtPageListWidgetItem*)));

    QVBoxLayout *verLayout = new QVBoxLayout(this);
    verLayout->setContentsMargins(0, 0, 0, 0);
    verLayout->setSpacing(0);
    verLayout->addWidget(widgetTitle, 1);
    verLayout->addWidget(m_photoListView, 7);
}

void PhotosView::SltLoadPhotos()
{
    m_listItems.clear();
    QDir dir(m_strDirPath);
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QFileInfoList list = dir.entryInfoList(QStringList() << "*.jpg" << "*.png" << "*.bmp");
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        QPixmap pixmap(fileInfo.absoluteFilePath());
        if (pixmap.width() > pixmap.height()) {
            pixmap = pixmap.scaledToHeight(200);
        } else {
            pixmap = pixmap.scaledToWidth(200);
        }
        pixmap = pixmap.copy(0, 0, 200, 200);
        m_listItems.insert(i, new QtPageListWidgetItem(i, fileInfo.absoluteFilePath(), pixmap));
    }
    m_photoListView->SetItems(m_listItems);
}

void PhotosView::SltCurrentItemClicked(QtPageListWidgetItem *item)
{
    ImageViewer *imageView = new ImageViewer(this);
    imageView->setGeometry(0, 0, this->width(), this->height());
    imageView->SetPixmap(item->m_nId, m_listItems);
}
