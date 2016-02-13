/**********************
 * bassin.h
 * --------
 * Classe pour le niveau des bassins
 * --------
 *
 * À Faire :
 *  - Doubler les variables, car il y a deux bassins
 *  - Mettre les numéros de 'Pin' dans la création de l'instance
 ***********************/

#ifndef BASSIN_H
#define BASSIN_H

/* Vitesse du son en mm/µs */
#define VITESSE_SON_mmus	0.330

/* Définition de la classe pour les bassins */
class Bassin {
public:
	int address;
	double niveau;
	std::string uniteIng;
	int distance(void);
	double distanceMax;
	static Bassin& Instance();
private:
	Bassin& operator = (const Bassin&) {}
	Bassin (const Bassin&) {}
	static Bassin m_instance;

	Bassin(int a, double d, std::string u) : address(a), distanceMax(d), uniteIng(u) {}
};

/* Acquisition de la distance devant le transceiver ultrason */
int Bassin::distance(){

	return 1;
}

#endif // BASSIN_H
