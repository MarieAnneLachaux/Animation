#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(1200,700);
    w.setWindowTitle("Movement Synthesis");
    w.show();


    return a.exec();
}
