#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QAudioFormat>
#include <QAudioOutput>
#include <QAudioDeviceInfo>

#include "nessounddevice.h"
#include "nesemulatewindow.h"
#include "nesscreenwidget.h"

#include "ui_nesemulatewindow.h"

#include "InfoNES_System.h"
#include "InfoNES.h"
#include "InfoNES_pAPU.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "controlhandlewidget.h"

/* RGB565 */
WORD NesPalette[ 64 ] =
{
    0x738e, 0x20d1, 0x0015, 0x4013, 0x880e, 0xa802, 0xa000, 0x7840,
    0x4140, 0x0200, 0x0280, 0x01c2, 0x19cb, 0x0000, 0x0000, 0x0000,
    0xbdd7, 0x039d, 0x21dd, 0x801e, 0xb817, 0xe00b, 0xd940, 0xca41,
    0x8b80, 0x0480, 0x0540, 0x0487, 0x0411, 0x0000, 0x0000, 0x0000,
    0xffdf, 0x3ddf, 0x5c9f, 0x445f, 0xf3df, 0xfb96, 0xfb8c, 0xfcc7,
    0xf5c7, 0x8682, 0x4ec9, 0x5fd3, 0x075b, 0x0000, 0x0000, 0x0000,
    0xffdf, 0xaf1f, 0xc69f, 0xd65f, 0xfe1f, 0xfe1b, 0xfdd6, 0xfed5,
    0xff14, 0xe7d4, 0xaf97, 0xb7d9, 0x9fde, 0x0000, 0x0000, 0x0000,
};

static NesSoundDevice *soundDevice = NULL;
static QWidget *applicationQWidget = NULL;
static unsigned char *pcmBuf = NULL;
static int pcmBufSize = 0;
static bool nesThreadRun = false;
static unsigned int joypad = 0;

NesEmulateWindow::NesEmulateWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NesEmulateWindow)
{
    ui->setupUi(this);

    nesThread = new NesThread(this);
    applicationQWidget = this;

    connect(nesThread, SIGNAL(loadFrame()), ui->nesScreenWidget, SLOT(loadFrame()));
}

NesEmulateWindow::~NesEmulateWindow()
{
    delete ui;
    nesThread->stop();
}

void NesEmulateWindow::on_actionOpen_triggered()
{
    QString nesFile = QFileDialog::getOpenFileName(this, "select NES file",
                                                   qApp->applicationDirPath(),
                                                   "nes files(*.nes)");
    if (nesFile.isEmpty() || (m_strFileName == nesFile)) return;
    if (nesThread->isRunning()) nesThread->stop();

    if(0 == InfoNES_Load(nesFile.toLocal8Bit().data()))
    {
        nesThreadRun = true;
        m_strFileName = nesFile;
        nesThread->start();
    }
}

void NesEmulateWindow::on_actionExit_triggered()
{
    nesThreadRun = false;

    nesThread->terminate();
    nesThread->wait();

    exit(0);
}

void NesEmulateWindow::on_actionsave_triggered()
{
    if (m_strFileName.isEmpty()) return;
    SaveSRAM(m_strFileName.toStdString().c_str());
}
void NesEmulateWindow::on_actioncontrol_triggered()
{
    ControlHandleWidget control;
    control.show();
}

void NesEmulateWindow::closeEvent(QCloseEvent *event)
{
    nesThreadRun = false;
    nesThread->stop();
    QWidget::closeEvent(event);
}

/**
 * 0  1   2       3       4    5      6     7
 * A  B   Select  Start  Up   Down   Left  Right
 */
void NesEmulateWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Space://space : A
    {
        joypad &= ~(1);
        joypad |= 1;
    }break;
    case Qt::Key_B://B : B
    {
        joypad &= ~(1<<1);
        joypad |= 1<<1;
    }break;
    case Qt::Key_1://1 : Select
    {
        joypad &= ~(1<<2);
        joypad |= 1<<2;
    }break;
    case Qt::Key_2://2 : Start
    {
        joypad &= ~(1<<3);
        joypad |= 1<<3;
    }break;
    case Qt::Key_Up://Up : up
    {
        joypad &= ~(1<<4);
        joypad |= 1<<4;
    }break;
    case Qt::Key_Down://Down : Down
    {
        joypad &= ~(1<<5);
        joypad |= 1<<5;
    }break;
    case Qt::Key_Left://Left : Left
    {
        joypad &= ~(1<<6);
        joypad |= 1<<6;
    }break;
    case Qt::Key_Right://Right : Right
    {
        joypad &= ~(1<<7);
        joypad |= 1<<7;
    }break;
    default:break;
    }
}

