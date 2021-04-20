#ifndef NESWIDGET_H
#define NESWIDGET_H

#include "qtwidgetbase.h"
#include "nesscreenwidget.h"

#include <QThread>

class mNesThread;

class NesWidget : public QtAnimationWidget
{
    Q_OBJECT
 public:
    NesWidget(QWidget *parent = 0);
    ~NesWidget();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);

    void setFileName(QString fileName);


public:
    mNesThread *mnesThread;
    QString    m_strFileName;

    NesScreenWidget *neswidget;
};

////////////////////////////////////////////////////////////////
class mNesThread : public QThread {
    Q_OBJECT
public:
    mNesThread(QObject *parent = 0);
    void stop();

signals:
    void loadFrame();

private:
    int     m_nRunFlag;

protected:
    void run() override;
};
#endif // NESWIDGET_H
