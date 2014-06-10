/*!
 * \file
 * \brief implementacja funkcji klasy lisc.
 *
 *  Plik zawiera implementacje funkcji sprawdzajacej czy mozlwy jest ruch,
 *  czy dane pole jest puste, czy jest mozliwe bicie, funkcji kopiujacej plansze,
 *  dodajacej wspolrzedne, wyszukujacej mozliwe ruchy, liczacej ilosc mozliwych ruchow
 *  oceniajacej ruch, zwracajacej indeks wektora z max i min ocena, funkcje zrwacajaca ocene
 *  max i min, minmax.
 */
#include "lisc.h"
using namespace std;

void lisc::ocen_ruch()
{
  int mark=0;
  int waga_pionka=5;
  int waga_damki=20;
  int i, j;

  for(i=0; i<8; i++){
    for(j=0; j<8; j++){
      if(move.plansza[i][j].pawn!=0){
	if(move.plansza[i][j].pawn==ktory_gracz || move.plansza[i][j].pawn==ktory_gracz+2){
	  if(move.plansza[i][j].damka)
	    mark=mark+waga_damki;
	  else
	    mark=mark+waga_pionka;
	}
	else{
	  if(move.plansza[i][j].damka)
	    mark=mark-waga_damki;
	  else
	    mark=mark-waga_pionka;
	}
      }
    }
  }
  
  if(ktory_gracz==1){
    for(i=0; i<8; i++){
      for(j=0; j<8; j++){
	if(move.plansza[i][j].pawn==1 || move.plansza[i][j].pawn==3){
	  if(6<=i && i<8) mark=mark+5;
	  if(4<=i && i<6) mark=mark+10;
	  if(2<=i && i<4) mark=mark+15;
	  if(0<=i && i<2) mark=mark+20;
	  if((i==0||i==7) && (j==0||j==7)) mark=mark+20;
	  if((i==1||i==6) && (j==1||j==6)) mark=mark+15;
	  if((i>1 && i<6) && (j>1 && j<6)) mark=mark+10;
	}
      }
      }
    if(move.wspx_kon==7) mark=mark+500;
    if(move.czy_zbicie()) mark=mark+300;
    if(czy_mozliwe_bicie(move.wspx_kon, move.wspy_kon)) mark=mark+300;
  }
  if(ktory_gracz==2){
    for(i=0; i<8; i++){
      for(j=0; j<8; j++){
	if(move.plansza[i][j].pawn==2 || move.plansza[i][j].pawn==4){
	  if(6<=i && i<8) mark=mark+20;
	  if(4<=i && i<6) mark=mark+15;
	  if(2<=i && i<4) mark=mark+10;
	  if(0<=i && i<2) mark=mark+5;
	  if((i==0||i==7) && (j==0||j==7)) mark=mark+20;
	  if((i==1||i==6) && (j==1||j==6)) mark=mark+15;
	  if((i>1 && i<6) && (j>1 && j<6)) mark=mark+10;
	}
      }
      }
    if(move.wspx_kon==0) mark=mark+500;
    if(move.czy_zbicie()) mark=mark+300;
    if(czy_mozliwe_bicie(move.wspx_kon, move.wspy_kon)) mark=mark+300;
    }
 
  move.ocena=mark;
}


void lisc::wykonaj_ocene_dla_wektora_lisci()
{
  int i;
  policz_ilosc_ruchow();
  for(i=0; i<ilosc_ruchow; i++)
    {
      mozliwe_ruchy[i].ocen_ruch();
    }
}


int lisc::zwroc_indeks_wektora_z_max_ocena()
{
  int max=0;
  int index=0;
  int i;
  policz_ilosc_ruchow();
  for(i=0; i<ilosc_ruchow; i++)
    {
      if (max<mozliwe_ruchy[i].move.ocena)
	{
	  max=mozliwe_ruchy[i].move.ocena;
	  index=i;
	}    
    }
  return index;
}


