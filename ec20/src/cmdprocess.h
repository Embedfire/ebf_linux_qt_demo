#ifndef CMDPROCESS_H
#define CMDPROCESS_H

#include <QProcess>

class CmdProcess : public QObject
{
    Q_OBJECT
public:
    typedef enum {
        Error,
        ErrorBusy,
        ErrorNone,
        WaitStarted,
        WaitFinished,
    } ErrorCode;
public:

    CmdProcess(QObject *parent = 0);
    ~CmdProcess();
    QProcess::ProcessState state();
    void initData();

    void setWorkdir(const QString workdir);
    void setOrder(const QString order);

    int startCmd();
    int startCmd(const QString order);
private slots:
    void readProcess();
    void finishedProcess(int exitCode, QProcess::ExitStatus exitStatus);
    void readyReadStandardOutput();
    void readyReadStandardError();

signals:
    void sendProcessMsg(const QString msg);

public:
    QProcess            *cmd;
private:
    ErrorCode           m_error;
    QString             m_order;
};

#endif // CMDPROCESS_H
