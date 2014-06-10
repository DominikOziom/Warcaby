#ifndef LISC_H
#define LISC_H

/*!
 * \file
 * \brief Definicja klasy lisc.
 *
 *  Plik zawiera zapowiedzi funkcji sprawdzajacej czy mozlwy jest ruch,
 *  czy dane pole jest puste, czy jest mozliwe bicie, funkcji kopiujacej plansze,
 *  dodajacej wspolrzedne, wyszukujacej mozliwe ruchy, liczacej ilosc mozliwych ruchow
 *  oceniajacej ruch, zwracajacej indeks wektora z max i min ocena, funkcje zrwacajaca ocene
 *  max i min, minmax.
 */

#include "ruch.h"


/*! 
 *\brief Klasa definiuje lisc drzewa oceniajacego
 *
 * Zawiera obiekt klasy ruch zawierajacy mozliwy ruch.
 * Wektor mozliwe_ruchy zawiera wszystkie mozliwe do wykonania
 * ruchy mogace wyniknac z sytuacji przedstawionej w move.
 * Zmienna ktory_gracz definiuje, czyja jest aktualnie kolej ruchu.
 * max_min przechowuje informacje o tym czy lisc znajduje sie
 * na poziomie max czy min.
 * ilosc_ruchow przechowuje ilosc mozliwych ruchow do wykonania
 * poczawszy od sytuacji w zmiennej move.
 */
