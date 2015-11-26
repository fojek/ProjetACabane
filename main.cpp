#include "interfaceoperateur.h"
#include "global.hpp"
#include <QApplication>
#include <stdio.h>
#include <stdint.h>
#include <wiringPi.h>
#include <gertboard.h>
#include <assert.h>
#include <python2.7/Python.h>
#include <string.h>
#include <iostream>
#include "commKoyo.h"
#include "bassin.h"

using namespace std;

long int echoStart=0;
long int echoEnd=0;
long int echoDuration=0;
int bassin2Level=0;

Bassin Bassin::m_instance=Bassin(1, 100, "cm");

Bassin& Bassin::Instance(){
    return m_instance;
}

Koyo Koyo::m_instance=Koyo(10);

Koyo& Koyo::Instance(){
	return m_instance;
}

PI_THREAD (threadBassin)
{
    Bassin & bassin2=Bassin::Instance();
    do
    {
        bassin2.distance();
        printf("distance : %f\n", bassin2.niveau);
        delay(500);
    } while(TRUE);
}

PI_THREAD (commPLC)
{
    Koyo & koyo=Koyo::Instance();
    Py_Initialize();
    do
    {
        koyo.koyoReadIn();
	koyo.koyoReadOut();

	std::cout << "E/S : " << (*koyo.Inputs) << " | " << (*koyo.Outputs) << "\n"; 

        delay(1000);

    } while(TRUE);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InterfaceOperateur w;
    wiringPiSetup () ;
    pinMode (0, OUTPUT) ;
    pinMode (TRIG, OUTPUT) ;
    pinMode (ECHO, INPUT) ;

    piThreadCreate(threadBassin);
    piThreadCreate(commPLC);

    w.show();

    return a.exec();
}
