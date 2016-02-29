#-------------------------------------------------
#
# Project created by QtCreator 2015-11-06T22:58:58
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = ProjetCabane
TEMPLATE = app


SOURCES += main.cpp\
        interfaceoperateur.cpp \
        commKoyo.cpp \
        lib/QCustomPlot/qcustomplot.cpp

HEADERS += interfaceoperateur.h \
        global.hpp \
        bassin.h \
        lib/QCustomPlot/qcustomplot.h \
        commKoyo.h

FORMS   += interfaceoperateur.ui

LIBS	+= C:\MySQL\lib\libmysql.lib

INCLUDEPATH += $$QT_PROJECT_DIR/lib/QCustomPlot/ \
               C:\MySQL\include
