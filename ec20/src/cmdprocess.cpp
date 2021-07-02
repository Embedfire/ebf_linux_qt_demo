#include "cmdprocess.h"

#include <QDir>

CmdProcess::CmdProcess(QObject *parent)
    : QObject(parent)
{
    cmd = new QProcess(this);
    cmd->setWorkingDirectory(QDir::currentPath());
    cmd->setReadChannel(QProcess::StandardOutput);
    connect(cmd, SIGNAL(readyRead()), this, SLOT(readProcess()));
    connect(cmd, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(finishedProcess(int,QProcess::ExitStatus)));

    connect(cmd,SIGNAL(readyReadStandardOutput()),this,SLOT(readyReadStandardOutput()));
    connect(cmd,SIGNAL(readyReadStandardError()),this,SLOT(readyReadStandardError()));

}
CmdProcess::~CmdProcess()
{
    cmd->close();
}
QProcess::ProcessState CmdProcess::state()
{
    return cmd->state();
}
void CmdProcess::setWorkdir(const QString workdir)
{
    cmd->setWorkingDirectory(workdir);
}
void CmdProcess::setOrder(const QString order)
{
    m_order = order;
}
int CmdProcess::startCmd()
{
    ErrorCode m_error = ErrorNone;
    if (cmd->state() == QProcess::NotRunning) {
        cmd->start(m_order);
    }
    else
    {
        m_error=ErrorBusy;
        emit sendProcessMsg(QString("process busy busy buys ...... ,  %1").arg(m_error));
    }

    return m_error;
}
int CmdProcess::startCmd(const QString order)
{
    m_error = ErrorNone;
    if (cmd->state() == QProcess::NotRunning) {
        cmd->start(order);

        if (!cmd->waitForStarted())
            return WaitStarted;

        if (!cmd->waitForFinished())
            return WaitFinished;
    }
    else
    {
        m_error=ErrorBusy;
        emit sendProcessMsg(QString("process busy busy buys ...... ,  %1").arg(m_error));
    }

    return m_error;
}

void CmdProcess::readProcess()
{
    //QString result = cmd->readAll();
    QString result = cmd->readAllStandardOutput();
    emit sendProcessMsg(result);
}
void CmdProcess::finishedProcess(int exitCode, QProcess::ExitStatus exitStatus)
{
    if(exitStatus != QProcess::ExitStatus::NormalExit)
    {
        m_error=Error;
        return;
    }

    m_error=ErrorNone;
}
void CmdProcess::readyReadStandardOutput()
{
    QString outStr = QString::fromLocal8Bit(cmd->readAllStandardOutput());
    emit sendProcessMsg(outStr);
}

void CmdProcess::readyReadStandardError()
{
    QString outStr = QString::fromLocal8Bit(cmd->readAllStandardError());
    emit sendProcessMsg(outStr);
}
