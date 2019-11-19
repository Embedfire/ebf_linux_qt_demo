/******************************************************************
 Copyright (C) 2019 - All Rights Reserved by
 文 件 名 : mpu6050thread.cpp --- Mpu6050Thread
 作 者    : Niyh(lynnhua)
 论 坛    : http://www.firebbs.cn
 编写日期 : 2019
 说 明    :
 历史纪录 :
 <作者>    <日期>        <版本>        <内容>
  Niyh	   2019    	1.0.0 1     文件创建
*******************************************************************/
#include "mpu6050thread.h"
#include <QDebug>

//包含头文件
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/time.h>
#include<errno.h>
#ifdef __arm__
#include<sys/ioctl.h>
#include<sys/select.h>
#endif
//宏定义
#define SMPLRT_DIV                                  0x19
#define CONFIG                                      0x1A
#define GYRO_CONFIG                                 0x1B
#define ACCEL_CONFIG                                0x1C
#define ACCEL_XOUT_H                                0x3B
#define ACCEL_XOUT_L                                0x3C
#define ACCEL_YOUT_H                                0x3D
#define ACCEL_YOUT_L                                0x3E
#define ACCEL_ZOUT_H                                0x3F
#define ACCEL_ZOUT_L                                0x40
#define TEMP_OUT_H                                  0x41
#define TEMP_OUT_L                                  0x42
#define GYRO_XOUT_H                                 0x43
#define GYRO_XOUT_L                                 0x44
#define GYRO_YOUT_H                                 0x45
#define GYRO_YOUT_L                                 0x46
#define GYRO_ZOUT_H                                 0x47
#define GYRO_ZOUT_L                                 0x48
#define PWR_MGMT_1                                  0x6B
#define WHO_AM_I                                    0x75
#define SlaveAddress                                0xD0
#define Address                                     0x68                  //MPU6050地址
#define I2C_RETRIES                                 0x0701
#define I2C_TIMEOUT                                 0x0702
#define I2C_SLAVE                                   0x0703       //IIC从器件的地址设置
#define I2C_BUS_MODE                                0x0780

Mpu6050Thread::Mpu6050Thread(QObject *parent) : QThread(parent),
    m_bRun(false),m_fd(-1)
{

}

Mpu6050Thread::~Mpu6050Thread()
{
    Stop();
}

void Mpu6050Thread::Stop()
{
    m_bRun = false;
    this->wait(2000);
}

//MPU6050初始化
int Mpu6050Thread::MPU6050_Init(void)
{
    int fd = -1;
#ifdef __arm__
    fd  = open("/dev/i2c-0", O_RDWR);               // open file and enable read and  write

    if (fd < 0)
    {
        perror("Can't open /dev/MPU6050 \n");       // open i2c dev file fail
        return - 1;
    }

    printf("open /dev/i2c-0 success !\n");          // open i2c dev file succes

    if (ioctl(fd, I2C_SLAVE, Address) < 0)
    {
        // set i2c address
        printf("fail to set i2c device slave address!\n");
        close(fd);
        return - 1;
    }

    printf("set slave address to 0x%x success!\n", Address);
    i2c_write(fd, PWR_MGMT_1, 0X00);
    i2c_write(fd, SMPLRT_DIV, 0X07);
    i2c_write(fd, CONFIG, 0X06);
    i2c_write(fd, ACCEL_CONFIG, 0X01);
    m_bRun = true;
#else
    m_bRun = true;
#endif

    return fd;
}

//MPU6050 wirte byte
quint8 Mpu6050Thread::i2c_write(int fd, quint8 reg, quint8 val)
{
    int retries;
    quint8 data[2];

    data[0] = reg;
    data[1] = val;

    for (retries = 5; retries; retries--)
    {
        if (write(fd, data, 2) == 2)
        {
            return 0;

        }

        usleep(1000 * 10);
    }

    return - 1;
}

//MPU6050 read byte
quint8 Mpu6050Thread::i2c_read(int fd, quint8 reg, quint8 * val)
{
    if (-1 == fd) {*val = (qrand() % 5);}

#ifdef __arm__
    int retries;

    for (retries = 5; retries; retries--)
    {
        if (write(fd, &reg, 1) == 1)
        {
            if (read(fd, val, 1) == 1)
            {
                return 0;
            }
        }

    }
#else
    Q_UNUSED(reg)
    Q_UNUSED(val)
#endif

    return - 1;
}

//get data
short Mpu6050Thread::GetData(quint8 REG_Address)
{
    quint8 H = 0;
    quint8 L = 0;
    i2c_read(m_fd, REG_Address, &H);

    usleep(1000);
    i2c_read(m_fd, REG_Address + 1, &L);

    return (H << 8) + L;
}


void Mpu6050Thread::run()
{
    m_fd = MPU6050_Init();

    qDebug() << "m_fd" << m_fd << m_bRun;

    while (m_bRun)
    {
        // printf("\033[2J");
        // usleep(1000 * 10);
        emit signalUpdate(0, ArgX, GetData(ACCEL_XOUT_H));

        // usleep(1000 * 10);
        emit signalUpdate(0, ArgY, GetData(ACCEL_YOUT_H));

        // usleep(1000 * 10);
        emit signalUpdate(0, ArgZ, GetData(ACCEL_ZOUT_H));

        // usleep(1000 * 10);
        emit signalUpdate(1, ArgX, GetData(GYRO_XOUT_H));

        // usleep(1000 * 10);
        emit signalUpdate(1, ArgY, GetData(GYRO_YOUT_H));

        // usleep(1000 * 10);
        emit signalUpdate(1, ArgZ, GetData(GYRO_ZOUT_H));
        usleep(1000 * 150);
    }
#ifdef __arm__
    close(m_fd);
#endif
}