int lisc::zwroc_indeks_wektora_z_min_ocena()
{
  int min;
  int index=0;
  int i;
  policz_ilosc_ruchow();
  min=mozliwe_ruchy[2].move.ocena;
  for(i=0; i<ilosc_ruchow-1; i++)
    {
      if (min>mozliwe_ruchy[i].move.ocena && mozliwe_ruchy[i].move.ocena!=0)
	{
	  min=mozliwe_ruchy[i].move.ocena;
	  index=i;
	}    
    }
  return index;
}


int lisc::zwroc_max_ocene_z_wektora()
{
  int max=0;
  int i;
  policz_ilosc_ruchow();
  for(i=0; i<ilosc_ruchow; i++)
    {
      if (max<mozliwe_ruchy[i].move.ocena)
	{
	  max=mozliwe_ruchy[i].move.ocena;
	}    
    }
  return max;
}


int lisc::zwroc_min_ocene_z_wektora()
{
  int min;
  int i;
  policz_ilosc_ruchow();
  min=mozliwe_ruchy[2].move.ocena;
  for(i=0; i<ilosc_ruchow-1; i++)
    {
      if (min>mozliwe_ruchy[i].move.ocena && mozliwe_ruchy[i].move.ocena!=0)
	{
	  min=mozliwe_ruchy[i].move.ocena;
	}    
    }
  return min;
}


int lisc::minmax(int glebokosc)
{
  int i, t;

  wyszukaj_mozliwe_ruchy();
  policz_ilosc_ruchow();
  skopiuj_wszedzie_plansze(ilosc_ruchow);
  for(i=0; i<ilosc_ruchow; i++)
    {
      mozliwe_ruchy[i].move.wykonaj_ruch();
    }

  if(glebokosc==1){
    wykonaj_ocene_dla_wektora_lisci();
    if(max_min){
      return zwroc_max_ocene_z_wektora();}
    else{
      return zwroc_min_ocene_z_wektora();}
  }

  for (i=0; i<ilosc_ruchow; i++)
    {
      t=mozliwe_ruchy[i].minmax(glebokosc-1);
      mozliwe_ruchy[i].move.ocena=t;
    }

  if(max_min){
    return zwroc_max_ocene_z_wektora();}
  else{
    return zwroc_min_ocene_z_wektora();}
}


void lisc::zwroc_wspolrzedne(int &wspx_pocz, int &wspy_pocz, int &wspx_kon, int &wspy_kon)
{
  int i;
  policz_ilosc_ruchow();
  for (i=0; i<ilosc_ruchow; i++){
    if(mozliwe_ruchy[i].move.ocena==move.ocena)
      {
	wspx_pocz=mozliwe_ruchy[i].move.wspx_pocz;
	wspy_pocz=mozliwe_ruchy[i].move.wspy_pocz;
	wspx_kon=mozliwe_ruchy[i].move.wspx_kon;
	wspy_kon=mozliwe_ruchy[i].move.wspy_kon;
      }
  }
}

lisc::lisc(){
  max_min=false;
}


bool lisc::czy_mozliwy_ruch(int x, int y)
{
  if(ktory_gracz==1){
    if(x<7 && y<7){
      if(move.plansza[x+1][y+1].pawn==0) return true;
    }
    if(x<7 && y>0){
      if(move.plansza[x+1][y-1].pawn==0) return true;
    }
    if(move.plansza[x][y].damka){
      if(x>0 && y<7){
	if(move.plansza[x-1][y+1].pawn==0) return true;
      }
      if(x>0 && y>0){
	if(move.plansza[x-1][y-1].pawn==0) return true;
      }}}
  else {
    if(x>0 && y<7){
      if(move.plansza[x-1][y+1].pawn==0) return true;
    }
    if(x>0 && y>0){
      if(move.plansza[x-1][y-1].pawn==0) return true;
    }
    if(!move.plansza[x][y].damka){
      if(x<7 && y<7){
	if(move.plansza[x+1][y+1].pawn==0) return true;
      }
      if(x<7 && y>0){
	if(move.plansza[x+1][y-1].pawn==0) return true;
      }}}
  return false;
}


