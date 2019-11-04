#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#ifdef Q_OS_WIN32
#include <QOpenGLWidget>
#endif
#include <QImage>
#include <QTimer>

#include "fce.h"
#include "nes.h"

#ifdef Q_OS_WIN32
class NesGamePannel : public QOpenGLWidget {
#else
class NesGamePannel : public QWidget {
#endif
    Q_OBJECT
public:
    NesGamePannel(QWidget *parent);
    ~NesGamePannel();

    void LoadGame(const QString &fileName);
    void Stop();

    void clearBackground(int c);

    void addPoint(int x, int y, int c);

    void display();
    void setFlag(Flags flag);
    void removeFlag(Flags flag);
    bool testFlag(Flags flag);

private slots:
    void SltStart();

protected:
    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

private:
    uint32_t m_nImageData[256 * 240];
    QImage  *m_imageBuff;
    QImage   m_imageDisplay;
    int      m_nKeyMap;

    QTimer  *m_timer;
    bool     m_bInit;

protected:

};

#endif // GAMEWIDGET_H
