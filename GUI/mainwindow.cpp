#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myglwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //myGLwidget *widget;
    myGLwidget *widget= new myGLwidget(0,0,0);
    widget->initializeGL();
    //widget->resizeGL(10,10);
    //widget->paintGL();

}

MainWindow::~MainWindow()
{
    delete ui;
}
