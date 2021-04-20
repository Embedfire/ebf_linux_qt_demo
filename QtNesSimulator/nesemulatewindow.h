#ifndef NESEMULATEWINDOW_H
#define NESEMULATEWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QThread>

namespace Ui {
class NesEmulateWindow;
}

class NesThread;

class NesEmulateWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NesEmulateWindow(QWidget *parent = 0);
    ~NesEmulateWindow();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void closeEvent(QCloseEvent *event);

private slots:
    void on_actionOpen_triggered();
    void on_actionExit_triggered();

    void on_actionsave_triggered();

    void on_actioncontrol_triggered();

public:
    Ui::NesEmulateWindow *ui;
    NesThread *nesThread;
    QString    m_strFileName;
};


////////////////////////////////////////////////////////////////
class NesThread : public QThread {
    Q_OBJECT
public:
    NesThread(QObject *parent = 0);
    void stop();

signals:
    void loadFrame();

private:
    int     m_nRunFlag;

protected:
    void run() override;
};

#endif // NESEMULATEWINDOW_H
