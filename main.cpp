#include <QApplication>
#include <QtGui>
#include "mainwindow.h"
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow win;
    win.show();

    return app.exec();
}