class lisc{
public:
  ruch move; /*! parametr typu ruch zawierajacy mozliwy ruch */
  vector<lisc> mozliwe_ruchy; /*! wektor typu lisc zawiera wszystkie mozliwe do wykonania */
  int ktory_gracz; /*! parametr typu int stwierdzajacy czyja jest aktualnie kolej ruchu. */
  bool max_min; /*! parametr typu bool stwierdzajacy czy lisc znajduje sie na poziomie max czy min. */
  int ilosc_ruchow; /*! parametr typu int przechowujacy ilosc mozliwych ruchow do wykonania na podstawie ulozenia pionkow w planszy w obiekcie move */


/*!
 * \brief Konstruktor obiektu lisc.
 */
  lisc();

/*! 
 *\brief Funkcja sprawdza czy mozliwy jest ruch pionkiem
 *
 * Funkcja okresla czy dla pionka o zadanych wspolrzednych istnieje
 * mozliwy do wykonania ruch.
 *
 *  \param[in] x  -  zmienna typu int zawierajaca wspolrzedna x wybranego pionka 
 *  \param[in] y  -  zmienna typu int zawierajaca wspolrzedna y wybranego pionka 
 *
 *  \return Zwraca true jesli ruch jest mozliwy i false w przeciwnym przypadku.
 */
  bool czy_mozliwy_ruch(int x, int y);

/*!
 * \brief Funkcja sprawdza czy zadane pole jest puste.
 *
 *  \param[in] x  -  zmienna typu int zawierajaca wspolrzedna x wybranego pionka 
 *  \param[in] y  -  zmienna typu int zawierajaca wspolrzedna y wybranego pionka 
 *
 *  \return Zwraca true jesli pole jest puste i false w przeciwnym przypadku.
 */
  bool czy_puste_pole(int x, int y);

/*!
 * \brief Funkcja sprawdza czy zadany pionek moze wykonac bicie.
 *
 *  \param[in] x  -  zmienna typu int zawierajaca wspolrzedna x wybranego pionka 
 *  \param[in] y  -  zmienna typu int zawierajaca wspolrzedna y wybranego pionka 
 *
 *  \return Zwraca true jesli bicie jest mozliwe i false w przeciwnym przypadku.
 */
  bool czy_mozliwe_bicie(int x, int y);

/*!
 * \brief Funkcja kopiujaca plansze 
 *
 * Funkcja kopiuje ruch wyjsciowy do zadanego obiektu w wektorze.
 *
 *  \param[in] indeks_wektora  -  zmienna typu int zawierajaca wybrane w wektorze miejsce dla danej planszy 
 */
  void skopiuj_plansze(int indeks_wektora);

/*!
 * \brief Funkcja kopiujaca wielokrotnie plansze
 *
 * Funkcja kopiuje ruch wyjsciowy do wszystkich obiektow w wektorze.
 *
 *  \param[in] rozmiar_wektora  -  zmienna typu int zawierajaca informacje o wielkosci wektora ruchow 
 */
  void skopiuj_wszedzie_plansze(int rozmiar_wektora);

/*!
 * \brief Funkcja dodaje wspolrzedne do obiektu ruch zapisanego w wektorze mozliwe_ruchy
 * 
 *  \param[in] x_pocz  -  zmienna typu int zawierajaca poczatkowa wspolrzedna x wybranego pionka 
 *  \param[in] y_pocz  -  zmienna typu int zawierajaca poczatkowa wspolrzedna y wybranego pionka 
 *  \param[in] x_kon   -  zmienna typu int zawierajaca koncowa wspolrzedna x wybranego pionka 
 *  \param[in] y_kon   -  zmienna typu int zawierajaca koncowa wspolrzedna y wybranego pionka 
 */
  void dodaj_wspolrzedne(int x_pocz, int y_pocz, int x_kon, int y_kon);

/*!
 * \brief Wyszukuje mozliwe ruchy
 *
 * Funkcja wyszukuje wszystkie mozliwe ruchy na podanej planszy 
 * i dla danego gracza i zapisuje je do wektora ruchow.
 */
  void wyszukaj_mozliwe_ruchy();

/*!
 * \brief zwraca wielkosc wektora ilosc_ruchow
 *
 * Funkcja zwraca ilosc mozliwych do wykonania ruchow
 * tj. zawartych w wektorze mozliwych ruchow.
 */
  void policz_ilosc_ruchow();

/*!
 * \brief funkcja oceniajaca plansze 
 *
 * Funkcja oceniajaca wykonany ruch
 * Punktowana jest ilosc pionkowna szachownicy
 * pionek za 5 i damka za 20.
 * Obszary blizej srodka na szachownicy sa nizej punktowane.
 * Wiersze blizej pierwotnej pozycji gracza sa wyzej punktowane.
 * Mozliwosc bicia to dodatkowe 300 punktow, a jesli po wykonanym biciu
 * nastepuje kolejne to dodawane do oceny jest kolejne 300 punktow.
 * Zdobycie damki to dodatkowe 500 punktow.
 * Styl oceniania ma wymusic na sztucznej inteligencji gre defensywna
 * i przesuwanie w miare wszystkich pionkow rownomiernie do przodu.
 */
  void ocen_ruch();

/*!
 * \brief Funkcja oblicza oceny ruchow dla kazdej mozliwosci w wektorze.
 */ 
  void wykonaj_ocene_dla_wektora_lisci();

/*!
 * \brief Funkcja zwraca indeks wektora, ktory zawiera
 * najwyzej punktowany ruch.
 */
  int zwroc_indeks_wektora_z_max_ocena();

/*!
 * \brief Funkcja zwraca indeks wektora, ktory zawiera
 * najwyzej punktowany ruch.
 */
  int zwroc_indeks_wektora_z_min_ocena();

/*!
 * \brief Zwraca najwyzsza ocene z calego wektora ruchow.
 */
  int zwroc_max_ocene_z_wektora();

/*!
 * \brief Zwraca najnizsza ocene z calego wektora ruchow.
 */
  int zwroc_min_ocene_z_wektora();

/*!
 * \brief Rekurencyjny algorytm min-max.
 *
 * Algorytm min-max bez zadnych usprawnien z mozliwoscia
 * definiowania glebokosci przeszukiwania drzewa ruchow.
 *
 *  \param[in] glebokosc   -  zmienna typu int decydujaca o glebokosci dzialania algorytmu minmax 
 *
 *  \return Zwraca ocene ostatniego ruchu.
 */
  int minmax(int glebokosc);

/*!
 * \brief Zmienia wspolrzedne w obiekcie ruch
 *
 * Funkcja zmienia zawartosc argumentow wpisujac do nich
 * wspolrzedne ruchu najbardziej korzystnego dla komputera
 * (pobrane z obiektu, o najwyzszej ocenie).
 *
 *  \param[in] &x_pocz  -  referencja do zmiennej typu int zawierajaca poczatkowa wspolrzedna x wybranego pionka 
 *  \param[in] &y_pocz  -  referencja do zmiennej typu int zawierajaca poczatkowa wspolrzedna y wybranego pionka 
 *  \param[in] &x_kon   -  referencja do zmiennej typu int zawierajaca koncowa wspolrzedna x wybranego pionka 
 *  \param[in] &y_kon   -  referencja do zmiennej typu int zawierajaca koncowa wspolrzedna y wybranego pionka 
 */
  void zwroc_wspolrzedne(int &wspx_pocz, int &wspy_pocz, int &wspx_kon, int &wspy_kon);
};


#endif
