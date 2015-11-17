// Classe pour le traitement des I/O pour la lecture du niveau des bassins

#define VITESSE_SON_mmus	0.330

class Bassin {
	static Bassin& Instance();
	double distanceMax;

public:
	int address;
	double niveau;
	std::string uniteIng;
	Bassin& operator = (const Bassin&) {}
	Bassin (const Bassin&) {}
	
	static Bassin m_instance;
	
	Bassin(int a, double d, std::string u) : address(a), distanceMax(d), uniteIng(u) {}

	void distance(void);
};

int Bassin::distance(){

        int i, echoStart, echoEnd;

	digitalWrite(TRIG, 1);
        delay(200);
        digitalWrite(TRIG, 0);
	
	i = millis(); 
        do {
		if ((millis() - i) > 200) return 0;
	} while (digitalRead(ECHO) == FALSE);
        
	echoStart = micros();

	i = millis(); 
        do {
		if ((millis() - i) > 200) return -1;
	} while (digitalRead(ECHO) == TRUE);

        echoEnd = micros();

        niveau = ((echoEnd-echoStart)*VITESSE_SON_mmus)/distanceMax;

        if(niveau>100) { niveau = 100; }

	return 1;
}
