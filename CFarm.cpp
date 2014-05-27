#include "CFarm.h"
#include "CBunny.h"
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <Windows.h>

using namespace std;

int Farm::startSymulacji() //tutaj bedzie glowne cialo symulacji
{
	int rok = 1;
	srand(time(NULL));
	cout << "                                    ---------------\n";
	cout << "                                  --===============--\n";
	cout << "                                --==Start symulacji==--\n";
	cout << "                                  --===============--\n";
	cout << "                                    ---------------\n";
	cout << "W kazdym momencie symulacji mozesz przeprowadzic odstrzal wciskajac 'k' + Enter\n";
	initFerma();
	przygotowanieSymulacji();
	do
	{
		mtx.lock();
		int narodzin = 0;
		int zgonow = 0;
		ruchKrolikow();
		narodzin = sprawdzNarodzenia();
		zgonow = sprawdzZgony();
		for (int j = 0; j < narodzin; j++)
		{
			dodajKrolika();
		}
		zarazanie();
		informacjeFarmy(rok, narodzin, zgonow);
		pokazSiatke();
		zwiekszWiek();
		Sleep(500);
		mtx.unlock();
		rok++;
		if (brakPlodnosciPopulacji())
		{
			cout << "Brak plodnych samiczek - ferma wymiera.\n";
		}
	} while(BunnyList.size() > 0);
	cout << "Farma wymarla w " << rok - 1 << " roku dzialalnosci.";
	cin.get();
	return 0;
}

int Farm::odstrzal()
{
	char odstrzal;
	//mtx.lock();
	do
	{
		odstrzal = getchar();
		if (odstrzal == 'k')
		{
			cout << "odstrzal krolikow - ginie polowa populacji";
			smiercKrolikow();
		}
	} while (BunnyList.size() > 0);
		//mtx.unlock();
	return 0;
}

void Farm::przygotowanieSymulacji()
{  
	for (int i = 0; i < 5; i++)	{ dodajKrolika();}
}

int Farm::sprawdzNarodzenia()
{
	int samce = 0;
	int samiczki = 0;
	for (list<bunny>::iterator it = BunnyList.begin(); it != BunnyList.end(); it++)
	{
		if (it->pokazPlec() == true && it->pokazCzyMutant() == false && it->pokazWiek() >= 2) samce++;
		if (it->pokazPlec() == false && it->pokazCzyMutant() == false && it->pokazWiek() >= 2) samiczki++;
	}
	if (samce == 0) return 0;
	else return samiczki;
}

int Farm::sprawdzZgony()
{
	int zgony = 0;
	bool usuniety;
	list<bunny>::iterator it;
	int i = 0;
	do
	{
		usuniety = false;
		for (it = BunnyList.begin(); it != BunnyList.end(); it++)
		{
			if ((it->pokazWiek() > 10 && it->pokazCzyMutant() == false) || (it->pokazWiek() > 50 && it->pokazCzyMutant() == true))
			{
				if (it->pokazPlec() == 0) liczbaSamiczek--;
				if (it->pokazCzyMutant() == 1) liczbaMutantow--;
				ferma[it->pobierzPozycjeX()][it->pobierzPozycjeY()] = '.';
				BunnyList.erase(it);
				usuniety = true;
				zgony++;
				break;
			}
		}
	} while (usuniety);
	return zgony;
}

void Farm::dodajKrolika()
{
	bunny newBunny;
	int x, y;
	newBunny.losujMutacje();
	newBunny.losujPlec();
	do
	{
		x = rand() % wymiar;
		y = rand() % wymiar;
	} while (ferma[x][y] == ' ');
	newBunny.zmienPozycje(x,y);
	BunnyList.push_back(newBunny);
	dodajDoSiatki();
	if (newBunny.pokazPlec() == 0) dodajSamiczke();
	if (newBunny.pokazCzyMutant() == 1) dodajMutanta();
}

