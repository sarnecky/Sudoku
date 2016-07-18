#include "biblioteki.h"

bool czy(int n){
	int liczby[9] = { 1, 3, 5, 7, 9, 11, 13, 15, 17 };
	for (int i = 0; i < 9; i++)
	{
		if (n == liczby[i])return true;
	}
	return false;
}


bool sprawdz(int x, int y, int zn, tablica tab[][SIZE])//sprawdzam czy nie ma takich samych liczb w ...
{
	int X = x - XD;
	int Y = y - YD;
	int i;
	for (i = 0; i < SIZE; i++)//wiersz
	{
		if (tab[i][X].wartosc == zn)return false;
	}
	for (i = 0; i < SIZE; i++)//kolumna
	{
		if (tab[Y][i].wartosc == zn)return false;
	}
	if (X == 1 || X == 7 || X == 13)//dla kwadratu
	{
		if (Y == 1 || Y == 7 || Y == 13)// zn jest na pozycji 0,0 OK
		{
			if (tab[Y + Z][X + Z].wartosc == zn)return false;
			if (tab[Y + Z][X + 2 * Z].wartosc == zn)return false;
			if (tab[Y + 2 * Z][X + Z].wartosc == zn)return false;
			if (tab[Y + 2 * Z][X + 2 * Z].wartosc == zn)return false;
		}
		if (Y == 3 || Y == 9 || Y == 15)// zn jest na pozycji 1,0 OK
		{
			if (tab[Y - Z][X + Z].wartosc == zn)return false;
			if (tab[Y + Z][X + Z].wartosc == zn)return false;
			if (tab[Y - Z][X + 2 * Z].wartosc == zn)return false;
			if (tab[Y + Z][X + 2 * Z].wartosc == zn)return false;
		}
		if (Y == 5 || Y == 11 || Y == 17)// zn jest na pozycji 2,0 OK
		{
			if (tab[Y - Z][X + Z].wartosc == zn)return false;
			if (tab[Y - Z][X + 2 * Z].wartosc == zn)return false;
			if (tab[Y - 2 * Z][X + Z].wartosc == zn)return false;
			if (tab[Y - 2 * Z][X + 2 * Z].wartosc == zn)return false;
		}
	}
	else if (X == 3 || X == 9 || X == 15)
	{
		if (Y == 1 || Y == 7 || Y == 13)// zn jest na pozycji 0,1 OK
		{
			if (tab[Y + Z][X + Z].wartosc == zn)return false;
			if (tab[Y + Z][X - Z].wartosc == zn)return false;
			if (tab[Y + 2 * Z][X + Z].wartosc == zn)return false;
			if (tab[Y + 2 * Z][X - Z].wartosc == zn)return false;
		}
		if (Y == 3 || Y == 9 || Y == 15)// zn jest na pozycji 1,1 OK
		{
			if (tab[Y + Z][X + Z].wartosc == zn)return false;
			if (tab[Y + Z][X - Z].wartosc == zn)return false;
			if (tab[Y - Z][X + Z].wartosc == zn)return false;
			if (tab[Y - Z][X - Z].wartosc == zn)return false;
		}
		if (Y == 5 || Y == 11 || Y == 17)// zn jest na pozycji 2,1 OK
		{
			if (tab[Y - Z][X - Z].wartosc == zn)return false;
			if (tab[Y - Z][X + Z].wartosc == zn)return false;
			if (tab[Y - 2 * Z][X - Z].wartosc == zn)return false;
			if (tab[Y - 2 * Z][X + Z].wartosc == zn)return false;
		}
	}
	else if (X == 5 || X == 11 || X == 17)
	{
		if (Y == 1 || Y == 7 || Y == 13)// zn jest na pozycji 0,2 OK
		{
			if (tab[Y + Z][X - Z].wartosc == zn)return false;
			if (tab[Y + Z][X - 2 * Z].wartosc == zn)return false;
			if (tab[Y + 2 * Z][X - Z].wartosc == zn)return false;
			if (tab[Y + 2 * Z][X - 2 * Z].wartosc == zn)return false;
		}
		if (Y == 3 || Y == 9 || Y == 15)// zn jest na pozycji 1,2 OK 
		{
			if (tab[Y - Z][X - Z].wartosc == zn)return false;
			if (tab[Y - Z][X - 2 * Z].wartosc == zn)return false;
			if (tab[Y + Z][X - Z].wartosc == zn)return false;
			if (tab[Y + Z][X - 2 * Z].wartosc == zn)return false;
		}
		if (Y == 5 || Y == 11 || Y == 17)// zn jest na pozycji 2,2 OK
		{
			if (tab[Y - Z][X - Z].wartosc == zn)return false;
			if (tab[Y - Z][X - 2 * Z].wartosc == zn)return false;
			if (tab[Y - 2 * Z][X - Z].wartosc == zn)return false;
			if (tab[Y - 2 * Z][X - 2 * Z].wartosc == zn)return false;
		}
	}
	return true;
}


