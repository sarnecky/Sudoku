#include "biblioteki.h"

void taba(ifstream &plik, element *lista)
{
	int licz = 0, j = 1;
	char p = ' ';
	while (lista->nastepny != NULL)
	{
		lista = lista->nastepny;
	}
	while (licz<81)
	{
		for (int i = 1; i < SIZE; i += 2)
		{
			plik >> p;
			if ((int)p != 45){
				lista->tab[j][i].wartosc = (int)p;
			}
			else {
				lista->tab[j][i].wartosc = 32;
			}
			licz++;
		}
		j += 2;
	}
}


void comments(ifstream &plik, element *lista)
{
	string s = "";
	int i, y, x, z;
	char p = ' ';
	plik >> s; //<comment
	s = "";
	while (lista->nastepny != NULL)
	{
		lista = lista->nastepny;
	}
	lista->jest_kom = 1;
	while (s != "</comments>")
	{
		i = 0;
		p = ' ';

		plik >> s; //row
		z = ((int)s[5] - 48);
		y = 2 * z - 1; //do nowego indexu dodajemy poprzedni i powstaje odpowiadajacy index naszej tabeli SIZE/SIZE 
		getline(plik, s, '>'); //col
		z = ((int)s[6] - 48);
		x = 2 * z - 1;  //do nowego indexu dodajemy poprzedni i powstaje odpowiadajacy index naszej tabeli SIZE/SIZE

		while (p != '<')
		{
			plik >> p;
			if (p != '<')
			{
				lista->tab[y][x].komentarz[i] = (int)p;
			}
			i++;
		}
		plik >> s;//comment>
		plik >> s;//<comment lub <comments>
	}
}


void plansza_startowa(ifstream &plik, element *lista, tablica tab[][SIZE]) //to jest pierwszy stan odpala sie po starcie sudoku 
{

	//sprawdzi czy lista->f nie rowna sie 1 i wypisze wlasnie ja na pierwsza plansze
	while (lista->nastepny!=NULL)
	{
		if(lista->f!=1)lista = lista->nastepny;
		else break;
	}
	for (int y = 1; y < 19; y += 2)
	{
		for (int x = 1; x < 19; x += 2)
		{
			tab[y][x].wartosc = lista->tab[y][x].wartosc;

			for (int k = 0; k < 9; k++)
			{
				tab[y][x].komentarz[k] = lista->tab[y][x].komentarz[k];
			}
		}
	}
}


void zrob_nowy_obszar_pamieci(element *nowy, element *lista)
{  //tworzymy nowy blok pamieci
	
		while(lista->nastepny != NULL)
		{
			lista = lista->nastepny;
		}

		nowy->nastepny = NULL;
		nowy->poprzedni = lista;
		lista->nastepny = nowy;
		for (int y = 1; y < SIZE; y += 2)
		{
			for (int x = 1; x < SIZE; x += 2)
			{
				for (int k = 0; k < 9; k++)
				{
					nowy->tab[y][x].komentarz[k] = SPACJA;
				}
			}
		}
}


void dodaj_xml_do_undo_redo(string name, element *lista, tablica tab[][SIZE])
{
	wyzeruj_active_state(lista);

	ifstream plik;
	string s, state;
	plik.open(name+".xml");

	element *nowy_element = new element;
	zrob_nowy_obszar_pamieci(nowy_element, lista);

	
	plik.seekg(44);// ustawienie bufora na liczbie w active-state
	getline(plik, s, '>'); //pobranie liczby
	s += ">";
	state = "nr=" + s;
	plik >> s;//<state
	plik >> s;//nr...

	if (s == state) nowy_element->f = 1;
	else nowy_element->f = 0;
	plik >> s;//<board>

	while (s != "</sudoku>")
	{	
		if (s == "<board>")
		{
			taba(plik,lista);

			plik >> s;//board>
			plik >> s;//<comments> lub </state>
			if (s == "<comments>")
			{
				comments(plik, lista);
			}
			plik >> s;//</state>
			plik >> s;//</state
			if (s != "</sudoku>")
			{
				element *nowy_element2 = new element;
				zrob_nowy_obszar_pamieci(nowy_element2, lista);

				plik >> s;//nr....>
				if (s == state) nowy_element2->f = 1;
				else nowy_element2->f = 0;
				plik >> s;//<board> LUB <commnents>
			}
		}
		else if (s == "<comments>")
		{
			comments(plik, lista);
			plik >> s;//<board>
			if (s == "<board>")
			{
				taba(plik, lista);
			}
			plik >> s;//</board>
			plik >> s;//</state>
			if (s != "</sudoku>")
			{
				element *nowy_element2 = new element;
				zrob_nowy_obszar_pamieci(nowy_element2, lista);

				plik >> s;//nr....>
				if (s == state) nowy_element2->f = 1;
				else nowy_element2->f = 0;
			}
		}
	}
	plansza_startowa(plik, lista, tab); //uruchamiamy plansze startowa
	plik.close();
}


