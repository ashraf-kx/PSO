#-------------------------------------------------
#
# Project created by QtCreator 2016-02-11T21:38:12
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PSO
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    model.cpp \
    pso.cpp \
    particle.cpp\
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    model.h \
    pso.h \
    particle.h\
    qcustomplot.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    W_value.txt \
    X_value.txt \
    Y_value.txt
