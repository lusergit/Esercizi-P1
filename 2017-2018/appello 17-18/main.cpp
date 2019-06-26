#include<iostream>
using namespace std;
struct nodo{int info ; nodo* next; nodo(int a=0, nodo*b=0){info=a; next=b;}};
struct coda{nodo* primo,* ultimo;coda(nodo*a=0,nodo*b=0){primo=a; ultimo=b;}};

coda push_beg(coda x, nodo*a)
{
  if(!x.primo)
    {
      x.primo=x.ultimo=a;
      a->next=0;
      return x;
    }
  a->next=x.primo;
  x.primo=a;
  return x;
}
coda push_end(coda x, nodo*a)
{
  if(!x.primo)
    {
      x.primo=x.ultimo=a;
      a->next=0;
      return x;
    }
  x.ultimo->next=a;
  x.ultimo=a;
  a->next=0;
  return x;
}

nodo* buildlist(int m)
{
  if(m>0)
    {
      int x;
      cin >> x;
      return new nodo(x,buildlist(m-1));
    }
  return 0;
}
nodo* clone(nodo*L)
{
  if(L)
    return new nodo(L->info,clone(L->next));
  return 0;
}
void stampaL(nodo*L)
{
  if(L)
    {
      cout<< L->info<<' ';
      stampaL(L->next);
    }
  else
    cout<<endl;
}

//PRE = L(n) composta da un solo nodo e L(ord) ben formata
void ins (nodo*& n, nodo*& ord){
    if(!ord || n->info <= ord->info){
        n->next = ord;
        ord = n;
        n = NULL;
    } else {
        ins(n,ord->next);
    }
}
//POST = inserisce il nodo di L(n) in L(ord) in modo che L(ord) sia ordinata
//       && svuota L(n)

//PRE = L ben formata e non vuota, ord ben formata
void ordric(nodo*&L, nodo*&ord){
    if(L->next) ordric(L->next,ord);
    ins(L,ord);
}
//POST = L vuota e ord ordinata composta coi nodi originari di L

//PRE = L(L) ben formata
int len(nodo* L){
    int x=0;
    while (L){
        x++;
        L=L->next;
    }
    return x;    
}
//POST = ritorna il numero di nodi in L(L)

void insert(coda& Q, nodo* n){
  if(!Q.primo || n->info < Q.primo->info){
    Q = push_beg(Q,n);
  } else if(n->info > Q.ultimo->info){
    Q = push_end(Q,n);
  } else {
    nodo* current = Q.primo;
    while (current->next && current->next->info < n->info)
    {
      current = current->next;
    }
    n->next = current->next;
    current->next = n;
  }
}

//PRE=(lista(L) ben formata, v_L è il valore iniziale dilista(L))
nodo* orditer(nodo* L){
  coda ordinata;
  while(L){
    nodo* tmp = L;
    L=L->next;
    tmp->next = 0;
    insert(ordinata,tmp);
  }
  return ordinata.primo;
}
//POST = (restituisce la lista composta dai nodi di v_L ordinati rispetto al campo info)

main()
{
  int  n;
  cout<<"start"<<endl;
  cin>> n;
  nodo*L=buildlist(n);
  stampaL(L);
  nodo*L1=clone(L);
  cout<<endl;
  nodo*L2=0;
  ordric(L,L2);
  stampaL(L2);
  nodo*y=orditer(L1);
  stampaL(y);
  cout<<"end"<<endl;
}