int Farm::zarazanie()
{
	int mutantow = 0; 
	int wyborKrolika;
	bool niezarazono;
	list<bunny>::iterator it; 
	for (it = BunnyList.begin(); it != BunnyList.end(); ++it)
	{
		if(it->pokazCzyMutant() == true) mutantow++;
	}
	while (mutantow > 0)
	{
		do
		{
			niezarazono = true;
			wyborKrolika = (rand() % BunnyList.size());
		    it = BunnyList.begin();
		    for (int i = 0; i < wyborKrolika; i++, it++);
			if (it->pokazCzyMutant() == false)
			{
				it->zarazenieKrolika();
				niezarazono = false;
				liczbaMutantow++;
			}
			if (liczbaMutantow == BunnyList.size())
			{
				niezarazono = false;
			}
		} while (niezarazono);
		mutantow--;
	}
	return 0;
}

void Farm::informacjeFarmy(int rok, int narodzin, int zgonow)
{
	ofstream NowyPlik;
	NowyPlik.open("C:\\plik.txt", ios::app);
	//NowyPlik.open("C:\\Users\\Marcin\\Documents\\Visual Studio 2013\\Projects\\bunnies\\plik.txt", ios::app);
	cout << "Rok " << rok << endl;
	NowyPlik << "Rok " << rok << endl;
	Sleep(200);
	cout << "Kroliki urodzone w tym roku: " << narodzin << endl;
	NowyPlik << "Kroliki urodzone w tym roku: " << narodzin << endl;
	Sleep(200);
	cout << "Kroliki zdechle w tym roku: " << zgonow << endl;
	NowyPlik << "Kroliki zdechle w tym roku: " << zgonow << endl;
	Sleep(200);
	cout << "Na Farmie jest " << BunnyList.size() << " krolikow.";
	NowyPlik << "Na Farmie jest " << BunnyList.size() << " krolikow.";
	Sleep(200);
	cout << " Z czego samcow: " << BunnyList.size() - pokazSamiczki();
	NowyPlik << " Z czego samcow: " << BunnyList.size() - pokazSamiczki();
	Sleep(200);
	cout << ", a samiczek: " << pokazSamiczki() << endl;
	NowyPlik << ", a samiczek: " << pokazSamiczki() << endl;
	Sleep(200);
	cout << "Liczba mutantow to " << pokazMutanty() << endl;
	NowyPlik << "Liczba mutantow to " << pokazMutanty() << endl;
	if (BunnyList.size() > limitKrolikow)
	{
		cout << "Brak zywnosci na farmie - umiera polowa populacji!" << endl;
		NowyPlik << "Brak zywnosci na farmie - umiera połowa populacji!" << endl;
		smiercKrolikow();
	}
	NowyPlik.close();
}

void Farm::zwiekszWiek()
{
	for (list<bunny>::iterator it = BunnyList.begin(); it != BunnyList.end(); it++)
	{
		it->zwiekszWiek();
	}
}

void Farm::smiercKrolikow()
{
	int usunieteKroliki = BunnyList.size() / 2;
	int losowy;
	list<bunny>::iterator it; 
	while (usunieteKroliki > 0)
	{
		it = BunnyList.begin();
		losowy = rand() % BunnyList.size();
		
		for (int i = 0; i < losowy; i++, it++);
		if (it->pokazPlec() == 0) liczbaSamiczek--;
		if (it->pokazCzyMutant() == 1) liczbaMutantow--;
		ferma[it->pobierzPozycjeX()][it->pobierzPozycjeY()] = '.';
		BunnyList.erase(it);
		usunieteKroliki--;
	}	
}

bool Farm::brakPlodnosciPopulacji()
{
	for (list<bunny>::iterator it = BunnyList.begin(); it != BunnyList.end(); it++)
	{
		if (it->pokazPlec() == 0 && it->pokazCzyMutant() == false && it->pokazWiek() > 2) return false;
	}
	return true;
}

/////////////////
void Farm::dodajSamiczke()
{
	liczbaSamiczek++;
}
void Farm::dodajMutanta()
{
	liczbaMutantow++;
}
////////////////dodatki

