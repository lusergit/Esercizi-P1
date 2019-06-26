#include<iostream>
using namespace std;
struct nodoA{int info; nodoA* left,*right; nodoA(int a=0, nodoA*b=0,nodoA*c=0){info=a; left=b; right=c;}};
struct nodo{nodoA* info; nodo* next; nodo(nodoA* a=0, nodo*b=0){info=a; next=b;}};

void stampa_l(nodoA *r)
{
  if(r)
    {
      cout<<r->info<<'(';
      stampa_l(r->left);
      cout<<',';
      stampa_l(r->right);
      cout<<')';
    }
  else
    cout<< '_';
}
int conta_n(nodoA*r)
{
   if(!r) return 0;
     else
    return conta_n(r->left)+conta_n(r->right)+1;
}

nodoA* insert(nodoA*r, int y)
{
  if(!r) return new nodoA(y);
   
  if(conta_n(r->left)<=conta_n(r->right))
    r->left=insert(r->left,y);
   else   
    r->right=insert(r->right,y); 
  return r;
}

nodoA* buildtree(nodoA*r, int dim)
{
  if(dim)
   {
    int z;
    cin>>z;
    nodoA*x=insert(r,z);
    return buildtree(x,dim-1);
   }
  return r;
}


void riempi(int*P,int m)
{
  if(m)
    {
      cin>>*P;
      riempi(P+1,m-1);
    }
}

void stampaL(nodo*a)
{
  if(a)
    {
      cout<<a->info->info<<' ';
      stampaL(a->next);      
    }
  else
    cout<<endl;
}

//PRE=(albero(r) ben formato, P ha dimP elementi con dimP>0)
nodo* match(nodoA* r, int* P, int dimP){
  if(!r) return NULL;
  if(r->info == *P){
    dimP--;
    P++;
    if(!dimP) return new nodo(r);
    nodo* left = match(r->left,P,dimP);
    if(left) return new nodo(r,left);
    nodo* right = match(r->right,P,dimP);
    if(right) return new nodo(r,right);
    return NULL;
  }

  nodo* left = match(r->left,P,dimP);
  if(left) return left;
  nodo* right = match(r->right,P,dimP);
  if(right) return right;
  return NULL;

}
//POST=(se esiste su un cammino di albero(r) un match di P, allora,
//      restituisce una lista concatenata con dimP nodi ciascuno dei quali punta
//      ad un nodo di albero(r) che partecipa al match trovato)
//      && (altrimenti restituisce 0)
/*
Correttezza funzione match:
  caso base:
    !r && PRE => c'è almeno ancora un match da fare, ma non avendo nodi su cui operare esso non può avvenire
    return NULL ==> POST

  caso ricorsivo:
    1:
      PRE && r->info == *P:
      dimP--; P++; // andrà fatto match sul prossimo elemento dell'array
      if(!dimP) return new nodo(r)
      // PRE && !dimP => finiti i match da fare, l'unico nodo da ritornare è quello che punta alla radice che ha compiuto il match
      // return new nodo(r) ==> POST
      a questo punto:
        dimP>0;
      //PRE_ric = alberi r->left && r->right ben formati, P ha dimP elementi con dimP>0
      nodo* left = match(r->left,P,dimP);
      if(left) return new nodo(r,left);
      nodo* right = match(r->right,P,dimP);
      if(right) return new nodo(r,right);
      // POST_ric = se esiste un cammino di albero(r->left) o albero(r->right) con match completo
                    allora restituisce una lista concatenata i cui nodi puntano ad un nodo del corrispondente albero
                    che partecipa al match trovato, favorendo albero(r->left)
                    && altrimenti restituisce NULL;
      le chiamate e i ritorni corrispondenti ==> POST
    
    2:
      PRE && r->info != *P;
      //PRE_ric = r->left ben formato, dimP>0
      nodo* left = match(r->left,P,dimP);
      //POST_ric = left contiene lista concatenata di nodi ch puntano a nodi dell'albero r->left che formano il match completp di P, oppure NULL
      if(left) return left; //if(left) => match trovato => return left ==> POST
      //PRE_ric = r->right ben formato, dimP>0
      nodo* right = match(r->right,P,dimP);
      //POST_ric = right contiene lista concatenata di nodi ch puntano a nodi dell'albero r->right che formano il match completp di P, oppure NULL
      if(right) return right; //if(right) => match trovato => return right ==> POST
      return NULL; //!right && !left => match non trovato, return NULL => POST
*/

main()
{
  int  n,m;
  cout<<"start"<<endl;
  cin>> n;
  nodoA*R=buildtree(0,n);
  stampa_l(R);
  cout<<endl;
  int P[50];
  cin>> m;
  riempi(P,m);
  nodo*a=match(R,P,m);
  if(a)
      stampaL(a);
    else
      cout<<"no match found"<<endl;
  cout<<"end"<<endl;
}