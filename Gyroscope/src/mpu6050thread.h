/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : mpu6050thread.h --- Mpu6050Thread
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#ifndef MPU6050THREAD_H
#define MPU6050THREAD_H

#include <QThread>

typedef enum {ArgX, ArgY, ArgZ} Argus;

class Mpu6050Thread : public QThread
{
    Q_OBJECT
public:
    explicit Mpu6050Thread(QObject *parent = 0);
    ~Mpu6050Thread();

    void Stop();
signals:
    void signalUpdate(int type, int index, qint16 value);

public slots:

private:
    bool m_bRun;
    int  m_fd;

 private:
    int MPU6050_Init(void);
    quint8 i2c_write(int m_fd, quint8 reg, quint8 val);
    quint8 i2c_read(int m_fd, quint8 reg, quint8 * val);
    short GetData(quint8 REG_Address);
protected:
    void run();
};

#endif // MPU6050THREAD_H
