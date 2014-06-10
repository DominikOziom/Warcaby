/*!
 * \file
 * \brief Czesc glowna programu Warcaby
 *
 * Czesc glowna programu, wyswietlajaca zasady gry, menu
 * i obslugujaca petle gry, ktora sie konczy, gdy ktorys 
 * z graczy straci wszystkie pionki. Wyswietlany jest wowczas komunikat
 * i konczona praca programu.
 */
#include "rozgrywka.h"
#include <iostream>
using namespace std;

int main()
{ 
  rozgrywka R;
  int wybor;

  cout << "\t\t***   " << "WARCABY" << "***" << endl << endl;
  cout << endl << endl << "\t\tWitajcie w grze!" << endl << endl;
  cout << "\t\t REGULY GRY" << endl << endl;
  cout << "Pionki poruszaja sie tylko do przodu po skosach" << endl;
  cout << "Mozliwe sa bicia do tylu" << endl;
  cout << "Mozliwe sa wielokrotne bicia" << endl;
  cout << "Po osiagniecu przeciwnej krawedzi pionek staje sie damka" << endl;
  cout << "Damka porusza sie we wszystkie strony o jedno pole" << endl;
  cout << "Bicia nie sa przymusowe" << endl << endl;
  cout << "SI jest ustawione na przeszukiwanie do 3 stopnia w glab" << endl;

  cout << "\t\tAby rozpoczac gre wcisnij ENTER";
  getchar();
  cout << "\t\tWybierz tryb gry:" << endl;
  cout << "\t\t1 --> gracz 1 vs gracz 2" << endl;
  cout << "\t\t2 --> gracz 1 vs komputer" << endl << endl;
  cout << "\t\tTwoj wybor:  ";
  cin >> wybor;
  cout << endl << endl;
  R.wyswietl();
  if(wybor==1){
    while((R.pionki_gracza(1)!=0)||(R.pionki_gracza(2)!=0)){
      if(R.pionki_gracza(1)==0){ break;}
      R.ruch_gracza(1);
      R.wyswietl();
      if(R.pionki_gracza(2)==0){ break;}
      R.ruch_gracza(2);
      R.wyswietl();
    }
  }
  if(wybor==2){
    while((R.pionki_gracza(1)!=0)||(R.pionki_gracza(2)!=0)){
      if(R.pionki_gracza(1)==0){ break;}
      R.ruch_gracza(1);
      R.wyswietl();
      if(R.pionki_gracza(2)==0){ break;}
      R.ruch_komputera(2);
      R.wyswietl();
    }
  }

  if(R.pionki_gracza(1)!=0)
    cout << endl << "\t\t" << "gracz 1" << " ZWYCIEZA! " << endl;
  else {
    if(wybor==1)
      cout << endl << "\t\t" << "gracz 2" << " ZWYCIEZA! " << endl;    
    else
      cout << endl << "\t\t" << "komputer" << " ZWYCIEZA! " << endl;  
  }  
  cin.ignore();
                    
  getchar();
  return 0;
}

