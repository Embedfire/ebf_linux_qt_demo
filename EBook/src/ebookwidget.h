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

private:
    QtWidgetTitleBar        *m_widgetTitle;
    QPushButton             *m_btnAdd;
    QPushButton             *m_btnBack;
    QPushButton             *m_btnSetting;
    QPushButton             *m_btnHome;
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
    void SltSetColorStyle();

    void SltFontSizeChanged(int size);
    void SltColorChanged(const QColor &color);
    void SltClosePalette();

    void SltFileSelected(const QString &fileName);
    void SltFileDialogClose();

protected:
    void resizeEvent(QResizeEvent *e);
    void mousePressEvent(QMouseEvent *);
};

#endif // EBOOKWIDGET_H
