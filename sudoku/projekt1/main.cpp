#include <stdlib.h>
#include "biblioteki.h"
tablica tab[SIZE][SIZE];
element *aktualny = new element;

int main()
{
	int zn = 0, x = XD + 9, y = YD + 9 , attr = 7, licznik = 0, kom = 0;
	string nazwapliku;
	string podpowiadam = " ";
	string jednoznaczna = " ";
	string komunikat = " ";
	int wart_jednoznaczna;
	int x_j, y_j; //wartosc indexow wartosci jednoznacznej
	string state, s;
	clock_t start, end;
	double czas = 0.0;

	//wype³nienie pierwszego elementu listy undo-redo pustymi miejscami aby uniknac bledow

	for (int y = 1; y < SIZE; y += 2)
	{
		for (int x = 1; x < SIZE; x += 2)
		{
			aktualny->tab[y][x].wartosc = SPACJA;

			for (int k = 0; k < 9; k++)
			{
				aktualny->tab[y][x].komentarz[k] = SPACJA;
			}
		}
	}
	aktualny->poprzedni = NULL;
	aktualny->f = 0;
	aktualny->nastepny = NULL;

	settitle("Sebastian Sarnecki 155189");
	textbackground(GREEN);
	tworz_plansze(tab);

	start = clock();  //czas start

	do {
		szukam_jednoznacznej(tab, jednoznaczna, x_j, y_j, wart_jednoznaczna);
		UI(x, y, attr, zn, tab, czas, licznik, podpowiadam, komunikat);
		podpowiedz_wyswietl(X_PODPOWIEDZ, Y_PODPOWIEDZ, jednoznaczna);
		gotoxy(x, y);

		komunikat = " ";
		podpowiadam = " ";
		zn = getch();

		if (zn == 0) {
			zn = getch();

			if (zn == GORA && y-YD!=1) y-=2;
			else if (zn == DOL && y-YD!=17) y += 2;
			else if (zn == LEWA && x-XD!=1) x-=2;
			else if (zn == PRAWA && x-XD!=17) x+=2;
		}
		else if (zn == BACKSPACE){//backspace
				remove(x, y, tab);
				dodaj_stan_do_listy(SPACJA, aktualny, x - XD, y - YD, 'z', 0);
				Licznik(licznik);
		}
		else if (zn == L){//l-lista mo¿liwych cyfr
				podpowiedz(x, y, tab, podpowiadam);
		}
		else if (zn == P ){//p-wpisanie cyfry w podpowiedzi
				tab[y_j][x_j].color = BIALY;
				tab[y_j][x_j].wartosc = wart_jednoznaczna;
				dodaj_stan_do_listy(wart_jednoznaczna, aktualny, x_j, y_j, 'z', 0);
				jednoznaczna = " ";
		}
		else if (zn == O){//0-odczyt z pliku
				nazwapliku = nazwa_pliku();
				dodaj_xml_do_undo_redo(nazwapliku, aktualny,tab);
				komunikat = "wczytano plik "+nazwapliku+ ".xml";
				//wczytaj(name,tab);
		}
		else if (zn == S){//s-zapis do pliku
				nazwapliku = nazwa_pliku();
				zapis_xml(aktualny, nazwapliku);
				zapisz(nazwapliku, tab);
		}
		else if (zn == R){//r-redo, ponowienie
				redo(aktualny, tab);
				Licznik(licznik);
		}
		else if (zn == I){// i - wczytujemy plik txt z plansza startowa
			nazwapliku = nazwa_pliku();
			wczytaj(nazwapliku,tab);
		}
		else if (zn == U){//u-undo, do przodu
				undo(aktualny, tab);
				Licznik(licznik);
		}
		else if (zn == K){//k-tryb komentarza
				obsluga_komentarza(x, y, zn, aktualny, tab);
		}
		else if (zn == H){//h-zaznaczenie kolorem tej samej liczby na 2 sekundy
				zaznacz(x, y, tab, XD,YD);
		}
		else if (czy_od_1_do_9(zn)) {
			if (sprawdz(x, y, zn, tab) == true){
				add(x, y, (int)zn, tab);
				dodaj_stan_do_listy((int)zn, aktualny, x-XD,y-YD,'z',0);
				Licznik(licznik);
			}
			else
			{
				komunikat = "kolizja wartosci";
			}
		}
		else{
			komunikat = "zly klawisz";
		}

		end = clock();
		czas = (end - start) / (double)CLOCKS_PER_SEC;
	} while (zn != Q);

	return 0;
}
