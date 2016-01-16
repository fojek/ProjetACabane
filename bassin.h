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

	/* Requis pour le calcul de la distance */
	int i, echoStart, echoEnd;

	/* Envoi du trig : ON pendant 200ms, puis OFF */
	digitalWrite(TRIG, 1);
	delay(200);
	digitalWrite(TRIG, 0);
	
	/* On attend le départ de l'impulsion d'écho*/
	i = millis(); 
	do {
		/* Retourne -1 si on manque l'impulsion, pour éviter une boucle sans fin */
		if ((millis() - i) > 200) return 0;
	} while (digitalRead(ECHO) == FALSE);
    
	/* Précisément, ceci est le départ de l'impulsion d'écho */
	echoStart = micros();

	/* On attend la fin de l'impulsion d'écho */
	i = millis(); 
	do {
		/* Retourne -1 si on manque l'impulsion, pour éviter une boucle sans fin */
		if ((millis() - i) > 200) return -1;
	} while (digitalRead(ECHO) == TRUE);

	/* Précisément, ceci est la fin de l'impulsion d'écho */
	echoEnd = micros();

	/* Calcul de la distance en pourcentage P/R au fond du bassin */
	niveau = ((echoEnd-echoStart)*VITESSE_SON_mmus)/distanceMax;

	/* Oops : */
	if(niveau>100) { niveau = 100; }

	return 1;
}

#endif // BASSIN_H
