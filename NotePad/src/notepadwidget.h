/******************************************************************
 Copyright (C) 2017 - All Rights Reserved by
 文 件 名 : notepadwidget.h ---
 作 者    : Niyh  (QQ:393320854)
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
           2019/9/8
*******************************************************************/
#ifndef NOTEPADWIDGET_H
#define NOTEPADWIDGET_H

#include <QWidget>
#include <QTextEdit>
#include "qtwidgetbase.h"
#include "qtpalettewidget.h"
#include "qtfiledialog.h"

#include <QScrollBar>

class TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEdit(QWidget* parent = 0);
    ~TextEdit() {}
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

////////////////////////////////////////////////////
class NotePadWidget : public QtAnimationWidget
{
    Q_OBJECT
public:
    NotePadWidget(QWidget *parent = 0);
    ~NotePadWidget();

    void OpenDocument(const QString &fileName);
    void SaveDocument(const QString &fileName);

private:
    TextEdit            *m_textEdit;
    QtWidgetTitleBar    *m_widgetTitle;
    QtPaletteWidget     *m_paletteWidget;
    QtFileDialog        *m_fileDialog;
    QMenu               *m_menuFile;
private:
    void InitWidget();

private slots:
    void SltBackHome();
    void SltActionTriggered(QAction *action);
    void SltSetPaletteConfig();
    void SltFontSizeChanged(int size);
    void SltColorChanged(const QColor &color);
    void SltClosePalette();

    void SltFileSelected(const QString &fileName);
    void SltFileDialogClose();
    void SltToolBtnClicked(int index);

    void ActionOpen();
    void NewDocument();
    void SaveDocument();

protected:
    void resizeEvent(QResizeEvent *e);
};

#endif // NOTEPADWIDGET_H
