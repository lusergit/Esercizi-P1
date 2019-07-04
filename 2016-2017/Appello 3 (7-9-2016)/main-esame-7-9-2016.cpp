#include<iostream>
#include<fstream>
using namespace std;
struct nodo{int info; nodo* next; nodo(int a=0, nodo* b=0){info=a; next=b;}}; // nodo di lista 
struct FIFO{nodo* primo, *ultimo;FIFO(nodo*a=0){primo=a; ultimo=a;}};

FIFO push_end(FIFO a, nodo*b)
{
  if(!a.primo)
  {a.primo=a.ultimo=b;}
  else
   {a.ultimo->next=b; a.ultimo=b;}
  return a;
}


struct nodoF {FIFO fi; nodoF* next;nodoF(FIFO a=FIFO(),nodoF*b=0){fi=a; next=b;}};

//funzioni ausiliarie

  void stampa_L(nodo*L)
{
 if(L)
  {cout<<L->info<<' '; stampa_L(L->next);}
 else
   cout<<endl;

}
 void stampa_F(nodoF* a)
{
  if(a)
   {stampa_L(a->fi.primo); 
    cout<<endl;
    stampa_F(a->next);
   }
  else
   cout<<endl;
}

nodo* costruisci(int dim)
{
 if(dim)
   {int x; cin>>x; return new nodo(x,costruisci(dim-1));}
 return 0;
}

//PRE = L non vuota e ben formata
nodo* taglia_uguali(nodo*& L){
  bool primo = true;
  FIFO to_return;
  while(primo || (L && L->info == to_return.primo->info)){
    nodo* tmp = L;
    L = L->next;
    tmp->next = 0;
    to_return = push_end(to_return, tmp);
    primo = false;
  }
  return to_return.primo;
}
//POST = ritorna puntatore a lista contenente i primi n nodi con campo info uguale, L punta al resto della lista

nodoF* cerca(nodoF* L, int x){
  while(L){
    if(L->fi.primo->info == x) return L;
    L = L->next;
  }
  return 0;
}

nodoF* smembra(nodo* L){
  nodoF* to_return = 0;
  while(L){
    nodo* tmp = taglia_uguali(L);
    nodoF* presente = cerca(to_return,tmp->info);
    if(presente){
      while(tmp){
        presente->fi = push_end(presente->fi, tmp);
        tmp = tmp->next;
      }
    } else {
      if(to_return){
        nodoF* fine_F = to_return;
        while(fine_F->next)
          fine_F = fine_F->next;
        fine_F->next = new nodoF();
        fine_F = fine_F->next;
        while(tmp){
          fine_F->fi = push_end(fine_F->fi,tmp);
          tmp = tmp->next;
        }
      } else {
        to_return = new nodoF();
        while(tmp){
          to_return->fi = push_end(to_return->fi,tmp);
          tmp = tmp->next;
        }
      }
    }
  }

  return to_return;
}

//PRE = L lista ben formata e non vuota, vL = L
nodo* ultimo(nodo*L){
  while(L->next){
    L = L->next;
  }
  return L;
}
//POST = ritorna puntatore all'ultimo nodo della lista vL

FIFO push_list(FIFO Q, nodo* L){
  if(Q.primo){
    Q.ultimo->next = L;
    Q.ultimo = ultimo(Q.primo);
  } else {
    if(L){
      Q.primo = L;
      Q.ultimo = ultimo(L);
    }
  }
  return Q;
}

/*
nodo* LO(nodoF* a){
  FIFO to_return;
  while(a){
    to_return = push_list(to_return, a->fi.primo);
  }
}
 */
 
main()
{
   int dim;
   
   cin>>dim;
   nodo*C=costruisci(dim);
  
   cout<<"Lista costruita"<<endl;
   stampa_L(C);
   nodoF* a=smembra(C);
   cout<<"Liste uniformi:"<<endl;
   stampa_F(a);
   
  //  nodo* b=LO(a);
  //  cout<<"Lista ordinata"<<endl;
  //  stampa_L(b);
   cout<<"end";
}
