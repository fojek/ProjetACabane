#include "commKoyo.h"
#include <python2.7/Python.h>
#include <iostream>

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
    
    /* Vérification de résultat valide : */
    if(PyInt_AsLong(pResult) == -1) {
        printf("C++ : koyoReadIn : Timeout gere correctement.\n");
        return 0;
    }
    
    /* Conversion du résultat PyObject en bitset 24 */
    inputs = new std::bitset<24> (PyInt_AsLong(pResult));

    do {} while(flag != 0);

    /* Copie vers le singleton */
    if (flag == 0) {
        flag = 1;
        Inputs = inputs;
        flag = 0;
    }

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
    
    /* Vérification de résultat valide : */
    if(PyInt_AsLong(pResult) == -1) {
        printf("C++ : koyoReadOut : Timeout gere correctement.\n");
        return 0;
    }
    /* Conversion du résultat PyObject en bitset 18 */
    outputs = new std::bitset<18> (PyInt_AsLong(pResult));

    do {} while(flag != 0);

    /* Copie vers le singleton */
    if (flag == 0) {
        flag = 1;
        Outputs = outputs;
        flag = 0;
    }

    /* Il faudrait gérer un résultat mauvais, ce n'est pas le cas pour le moment */
    return 1;
}

/* Ecriture des sorties */
int Koyo::koyoWriteOut()
{
    do {} while(flag != 0);

    /* Copie vers le singleton */
    if (flag == 0) {
        flag = 1;
        int i;
        
		/* Variables requises pour l'encapsulation */
		PyObject *pName, *pModule, *pDict, *pFunc, *pArg;

		/* Préparation de l'exécution du script Python */
		PyRun_SimpleString ("import sys; sys.path.insert(0, '/home/ProjetCabane')");
		pName = PyString_FromString("commKoyo");
		pModule = PyImport_Import(pName);
		pDict = PyModule_GetDict(pModule);
		pFunc = PyDict_GetItemString(pDict, "WriteOutput");
		pArg = PyTuple_New(2);
		
        /* On verifie si un input a change */
        for(i=0; i<17; i++) {
            if(Outputs->test(i) != Outputs_buffer->test(i)){
                printf("Input %i doit etre mis a jour.\n", i);
                
                /* Exécution du script et récupération du résultat */
                PyTuple_SetItem(pArg, 0, PyInt_FromLong(i));
                PyTuple_SetItem(pArg, 1, PyInt_FromLong(Outputs_buffer->test(i)));
                
				PyObject *pResult = PyObject_CallObject(pFunc, pArg);
				//Py_DECREF(pArg);
            }
        }

        /* Ceci copie l'etat actuel dans le buffer */
        //Outputs_buffer = Outputs;
        /*
        Outputs_buffer->none();
        for(i=0; i<17; i++) {
            if(Outputs->test(i)){
                Outputs_buffer->set(i);
            }
        }*/
        flag = 0;
    }

    /* Il faudrait gérer un résultat mauvais, ce n'est pas le cas pour le moment */
    return 1;
}

