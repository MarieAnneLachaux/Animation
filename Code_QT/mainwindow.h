#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myglwidget.h"
#include <QSlider>
#include<QPushButton>
#include<QScrollArea>
#include<QListWidget>
#include<QListWidgetItem>
#include<QTimer>
#include<QLineEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    myGLwidget *widget1;
    myGLwidget *widget2;


private:
    Ui::MainWindow *ui;
    QSlider *slider1;
    QSlider *slider2;
    QListWidget *listview;
    QListWidget *listview2;
    QListWidget *listview3;
    QPushButton *play1;
    QPushButton *play2;
    QPushButton *chooseDebut;
    QPushButton *chooseFin;
    QPushButton *create;
    QTimer *m_timer;
    QTimer *m_timer2;
    QScrollArea *scroll;
    QLineEdit *texte;
    QLineEdit *texte2;
    int player1;
    int player2;



    bool continuer;

public slots:
    void mySlot();
    void mySlot2(int p);
    void slotPlay1();
    void mySlot2();
    void mySlot22(int p);
    void slotPlay2();
    void slotChooseEnd();
     void slotChooseDebut();
    void generate();

};

#endif // MAINWINDOW_H
