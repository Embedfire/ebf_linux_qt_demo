#ifndef NESSCREENWIDGET_H
#define NESSCREENWIDGET_H

#include <QObject>
#include <QMutex>
#include <QImage>
#include <QOpenGLWidget>
#include <QWidget>

class NesScreenWidget : public QWidget
{
    Q_OBJECT
public:
    NesScreenWidget(QWidget *parent);
    ~NesScreenWidget();

public slots:
    void loadFrame();

private:
    QImage image;
    QMutex mutex;

protected:
    void paintEvent(QPaintEvent *) override;
};

#endif // NESSCREENWIDGET_H
