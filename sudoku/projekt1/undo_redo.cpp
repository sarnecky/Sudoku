#include "biblioteki.h"

void remove(element *lista, int xx, int yy)
{
	if (lista->nastepny == NULL){}
	else{
		while (lista->nastepny != NULL)
		{
			element *usuwany = lista->nastepny; // zapamiêtujemy usuwany element 
			lista->nastepny = usuwany->nastepny;   // przestawiamy wskaŸnik next by omija³ usuwany element 
			delete(usuwany);             // usuwamy z pamiêci  
		}
	}

}


void dodaj_stan_do_listy(int wartosc, element *lista, int xx, int yy, char co, int index_kom)
{
	element *nowy_element = new element;

	if (co == 'k'){  //jezeli jest komentarzem
		nowy_element->jest_kom = 1;
		while (lista->nastepny != NULL)//szukamy ostatniego elementu listy
				lista = lista->nastepny; //dajemy adres nastepnego elementu

		for (int y = 1; y < SIZE; y += 2) //kopiujemy do nowego elementu ostatni element listy
		{
			for (int x = 1; x < SIZE; x += 2)
			{
				nowy_element->tab[y][x] = lista->tab[y][x];
			    for (int k = 0; k < 9; k++)
				{
					nowy_element->tab[y][x].komentarz[k] = lista->tab[y][x].komentarz[k];
				}
			}
		}
		nowy_element->tab[yy][xx].komentarz[index_kom] = wartosc;  //wpisujemy nowa wartosc
	}
	else{  //jezeli nie jest komentarzem

		nowy_element->jest_kom = 0;
		while (lista->nastepny != NULL)//szukamy ostatniego elementu listy
		{		//zak³adamy ze user bedzie edytowac aktualny element listy
			if (lista->tab[yy][xx].wartosc != SPACJA && lista->f == 1){
				//jezeli napotkamy po drodze element, ktory jest juz w liscie,
				//usuwamy wszystkie kolejne
				remove(lista, xx, yy);//usuwamy elementy od yy,xx do konca listy
				lista->nastepny = NULL;
				//lista->f = 1;//ten elemenet staje sie aktualnym, bo poprzednie stany zostaly usuniete
			}
			else
			{
				lista = lista->nastepny; //dajemy adres nastepnego elementu
			}

		}
		for (int y = 1; y < SIZE; y += 2) //kopiujemy do nowego elementu ostatni element listy
		{
			for (int x = 1; x < SIZE; x += 2){

				nowy_element->tab[y][x] = lista->tab[y][x];

				for (int k = 0; k < 9; k++)
				{
					nowy_element->tab[y][x].komentarz[k] = lista->tab[y][x].komentarz[k];
				}
			}
		}
		nowy_element->tab[yy][xx].wartosc = wartosc;  //wpisujemy nowa wartosc
	}
	nowy_element->poz_x = xx;
	nowy_element->poz_y = yy;
	nowy_element->nastepny = NULL;   //kolejna wartosc, nie istnieje, nowy_element wskazuje na NULL
	nowy_element->poprzedni = lista;   //powrot do poprzedniego elementu
	nowy_element->f = 1;   //nowy staje sie aktualnym
	lista->nastepny = nowy_element; //poprzedni element wskazuje na nowy element listy
	lista->f = 0;  //poprzedni element nie ju¿ jest aktualnym, wiec f=0
}


void undo(element *lista, tablica tab[][SIZE])
{

	while (lista->nastepny != NULL)//szukamy ostatniego elementu listy
	{
		if (lista->f != 1)lista = lista->nastepny;//szukamy aktualnego elementu
		else break;
	}
	if (lista->poprzedni != NULL){  //warunek, aby nie wejsc do elementu NULL

		lista->f = 0;
		lista = lista->poprzedni;
		lista->f = 1;	//poprzedni element staje sie aktualnym

		for (int y = 1; y < SIZE; y += 2) //wpisanie poprzedniego stanu do tablicy
		{
			for (int x = 1; x < SIZE; x += 2)
			{
				tab[y][x].wartosc = lista->tab[y][x].wartosc;

				for (int k = 0; k < 9; k++) //wpisanie zmienionej wartosci komentarza do tablicy ktora wyswietla go na ekranie
				{
					tab[y][x].komentarz[k] = lista->tab[y][x].komentarz[k];
				}
			}
		}
	}
}


void redo(element *lista, tablica tab[][SIZE])
{

	while (lista->nastepny != NULL)//szukamy ostatniego elementu listy
	{
		if (lista->f != 1)lista = lista->nastepny;   //je¿eli po drodze znajdzie aktualny element to zmieni jego adres na kolejny
		else
		{
			lista->f = 0;
			lista = lista->nastepny;
			lista->f = 1;  //wczesniejszy element staje sie aktualnym
			break;
		}
	}
	for (int y = 1; y < SIZE; y += 2) //wpisanie poprzedniego stanu do tablicy
	{
		for (int x = 1; x < SIZE; x += 2)
		{
			tab[y][x].wartosc = lista->tab[y][x].wartosc;

			for (int k = 0; k < 9; k++) //wpisanie zmienionej wartosci komentarza do tablicy ktora wyswietla go na ekranie
			{
				tab[y][x].komentarz[k] = lista->tab[y][x].komentarz[k];
			}
		}
	}
}
