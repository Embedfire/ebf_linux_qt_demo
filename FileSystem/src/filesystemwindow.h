/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : filesystemwindow.h ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/15
*******************************************************************/
#ifndef FILESYSTEMWINDOW_H
#define FILESYSTEMWINDOW_H

#include <QWidget>
#include <QFileSystemModel>
#include <QTableView>
#include "qtaddressbar.h"
#include "qtwidgetbase.h"
#include "qtlistwidget.h"
#include "qtpressmovelistview.h"

#include <QFileSystemModel>

class NotePadWidget;

class FileSystemWindow : public QtAnimationWidget
{
    Q_OBJECT
public:
    FileSystemWindow(QWidget *parent = 0);
    ~FileSystemWindow();

private:
    QtAddressBar        *m_addressBar;
    QtPressMoveListView *m_listView;
    QFileSystemModel    *m_model;

    QString              m_strRootPath;

    NotePadWidget       *m_notePadWidget;
private:
    void InitWidget();
    Q_SLOT void InitModel();

private slots:
    void SltItemClicked(const QModelIndex &index);
    void SltAddressChanged(const QString &addr);
    void SltNotePadHide();
    void SltBtnRecentClicked(int index);

protected:
    void resizeEvent(QResizeEvent *e);
};

#endif // FILESYSTEMWINDOW_H
