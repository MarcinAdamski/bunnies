#ifndef CFARM_H
#define CFARM_H
#include "CBunny.h"
#include <list>
#include <fstream>
#include <mutex>          // std::mutex
#include <thread>

const int wymiar = 40;
const int limitKrolikow = 500;

class Farm
{
private:
	int liczbaSamiczek;
	int liczbaMutantow;
	char ferma[wymiar][wymiar];
public:
	std::list<bunny> BunnyList;
	std::mutex mtx;
	//metody
	void initFerma(void);
	int startSymulacji(void);   // 1 watek
	int odstrzal(void);         // 2 watek
	void przygotowanieSymulacji(void); //pierwsze 5 krolikow
	int sprawdzNarodzenia(void); // czy jest samiec i ile samiczek
	int sprawdzZgony(void); // kasacja krolików starszych niz 10 lat (50 lat dla mutantow)
	void dodajKrolika(); // dodanie krolika do listy
	int zarazanie(void); // mutanty w akcji
	void informacjeFarmy(int rok, int narodzin, int zgonow); // wyswietlanie danych symulacji
	void zwiekszWiek(void);
	void smiercKrolikow(void);
	bool brakPlodnosciPopulacji(void);
	//metody związane z tablica ferma
	void dodajDoSiatki();
	void pokazSiatke(void);
	void ruchKrolikow(void);
	//metody dla zmiennych
	void dodajSamiczke(void);
	void dodajMutanta(void);
	int pokazSamiczki(void) { return liczbaSamiczek; }
	int pokazMutanty(void) { return liczbaMutantow; }
	
};

#endif