bool lisc::czy_puste_pole(int x, int y){
  if((x>=0)&&(x<8)&&(y>=0)&&(y<8)){
    if(move.plansza[x][y].pawn==0)
      return true;
  }
  return false;
}


bool lisc::czy_mozliwe_bicie(int x, int y)
{
  if(ktory_gracz==1){
    if(x<6&&y<6){
      if(move.plansza[x+1][y+1].pawn==2 || move.plansza[x+1][y+1].pawn==4){
	if(move.plansza[x+2][y+2].pawn==0){ return true;}
      }}

    if(x<6&&y>1){
      if(move.plansza[x+1][y-1].pawn==2 || move.plansza[x+1][y-1].pawn==4){
	if(move.plansza[x+2][y-2].pawn==0){ return true;}
      }}

    if(x>1&&y<6){
      if(move.plansza[x-1][y+1].pawn==2 || move.plansza[x-1][y+1].pawn==4){
	if(move.plansza[x-2][y+2].pawn==0){ return true;}
      }}

    if(x>1&&y>1){
      if(move.plansza[x-1][y-1].pawn==2 || move.plansza[x-1][y-1].pawn==4){
	if(move.plansza[x-2][y-2].pawn==0){ return true;}
      }}
  }
  else {
    if(x<6&&y<6){
      if(move.plansza[x+1][y+1].pawn==1 || move.plansza[x+1][y+1].pawn==3){
	if(move.plansza[x+2][y+2].pawn==0){ return true;}
      }}

    if(x<6&&y>1){
      if(move.plansza[x+1][y-1].pawn==1 || move.plansza[x+1][y-1].pawn==3){
	if(move.plansza[x+2][y-2].pawn==0){ return true;}
      }}

    if(x>1&&y<6){
      if(move.plansza[x-1][y+1].pawn==1 || move.plansza[x-1][y+1].pawn==3){
	if(move.plansza[x-2][y+2].pawn==0){ return true;}
      }}

    if(x>1&&y>1){
      if(move.plansza[x-1][y-1].pawn==1 || move.plansza[x-1][y-1].pawn==3){
	if(move.plansza[x-2][y-2].pawn==0){ return true;}
      }}
  }
  return false;
}


void lisc::skopiuj_plansze(int indeks_wektora)
{
  int i, j;
  for(i=0; i<8; i++){
    for(j=0; j<8; j++){
      mozliwe_ruchy[indeks_wektora].move.plansza[i][j].pawn=move.plansza[i][j].pawn;
      mozliwe_ruchy[indeks_wektora].move.plansza[i][j].damka=move.plansza[i][j].damka;
    }
  }
}


void lisc::skopiuj_wszedzie_plansze(int rozmiar_wektora)
{
  int i;
  for(i=0; i<rozmiar_wektora; i++){
    skopiuj_plansze(i);
  }
}


void lisc::dodaj_wspolrzedne(int x_pocz, int y_pocz, int x_kon, int y_kon)
{
  lisc Wspolrzedne;
  Wspolrzedne.move.wspx_pocz=x_pocz;
  Wspolrzedne.move.wspy_pocz=y_pocz;
  Wspolrzedne.move.wspx_kon=x_kon;
  Wspolrzedne.move.wspy_kon=y_kon;

  if(ktory_gracz==1)
    Wspolrzedne.ktory_gracz=2;
  else
    Wspolrzedne.ktory_gracz=1;

  Wspolrzedne.max_min=(!max_min);
  mozliwe_ruchy.push_back(Wspolrzedne);
}


