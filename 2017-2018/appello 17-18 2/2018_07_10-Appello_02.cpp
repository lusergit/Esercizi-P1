#include<iostream>
using namespace std;
struct nodo{int  info; nodo* next; nodo(int a=0, nodo*b=0){info=a; next=b;}};
struct coda{nodo* primo, *ultimo; coda(nodo*a=0,nodo*b=0){primo=a; ultimo=b;}};
coda push_end(coda a, nodo*b)
{
  if(!a.primo)
    {
      a.primo=a.ultimo=b;
      b->next=0;
      return a;
    }
  a.ultimo->next=b;
  a.ultimo=b;
  b->next=0;
  return a;
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
void build_array(int *P, int x)
{
  if(x)
    {
      cin>> *P;
      build_array(P+1,x-1);    
    }
}

nodo* build_list(int n)
{
  if(n)
    {
      int x;
      cin >> x;
      return new nodo(x,build_list(n-1));
    }
  return 0;
}

nodo* clone(nodo*L)
{
  if(!L) return 0;
  return new nodo(L->info,clone(L->next));
}

nodo* distr_ric(nodo *&L, int* A, int dimA, int n){
  if(!L) return NULL;
  if(dimA){
    if(*A == n){
    nodo* tmp=L;
    L=L->next;
    tmp->next=distr_ric(L,A+1,dimA-1,n+1);
    return tmp;
    } else {
      return distr_ric(L->next,A,dimA,n+1);
    }
  }
  return NULL;
}

//PRE_f = L ben formata, A array con dimA elementi definiti non negativi e crescenti dimA>0, vL = L
nodo* distr_iter(nodo* &L, int* A, int dimA){
  coda to_del, resto;
  nodo* current = L;
  //PRE_for = PRE_f && resto e to_del code ben formate e vuote, L(current) = L = vL && vA = A, vdimA = dimA
  for(int i=0; current; i++)
  //R = dimA >= 0, L(current) ben formata, all'iterazione i-esima staccati i primi i nodi, ognuno inserito
  //    in resto se il suo indice (i) non è in A, inserito in to_del se il suo indice (i) è in vA
  {
    nodo * tmp = current;
    current = current->next;
    tmp->next = 0;
    if(dimA){
      if(i == *A){
        to_del = push_end(to_del,tmp);
        A++;
        dimA--;
      } else {
        resto = push_end(resto,tmp);
      }
    } else {
      resto = push_end(resto, tmp);
    }
  }
  //POST_for = tutti i nodi di indice valido (i < len(vL)) sono stati inseriti in to_del, resto contiene i nodi il cui indice non è presente in A

  L = resto.primo;
  return to_del.primo;
}
//POST_f = Restituisce L1 la lista dei nodi di vL i cui indici sono in A, mentre L diventa L2 la lista dei nodi
//       i cui indici non sono in A entrambe mantengono l'ordine relatvo che avevano in vL


/*
Dim for e while di distr_iter
for:
condizione iniziale:
  PRE_f => dimA > 0 && (i=0, => iterazione 0, staccati 0 nodi) => R

invarianza:
  R && dimA && current => (dimA>0) && (L(current) non vuota) && staccati i primi i nodi di vL e inseriti in resto o to_del a seconda
  che il loro indice appaia o meno in vA => dimA>=0, L(current) ben formata, staccati .. => R

uscita:
  R && !(current)
    => vL percorsa interamente, per invarianza ogni nodo è stato inserito o in to_del o in resto a seconda che il suo indice ci fosse o meno in A
    => to_del contiene i nodi il cui indice è in A, resto contiene i nodi il cui indice non è in A

ritorno:
  L = resto.primo && return to_del.primo => POST_f
 */

int main()
{
  int  n,m;
  cout<<"start"<<endl;
  cin>> n;
  nodo*L=build_list(n);
  nodo*L1=clone(L);
  cin>>m;
  int*A=new int[m];
  build_array(A,m);
  nodo*y=distr_iter(L,A,m);
  cout << endl;
  stampa_lista(y);
  stampa_lista(L);
  y=distr_ric(L1,A,m,0);
  cout << endl;
  stampa_lista(y);
  stampa_lista(L1);
  
  cout<<"end"<<endl;
  return 0;
}