void tworz_plansze(tablica tab[][SIZE])
{
	for (int y = 0; y < SIZE; y++)//y
	{

		for (int x = 0; x < SIZE; x++)//x
		{
			if (y == 0)
			{
				if (czy(x))tab[y][x].wartosc = 205;//linia prosta gorna
				else if (x == 0)tab[y][x].wartosc = 201;//gorna krawedz lewa
				else if (x == 18)tab[y][x].wartosc = 187;//dolna krawedz prawa
				else tab[y][x].wartosc = 203;//gorna zaslepka

			}
			else if (y == 18)
			{
				if (czy(x))tab[y][x].wartosc = 205;//linia prosta dolna
				else if (x == 0)tab[y][x].wartosc = 200;//dolna krawdz lewa
				else if (x == 18)tab[y][x].wartosc = 188;//dolna krawedz prawa
				else tab[y][x].wartosc = 202;//dolna zaslepka
			}
			else if (czy(y))
			{
				if (czy(x))tab[y][x].wartosc = 32;//wolne miejsce
				else if (x == 0 || x == 6 || x == 12 || x == 18)tab[y][x].wartosc = 186;//gruba pionowa
				else tab[y][x].wartosc = 179;//cienka pionowa
			}
			else
			{

				if ((czy(x) == true) && (y == 6 || y == 12))tab[y][x].wartosc = 205;//gruba pozioma
				else if ((czy(x) == true) && (y != 6 || y != 12))tab[y][x].wartosc = 196;
				else if (x == 6 || x == 12)tab[y][x].wartosc = 206;
				else if (x == 0)tab[y][x].wartosc = 204;
				else if (x == 18)tab[y][x].wartosc = 185;
				else {
					if (y == 6 || y == 12) tab[y][x].wartosc = 206;
					else tab[y][x].wartosc = 197;

				}
			}
		}
	}
}


void narysuj_diagram(int x1, int y1, tablica tab[][SIZE])
{
	int x = 0, y = 0;
	for (y = 0; y < SIZE; y++)//y
	{
		x = 0;
		gotoxy(x1 + x, y1 + y);
		for (x = 0; x < SIZE; x++)//x
		{
			if (tab[y][x].color==NIEBIESKI)
			{
				textcolor(tab[y][x].color);
				cout << (char)tab[y][x].wartosc;
			}
			else
			{
				textcolor(BIALY);
				cout << (char)tab[y][x].wartosc;
			}

		}
		cout << endl;
	}
}


void narysuj_pomoc(int x1, int y1)
{
	gotoxy(x1, y1);
	cputs("q = wyjscie");
	gotoxy(x1, y1 + 1);
	cputs("backspace = usuniecie");
	gotoxy(x1, y1 + 2);
	cputs("u = undo, r = redo");
	gotoxy(x1, y1 + 3);
	cputs("l = lista mozliwosci");
	gotoxy(x1, y1 + 4 );
	cputs("strzalki = poruszanie");
	gotoxy(x1, y1 + 5);
	cputs("s = zapis, o = odczyt");
	gotoxy(x1, y1 + 6);
	cputs("k = tryb komentarza");
	gotoxy(x1, y1 + 7);
	cputs("p = wpisanie podpowiedzi");
	gotoxy(x1, y1 + 8);
	cputs("h = podswietlenie on/off");
	gotoxy(x1, y1 + 9);
	cputs("i = startowa plansza");
}