void Farm::dodajDoSiatki()
{
	for (list<bunny>::iterator it = BunnyList.begin(); it != BunnyList.end(); it++)
	{
		it->zmienAvatar();
		ferma[it->pobierzPozycjeX()][it->pobierzPozycjeY()] = it->pobierzAvatar();
	}
}

void Farm::pokazSiatke(void)
{
	dodajDoSiatki();
	ofstream NowyPlik;
	NowyPlik.open("C:\\siatka.txt", ios::app);
	cout << "--------------------------------------------------------------------------------\n";
	NowyPlik << "--------------------------------------------------------------------------------\n";
	for (int i = 0; i < wymiar; i++)
	{
		for (int j = 0; j < wymiar; j++)
		{
			cout << ferma[i][j];
			NowyPlik << ferma[i][j];
		}
		cout << endl;
		NowyPlik << endl;
	}
	cout << "--------------------------------------------------------------------------------";
	NowyPlik << "--------------------------------------------------------------------------------";
}
void Farm::initFerma(void)
{
	for (int i = 0; i < wymiar; i++)
	{
		for (int j = 0; j < wymiar; j++)
		{
			ferma[i][j] = '.';
		}
	}
}

void Farm::ruchKrolikow(void)
{
	int kierunekRuchu;
	int licznik;
	bool move;
	for (list<bunny>::iterator it = BunnyList.begin(); it != BunnyList.end(); it++)
	{
		move = false;
		licznik = 0;
		kierunekRuchu = rand() % 4;
		do
		{
			kierunekRuchu = kierunekRuchu % 4;
			switch (kierunekRuchu)
			{
			case 0:  //pole po lewej
				if (ferma[it->pobierzPozycjeX() - 1][it->pobierzPozycjeY()] != '.' || it->pobierzPozycjeX() == 0) break;
				else
				{
					ferma[it->pobierzPozycjeX() - 1][it->pobierzPozycjeY()] = it->pobierzAvatar();
					ferma[it->pobierzPozycjeX()][it->pobierzPozycjeY()] = '.';
					it->zmienPozycje(it->pobierzPozycjeX() - 1, it->pobierzPozycjeY());
					move = true;
					break;
				}
			case 1:  //pole u góry
				if (ferma[it->pobierzPozycjeX()][it->pobierzPozycjeY() - 1] != '.' || it->pobierzPozycjeY() == 0) break;
				else
				{
					ferma[it->pobierzPozycjeX()][it->pobierzPozycjeY() - 1] = it->pobierzAvatar();
					ferma[it->pobierzPozycjeX()][it->pobierzPozycjeY()] = '.';
					it->zmienPozycje(it->pobierzPozycjeX(), it->pobierzPozycjeY() - 1);
					move = true;
					break;
				}
			case 2:  //pole po prawej
				if (ferma[it->pobierzPozycjeX() + 1][it->pobierzPozycjeY()] != '.' || it->pobierzPozycjeX() == wymiar - 1) break;
				else
				{
					ferma[it->pobierzPozycjeX() + 1][it->pobierzPozycjeY()] = it->pobierzAvatar();
					ferma[it->pobierzPozycjeX()][it->pobierzPozycjeY()] = '.';
					it->zmienPozycje(it->pobierzPozycjeX() + 1, it->pobierzPozycjeY());
					move = true;
					break;
				}
			case 3:  //pole na dole
				if (ferma[it->pobierzPozycjeX()][it->pobierzPozycjeY() + 1] != '.' || it->pobierzPozycjeY() == wymiar - 1) break;
				else
				{
					ferma[it->pobierzPozycjeX()][it->pobierzPozycjeY() + 1] = it->pobierzAvatar();
					ferma[it->pobierzPozycjeX()][it->pobierzPozycjeY()] = '.';
					it->zmienPozycje(it->pobierzPozycjeX(), it->pobierzPozycjeY() + 1); 
					move = true;
					break;
				}
			}
			kierunekRuchu++;
			licznik++;
			if (licznik == 4) move = true; //zeby nie szukal ruchu w nieskonczonosc :)
			kierunekRuchu = rand() % 4;
		} while (!move);
	}
}
