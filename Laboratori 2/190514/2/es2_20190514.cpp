#include<iostream>
using namespace std;

struct nodo{int info; nodo* next; nodo(int a=0, nodo* b=0){info=a; next=b;}};

nodo* crea(int dim)
{
 if(dim)
  {
    int x;
    cin>>x;
    return new nodo(x,crea(dim-1));
  }
 return 0;
}


void leggi(int dim, int*P)
{
  if(dim)
   {
    cin>>*P;
    leggi(dim-1,P+1);
   }

}

void stampa(nodo* L){
  if(!L){
    cout << endl;
    return;
  }
  cout << L->info;
  if(L->next) cout << " -> ";
  stampa(L->next);
}

nodo* match(nodo* &L, int* &P, int &dimP){ 
  if(!L || !dimP) return NULL;
  if(L->info == *P){
    nodo* tmp = L;
    L = L->next;
    dimP--;
    P++;
    tmp->next=match(L,P,dimP);
    return tmp;
  }
  return match(L->next,P,dimP);
}

main()
{
  int dim, dimP, P[20], *p=P;
  cout<<"start"<<endl;
  cin>>dim;
  nodo* L1=crea(dim);
  cin>>dimP;
  leggi(dimP, P);
  nodo* L2 = match(L1,p,dimP);//da fare
  stampa(L2); //da fare
  stampa(L1);
  if(dimP){
    cout << "Match non completo, rimangono: [ ";
    for(int i=0; i<dimP; i++){
      cout << p[i] << ' ';
    }
    cout << "]" << endl;
  }
  cout<<"end"<<endl;
}