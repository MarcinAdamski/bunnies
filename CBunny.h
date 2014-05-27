#ifndef BUNNY_H
#define BUNNY_H

//klasa kroliczka

class bunny
{
private:
	bool sexMale;
	int age;
	bool radioactive_mutant_vampire_bunny;
	char avatar;
	int pozX, pozY;
public:
	//konstruktor
    //bunny(bool sex, bool mutant) { sexMale = sex; age = 1; radioactive_mutant_vampire_bunny = mutant; }
	//bunny() { sexMale = losujPlec(); age = 1; radioactive_mutant_vampire_bunny = losujMutacje(); }
	bunny() { sexMale = true; 
	          age = 1; 
			  radioactive_mutant_vampire_bunny = false; 
			  avatar = 'm';
			  pozX = pozY = 0; }
	~bunny() {};
	//metody
	void zwiekszWiek(void);
	void zarazenieKrolika(void);
	void zmienPozycje(int x, int y);
	void zmienAvatar(void);
	// metody odczytu pól
	int pokazWiek(void);
	bool pokazPlec(void);
	bool pokazCzyMutant(void);
	int pobierzPozycjeX(void);
	int pobierzPozycjeY(void);
	char pobierzAvatar(void);
	//metody dla stworzenia krolika
	void losujPlec(void);
	void losujMutacje(void);
};



#endif