void NesEmulateWindow::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Space://space : A
    {
        joypad &= ~(1);
    }break;
    case Qt::Key_B://B : B
    {
        joypad &= ~(1 << 1);
    }break;
    case Qt::Key_1://1 : Select
    {
        joypad &= ~(1 << 2);
    }break;
    case Qt::Key_2://2 : Start
    {
        joypad &= ~(1 << 3);
    }break;
    case Qt::Key_Up://Up : up
    {
        joypad &= ~(1 << 4);
    }break;
    case Qt::Key_Down://Down : Down
    {
        joypad &= ~(1 << 5);
    }break;
    case Qt::Key_Left://Left : Left
    {
        joypad &= ~(1<<6);
    }break;
    case Qt::Key_Right://Right : Right
    {
        joypad &= ~(1 << 7);
    }break;
    default:break;
    }
}

void *InfoNES_MemoryCopy(void *dest, const void *src, int count)
{
    return memcpy(dest, src, count);
}

void InfoNES_ReleaseRom()
{
    if ( ROM )
    {
        free( ROM );
        ROM = NULL;
    }

    if ( VROM )
    {
        free( VROM );
        VROM = NULL;
    }
}

void *InfoNES_MemorySet(void *dest, int c, int count)
{
    return memset(dest, c, count);
}

void InfoNES_LoadFrame()
{
    NesEmulateWindow *newWindow = (NesEmulateWindow *) applicationQWidget;
    emit newWindow->nesThread->loadFrame();
}

void InfoNES_PadState(DWORD *pdwPad1, DWORD *pdwPad2, DWORD *pdwSystem)
{
    *pdwPad1 = joypad;
    *pdwPad2 = 0;
    *pdwSystem = 0;
}

void InfoNES_MessageBox(const char *pszMsg, ...)
{
    Q_UNUSED(pszMsg)
}

int InfoNES_ReadRom(const char *pszFileName)
{
    /*
     *  Read ROM image file
     *
     *  Parameters
     *    const char *pszFileName          (Read)
     *
     *  Return values
     *     0 : Normally
     *    -1 : Error
     */

    FILE *fp;

    /* Open ROM file */
    fp = fopen( pszFileName, "rb" );

    if ( fp == NULL )
        return(-1);

    /* Read ROM Header */
    fread( &NesHeader, sizeof NesHeader, 1, fp );
    if ( memcmp( NesHeader.byID, "NES\x1a", 4 ) != 0 )
    {
        /* not .nes file */
        fclose( fp );
        return(-1);
    }

    /* Clear SRAM */
    memset( SRAM, 0, SRAM_SIZE );

    /* If trainer presents Read Triner at 0x7000-0x71ff */
    if ( NesHeader.byInfo1 & 4 )
    {
        fread( &SRAM[0x1000], 512, 1, fp );
    }

    /* Allocate Memory for ROM Image */
    ROM = (BYTE *) malloc( NesHeader.byRomSize * 0x4000 );

    /* Read ROM Image */
    fread( ROM, 0x4000, NesHeader.byRomSize, fp );

    if ( NesHeader.byVRomSize > 0 )
    {
        /* Allocate Memory for VROM Image */
        VROM = (BYTE *) malloc( NesHeader.byVRomSize * 0x2000 );

        /* Read VROM Image */
        fread( VROM, 0x2000, NesHeader.byVRomSize, fp );
    }

    /* File close */
    fclose( fp );
    return 0;
}

int SaveSRAM(const char *fileName)
{
/*
 *  Save a SRAM
 *
 *  Return values
 *     0 : Normally
 *    -1 : SRAM data couldn't be written
 */

    FILE		*fp;
    int		nUsedTable[256];
    unsigned char	chData;
    unsigned char	chPrevData;
    unsigned char	chTag;
    int		nIdx;
    int		nEncoded;
    int		nEncLen;
    int		nRunLen;
    unsigned char	pDstBuf[SRAM_SIZE];

    /*-------------------------------------------------------------------*/
    /*  Compress a SRAM data                                             */
    /*-------------------------------------------------------------------*/

    memset( nUsedTable, 0, sizeof nUsedTable );

    for ( nIdx = 0; nIdx < SRAM_SIZE; ++nIdx )
    {
        ++nUsedTable[SRAM[nIdx++]];
    }
    for ( nIdx = 1, chTag = 0; nIdx < 256; ++nIdx )
    {
        if ( nUsedTable[nIdx] < nUsedTable[chTag] )
            chTag = nIdx;
    }

    nEncoded	= 0;
    nEncLen		= 0;
    nRunLen		= 1;

    pDstBuf[nEncLen++] = chTag;

    chPrevData = SRAM[nEncoded++];

    while ( nEncoded < SRAM_SIZE && nEncLen < SRAM_SIZE - 133 )
    {
        chData = SRAM[nEncoded++];

        if ( chPrevData == chData && nRunLen < 256 )
            ++nRunLen;
        else{
            if ( nRunLen >= 4 || chPrevData == chTag )
            {
                pDstBuf[nEncLen++]	= chTag;
                pDstBuf[nEncLen++]	= chPrevData;
                pDstBuf[nEncLen++]	= nRunLen - 1;
            }else  {
                for ( nIdx = 0; nIdx < nRunLen; ++nIdx )
                    pDstBuf[nEncLen++] = chPrevData;
            }

            chPrevData	= chData;
            nRunLen		= 1;
        }
    }
    if ( nRunLen >= 4 || chPrevData == chTag )
    {
        pDstBuf[nEncLen++]	= chTag;
        pDstBuf[nEncLen++]	= chPrevData;
        pDstBuf[nEncLen++]	= nRunLen - 1;
    }else  {
        for ( nIdx = 0; nIdx < nRunLen; ++nIdx )
            pDstBuf[nEncLen++] = chPrevData;
    }

    /*-------------------------------------------------------------------*/
    /*  Write a SRAM data                                                */
    /*-------------------------------------------------------------------*/

    /* Open SRAM file */
    fp = fopen(fileName, "wb" );
    if ( fp == NULL )
        return(-1);

    /* Write SRAM data */
    fwrite( pDstBuf, nEncLen, 1, fp );

    /* Close SRAM file */
    fclose( fp );

    /* Successful */
    return(0);
}

