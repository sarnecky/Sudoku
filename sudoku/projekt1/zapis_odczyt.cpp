#include "biblioteki.h"

void wczytaj(string name, tablica tab[][SIZE])
{
	ifstream plik;
	plik.open(name+".txt");
	string s;
	int i = 1, y = 1, x = 1;

	//wyspacjowanie zapobiegnie b³êdom, gdy linijka nie ma 9 znaków
	for (int y = 1; y < SIZE; y += 2)
	{
		for (int x = 1; x < SIZE; x += 2)
		{
			tab[y][x].wartosc = SPACJA;//32numer ascii spacji
		}
	}
	while (!plik.eof() && y <18)
	{
		getline(plik, s);
		s = s + '\0';
		i = 0;
		x = 1;
		while (i < s.size() && x < SIZE)
		{
			tab[y][x].wartosc = (int)s[i];
			i++;
			x += 2;
		}
		y += 2;
	}
	plik.close();
}


void zapisz(string name, tablica tab[][SIZE])
{
	ofstream zapis;
	zapis.open(name+".txt");
	string s[9];
	int j = 0, y = 1, x = 1;
	zapis << "Sudoku" << endl;
	for (int y = 1; y < SIZE; y += 2)
	{
		for (int x = 1; x < SIZE; x += 2)
		{
			if (tab[y][x].wartosc!=SPACJA)
				zapis << (char)tab[y][x].wartosc;
			else
				zapis <<"-";
		}
		zapis << endl;
	}
	zapis.close();
}