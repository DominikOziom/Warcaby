/*!
 * \file
 * \brief Implementacja funkcji klasy rozgrywka.
 *
 *  Plik zawiera implementacje funkcji wyswietlajacej plansze, liczacej ilosc pionkow
 *  przenoszacej pionek, zbijajacej pionek, zmieniajacej pionek w damke, wywolujaca
 *  ruch gracza oraz ruch komputera, sprawdzajacej czy dane pole jest puste, czy mozliwy
 *  jest ruch pionkiem, czy dany ruch jest poprawny, czy mozliwe jest bicie oraz czy dany
 *  ruch jest biciem
 */
#include "rozgrywka.h"
using namespace std;

rozgrywka::rozgrywka(){
  int i,j;
 
  for(i=0;i<3;i++)
    {
      for(j=0;j<8;j++)
	{
	  if((i==0&&(j==0||j==2||j==4||j==6))||(i==1&&(j==1||j==3||j==5||j==7))||(i==2&&(j==0||j==2||j==4||j==6))){
	    board[i][j].pawn=0;
	    board[i][j].damka=false;}
	  else {
	    board[i][j].pawn=1;
	    board[i][j].damka=false;}
	}
    }

  for(i=3;i<5;i++)
    {
      for(j=0;j<8;j++)
	{
	  board[i][j].pawn=0;
	  board[i][j].damka=false;}
	}

  for(i=5;i<8;i++)
    {
      for(j=0;j<8;j++)
	{
	  if((i==5&&(j==1||j==3||j==5||j==7))||(i==7&&(j==1||j==3||j==5||j==7))||(i==6&&(j==0||j==2||j==4||j==6))){
	    board[i][j].pawn=0;
	    board[i][j].damka=false;}
	  else {
	    board[i][j].pawn=2;
	    board[i][j].damka=false;}
	}
    }
}


void rozgrywka::wyswietl() 
{           
  int i,j,w,z;
  system("clear");
  cout << endl;
  cout << "   GRACZ 1    ";
  cout << "\t ";
  for(w=0;w<8;w++){
    cout << "______";}
  cout << "_" << endl; 
  for(i=0;i<8;i++)
    {
      cout << "\t\t|";
      for(w=0;w<8;w++){
	cout << "|";
	if (board[i][w].pawn==0)
	  cout << "     ";
	else
	for(z=0;z<5;z++)
	cout << board[i][w].pawn;}
      cout << "||" << endl;


      cout << "\t\t||";
      for(j=0;j<8;j++){
        {
	if (board[i][j].pawn==0)
	  cout << "     ";
	else
	  for(z=0;z<5;z++)
	  cout << board[i][j].pawn;
        }
	cout <<"|";}
      cout << "|" <<  "   |" << (i+1) << endl;
      cout << "\t\t|";
      for(w=0;w<8;w++)
	cout << "|_____";
      cout << "||" << endl;
    }
  cout << "   GRACZ 2    ";
 cout << "\t ";
  for(i=0;i<8;i++)
    cout << "   _  ";
  cout << endl;   
  cout << "\t\t";
  for(i=0;i<8;i++)
    cout << "    " << i+1 << " ";
  cout << endl << endl;    
}


int rozgrywka::pionki_gracza( int ktory_gracz)
{
  int i,j, ilosc=0;
  int pion, p1, p2;
  p1=ktory_gracz;
  p2=ktory_gracz+2;
    
  for(i=0;i<8;i++)
    {
      for(j=0;j<8;j++)
        {
	  pion=board[i][j].pawn;
	  if((pion==p1) || (pion==p2)){ //liczymy pionki i damki danego gracza
	    ilosc++;}
        }
    }
  return ilosc;    
}

void rozgrywka::przenies_pionek( int wspx_pocz, int wspy_pocz, int wspx_kon, int wspy_kon, int ktory_gracz )
{
  int pionek;
  bool dama;
  pionek=board[wspx_pocz][wspy_pocz].pawn;
  dama=board[wspx_pocz][wspy_pocz].damka;
  board[wspx_pocz][wspy_pocz].pawn=0;
  board[wspx_pocz][wspy_pocz].damka=false;

  board[wspx_kon][wspy_kon].pawn=pionek;
  board[wspx_kon][wspy_kon].damka=dama;
    
}


