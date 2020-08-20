#include <QApplication>
#include "browserwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    BrowserWindow w;
#ifdef __arm__
    w.showFullScreen();
#else
    w.resize(800, 480);
    w.show();
#endif

    return a.exec();
}
