#include "interfaceoperateur.h"
#include "global.hpp"
#include <QApplication>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
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

/* Boucle principale */
int main(int argc, char *argv[])
{
	/* Initialisation variables QT */
    QApplication::addLibraryPath("pluginsFolder");
	QApplication a(argc, argv);
	InterfaceOperateur w;

	/* Démarrage du GUI */
	w.show();

	return a.exec();
}
