#include <iostream>
#include "commKoyo.h"
/* Lecture des entrées */
int Koyo::koyoReadIn()
{
    /* Contenant temporaire pour les entrées */
    std::bitset<24> *inputs;

    inputs = new std::bitset<24>;

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

    outputs = new std::bitset<18>;

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

        flag = 0;
    }

    /* Il faudrait gérer un résultat mauvais, ce n'est pas le cas pour le moment */
    return 1;
}

