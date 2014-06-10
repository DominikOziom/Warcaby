/*!
 * \file
 * \brief Implementacje funkcji klasy ruch
 *
 * Zawiera implementacje konstruktora klasy, funkcji sprawdzajacej
 * czy bylo bicie oraz funkcji wykonujacej ruch pionka na planszy
 */
#include "ruch.h"
using namespace std;


ruch::ruch(){
  int i, j;
plansza=new pionek*[8];
for(i=0;i<8;i++)
{
plansza[i]=new pionek [8];
}

  for(i=0;i<8;i++){
    for(j=0;j<8;j++){
      plansza[i][j].pawn=0;
      plansza[i][j].damka=false;
    }
  }
  wspx_pocz=wspy_pocz=wspx_kon=wspy_kon=ocena=0;
}



bool ruch::czy_zbicie()
{
  int delt_x, delt_y;

  delt_x=abs(wspx_kon-wspx_pocz);
  delt_y=abs(wspy_kon-wspy_pocz);

  if(delt_x==2 && delt_y==2)
    { return true;}
  return false;
}



void ruch::wykonaj_ruch()
{
  if(czy_zbicie()){
  int x_bite, y_bite;
  x_bite=(wspx_pocz+wspx_kon)/2;
  y_bite=(wspy_pocz+wspy_kon)/2;
  plansza[x_bite][y_bite].pawn=0;
  plansza[x_bite][y_bite].damka=false;
  }
  plansza[wspx_kon][wspy_kon].pawn=plansza[wspx_pocz][wspy_pocz].pawn;
  plansza[wspx_kon][wspy_kon].damka=plansza[wspx_pocz][wspy_pocz].damka;   
  plansza[wspx_pocz][wspy_pocz].pawn=0;
  plansza[wspx_pocz][wspy_pocz].damka=false;
}
