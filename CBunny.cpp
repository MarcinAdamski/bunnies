#include "CBunny.h"
#include <cstdlib>
#include <time.h>
#include <iostream>

/*bool operator< (const bunny &rhs)
{
	if (this->age < rhs.age) return true;
	else return false;
}*/

//metody
void bunny::zwiekszWiek(void)
{
	age++;
}

void bunny::zarazenieKrolika(void)
{
	radioactive_mutant_vampire_bunny = true;
}

void bunny::zmienPozycje(int x, int y)
{
	pozX = x;
	pozY = y;
}

void bunny::zmienAvatar()
{
	if (radioactive_mutant_vampire_bunny == true) avatar = 'X';
	else if (age >= 2)
	{
		if (sexMale == true) avatar = 'M';
		else avatar = 'F';
	}
	else
	{
		if (sexMale == true) avatar = 'm';
		else avatar = 'f';
	}
}
///////////////metody odczytu
int bunny::pokazWiek(void){	return age;}
bool bunny::pokazPlec(void){ return sexMale;}
bool bunny::pokazCzyMutant(void){ return radioactive_mutant_vampire_bunny;}
int bunny::pobierzPozycjeX(void){ return pozX;}
int bunny::pobierzPozycjeY(void){ return pozY; }
char bunny::pobierzAvatar(void){ return avatar;}

////////////////
void bunny::losujMutacje(void)
{
	int losowa;
	losowa = rand() % 50;
	if (losowa == 25) radioactive_mutant_vampire_bunny = true; //2% szans na mutacje
	else radioactive_mutant_vampire_bunny = false;
}

void bunny::losujPlec(void)
{
	int losowa;
	losowa = rand() % 2;
	if (losowa == 0) sexMale = true;
	else sexMale = false;
}
