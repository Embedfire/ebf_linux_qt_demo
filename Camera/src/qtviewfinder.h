#ifndef QTVIEWFINDER_H
#define QTVIEWFINDER_H

#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QToolButton>

#include "cameraconfig.h"

class QtViewFinder : public QCameraViewfinder
{
    Q_OBJECT

public:
    explicit QtViewFinder(QWidget *parent = nullptr);
    ~QtViewFinder();

private:
    CameraConfig *config;
    QLabel *show_image;
    QPushButton *m_returnbtn;
    QPushButton *take_picture;
    QToolButton *show_config;
    QTimer *timer_hide;

    QPixmap m_pixmapMenu;

protected:
    bool m_bZoom;
    qreal m_scaleX;
    qreal m_scaleY;

    int   m_nBaseWidth;
    int   m_nBaseHeight;

private slots:
    void on_returnbtn_clicked(bool clicked);
    void on_take_picture();
    void on_show_config();
    void on_hide_image();

public slots:
    void loadImage(QString image_path);
    void setEnabledTake(bool enable);
    void setSize(int width, int height);

signals:
    void returnbtn_clicked_signal();
    void take_picture_signal();

};

#endif // QTVIEWFINDER_H
