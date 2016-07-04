#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QtOpenGL>
#include <QOpenGLWidget>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "Arbre.h"
#include "Matrix.h"
#include "Vec3.h"
#include <QTime>

class myGLwidget: public QOpenGLWidget
{
     Q_OBJECT
public:
    explicit myGLwidget(int framesPerSecond = 0, QWidget *parent = 0, char *name = 0);
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void keyPressEvent( QKeyEvent *keyEvent );
    void repaindre();

    void drawSphere(int n_horizontales, int n_verticales);
    void glSphere (float x, float y, float z, float radius);
    int m;

public slots:
    virtual void timeOutSlot();


private:
    QTimer *t_Timer;
    Arbre arbre;


};

#endif // MYGLWIDGET_H
