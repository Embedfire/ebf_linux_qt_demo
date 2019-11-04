#ifndef BROWSERWINDOW_H
#define BROWSERWINDOW_H

#include "qtwidgetbase.h"
#include <QLineEdit>
#include <QWebEngineView>

class BrowserWindow : public QtAnimationWidget
{
    Q_OBJECT
public:
    explicit BrowserWindow(QWidget *parent = 0);
    ~BrowserWindow();

signals:

public slots:

private:
    QLineEdit       *m_lineEditHostAddr;
    QWebEngineView  *m_webView ;
private:
    void InitWidget();

private slots:
    void SltGotoHostAddr();
    void SltGoToHome();

};

#endif // BROWSERWINDOW_H