void board(element *lista, ofstream &xml)
{
	for (int y = 1; y < 19; y += 2)
	{
		for (int x = 1; x < 19; x += 2)
		{
			if (lista->tab[y][x].wartosc != SPACJA)
			{
				xml << (char)lista->tab[y][x].wartosc << " ";
			}
			else xml << "- ";

		}
		xml << endl;
	}
}


bool sprawdz_kom(element *lista, int x, int y)
{
	int l = 0;
	for (int i = 0; i < 9; i++)
	{
		if (lista->tab[y][x].komentarz[i] != SPACJA)l++;
	}

	if (l==0)return false; //nie ma zadnego komentarza
	else return true; //jest komentarz
	
}


void comment(element *lista, ofstream &xml)
{
	int k;
	for (int y = 1; y < 19; y += 2)
	{
		for (int x = 1; x < 19; x += 2)
		{

			if (sprawdz_kom(lista,x,y))
			{
				k = 0;
				xml << "<comment row=" << "\"" << x / 2 + 1 << "\" col=" << "\"" << y / 2 + 1 << "\">";
				while (lista->tab[y][x].komentarz[k] != SPACJA)
				{
					xml << (char)lista->tab[y][x].komentarz[k]<<" ";
					k++;
				}
				xml << "</comment>" << endl;
			}
		}
	}
}


void zapis_xml(element *lista, string name)  
{ 
	int i = 1;
	string a;
	while (lista->nastepny != NULL)//znalezienie active state
	{
		if (lista->f != 1)i++;
		else break;
		lista = lista->nastepny;
	}
	while (lista->poprzedni != NULL)//powrot do poczatku
		lista = lista->poprzedni;

	ofstream xml;
	xml.open(name+".xml");
	
	xml << "<?xml version=\"1.0\"?>" << endl;
	xml << "<sudoku active-state="<<"\""<< i<<"\">" << endl;
	i = 1;
	while(lista->nastepny!=NULL) //wypisujemy kolejne elementy undo-redo do xmla
	{
		xml << "<state nr=" << "\"" << i << "\">" << endl;
		xml << "<board>" << endl;
		board(lista, xml); //wypisanie board
		xml << "</board>" << endl;

		if (lista->jest_kom == 1)
		{
			xml << "<comments>" << endl;
			comment(lista, xml);//wpisanie komentarza
			xml << "</comments>" << endl;
		}

		xml << "</state>" << endl;
		lista = lista->nastepny;
		i++;
	}
		//wypisuje ostatni element listy
		xml << "<state nr=" << "\"" << i << "\">" << endl;
		xml << "<board>" << endl;
		board(lista, xml);  //wypisanie board
		xml << "</board>" << endl;

		if (lista->jest_kom == 1)
		{
			xml << "<comments>" << endl;
			comment(lista, xml);//wpisanie komentarza
			xml << "</comments>" << endl;
		}
		xml << "</state>" << endl;
		xml << "</sudoku>";
		xml.close();
}


void wyzeruj_active_state(element *lista)
{  //poprzednie elementy staja sie nieaktualne
	while (lista->nastepny != NULL)
	{
		lista->f = 0;
		lista = lista->nastepny;
	}
	lista->f = 0;
}