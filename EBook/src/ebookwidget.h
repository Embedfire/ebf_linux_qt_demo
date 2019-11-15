/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : ebookwidget.h ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/8
*******************************************************************/
#ifndef EBOOKWIDGET_H
#define EBOOKWIDGET_H

#include <QWidget>
#include "qtwidgetbase.h"
#include "qtebooklist.h"
#include "qtpalettewidget.h"
#include "qtfiledialog.h"

#include <QPushButton>
#include <QTextBrowser>
#include <QScrollBar>

class TextBrowser : public QTextBrowser
{
    Q_OBJECT
public:
    explicit TextBrowser(QWidget* parent = 0);
    ~TextBrowser() {}
signals:
    void signalClicked();

private:
    bool m_bPressed;
    QPoint m_startPos;
    QScrollBar *m_scrollbar;
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
};

class EBookWidget : public QtAnimationWidget
{
    Q_OBJECT

public:
    EBookWidget(QWidget *parent = 0);
    ~EBookWidget();

    typedef enum {BtnHome, BtnBack, BtnAdd, BtnSetting} ToolBtn;
private:
    QtWidgetTitleBar        *m_widgetTitle;
    QtPixmapButton          *m_btnAdd;
    QtPixmapButton          *m_btnBack;
    QtPixmapButton          *m_btnSetting;

    TextBrowser             *m_textBrowser;
    QtEbookList             *m_booksView;

    QString                  m_strDirPath;
    QtPaletteWidget         *m_paletteWidget;
    QtFileDialog            *m_fileDialog;
private:
    void InitWidget();
    void LoadFileToBrowser(const QString &fileName);

    void ChangePage(int index);

private slots:
    void SltBtnBack();
    void SltLoadEbooks();
    void SltAddEbool();
    void SltCurrentItemClicked(QtPageListWidgetItem *item);

    void SltFontSizeChanged(int size);
    void SltColorChanged(const QColor &color);
    void SltClosePalette();

    void SltFileSelected(const QString &fileName);
    void SltFileDialogClose();
    void SltToolBtnClicked(int index);

protected:
    void resizeEvent(QResizeEvent *e);
    void mousePressEvent(QMouseEvent *);
};

#endif // EBOOKWIDGET_H
