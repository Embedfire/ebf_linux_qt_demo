#ifndef NESSOUNDDEVICE_H
#define NESSOUNDDEVICE_H

#include <QObject>
#include <QIODevice>
#include <QList>
#include <QByteArray>
#include <QMutex>
#include <QMutexLocker>
#include <QWaitCondition>

class NesSoundDevice : public QIODevice
{
    Q_OBJECT

public:
    NesSoundDevice(QObject *parent=0);

    virtual qint64 readData(char *data, qint64 maxlen);
    virtual qint64 writeData(const char *data, qint64 len);

private:
    QList<QByteArray> pcmBuff;
    QMutex mutex;
    QWaitCondition pcmDataReady;
};

#endif // NESSOUNDDEVICE_H