void rozgrywka::zbicie( int wspx_pocz, int wspy_pocz, int wspx_kon, int wspy_kon, int ktory_gracz)
{
  int wspx_pionka_bitego, wspy_pionka_bitego, pion;
  bool dama;

  wspx_pionka_bitego=(wspx_kon+wspx_pocz)/2;
  wspy_pionka_bitego=(wspy_kon+wspy_pocz)/2;
  dama=board[wspx_pocz][wspy_pocz].damka;
  pion=board[wspx_pocz][wspy_pocz].pawn;
  board[wspx_pionka_bitego][ wspy_pionka_bitego].pawn=0;
  board[wspx_pocz][wspy_pocz].pawn=0;
  board[wspx_pocz][wspy_pocz].damka=false;

  board[wspx_kon][wspy_kon].pawn=pion;
  board[wspx_kon][wspy_kon].damka=dama;
  cout << "\t\t" << "gracz "<< ktory_gracz << " ZBIJA PRZECIWNIKA!" << endl;
} 


void rozgrywka::damka( int wspx_kon, int wspy_kon, int ktory_gracz)
{
  if(wspx_kon==0 && ktory_gracz==2){
    board[wspx_kon][wspy_kon].pawn=4;
    board[wspx_kon][wspy_kon].damka=true;
    cout << endl << "\t\tPionek gracza" <<ktory_gracz << "zmienia sie w damke!";
  }
  if(wspx_kon==7 && ktory_gracz==1){
    board[wspx_kon][wspy_kon].pawn=3;
    board[wspx_kon][wspy_kon].damka=true;
    cout << endl << "\t\tPionek gracza" <<ktory_gracz << "zmienia sie w damke!";
  }
}


bool rozgrywka::czy_puste_pole(int x, int y)
{
  if(board[x][y].pawn==0) return true;
  else return false;
}


bool rozgrywka::czy_mozliwy_ruch(int x, int y, int ktory_gracz)
{
  if(ktory_gracz==1){
    if(!board[x][y].damka){
      if(x+1<=7 && y+1<=7){
	if(board[x+1][y+1].pawn==0) return true;
      }
      if(x+1<=7 && y-1>=0){
	if(board[x+1][y-1].pawn==0) return true;
      }}
    else{
      if(x+1<=7 && y+1<=7){
	if(board[x+1][y+1].pawn==0) return true;
      }
      if(x+1<=7 && y-1>=0){
	if(board[x+1][y-1].pawn==0) return true;
      }
      if(x-1>=0 && y+1<=7){
	if(board[x-1][y+1].pawn==0) return true;
      }
      if(x-1>=0 && y-1>=0){
	if(board[x-1][y-1].pawn==0) return true;
      }}}
  else {
 if(!board[x][y].damka){
      if(x-1>=0 && y+1<=7){
	if(board[x-1][y+1].pawn==0) return true;
      }
      if(x-1>=0 && y-1>=0){
	if(board[x-1][y-1].pawn==0) return true;
      }}
    else{
      if(x+1<=7 && y+1<=7){
	if(board[x+1][y+1].pawn==0) return true;
      }
      if(x+1<=7 && y-1>=0){
	if(board[x+1][y-1].pawn==0) return true;
      }
      if(x-1>=0 && y+1<=7){
	if(board[x-1][y+1].pawn==0) return true;
      }
      if(x-1>=0 && y-1>=0){
	if(board[x-1][y-1].pawn==0) return true;
      }}}
  return false;
  }
 

bool rozgrywka::czy_poprawny_ruch(int xpocz, int ypocz, int xkon, int ykon, int ktory_gracz){
  int delt_x, delt_y;
  if(!czy_puste_pole(xkon, ykon)){ return false;}
  delt_x=abs(xkon-xpocz);
  delt_y=abs(ykon-ypocz);
  if(delt_x!=delt_y){ return false;}

  if(czy_bicie(xpocz, ypocz, xkon, ykon, ktory_gracz)){
    if(delt_x!=2 || delt_y!=2){ return false;}
    else return true;}
  else
    if(board[xpocz][ypocz].damka){
      if(delt_x!=1 || delt_y!=1){ return false;}
      else return true;
    }
    else{
      if(board[xpocz][ypocz].pawn==1 && ktory_gracz==1){
	if((xkon-xpocz)==1 && (delt_y==1)) return true;}
      if(board[xpocz][ypocz].pawn==2 && ktory_gracz==2){
	if((xpocz-xkon)==1 && (delt_y==1)) return true;}
    }
  return false;
}


