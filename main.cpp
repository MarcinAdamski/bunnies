#include <iostream>
#include <stdio.h>
#include "CFarm.h"
#include "CBunny.h"
#include <cstdlib>
#include <time.h>
#include <Windows.h>
#include <list>

//test klasy bunny
void test(void)
{
	std::cout << "Tworze krolika\n";
	bunny nowy;
	bunny nowy2;
	std::cout << "plec: " << nowy.pokazPlec() << ",  mutant: " << nowy.pokazCzyMutant() << ", wiek: " << nowy.pokazWiek() << ",avatar: " << nowy.pobierzAvatar() << std::endl;
	nowy.losujMutacje();
	nowy.losujPlec();
	nowy.zmienAvatar();
	std::cout << "plec: " << nowy.pokazPlec() << ",  mutant: " << nowy.pokazCzyMutant() << ", wiek: " << nowy.pokazWiek() << ",avatar: " << nowy.pobierzAvatar() << std::endl;
	std::cout << "plec: " << nowy2.pokazPlec() << ",  mutant: " << nowy2.pokazCzyMutant() << ", wiek: " << nowy2.pokazWiek() << ",avatar: "<< nowy2.pobierzAvatar()<<std::endl;
	nowy2.losujMutacje();
	nowy2.losujPlec();
	nowy2.zwiekszWiek();
	nowy2.zmienAvatar();
	std::cout << "plec: " << nowy2.pokazPlec() << ",  mutant: " << nowy2.pokazCzyMutant() << ", wiek: " << nowy2.pokazWiek() << ",avatar: " << nowy2.pobierzAvatar() << std::endl;
	nowy2.zarazenieKrolika();
	nowy2.zmienAvatar();
	std::cout << "plec: " << nowy2.pokazPlec() << ",  mutant: " << nowy2.pokazCzyMutant() << ", wiek: " << nowy2.pokazWiek() << ",avatar: " << nowy2.pobierzAvatar() << std::endl;
	std::cout << "test losowania plci:\n";
	for (int i = 0; i < 10; i++)
	{
		nowy2.losujPlec();
		std::cout << "plec: " << nowy2.pokazPlec() << "\n";
	}
}

//test klasy Farm
void test2(void)
{
	Farm FarmaKrolikow;
	FarmaKrolikow.initFerma();
	FarmaKrolikow.dodajKrolika();
	FarmaKrolikow.pokazSiatke();
	for (int i = 0; i < 5; i++)
	{
		FarmaKrolikow.ruchKrolikow();
		FarmaKrolikow.pokazSiatke();

		getchar();
	}
}


void zacznijOdstrzal(Farm *farma)
{
	farma->odstrzal();
}
void zacznijSymulacje(Farm *farma)
{
	farma->startSymulacji();
}


int main()
{
	srand(time(NULL));
	//test();
	//test2(); 

	Farm FarmaKrolikow;
	std::thread first(zacznijSymulacje, &FarmaKrolikow);
	std::thread second(zacznijOdstrzal, &FarmaKrolikow);
	first.join();
	second.join();


	getchar();
	return 0;
}


