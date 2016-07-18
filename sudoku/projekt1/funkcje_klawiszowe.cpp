#include "biblioteki.h"

void add(int x, int y, int zn, tablica tab[][SIZE])
{
	//z tryb zwyk³y
	//k -tryb komentarza
	int X = x - XD;
	int Y = y - YD;
	if (czy(X) && czy(Y)) tab[Y][X].wartosc = zn;
	else {}
	//sprawdzac czy nie ma sciany
	//komunikat sciany

		tab[Y][X].color = BIALY;

}


void remove(int x, int y, tablica tab[][SIZE])
{
	int X = x - XD;
	int Y = y - YD;
	if (czy(X) && czy(Y))tab[Y][X].wartosc = SPACJA;
	else{}
	//TODO 
	//sprawdzac  czy jest liczba
	//sprawdzac czy nie jest sciana
}


void zaznacz(int x, int y, tablica tab[][SIZE], int x1, int y1)
{
	int X = x - XD;
	int Y = y - YD;
	int i, j;
	if (tab[Y][X].color == 7)//chcemy podswietlic
	{
		for (i = 1; i < SIZE; i+=2)//y
			{
				j = 0;
				for (j = 1; j < SIZE; j+=2)//x
				{

					if (tab[i][j].wartosc == tab[Y][X].wartosc)
					{
						tab[i][j].color = NIEBIESKI;
						cout << (char)tab[i][j].wartosc;
					}
					else
					{
						tab[i][j].color = BIALY;
						cout << (char)tab[i][j].wartosc;
					}

				}
			}
	}
	else{ //chcemy usunac podswietlenie
		for (i = 0; i < SIZE; i++)//y
		{
			j = 0;
			for (j = 0; j < SIZE; j++)//x
			{
				textcolor(7);
				tab[i][j].color = 7;
			}
		}
	}
	
}


void dodaj_kom(int x, int y, int j, int zn, tablica tab[][SIZE])
{
	int X = x - XD;
	int Y = y - YD;

	tab[Y][X].komentarz[j] = zn;
	wyswietl_kom(x, y, tab, X_KOM, Y_KOM);
}


void usun_kom(int x, int y, int j, tablica tab[][SIZE])
{
	int X = x - XD;
	int Y = y - YD;
	tab[Y][X].komentarz[j] = SPACJA;//znak asci spacji-wolna przestrzen
	wyswietl_kom(x, y, tab, X_KOM, Y_KOM);
}


bool sprawdz_czy_istnieje(int x, int y, int j, int zn, tablica tab[][SIZE])
{
	int X = x - XD;
	int Y = y - YD;

	for (int i = 0; i < 9; i++)
	{
		if (tab[Y][X].komentarz[i] == zn)return false;
	}
	return true;
}


void wyswietl_kom(int x, int y, tablica tab[][SIZE], int x1, int y1)
{  //wyswietla komentarz do danego pola
	int X = x - XD;
	int Y = y - YD;
	gotoxy(x1, y1);
	cputs("Komentarz:");
		for (int i = 0; i < 9; i++)
		{
			gotoxy(x1+i, y1+1);
			cout << (char)tab[Y][X].komentarz[i];
		}
}


bool czy_od_1_do_9(int zn)
{   //sprawdzam czy wcisiniety klawisz to liczba 1-9
	if (zn >= 49 && zn <= 57)return true;
	return false;
}


void obsluga_komentarza(int x, int y, int zn, element *lista, tablica tab[][SIZE])
{
	int X = x - XD;
	int Y = y - YD;
	int j = 0; //aktuala pozycja w tablicy kom
	do {

		wyswietl_kom(x, y, tab, X_KOM, Y_KOM);
		gotoxy(X_KOM + j, Y_KOM+1);
		zn = getch();

		if (zn == 0) {
			zn = getch();

			if (zn == LEWA) j--;
			else if (zn == PRAWA) j++;
		}
		else if (zn == BACKSPACE){//backspace
			usun_kom(x, y, j, tab);
			if (j > 0){//zabezpieczenie zeby u¿ytkownik nie wyszedl poza tablice przy skracaniu dlugosci komentarza
				dodaj_stan_do_listy(SPACJA, lista, X, Y, 'k', j);
				j--;
			}
		}
		else if (czy_od_1_do_9(zn)){//wartosc liczba
			if (sprawdz_czy_istnieje(x, y, j, zn, tab))
			{
				dodaj_kom(x, y, j, zn, tab);
				dodaj_stan_do_listy(zn, lista, X, Y, 'k', j);
				j++;
			}
		}
	} while (zn != K);
}


string nazwa_pliku()
{
	string n="";

	gotoxy(X_NAZWA, Y_NAZWA);
	cout << "Wprawadz nazwe:";
	cin >> n;

	return n;
}