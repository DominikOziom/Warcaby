#ifndef RUCH_H
#define RUCH_H

/*!
 * \file
 * \brief Definicja klasy ruch i pionek.
 *
 * Zawiera zapowiedzi konstruktora klasy, funkcji sprawdzajacej
 * czy bylo bicie oraz funkcji wykonujacej ruch pionka na planszy
 */

#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include <vector>

using namespace std;


/*!
 * \brief Klasa definiująca pionek
 *
 * wartosci zmiennej pawn == 1 lub pawn == 2 w zaleznosci od gracza
 * jesli pionek jest damka (damka==true) to pawn ma wartosc
 * oryginalna przemnozona przez 2
 */
class pionek{
public:
  int pawn;/*! parametr typu int ktorego wartosc wskazuje na odpowiedni pionek danego gracza */
  bool damka;/*! parametr typu bool stwierdzajacy czy dana figura to damka czy nie */

};

/*! 
 *\brief Klasa definiuje mozliwy ruch
 *
 * Zawiera szachownice z wykonanym ruchem
 * zadanym poprzez wspolrzedne poczatkowe i koncowe.
 * Dodatkowo zawiera zmienna ocena, ktora pozniej sluzy
 * do przechowywania oceny aktualnej sytuacji na planszy.
 */
class ruch{
public:
  pionek **plansza;/*! parametr typu pionek deklarujacy plansze do gry w warcaby */
  int wspx_pocz;/*! parametr typu int zawierajacy wspolrzedna x poczatkowa ruchu */
  int wspy_pocz;/*! parametr typu int zawierajacy wspolrzedna y poczatkowa ruchu */
  int wspx_kon;/*! parametr typu int zawierajacy wspolrzedna x koncowa ruchu */
  int wspy_kon;/*! parametr typu int zawierajacy wspolrzedna y koncowa ruchu */
  int ocena;/*! parametr typu int zawierajacy ocene tablicy pionkow */


/*!
 * \brief Konstruktor obiektu ruch.
 */
  ruch();

/*!
 * \brief Funkcja stwierdza czy zadany ruch jest biciem.
 *
 *  funkcja typu bool sprawdzajaca czy dany ruch gracza jest biciem.
 *  Czyta w tym celu wspolrzedne wspx_pocz, wspy_pocz oraz wspx_kon i wspy_kon
 *
 *   \return Zwraca true jesli ruch byl biciem i false w przeciwnym przypadku.
 */
  bool czy_zbicie();

/*!
 * \brief Funkcja wykonuje zadany ruch.
 *
 *  Funkcja typu void wykonujaca ruch na obiekcie typu pionek poprzez odczytanie 
 *  wspolrzednych obiektu typu ruch. 
 */
  void wykonaj_ruch(); // funkcja wykonuje zadany ruch
};



#endif