bool rozgrywka::czy_mozliwe_bicie(int x, int y, int ktory_gracz)
{
  if(ktory_gracz==1){
    if(x+2<=7&&y+2<=7){
      if(board[x+1][y+1].pawn==2 || board[x+1][y+1].pawn==4){
	if(board[x+2][y+2].pawn==0) return true;
      }}
    if(x+2<=7&&y-2>=0){
      if(board[x+1][y-1].pawn==2 || board[x+1][y-1].pawn==4){
	if(board[x+2][y-2].pawn==0) return true;
      }}
    if(x-2>=0&&y+2<=7){
      if(board[x-1][y+1].pawn==2 || board[x-1][y+1].pawn==4){
	if(board[x-2][y+2].pawn==0) return true;
      }}
    if(x-2>=0&&y-2>=0){
      if(board[x-1][y-1].pawn==2 || board[x-1][y-1].pawn==4){
	if(board[x-2][y-2].pawn==0) return true;
      }}
  }
  else {
    if(x+2<=7&&y+2<=7){
      if(board[x+1][y+1].pawn==1 || board[x+1][y+1].pawn==3){
	if(board[x+2][y+2].pawn==0) return true;
      }}
    if(x+2<=7&&y-2>=0){
      if(board[x+1][y-1].pawn==1 || board[x+1][y-1].pawn==3){
	if(board[x+2][y-2].pawn==0) return true;
      }}
    if(x-2>=0&&y+2<=7){
      if(board[x-1][y+1].pawn==1 || board[x-1][y+1].pawn==3){
	if(board[x-2][y+2].pawn==0) return true;
      }}
    if(x-2>=0&&y-2>=0){
      if(board[x-1][y-1].pawn==1 || board[x-1][y-1].pawn==3){
	if(board[x-2][y-2].pawn==0) return true;
      }}
  }
  return false;
}

bool rozgrywka::czy_bicie(int wspx_pocz, int wspy_pocz, int wspx_kon, int wspy_kon, int ktory_gracz)
{
  int delt_x, delt_y, x_zbijany, y_zbijany;
  int przeciwnik;
  delt_x=abs(wspx_kon-wspx_pocz);
  delt_y=abs(wspy_kon-wspy_pocz);

  x_zbijany=(wspx_pocz+wspx_kon)/2;
  y_zbijany=(wspy_pocz+wspy_kon)/2;
  przeciwnik=board[x_zbijany][y_zbijany].pawn;

  if(delt_x==2 && delt_y==2){
    if ((ktory_gracz==1 && przeciwnik==2) || (ktory_gracz==2 && przeciwnik==1)) return true;}
  return false;

}


