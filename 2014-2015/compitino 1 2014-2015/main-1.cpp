#include<iostream>
#include<fstream>
using namespace std;
struct tripla{
  int prof, riga, colonna; 
  tripla(int a=0, int b=0, int c=0){
    prof=a;
    riga=b;
    colonna=c;
  }
}; //per modellare posizione in sotto-array

//PRE = ele, H, L, lim3=2 e lim 3 definiti
int elem(int ele, int H, int L, int lim2, int lim3){
  return (ele*lim3)%H + (ele/H)*lim2*lim3;
}
//POST = restituisce la distanza dell'elemento in posizione ele dal primo elemento del sottoarray di dimensione H*L

// PRE=  (X è un array che contiene almeno lim1*lim2*lim3 elementi e va listo come int Y[lim1][lim2][lim3], 
//       (r,c,H,L) definisce un sotto-array di Y(r+H<=lim2 e c+L<=lim3), P è un array che contiene dimPelementi, 
//       el è l'indice di un elemento del sotto-array (r,c,H,L)a partire dal qualeil sotto-array ha ancora almeno dimP elementi)
bool match(int* X, int r, int c, int H, int L, int lim1, int lim2, int lim3, int*P, int dimP, int e){
  bool match=true;
  int *Y = (X+c)+r*lim3;
  for(int i=0; i<dimP && match; i++){
    match = Y[elem(e+i,H,L,lim2,lim3)] == P[i];
  }
  return match;
}
// POST=(restituisce true se il sotto-array (r,c,H,L) ha un match contiguo a partire dall'elemento el con P[0..dimP-1]e false altrimenti)

main()
{
  ifstream IN("input");

  ofstream OUT("output");
  if(IN && OUT) 
  { 
   
   int X[400],P[50], n_el, dimP, lim1,lim2,lim3;
   
   IN>>lim1>>lim2>>lim3;
   IN>>n_el;
   for(int i=0; i<n_el; i++)
     IN >> X[i];
   int r,c,h,l;
   IN>>r>>c>>h>>l; //definisce sotto-array
   
   IN>>dimP;
   for(int i=0; i<dimP; i++)
    IN>>P[i];

  int el_v_fetta = lim1*h;
  int count = 0;

// PRE = el_v_fetta contiene quanti elemnti ha una v-fetta, count=0, l>1 v fette da controllare del tassello che inizia dall'elemento in posizione r,c
  for(int i=0; i<l; i++){
    //R = 0<=i<=l && il ciclo i-esimo controllate i v-fette
    //PRE = 0<=i<l
    for(int e=0; e<el_v_fetta-dimP+1; e++){
    //R = 0<=e<=el_v_fetta-dim+1 (elementi utili da quali può partire un match)
    //    && al ciclo e-esimo controllati e elementi della v-fetta i
        if(match(X,r,c+i,h,l,lim1,lim2,lim3,P,dimP,e)){
          OUT<<"trovato match a partire dall'elemento "<<e+(i*lim1)<<endl;
          e+=dimP-1;
          count++;
        } else {
          OUT<<"a partire dall'elemento "<<e+(i*lim1)<<" non c'e' match"<<endl;
        }
      }
    //POST = scrive in output se ci sono stati o meno match sulla v-fetta i && contatore aumentato di uno per ogni match trovato
  }
//POST = controllate tutte le v-fette, scritti in output i match trovati && count contiene quanti match in tutto sono stati trovati
    OUT<<"n. totale match="<<count<<endl;
    
    IN.close(); OUT.close(); 
    }
    else
    cout<<"errore con i files";
  }

/*
Correttezza ciclo interno al main:
  PRE && R => R:

*/