void lisc::wyszukaj_mozliwe_ruchy()
{
  int i, j;
  ruch Wspolrzedne;

  if(ktory_gracz==1)
    {
      for(i=0; i<8; i++)
	{
	  for(j=0; j<8; j++)
	    {
	      if(move.plansza[i][j].pawn==1 || move.plansza[i][j].pawn==3)
		{
		  if(czy_mozliwy_ruch(i, j))
		    {
		      if(czy_puste_pole(i+1, j+1))
			{
			  dodaj_wspolrzedne(i, j, i+1, j+1);			
			}
		      if(czy_puste_pole(i+1, j-1))
			{
			  dodaj_wspolrzedne(i, j, i+1, j-1);			
			}
		      if(move.plansza[i][j].pawn==3)
			{			 
			  if(czy_puste_pole(i-1, j+1))
			    {
			      dodaj_wspolrzedne(i, j, i-1, j+1);       	   
			    }
			  if(czy_puste_pole(i-1, j-1))
			    {
			      dodaj_wspolrzedne(i, j, i-1, j-1);	
			    }			    
			}
		    }
		  if(czy_mozliwe_bicie(i, j))
		    {
		      if(czy_puste_pole(i+2, j+2))
			{
			  if(move.plansza[i+1][j+1].pawn!=1 && move.plansza[i+1][j+1].pawn!=3)
			    {
			      dodaj_wspolrzedne(i, j, i+2, j+2);			
			    }
			}
		      if(czy_puste_pole(i+2, j-2))
			{
			  if(move.plansza[i+1][j-1].pawn!=1 && move.plansza[i+1][j-1].pawn!=3)
			    {
			      dodaj_wspolrzedne(i, j, i+2, j-2);
			    }			
			}
		      if(czy_puste_pole(i-2, j+2))
			{
			  if(move.plansza[i-1][j+1].pawn!=1 && move.plansza[i-1][j+1].pawn!=3)
			    {
			      dodaj_wspolrzedne(i, j, i-2, j+2);
			    }			
			}
		      if(czy_puste_pole(i-2, j-2))
			{
			  if(move.plansza[i-1][j-1].pawn!=1 && move.plansza[i-1][j-1].pawn!=3)
			    {
			      dodaj_wspolrzedne(i, j, i-2, j-2);	
			    }		
			}     
		    }
		}	     
	    }
	}
    }
  else
    {
     for(i=0; i<8; i++)
	{
	  for(j=0; j<8; j++)
	    {
	      if(move.plansza[i][j].pawn==2 || move.plansza[i][j].pawn==4)
		{
		  if(czy_mozliwy_ruch(i, j))
		    {
		      if(czy_puste_pole(i-1, j+1))
			{
			  dodaj_wspolrzedne(i, j, i-1, j+1);			
			}
		      if(czy_puste_pole(i-1, j-1))
			{
			  dodaj_wspolrzedne(i, j, i-1, j-1);			
			}
		      if(move.plansza[i][j].pawn==4)
			{			 
			  if(czy_puste_pole(i+1, j+1))
			    {
			      dodaj_wspolrzedne(i, j, i+1, j+1);	       
			    }
			  if(czy_puste_pole(i+1, j-1))
			    {
			      dodaj_wspolrzedne(i, j, i+1, j-1);	
			    }			    
			}
		    }
		  if(czy_mozliwe_bicie(i, j))
		    {
		      if(czy_puste_pole(i+2, j+2))
			{
			  if(move.plansza[i+1][j+1].pawn!=2 && move.plansza[i-1][j-1].pawn!=4)
			    {
			      dodaj_wspolrzedne(i, j, i+2, j+2);
			    }			
			}
		      if(czy_puste_pole(i+2, j-2))
			{
			  if(move.plansza[i+1][j-1].pawn!=2 && move.plansza[i-1][j-1].pawn!=4)
			    {
			      dodaj_wspolrzedne(i, j, i+2, j-2);
			    }		       
			}
		      if(czy_puste_pole(i-2, j+2))
			{
			  if(move.plansza[i-1][j+1].pawn!=2 && move.plansza[i-1][j-1].pawn!=4)
			    {
			      dodaj_wspolrzedne(i, j, i-2, j+2);	
			    }		
			}
		      if(czy_puste_pole(i-2, j-2))
			{
			  if(move.plansza[i-1][j-1].pawn!=2 && move.plansza[i-1][j-1].pawn!=4)
			    {
			      dodaj_wspolrzedne(i, j, i-2, j-2);
			    }		       
			}		     
		    }
		}	     
	    }
	}
    }
}


void lisc::policz_ilosc_ruchow()
{
  ilosc_ruchow= mozliwe_ruchy.size();
}

