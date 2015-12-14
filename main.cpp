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

/* Création du singleton pour les bassins */
Bassin Bassin::m_instance=Bassin(1, 100, "cm");

/* Fonction qui retourne l'addresse du singleton pour les bassins */
Bassin& Bassin::Instance(){
    return m_instance;
}

/* Création du singleton pour le Koyo */
Koyo Koyo::m_instance=Koyo(10);

/* Fonction qui retourne l'addresse du singleton pour le Koyo */
Koyo& Koyo::Instance(){
	return m_instance;
}

/* Thread d'acquisition du niveau des bassins */
PI_THREAD (threadBassin)
{
	/* Retour de l'addresse du singleton */
    Bassin & bassin2=Bassin::Instance();
	
	/* Boucle principale bassins */
    do
    {
		/* Recherche de la distance */
        bassin2.distance();
        printf("distance : %f\n", bassin2.niveau);
		
		/* La boucle s'effectue chaque 500 ms */
        delay(500);
    } while(TRUE);
}

/* Thread de communication avec le Koyo */
PI_THREAD (commPLC)
{
	/* Retour de l'addresse du singleton */
    Koyo & koyo=Koyo::Instance();
	
	/* Initialisation du module pour l'encapsulation Python */
    Py_Initialize();
	
	/* Boucle principale Koyo */
    do
    {
		/* À faire : écriture des sorties */
		koyo.koyoWriteOut();
		
		/* Acquisitionde l'état des E/S */
        koyo.koyoReadIn();
		koyo.koyoReadOut();

		std::cout << "E/S : " << (*koyo.Inputs) << " | " << (*koyo.Outputs) << "\n"; 

		/* La boucle s'effectue chaque 1000 ms */
        delay(1000);
    } while(TRUE);
}

/* Boucle principale */
int main(int argc, char *argv[])
{
    /* Initialisation variables QT */
	QApplication a(argc, argv);
    InterfaceOperateur w;
	
	/* Initialisation de wiringPi (entrées / sorties) */
    wiringPiSetup () ;
	
	/* Assignation et initialisation des entrées sorties */
	// Devra être adapté pour 2x ultrasons + 1x MCP3008
    pinMode (0, OUTPUT) ;
    pinMode (TRIG, OUTPUT) ;
    pinMode (ECHO, INPUT) ;

	/* Démarrages des threads */
    piThreadCreate(threadBassin);
    piThreadCreate(commPLC);

	/* Démarrage du GUI */
    w.show();

    return a.exec();
}
