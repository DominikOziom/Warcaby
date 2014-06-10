#ifndef ROZGRYWKA_H
#define ROZGRYWKA_H

/*!
 * \file
 * \brief Definicja klasy rozgrywka.
 *
 *  Plik zawiera zapowiedzi funkcji wyswietlajacej plansze, liczacej ilosc pionkow
 *  przenoszacej pionek, zbijajacej pionek, zmieniajacej pionek w damke, wywolujaca
 *  ruch gracza oraz ruch komputera, sprawdzajacej czy dane pole jest puste, czy mozliwy
 *  jest ruch pionkiem, czy dany ruch jest poprawny, czy mozliwe jest bicie oraz czy dany
 *  ruch jest biciem
 */

#include "lisc.h"

/*!
 * \brief Klasa definiuje obiekt rzawierajacy rzeczywisty i aktualny stan
 * szachownicy i drzewo oceniajace ruchy.
 */
class rozgrywka{
public:
  pionek board[8][8]; /*! parametr typu pionek zawierajacy tablice dwuwymiarowa bedaca plansza do gry w warcaby */
  lisc drzewo_oceniajace; /*! parametr typu lisc uzyte w celu automatycznego wyszukania najlepszego ruchu (dla komputera) */

/*!
 * \brief Konstruktor obiektu rozgrywka.
 */
  rozgrywka();  

/*!
 * \brief Funkcja drukuje plansze z pionkami na standardowym wyjsciu.
 */
  void wyswietl();

/*!
 * \brief Funkcja zlicza aktualne pionki zadanego gracza.
 *
 * Funkcja liczy pionki danego gracza znajdujace sie na planszy i zwraca ich ilosc.
 *
 *  \param[in] ktory_gracz  -  zmienna typu int okreslajaca gracza, 1 to gracz pierwszy, 2 to gracz drugi 
 *
 *  \return Zwraca ilosc pionkow gracza.
 */
  int pionki_gracza( int ktory_gracz);

/*!
 * \brief Funkcja przenosi pionek.
 *
 *  Funkcja przenosi pionek danego gracza z wspolrzednych poczatkowych na koncowe.
 *
 *  \param[in]   wspx_pocz  -  zmienna typu int zawierajaca poczatkowa wspolrzedna x wybranego pionka 
 *  \param[in]   wspy_pocz  -  zmienna typu int zawierajaca poczatkowa wspolrzedna y wybranego pionka 
 *  \param[in]    wspx_kon  -  zmienna typu int zawierajaca koncowa wspolrzedna x wybranego pionka 
 *  \param[in]    wspy_kon  -  zmienna typu int zawierajaca koncowa wspolrzedna y wybranego pionka 
 *  \param[in] ktory_gracz  -  zmienna typu int okreslajaca gracza, 1 to gracz pierwszy, 2 to gracz drugi 
 */
  void przenies_pionek( int wspx_pocz, int wspy_pocz, int wspx_kon, int wspy_kon, int ktory_gracz );

/*!
 * \brief Funkcja zbija pionek.
 *
 *  Funkcja czyszczaca pole o wspol_pocz i pole pionka bitego i wstawiajaca pionek we wsp_kon.
 *
 *  \param[in]   wspx_pocz  -  zmienna typu int zawierajaca poczatkowa wspolrzedna x wybranego pionka 
 *  \param[in]   wspy_pocz  -  zmienna typu int zawierajaca poczatkowa wspolrzedna y wybranego pionka 
 *  \param[in]    wspx_kon  -  zmienna typu int zawierajaca koncowa wspolrzedna x wybranego pionka 
 *  \param[in]    wspy_kon  -  zmienna typu int zawierajaca koncowa wspolrzedna y wybranego pionka 
 *  \param[in] ktory_gracz  -  zmienna typu int okreslajaca gracza, 1 to gracz pierwszy, 2 to gracz drugi 
 */
  void zbicie( int wspx_pocz, int wspy_pocz, int wspx_kon, int wspy_kon, int ktory_gracz);

/*!
 * \brief Funkcja awansuje pionek na damke.
 *
 *  Funkcja sprawdza czy dany pionek moze stac sie damka i jesli tak to go awansuje.
 * 
 *  \param[in]       x_kon  -  zmienna typu int zawierajaca koncowa wspolrzedna x wybranego pionka 
 *  \param[in]       y_kon  -  zmienna typu int zawierajaca koncowa wspolrzedna y wybranego pionka 
 *  \param[in] ktory_gracz  -  zmienna typu int okreslajaca gracza, 1 to gracz pierwszy, 2 to gracz drugi 
 */
  void damka( int wspx_kon, int wspy_kon, int ktory_gracz);

/*!
 * \brief Funkcja wczytujaca ruch gracza.
 *
 *  Funkcja przeprowadza zadanego gracza przez proces wykonywania jego ruchu.
 *  Po podaniu wspolrzednyc ruch jest wykonywany.
 *  To tutaj sprawdzana jest mozliwosc wielokrotnego bicia.
 * 
 *  \param[in] ktory_gracz  -  zmienna typu int okreslajaca gracza, 1 to gracz pierwszy, 2 to gracz drugi 
 */
  void ruch_gracza(int ktory_gracz);

/*!
 * \brief Funkcja wczytujaca ruch komputera.
 *
 * Funkcja przeprowadza SI przez proces wykonywania ruchu.
 * Po wygenerowaniu wspolrzednyc ruch jest wykonywany.
 * Obslugiwana jest mozliwosc wielokrotnego bicia.
 * Zmienna lokalna glebokosc definiuje glebokosc przeszukiwania
 * drzewa oceniajacego.
 * 
 *  \param[in] ktory_gracz  -  zmienna typu int okreslajaca gracza, 1 to gracz pierwszy, 2 to gracz drugi 
 */
  void ruch_komputera(int ktory_gracz);

/*!
 * \brief Funkcja sprawdza czy pole o danych wspolrzednych jest puste.
 * 
 *  \param[in]       x  -  zmienna typu int zawierajaca wspolrzedna x wybranego pola 
 *  \param[in]       y  -  zmienna typu int zawierajaca wspolrzedna y wybranego pola 
 *
 *  \return Zwraca true jesli pole jest puste i false w przeciwnym wypadku.
 */
  bool czy_puste_pole(int x, int y);

/*!
 * \brief Funkcja sprawdza czy mozliwy jest ruch pionkiem.
 * 
 *  Funkcja sprawdza czy mozliwy jest ruch dla pionka o zadanych wspolrzednych ( ale nie bicie ).
 *
 *  \param[in]       x  -  zmienna typu int zawierajaca wspolrzedna x wybranego pionka 
 *  \param[in]       y  -  zmienna typu int zawierajaca wspolrzedna y wybranego pionka
 *  \param[in] ktory_gracz  -  zmienna typu int okreslajaca gracza, 1 to gracz pierwszy, 2 to gracz drugi 
 *
 *  \return Zwraca true jesli ruch jest mozliwy i false w przeciwnym wypadku.
 */
  bool czy_mozliwy_ruch(int x, int y, int ktory_gracz);

/*!
 * \brief Funkcja sprawdza poprawnosc ruchu.
 * 
 *  Funkcja sprawdza poprawnosc ruchu zadanego w argumentach wejsciowych.
 *
 *  \param[in]       xpocz  -  zmienna typu int zawierajaca poczatkowa wspolrzedna x wybranego pionka 
 *  \param[in]       ypocz  -  zmienna typu int zawierajaca poczatkowa wspolrzedna y wybranego pionka 
 *  \param[in]        xkon  -  zmienna typu int zawierajaca koncowa wspolrzedna x wybranego pionka 
 *  \param[in]        ykon  -  zmienna typu int zawierajaca koncowa wspolrzedna y wybranego pionka 
 *  \param[in] ktory_gracz  -  zmienna typu int okreslajaca gracza, 1 to gracz pierwszy, 2 to gracz drugi 
 *
 *  \return Zwraca true jesli ruch jest poprawny i false w przeciwnym wypadku.
 */
  bool czy_poprawny_ruch(int xpocz, int ypocz, int xkon, int ykon, int ktory_gracz);

/*!
 * \brief Funkcja sprawdza czy mozliwe jest bicie.
 * 
 *  Funkcja sprawdza czy mozliwe jest bicie z danego pola (w zakresie danej planszy).
 *
 *  \param[in]        wspx  -  zmienna typu int zawierajaca wspolrzedna x wybranego pionka 
 *  \param[in]        wspy  -  zmienna typu int zawierajaca wspolrzedna y wybranego pionka
 *  \param[in] ktory_gracz  -  zmienna typu int okreslajaca gracza, 1 to gracz pierwszy, 2 to gracz drugi 
 *
 *  \return Zwraca true jesli bicie jest mozliwe i false w przeciwnym wypadku.
 */
  bool czy_mozliwe_bicie(int wspx, int wspy, int ktory_gracz);

/*!
 * \brief Funkcja sprawdza czy wykonalo sie bicie.
 *
 *  \param[in]   wspx_pocz  -  zmienna typu int zawierajaca poczatkowa wspolrzedna x wybranego pionka 
 *  \param[in]   wspy_pocz  -  zmienna typu int zawierajaca poczatkowa wspolrzedna y wybranego pionka 
 *  \param[in]    wspx_kon  -  zmienna typu int zawierajaca koncowa wspolrzedna x wybranego pionka 
 *  \param[in]    wspy_kon  -  zmienna typu int zawierajaca koncowa wspolrzedna y wybranego pionka 
 *  \param[in] ktory_gracz  -  zmienna typu int okreslajaca gracza, 1 to gracz pierwszy, 2 to gracz drugi 
 *
 *  \return Zwraca true jesli jest bicie i false w przeciwnym wypadku.
 */
  bool czy_bicie(int wspx_pocz, int wspy_pocz, int wspx_kon, int wspy_kon, int ktory_gracz);
};




#endif
