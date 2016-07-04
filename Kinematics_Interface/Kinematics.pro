#-------------------------------------------------
#
# Project created by QtCreator 2016-06-19T15:15:15
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kinematics
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myglwidget.cpp \
    Arbre.cpp

HEADERS  += mainwindow.h \
    myglwidget.h \
    Arbre.h \
    Matrix.h \
    Vec3.h

FORMS    += mainwindow.ui

DISTFILES += \
    data/walk_turn_180.bvh \
    swagger.svml

RESOURCES += \
    data.qrc


