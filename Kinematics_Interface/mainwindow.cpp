#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myglwidget.h"
#include <QPushButton>
#include<stdio.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   QPalette Pal(palette());

     //set black background
    Pal.setColor(QPalette::Background, Qt::black);


    ui->setupUi(this);
    widget1= new myGLwidget(60,this,"opengl");
    widget1->resize(400,400);
    widget1->move(10,100);

    //this->show();

   slider1= new QSlider(Qt::Horizontal,this);
   slider1->setMinimum(0);
   slider1->setMaximum(118);
   slider1->setGeometry(10, 540, 400, 20);

  play1=new QPushButton("Play",this);
  play1->move(60,35);
  play1->resize(100,30);

 pause1=new QPushButton("Pause",this);
 pause1->move(250,35);
 pause1->resize(100,30);

choose=new QPushButton("Choose",this);
choose->move(160,600);
choose->resize(100,30);

listview=new QListWidget(this);
listview->move(450,100);
listview->resize(150,500);

texte = new QLineEdit(this);
texte->setText("Position:" + QString::number(widget1->m));
texte->move(10,510);
texte->resize(120,25);
texte->setReadOnly(true);


widget2= new myGLwidget(60,this,"opengl");
widget2->resize(400,400);
widget2->move(610,100);

slider2= new QSlider(Qt::Horizontal,this);
slider2->setMinimum(0);
slider2->setMaximum(118);
slider2->setGeometry(610, 540, 400, 20);

play2=new QPushButton("Play",this);
play2->move(660,35);
play2->resize(100,30);

pause2=new QPushButton("Pause",this);
pause2->move(850,35);
pause2->resize(100,30);

texte2 = new QLineEdit(this);
texte2->setText("Position:" + QString::number(widget2->m));
texte2->move(610,510);
texte2->resize(120,25);
texte2->setReadOnly(true);

create=new QPushButton("Create",this);
create->move(1000,35);
create->resize(100,30);

//listview->addScrollBarWidget(widget1,Qt::AlignCenter);

  m_timer=new QTimer(this);
  m_timer2=new QTimer(this);
  QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(mySlot()));
  QObject::connect(slider1, SIGNAL(valueChanged(int)), this, SLOT(mySlot2(int)));
  QObject::connect(play1, SIGNAL(clicked()), this, SLOT(slotPlay1()));
  QObject::connect(pause1, SIGNAL(clicked()), this, SLOT(slotPause1()));
  QObject::connect(choose, SIGNAL(clicked()), this, SLOT(slotChoose()));

  QObject::connect(m_timer2, SIGNAL(timeout()), this, SLOT(mySlot2()));
  QObject::connect(slider2, SIGNAL(valueChanged(int)), this, SLOT(mySlot22(int)));
  QObject::connect(play2, SIGNAL(clicked()), this, SLOT(slotPlay2()));
  QObject::connect(pause2, SIGNAL(clicked()), this, SLOT(slotPause2()));

  QObject::connect(create, SIGNAL(clicked()), this, SLOT(generate()));



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mySlot() {
    if (widget1->m<118)
    widget1->m=(widget1->m+1);

    else widget1->m=0;
    slider1->setValue(widget1->m);
    texte->setText("Position:" + QString::number(widget1->m));
  update();
}

void MainWindow::mySlot2(int p) {
    widget1->m=p;
    texte->setText("Position:" + QString::number(widget1->m));
    update();
}

void MainWindow::slotPlay1() {
    m_timer->start(100);
}

void MainWindow::slotPause1() {
    m_timer->stop();
}

void MainWindow::mySlot2() {
    if (widget2->m<118)
    widget2->m=(widget2->m+1);

    else widget2->m=0;
    slider2->setValue(widget2->m);
    texte2->setText("Position:" + QString::number(widget2->m));
  update();
}

void MainWindow::mySlot22(int p) {
    widget2->m=p;
    texte2->setText("Position:" + QString::number(widget2->m));
    update();
}

void MainWindow::slotPlay2() {
    m_timer2->start(100);
}

void MainWindow::slotPause2() {
    m_timer2->stop();
}

void MainWindow::slotChoose() {

    QListWidgetItem * item= new QListWidgetItem();
    item->setSizeHint(QSize(150,150));
    myGLwidget * glwidget = new myGLwidget(60,this);
        glwidget->m=slider1->value();
        listview->addItem(item);
        listview->setItemWidget(item,glwidget);

}

void MainWindow::generate() {

}