void rozgrywka::ruch_gracza(int ktory_gracz)
{ 
  int wspx_pocz, wspy_pocz, wspx_kon, wspy_kon;
  int i=0, z, x, y;
        
  cout << "gracz " << ktory_gracz << ": podaj wspolrzedne pionka: wiersz kolumna (np. 3 3 ), ktory chcesz ruszyc: "  << endl; 
  while(i!=(-1))
    {
      if(i>0)cout <<  "Wybierz odpowiedni pionek!" << endl;  
      cin >> wspx_pocz;
      cin >> wspy_pocz;
      wspx_pocz--;
      wspy_pocz--;
      if(((board[wspx_pocz][wspy_pocz].pawn==ktory_gracz||board[wspx_pocz][wspy_pocz].pawn==(ktory_gracz+2)) && czy_mozliwy_ruch(wspx_pocz, wspy_pocz, ktory_gracz))||czy_mozliwe_bicie(wspx_pocz,wspy_pocz,ktory_gracz))  //jesli pionek odpowiada danemu graczowi i da sie wykonac ruch 
	i=-1;
      else{
	i=1;
      }}
    
  cout << "gracz " << ktory_gracz << ": podaj, gdzie chcesz ruszyc: "  << endl; 

  i=0;

  while(i!=(-1)) //wczytywanie docelowych wspolrzednych pionka
    {
      if(i==2)
	cout << "Bledny ruch! Podaj wspolrzedne ponownie: " << endl;
      cin >> wspx_kon;
      cin >> wspy_kon;
      wspx_kon--;
      wspy_kon--;
      if(!czy_poprawny_ruch(wspx_pocz, wspy_pocz, wspx_kon, wspy_kon, ktory_gracz)){
	i=2;
      }
      else {
	if(czy_bicie(wspx_pocz, wspy_pocz, wspx_kon, wspy_kon, ktory_gracz)){
	  zbicie(wspx_pocz, wspy_pocz, wspx_kon, wspy_kon, ktory_gracz);
	  damka(wspx_kon, wspy_kon, ktory_gracz);
	  wyswietl();
	  if(czy_mozliwe_bicie(wspx_kon, wspy_kon, ktory_gracz)){
	    x=wspx_kon;
	    y=wspy_kon;
	    do{
	      z=0;
	      while(z!=-1){
		cout << "gracz " << ktory_gracz << " kontynuuje bicie:" << endl;
		cin >> wspx_kon;
		cin >> wspy_kon;
		wspx_kon--;
		wspy_kon--;
		if(czy_bicie(x, y, wspx_kon, wspy_kon, ktory_gracz)){
		  zbicie(x, y, wspx_kon, wspy_kon, ktory_gracz);
		  damka(wspx_kon, wspy_kon, ktory_gracz);
		  wyswietl();
		  z=-1;
		  x=wspx_kon;
		  y=wspy_kon;
		}
		else{
		  z=1;
		}
	      }
	      i=-1;
	    }
	    while(czy_mozliwe_bicie(wspx_kon, wspy_kon, ktory_gracz));
	  }
	  i=-1;
	}
	else {
	  przenies_pionek( wspx_pocz, wspy_pocz, wspx_kon, wspy_kon, ktory_gracz );
	  damka(wspx_kon, wspy_kon, ktory_gracz);
	  i=-1;
	}
      }
    }
}


void rozgrywka::ruch_komputera(int ktory_gracz){
 int wspx_pocz, wspy_pocz, wspx_kon, wspy_kon;
  int a,b;
  int glebokosc=3;

  drzewo_oceniajace.ktory_gracz=2;
  drzewo_oceniajace.max_min=true;
  for(a=0; a<8; a++){
    for(b=0; b<8; b++){
      drzewo_oceniajace.move.plansza[a][b].pawn=board[a][b].pawn;
      drzewo_oceniajace.move.plansza[a][b].damka=board[a][b].damka;
    }
  }
  drzewo_oceniajace.move.ocena=drzewo_oceniajace.minmax(glebokosc);
  drzewo_oceniajace.zwroc_wspolrzedne(wspx_pocz, wspy_pocz, wspx_kon, wspy_kon);

  if(czy_bicie(wspx_pocz, wspy_pocz, wspx_kon, wspy_kon, ktory_gracz)){
    zbicie(wspx_pocz, wspy_pocz, wspx_kon, wspy_kon, ktory_gracz);
    damka(wspx_kon, wspy_kon, ktory_gracz);
    wyswietl();
    while(czy_mozliwe_bicie(wspx_kon, wspy_kon, ktory_gracz)){
	  cout << "komputer kontynuuje ruch:" << endl;
	  drzewo_oceniajace.ktory_gracz=2;
	  drzewo_oceniajace.max_min=true;
	  for(a=0; a<8; a++){
	    for(b=0; b<8; b++){
	      drzewo_oceniajace.move.plansza[a][b].pawn=board[a][b].pawn;
	      drzewo_oceniajace.move.plansza[a][b].damka=board[a][b].damka;
	    }
	  }
	  drzewo_oceniajace.move.ocena=drzewo_oceniajace.minmax(glebokosc);
	  drzewo_oceniajace.zwroc_wspolrzedne(wspx_pocz, wspy_pocz, wspx_kon, wspy_kon);

	  if(czy_bicie(wspx_pocz, wspy_pocz, wspx_kon, wspy_kon, ktory_gracz)){
	    zbicie(wspx_pocz, wspy_pocz, wspx_kon, wspy_kon, ktory_gracz);
	    damka(wspx_kon, wspy_kon, ktory_gracz);
	    wyswietl();
	  }
	}
      }
  else {
    przenies_pionek( wspx_pocz, wspy_pocz, wspx_kon, wspy_kon, ktory_gracz );
    damka(wspx_kon, wspy_kon, ktory_gracz);
  }
}

