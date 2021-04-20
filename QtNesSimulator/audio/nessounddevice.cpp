#include "nessounddevice.h"

#include <QDebug>

NesSoundDevice::NesSoundDevice(QObject *parent):QIODevice(parent)
{

}

qint64 NesSoundDevice::readData(char *data, qint64 maxlen)
{
    //QMutexLocker locker(&mutex);
    int readLength = 0;

    mutex.lock();
    if(pcmBuff.empty())
    {
        pcmDataReady.wait(&mutex);
    }

    QList<QByteArray>::iterator it = pcmBuff.begin();

    for(; it!=pcmBuff.end();)
    {
        QByteArray byte = *it;

        if((maxlen - readLength) >= byte.length())
        {
            memcpy(data + readLength, byte.data(), byte.length());

            it = pcmBuff.erase(it);
            readLength += byte.length();
            continue;
        }
        else
        {
            break;
        }
        it++;
    }
    mutex.unlock();

    return readLength;
}

qint64 NesSoundDevice::writeData(const char *data, qint64 len)
{
    QByteArray byte;

    byte.append(data, len);

    pcmDataReady.wakeAll();

    QMutexLocker locker(&mutex);
    pcmBuff.append(byte);
    return len;
}
