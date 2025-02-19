#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.setWindowTitle("Tema 1 - LU e LDP");
    w.resize(800, 600);
    w.show();
    return app.exec();
}
