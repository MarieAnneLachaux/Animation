#include "myGLwidget.h"

using namespace std;

myGLwidget::myGLwidget(int framesPerSecond, QWidget *parent, char *name): QOpenGLWidget(parent)
{
    setWindowTitle(QString::fromUtf8(name));
    if(framesPerSecond == 0)
        t_Timer = NULL;
    else
    {
        int seconde = 1000; // 1 seconde = 1000 ms
        int timerInterval = seconde / framesPerSecond;
        t_Timer = new QTimer(this);
        connect(t_Timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
        t_Timer->start( timerInterval );
    }

    m=0;
}

void myGLwidget::initializeGL(){
    glShadeModel(GL_SMOOTH);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

        arbre.loadBVH("/Users/etcheverrymayalen/TRAVAIL/TELECOM_2A/IGR205/InverseKinematics/data/walk_turn_180.bvh");
        arbre.generateSvml();
}

void myGLwidget::resizeGL(int width, int height){
    if(height == 0)
            height = 1;
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //gluPerspective(90.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

}

void myGLwidget::drawSphere(int n_horizontales, int n_verticales) {
    int i, j;

    //n_horizontales= nombre de ligne horizontales
    for(i = 0; i <= n_horizontales; i++) {
        double theta0 = M_PI * (double) (i - 1) / n_horizontales;
        double z0  = cos(theta0);
        double r0 =  sin(theta0); //rayon du petit cercle sur lequel est M0

        double theta1 = M_PI * (double) i / n_horizontales;
        double z1 = cos(theta1);
        double r1 = sin(theta1);

        glBegin(GL_TRIANGLE_STRIP);

        for(j = 0; j <= n_verticales; j++) {
            double phi = 2 * M_PI * (double) (j - 1) / n_verticales;
            double x = cos(phi);
            double y = sin(phi);

            glNormal3f(x * r0, y * r0, z0);
            glColor3f(0.28, 0.5, 1.0);
            glVertex3f(x * r0, y * r0, z0);

            glNormal3f(x * r1, y * r1, z1);
            glColor3f(0.28, 0.5, 1.0);
            glVertex3f(x * r1, y * r1, z1);
        }

        glEnd();
    }

}

void myGLwidget::glSphere (float x, float y, float z, float radius) {
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glTranslated(x,y,z);
    glScaled(radius,radius,radius);
    drawSphere(30, 30); //sphere
    glPopMatrix();
}

void myGLwidget::paintGL(){
    //int m = (QTime::currentTime().msec())%119;  //(int)(currentTime/100)%119;
    //int m =0;
    //for ( int m=0;m<119;m+=10){



        for (int i =0;i<83;i++){
            glSphere(arbre.N[i]->p[m][0],arbre.N[i]->p[m][1],arbre.N[i]->p[m][2],0.01);
        }

        for (int i =1;i<83;i++){
        glLineWidth(1.0);
        glBegin(GL_LINES);
        glColor3f(0.28,0.5,1.0);
        glVertex3f (arbre.N[i]->p[m][0], arbre.N[i]->p[m][1], arbre.N[i]->p[m][2]);
        glVertex3f (arbre.N[arbre.N[i]->father]->p[m][0], arbre.N[arbre.N[i]->father]->p[m][1], arbre.N[arbre.N[i]->father]->p[m][2]);
            glEnd();}

            glSphere(arbre.N[83]->p[m][0],arbre.N[83]->p[m][1],arbre.N[83]->p[m][2],0.1);
       //}


}


void myGLwidget::keyPressEvent( QKeyEvent *keyEvent ){
    switch(keyEvent->key())
        {
            case Qt::Key_Escape:
                close();
                break;
        }
}


void myGLwidget::timeOutSlot()
{
}

void myGLwidget::repaindre(){
    update();
}


