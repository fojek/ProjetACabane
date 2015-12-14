/**********************
/* commKoyo.h
/* --------
/* Classe pour le niveau des bassins 
/* --------
/* 
/* À Faire :
/*  - Écrire la fonction koyoWriteOut()
/*  - Doubler les variables, car il y a deux bassins
/*  - Mettre les numéros de 'Pin' dans la création de l'instance
/***********************/

#ifndef COMMKOYO_H
#define COMMKOYO_H

/* Requis pour les array de bits */
#include <bitset>

/* Classe pour la communication avec Koyo */
class Koyo {
public:
	int addresseIP;
	/* 20 entrées, octal : 0-7, 10-17, 20-23. 8,9,18,19 n'existent pas */
	std::bitset<24> *Inputs; 
	/* 16 sorties, octal : 0-7, 10-17. 8,9 n'existent pas */
	std::bitset<18> *Outputs;
	int koyoReadIn(void);
	int koyoReadOut(void);
	int koyoWriteOut(void);
	static Koyo& Instance();

private:
	Koyo& operator = (const Koyo&) {}
	Koyo (const Koyo&) {}
	static Koyo m_instance;
	Koyo(int ip) : addresseIP(ip) {
		Inputs = new std::bitset<24>;
	}
};

/* Lecture des entrées */
int Koyo::koyoReadIn()
{
	/* Contenant temporaire pour les entrées */
	std::bitset<24> *inputs;

	/* Variables requises pour l'encapsulation */
	PyObject *pName, *pModule, *pDict, *pFunc;
	
	/* Préparation de l'exécution du script Python */
	PyRun_SimpleString ("import sys; sys.path.insert(0, '/home/ProjetCabane')");
	pName = PyString_FromString("commKoyo");
	pModule = PyImport_Import(pName);
	pDict = PyModule_GetDict(pModule);
	pFunc = PyDict_GetItemString(pDict, "ReadIn");

	/* Exécution du script et récupération du résultat */
	PyObject *pResult = PyObject_CallObject(pFunc, NULL);
	
	/* Conversion du résultat PyObject en bitset 24 */
	inputs = new std::bitset<24> (PyInt_AsLong(pResult));

	/* Copie vers le singleton */
	Inputs = inputs;
	
	/* Il faudrait gérer un résultat mauvais, ce n'est pas le cas pour le moment */
	return 1;
}

/* Lecture des sorties */
int Koyo::koyoReadOut()
{
	/* Contenant temporaire pour les entrées */
	std::bitset<18> *outputs;

	/* Variables requises pour l'encapsulation */
	PyObject *pName, *pModule, *pDict, *pFunc;
	
	/* Préparation de l'exécution du script Python */
	PyRun_SimpleString ("import sys; sys.path.insert(0, '/home/ProjetCabane')");
	pName = PyString_FromString("commKoyo");
	pModule = PyImport_Import(pName);
	pDict = PyModule_GetDict(pModule);
	pFunc = PyDict_GetItemString(pDict, "ReadOut");
	
	/* Exécution du script et récupération du résultat */
	PyObject *pResult = PyObject_CallObject(pFunc, NULL);
	
	/* Conversion du résultat PyObject en bitset 18 */
	outputs = new std::bitset<18> (PyInt_AsLong(pResult));
	
	/* Copie vers le singleton */
	Outputs = outputs;
	
	/* Il faudrait gérer un résultat mauvais, ce n'est pas le cas pour le moment */
	return 1;
}

#endif // COMMKOYO_H