#include<iostream>
using namespace std;
struct nodo{int info; nodo*next; nodo(int a=0, nodo*b=0){info=a; next=b;}};
// funzioni per input e output
nodo *buildL(int k)
{
  if(!k) return 0;
  else
    {
      int x;
      cin>>x;
      return new nodo(x,buildL(k-1));
    }
}
void leggiA(int*A,int k)
{
  for(int i=0; i<k; i++)
    cin>>A[i];
}
nodo* clone(nodo*L)
{
  if(!L) return 0;
  else
    return new nodo(L->info,clone(L->next));
}
void stampa(nodo*L)
{
  if(!L) cout<<endl;
  else
    {
      cout<<L->info<<' ';
      stampa(L->next);
    }
}

void conc(nodo*& L1, nodo* L2){
  if(!L1){
    L1=L2;
    return;
  }
  conc(L1->next,L2);
}

nodo* trim(nodo*& L, int dim){
    if(!dim){
      nodo* tmp = L;
      L=NULL;
      return tmp;
    }
    if(!L) return NULL;
    else return trim(L->next,dim-1);
}

//PRE = (lista(L), lista(L1), e lista(L2) sono ben formate
//       A contiene dimA elementi non negativi, con dimA pari>=0
//       vL=lista(L),vL1=lista(L1),vL2=lista(L2))

void Fric(nodo* L, int* A, int dimA, nodo*& L1, nodo*& L2){
  if(!L) return;
  if(dimA){
    nodo* tmp = trim(L,*A);
    conc(L1,L);
    Fric(tmp,A+1,dimA-1,L2,L1);
  } else {
    conc(L1,L);
  }
}

//POST = (i nodi di vL sono distribuiti correttamente su 2 liste
//       X1 e X2 secondo i valori di A e L1=vL1@X1 e L2=vL2@X2)

//PRE = L lista ben formata e non vuota, k numero intero >=1
nodo* trim_iter(nodo* L, int k){
  while(k>1 && L){
    L=L->next;
    k--;
  }
  if(L){
    nodo* tmp = L->next;
    L->next = 0;
    return tmp;
  }
  return NULL;
}
//

//PRE = L, resto liste ben formate
nodo* conc_iter(nodo* L, nodo* resto){
  if(!L) return resto;
  nodo* start = L;
  while(L->next) L=L->next;
  L->next = resto;
  return start;
}
//POST ritorna L@resto

//PRE = (lista(L), lista(L1), e lista(L2) sono ben formate
//       A contiene dimA elementi non negativi, con dimA pari>=0
//       vL=lista(L),vL1=lista(L1),vL2=lista(L2))
void Fiter(nodo* L, int* A, int dimA, nodo* &L1, nodo*& L2){
  for(int i=0; i<dimA && L; i++){
    //cout << "Zi, sta: " << i << ',' << A[i] << endl;
    if(A[i] > 0){
      nodo* next = trim_iter(L,A[i]);
      //if(!next) cout << "Zi, qualcosa non va qui" << endl;
      //stampa(next);
      if(i%2 == 0){
        L1 = conc_iter(L1,L);
      } else L2 = conc_iter(L2,L);
      L=next;
    }
  }
  if(L){
    if(dimA%2)
      L2 = conc_iter(L2,L);
    else L1 = conc_iter(L1,L);
  }
}
//POST = (i nodi di vL sono distribuiti correttamente su 2 liste
//       X1 e X2 secondo i valori di A e L1=vL1@X1 e L2=vL2@X2)

nodo* clone_iter(nodo*L){
  nodo *primo, *ultimo;
  while(L){
    if(!primo){
      primo = ultimo = new nodo(L->info);
    } else {
      ultimo->next = new nodo(L->info);
      ultimo = ultimo->next;
    }
    L=L->next;
  }
  return primo;
}

main()
{
  cout<<"start"<<endl;
  int n, dimA;
  cin >> n >> dimA;
  int*A=new int[dimA];
  int*B=new int[dimA];
  nodo*L=buildL(n);
  nodo*altra=clone(L);
  //stampa(L);
  leggiA(A,dimA);
  leggiA(B,dimA);
  
  nodo*L1=0,*L2=0;
  Fric(L,A,dimA,L1,L2);
  stampa(L1);
  stampa(L2);

  cout << endl;
  
  nodo*L3=0,*L4=0;
  Fiter(altra,B,dimA,L3,L4);
  stampa(L3);
  stampa(L4);
  cout<<"end"<<endl;
}
