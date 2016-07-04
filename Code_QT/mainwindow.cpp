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

    player1=0;
    player2=0;
    ui->setupUi(this);
    widget1= new myGLwidget(60,this,"opengl",1);
    widget1->resize(400,400);
    widget1->move(10,100);


   slider1= new QSlider(Qt::Horizontal,this);
   slider1->setMinimum(0);
   slider1->setMaximum(118);
   slider1->setGeometry(10, 540, 400, 20);

  play1=new QPushButton("Play",this);
  play1->move(155,35);
  play1->resize(100,30);

chooseDebut=new QPushButton("Choose\nBegining",this);
chooseDebut->move(60,585);
chooseDebut->resize(100,60);

chooseFin=new QPushButton("Choose\nEnd",this);
chooseFin->move(250,585);
chooseFin->resize(100,60);


listview=new QListWidget(this);
listview->move(445,100);
listview->resize(150,150);

listview2=new QListWidget(this);
listview2->move(605,100);
listview2->resize(150,150);

//listview3=new QListWidget(this);
//listview3->move(790,100);
//listview3->resize(400,400);

texte = new QLineEdit(this);
texte->setText("Position: " + QString::number(widget1->m));
texte->move(10,510);
texte->resize(120,25);
texte->setReadOnly(true);
texte->setStyleSheet("* {background-color:rgba(0,0,0,0);border: 1px solid transparent;}");


widget2= new myGLwidget(60,this,"opengl",2);
widget2->move(-100,-100);


slider2= new QSlider(Qt::Horizontal,this);
slider2->setMinimum(0);
slider2->setMaximum(118);
slider2->setGeometry(790, 540, 400, 20);

play2=new QPushButton("Play",this);
play2->move(935,35);
play2->resize(100,30);

texte2 = new QLineEdit(this);
texte2->setText("Position: " + QString::number(widget2->m));
texte2->move(790,510);
texte2->resize(120,25);
texte2->setReadOnly(true);
texte2->setStyleSheet("* {background-color:rgba(0,0,0,0);border: 1px solid transparent;}");



create=new QPushButton("Synthesize\nMovement",this);
create->move(550,270);
create->resize(100,60);

//listview->addScrollBarWidget(widget1,Qt::AlignCenter);

  m_timer=new QTimer(this);
  m_timer2=new QTimer(this);
  QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(mySlot()));
  QObject::connect(slider1, SIGNAL(valueChanged(int)), this, SLOT(mySlot2(int)));
  QObject::connect(play1, SIGNAL(clicked()), this, SLOT(slotPlay1()));
  QObject::connect(chooseDebut, SIGNAL(clicked()), this, SLOT(slotChooseDebut()));
  QObject::connect(chooseFin, SIGNAL(clicked()), this, SLOT(slotChooseEnd()));

  QObject::connect(m_timer2, SIGNAL(timeout()), this, SLOT(mySlot2()));
  QObject::connect(slider2, SIGNAL(valueChanged(int)), this, SLOT(mySlot22(int)));
  QObject::connect(play2, SIGNAL(clicked()), this, SLOT(slotPlay2()));

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
    if ( player1==0){
        m_timer->start(100);
        play1->setText("Pause");
        player1=1;}
    else{
        m_timer->stop();
        play1->setText("Play");
        player1=0;
    }
}


void MainWindow::mySlot2() {
    if (widget2->m<118){
      widget2->m=(widget2->m+1);
    }

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
    if ( player2==0){
        m_timer2->start(100);
        play2->setText("Pause");
        player2=1;}
    else{
        m_timer2->stop();
        play2->setText("Play");
        player2=0;
    }
}

void MainWindow::slotChooseDebut() {
    listview->clear();
    QListWidgetItem * item= new QListWidgetItem();
    item->setSizeHint(QSize(150,150));
    myGLwidget * glwidget = new myGLwidget(60,this);
        glwidget->m=slider1->value();
        listview->addItem(item);
        listview->setItemWidget(item,glwidget);

}


void MainWindow::slotChooseEnd() {
    listview2->clear();
    QListWidgetItem * item= new QListWidgetItem();
    item->setSizeHint(QSize(150,150));
    myGLwidget * glwidget = new myGLwidget(60,this);
        glwidget->m=slider1->value();
        listview2->addItem(item);
        listview2->setItemWidget(item,glwidget);

}


void MainWindow::generate() {
   widget2->resize(400,400);
   widget2->move(790,100);
}

