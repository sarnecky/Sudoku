#ifndef biblioteki_h
#define biblioteki_h
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <time.h>
#include "conio2.h"


#define SIZE 19 //ROZMIAR TABLICY
#define Z 2
#define SPACJA 32 
#define ZERO 48 

//klawisze(bez capslocka)
#define GORA 0x48 
#define DOL 0x50 
#define LEWA 0x4b 
#define PRAWA 0x4d 
#define BACKSPACE 0x08
#define L 0x6c 
#define O 0x6f
#define S 0x73
#define R 0x72
#define U 0x75
#define K 0x6b
#define H 0x68
#define Q 0x71
#define P 0x70
#define ENTER 0x0d
#define I 0x69
//stale pomocy, licznika i planszy
#define X_HELP 45
#define Y_HELP 1
#define X_LICZNIK 25
#define Y_LICZNIK 1
#define XD 10 //PRZESUNIECIE NA OSI X
#define YD 6 //PRZESUNIECIE NA OSI Y
#define X_HELP2 45
#define Y_HELP2 11
#define X_KOM 45
#define Y_KOM 14
#define X_NAZWA 45
#define Y_NAZWA 20
#define X_PODPOWIEDZ 45
#define Y_PODPOWIEDZ 23
#define X_LISTA 45
#define Y_LISTA 22
//kolory
#define NIEBIESKI 9
#define BIALY 7

using namespace std;

struct tablica{
	int color;
	int wartosc;
	int komentarz[9];
	
};
struct element{

	element *nastepny; //wskaznik na nastêpny stan planszy
	element *poprzedni; //wskaznik na poprzedni stan planszy

	tablica tab[SIZE][SIZE]; //tablica przechowujaca stany
	int f; //aktualnie obslugiwany stan to 1, 0 to inny element

	int poz_x, poz_y; //pozycje kurosra
	int jest_kom; //jezeli jest komentarz to 1, a jezeli nie ma to 0
};

void wczytaj(string name, tablica tab[][SIZE]);
void zapisz(string name, tablica tab[][SIZE]);


bool czy(int n);
bool sprawdz(int x, int y, int zn, tablica tab[][SIZE]);//sprawdzam czy nie ma takich samych liczb w ...
void tworz_plansze(tablica tab[][SIZE]);
void narysuj_diagram(int x1, int y1, tablica tab[][SIZE]);
void narysuj_menu(int x1, int y1);
void czas_gry_licznik(int x1, int y1, double czas, int & licznik);
void help(int x, int y, int xd, int yd, tablica tab[][SIZE], int x1, int y1, int zn, string komunikat);
void podpowiedz_wyswietl(int x1, int y1, string &podpowiadam);
void podpowiedz(int x, int y, tablica tab[][SIZE], string &podpowiadam);
void UI(int x, int y, int attr, int zn, tablica tab[][SIZE], double czas, int & licznik, string &podpowiadam, string &komunikat);
void Licznik(int & licznik);
bool czy_od_1_do_9(int zn);
void dodaj_kom(int x, int y, int j, int zn, tablica tab[][SIZE]);
void usun_kom(int x, int y, int j, tablica tab[][SIZE]);
bool sprawdz_czy_istnieje(int x, int y, int j, int zn, tablica tab[][SIZE]);
void wyswietl_kom(int x, int y, tablica tab[][SIZE], int x1, int y1);
void obsluga_komentarza(int x, int y, int zn, element *lista, tablica tab[][SIZE]);
void zmien_kolor_ramki(tablica tab[][SIZE]);
void szukam_jednoznacznej(tablica tab[][SIZE], string &jednoznaczna, int &x_j, int &y_j, int &wart_jednoznaczna);


void remove(element *lista, int xx, int yy);
void dodaj_stan_do_listy(int wartosc, element *lista, int xx, int yy, char co, int index_kom);
void undo(element *lista, tablica tab[][SIZE]);
void redo(element *lista, tablica tab[][SIZE]);



void add(int x, int y, int zn, tablica tab[][SIZE]);
void remove(int x, int y, tablica tab[][SIZE]);
void zaznacz(int x, int y, tablica tab[][SIZE], int x1, int y1);
string nazwa_pliku();

void taba(ifstream &plik, element *lista);
void comments(ifstream &plik, element *lista);
void plansza_startowa(ifstream &plik, element *lista, tablica tab[][SIZE]);
void dodaj_xml_do_undo_redo(string name, element *lista, tablica tab[][SIZE]);
void zapis_xml(element *lista, string nazwa);
void wyzeruj_active_state(element *lista);
void zrob_nowy_obszar_pamieci(element *nowy, element *lista);

#endif