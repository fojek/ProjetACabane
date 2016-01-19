/**********************
 * commKoyo.h
 * --------
 * Classe pour le niveau des bassins
 * --------
 *
 * À Faire :
 *  - Écrire la fonction koyoWriteOut()
 *  - Doubler les variables, car il y a deux bassins
 *  - Mettre les numéros de 'Pin' dans la création de l'instance
 ***********************/

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
    std::bitset<18> *Outputs_buffer;
    /* Pour empecher de lire une variable utilisee dans un autre thread */
    int flag = 0;

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

#endif // COMMKOYO_H
