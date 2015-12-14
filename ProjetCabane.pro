#-------------------------------------------------
#
# Project created by QtCreator 2015-11-06T22:58:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjetCabane
TEMPLATE = app


SOURCES += main.cpp\
        interfaceoperateur.cpp

HEADERS  += interfaceoperateur.h \
    global.hpp \
    bassin.h

FORMS    += interfaceoperateur.ui

LIBS	 += -lwiringPi \
         -lpython2.7