int InfoNES_Menu()
{
    return nesThreadRun ? 0 : -1;
}

void InfoNES_SoundOutput(int samples, BYTE *wave1, BYTE *wave2, BYTE *wave3, BYTE *wave4, BYTE *wave5)
{
    int i;
    unsigned char wav;
    if(0 == pcmBufSize)
    {
        pcmBuf = (unsigned char *)malloc(samples);
        if(NULL == pcmBuf)
        {
            qDebug()<<"malloc failed";
            return ;
        }
        pcmBufSize = samples;
    }
    else if(pcmBufSize < samples)
    {
        pcmBuf = (unsigned char *)realloc(pcmBuf, samples);
        if(NULL == pcmBuf)
        {
            qDebug()<<"realloc failed";
            return ;
        }
        pcmBufSize = samples;
    }

    for (i=0; i <samples; i++)
    {
        wav = (wave1[i] + wave2[i] + wave3[i] + wave4[i] + wave5[i]) / 5;
        //单声道 8位数据
        pcmBuf[i] = wav;
    }
    soundDevice->write((const char *)pcmBuf, samples);

    //Thread sleep for audio play time ms : 1000 * samples / (channel * bitWidth) / 44100
    int ms = 1000 * samples / (1 * 8) / 44100;
    QThread::msleep(ms);
}

void InfoNES_SoundInit()
{
    qDebug()<<"InfoNES_SoundInit";
}

int InfoNES_SoundOpen(int samples_per_sync, int sample_rate)
{
    qDebug()<< "InfoNES_SoundOpen " << "samples:" << samples_per_sync << " rate:" << sample_rate;
    QAudioDeviceInfo deviceInfo(QAudioDeviceInfo::defaultOutputDevice());

    //QAudioDeviceInfo defaultDeviceInfoIn = QAudioDeviceInfo::defaultInputDevice();
    QString strinNameDefault = deviceInfo.deviceName();

    qDebug()<<"available"<<strinNameDefault;

    QAudioFormat format;

//    format.setChannelCount(1);
//    format.setSampleSize(8);
//    format.setCodec("audio/pcm");
//    format.setSampleType(QAudioFormat::SignedInt);//fix ubuntu audio output
//    format.setByteOrder(QAudioFormat::LittleEndian);
//    format.setSampleRate(sample_rate);

//    if(! deviceInfo.isFormatSupported(format))
//    {
//        QMessageBox::information(applicationQWidget, "info", "output audio format not supported");
//        return -1;
//    }

    QAudioOutput *audioOutput = new QAudioOutput(deviceInfo, format, applicationQWidget);
    soundDevice = new NesSoundDevice((QObject*)applicationQWidget);
    soundDevice->open(QIODevice::ReadOnly | QIODevice::WriteOnly);

    audioOutput->start(soundDevice);

    return 0;
}

void InfoNES_SoundClose()
{
    if (NULL == soundDevice) {
        soundDevice->close();
        delete soundDevice;
        soundDevice = NULL;
    }

    if(NULL != pcmBuf)
    {
        free(pcmBuf);
        pcmBuf = NULL;
    }

    qDebug()<<"InfoNES_SoundClose";
}

void InfoNES_Wait()
{
}

//////////////////////////////////////////////////////////////////
NesThread::NesThread(QObject *parent) : QThread(parent)
{
    m_nRunFlag = 0;
}

void NesThread::stop()
{
    m_nRunFlag = 0;
    this->quit();
    this->wait();
}

void NesThread::run()
{
    m_nRunFlag = 1;
    InfoNES_Init();

    // Main loop
    while ( 1 == m_nRunFlag)
    {
        /*-------------------------------------------------------------------*/
        /*  To the menu screen                                               */
        /*-------------------------------------------------------------------*/
        if ( InfoNES_Menu() == -1 )
            break;  // Quit

        /*-------------------------------------------------------------------*/
        /*  Start a NES emulation                                            */
        /*-------------------------------------------------------------------*/
        InfoNES_Cycle(&m_nRunFlag);
    }

    // Completion treatment
    InfoNES_Fin();
    qDebug() << "stop the game";
}