void czas_gry_licznik(int x1, int y1, double czas, int & licznik)
{

	gotoxy(x1, y1);
	cputs("Czas gry: ");
	cout.setf(ios::fixed);//notacja typu 0.23432 zamiast 3.14159e+000
	cout.precision(2);//miejsca po przecinku
	cout << czas << " s";
	gotoxy(x1, y1 + 2);
	cputs("Licznik: ");
	cout << licznik << " ruchow" << endl;
	//MA LICZYÆ NIEWPISANE ?
}


void help(int x, int y, tablica tab[][SIZE], int x1, int y1, int zn, string &komunikat)
{
	gotoxy(x1, y1);
	cputs("Help:");
	cout << komunikat;
}


void podpowiedz_wyswietl(int x1, int y1, string &podpowiadam)
{
	gotoxy(x1, y1);
	if (podpowiadam == " "){}
	else{
		cputs("Podpowiadam:");
		cout << podpowiadam << endl;
	}

}


void podpowiedz(int x, int y, tablica tab[][SIZE], string &podpowiadam)
{
	podpowiadam = " ";
	int j = 0, w, X, Y, znak;
	for (int i = 1; i <= 9; i++)
	{
		if (sprawdz(x, y, 48 + i, tab) == true)//sprawdzamy czy wystepuja konflikty kolumna, wiersz, kwadrat
		{
			podpowiadam += (char)(ZERO + i); //48 kod asci 0
			podpowiadam += " "; //dodajemy spacje dla przejrzystosci
			X = x - XD;
			Y = y - YD;
			znak = i;
		}
		else j++;
	}
	if (j == 9)podpowiadam = "Sproboj inny uklad";//jezeli wystepuje 9 konfliktow, trzeba zmienic uklad
	if (j == 8){ //jezeli jest 8 konfliktow, jeden jest oczywisty do rozwiazania
		podpowiadam += "Wcisnij p, aby wstawic";
		podpowiedz_wyswietl(X_LISTA, Y_LISTA, podpowiadam);
		gotoxy(x, y);
		w = getch();
		if (w == P)//wcisiniecie p
		{
			tab[Y][X].color = BIALY;
			tab[Y][X].wartosc = (48 + znak);
		}
		podpowiadam = " ";
	}
}


void szukam_jednoznacznej(tablica tab[][SIZE], string &jednoznaczna, int &x_j, int &y_j, int &wart_jednoznaczna)
{
	int mozliwosc = 0;
	int wartosc;
	jednoznaczna = "";
	for (int y = 1; y < SIZE; y += 2)
	{
		for (int x = 1; x < SIZE; x += 2)
		{
			mozliwosc = 0;
			for (int i = 1; i <= 9; i++)
			{

				if (sprawdz(x + XD, y + YD, ZERO + i, tab) == true)//sprawdzamy ile wartosci mozna wpisac w pole
				{
					mozliwosc++;  //szuakana wartosc
					wartosc = ZERO + i;
				}
			}
			
			if (mozliwosc == 1 && tab[y][x].wartosc==SPACJA){ //jedyna wartosc ktora mozna wpisac
				jednoznaczna += "Wstaw ";
				jednoznaczna += (char)wartosc;
				jednoznaczna += ",klawisz p";
				podpowiedz_wyswietl(X_PODPOWIEDZ, Y_PODPOWIEDZ, jednoznaczna);
				x_j = x;
				y_j = y;
				wart_jednoznaczna = wartosc;
				x = 20;
				y = 20;
			}
			
		}
	}
	if (mozliwosc == 0)jednoznaczna += "Wygrales";

}


void UI(int x, int y, int attr, int zn, tablica tab[][SIZE], double czas, int &licznik, string &podpowiadam, string &komunikat)
{
	clrscr();
	textcolor(7);
	czas_gry_licznik(X_LICZNIK, Y_LICZNIK, czas, licznik);
	podpowiedz_wyswietl(50, 17, podpowiadam);
	narysuj_diagram(XD, YD, tab);
	narysuj_pomoc(X_HELP, Y_HELP);
	help(x, y, tab, X_HELP2, Y_HELP2, zn, komunikat);
	wyswietl_kom(x, y, tab, X_KOM, Y_KOM);//komentarz do danego pola
	gotoxy(x, y);
	textcolor(attr);
}


void Licznik(int & licznik)
{
	licznik++;
}