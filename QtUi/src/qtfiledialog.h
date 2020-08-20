/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : filedialog.h --- FileDialog
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/21
*******************************************************************/
#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>

#include "qtwidgetbase.h"
#include "qtaddressbar.h"
#include "qtpressmovelistview.h"
#include <QFileSystemModel>

#ifdef QtUi
#include <QtUi>
class QTUISHARED_EXPORT LineEdit : public QLineEdit {
#else
class LineEdit : public QLineEdit {
#endif
    Q_OBJECT
public:
    explicit LineEdit(QWidget *parent = 0) :
        QLineEdit(parent)
    {}
signals:
    void signalFocus(bool bOk);

protected:
    void focusInEvent(QFocusEvent *e){
        emit signalFocus(true);
        QLineEdit::focusInEvent(e);
    }
    void focusOutEvent(QFocusEvent *e) {
        emit signalFocus(false);
        QLineEdit::focusOutEvent(e);
    }
};

#ifdef QtUi
class QTUISHARED_EXPORT QtFileDialog : public QtAnimationWidget {
#else
class QtFileDialog : public QtAnimationWidget {
#endif
    Q_OBJECT
public:
    explicit QtFileDialog(QWidget *parent = 0);
    ~QtFileDialog();

    void setSaveFileMode(bool bOk);
    void setRootPath(const QString &path);
    bool isSaveFileMode();

signals:
    void signalSelected(const QString &file);

public slots:

private:
    QtAddressBar        *m_addressBar;
    QtPressMoveListView *m_listView;
    QFileSystemModel    *m_model;
    LineEdit            *m_lineEditPath;
    QLabel              *m_keyboard;

    QString              m_strRootPath;
    QStringList          m_strListFilter;

    bool    m_bSaveFile;
private:
    void InitWidget();

private slots:
    void InitModel();
    void SltAnimationFinished();
    void SltTextFocusChanged(bool bOk);
    void SltBtnOkClicked();

private slots:
    void SltItemClicked(const QModelIndex &index);
    void SltItemFileClicked(const QModelIndex &index);
    void SltAddressChanged(const QString &addr);
    void SltBtnRecentClicked(int index);

protected:
    void resizeEvent(QResizeEvent *e);
};

#endif // FILEDIALOG_H
