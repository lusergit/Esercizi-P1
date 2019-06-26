#include<iostream>

#include "code.h"
using namespace std;


struct nodoA{char info; nodoA*left,*right; nodoA(char a='\0',nodoA*b=0,nodoA*c=0){info=a;left=b;right=c;}};

//-----------------parte vecchia-----------------------
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

nodoA* insert(nodoA*r, char y)
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
    char z;
    cin>>z;
    nodoA*x=insert(r,z);
    return buildtree(x,dim-1);
   }
  return r;
}
void stampa_lista(nodo*L)
{
  if(L)
  {
    cout<<L->info<<' ';
    stampa_lista(L->next);
  }
  else
    cout<<endl;

}

//PRE = lista(L1) e lista(L2) ben formate e ordinate
nodo* fuse(nodo*L1, nodo*L2){
  nodo  *currentL1 = L1, *currentL2 = L2;
  coda corretta;
  while(currentL1 && currentL2){
    if(currentL1->info < currentL2->info){
      nodo*tmp = currentL1;
      currentL1 = currentL1->next;
      push(tmp,corretta);
    } else {
      nodo*tmp = currentL2;
      currentL2 = currentL2->next;
      push(tmp,corretta);
    }
  }
  if(currentL1){
    push_list(currentL1,corretta);
  } else if(currentL2){
    push_list(currentL2,corretta);
  }
  return corretta.inizio;
}
//POST = restituisce unica lista formata dalle due iniziali fuse in modo da mantenere l'ordine tra i nodi

//PRE = albero r ben formato
nodo* build_list(nodoA* r){
  if(!r) return NULL;
  nodo* left = build_list(r->left);
  nodo* right = build_list(r->right);
  if(!left && !right) return new nodo(r->info);
  nodo* tmp = fuse(left,right);
  return fuse(new nodo(r->info), tmp);
}
//POST = restituisce lista coi campi info uguali a quelli di r ordinati in ordine crescente
main()
{
  int  n;
  cout<<"start"<<endl;
  cin>> n;
  nodoA*R=buildtree(0,n);
  stampa_l(R);
  cout<<endl;
  nodo*x=build_list(R);
  stampa_lista(x);
  cout<<"end"<<endl;
}
