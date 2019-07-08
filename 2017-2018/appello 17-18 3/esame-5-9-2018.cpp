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

//PRE = L lista ben formata e non vuota, formata da k_nodi@resto
nodo* trim(nodo*& L, int k){
  if(!k) return 0;
  nodo* to_return = L, * current = L;
  for(int i=0; i<k-1 && current; i++){
    current = current->next;
  }
  if (current){
    L = current->next;
    current->next = 0;
  } else L = 0;

  return to_return;
}
//POST = ritorna puntatore a k_nodi, lista formata al massimo da k nodi, L punta a resto

//PRE = L ben formata e non vuota
nodo* ultimo(nodo* L){
  while(L->next) L=L->next;
  return L;
}
//POST = ritorna puntatore all'ultimo nodo di L

//PRE = L1, L2 ben formate
void conc(nodo * &L1, nodo * L2){
  if(L1){
    ultimo(L1)->next = L2;
  } else L1 = L2;
}
//POST = forma (L1 = L1@L2)

//PRE = L, L1, L2 ben formate, A vettore di dimA elementi con dimA pari, vL1=L1, vL2=L2, vL=L,
void Fiter(nodo* L, int * A, int dimA, nodo*& L1, nodo*& L2){
  for(int i=0; i<dimA && L; i++){
    nodo* current = trim(L,A[i]);
    if(i%2){
      conc(L2,current);
    } else conc(L1,current);
  }
  conc(L1,L);
}
//POST = i nodi di vL sono distribuiti correttamente su due liste X1 e X2 secondo i valor di A && L1=vL1@X1, L2=vL2@X2

main()
{
  cout<<"start"<<endl;
  int n, dimA, A[20];
  cin >> n >> dimA;
  nodo*L=buildL(n);
  stampa(L);
  leggiA(A,dimA);
  nodo*X=clone(L);
  nodo*L1=0,*L2=0;
  Fiter(L,A,dimA,L1,L2);
  stampa(L1);
  stampa(L2);
  L1=0;
  L2=0;
  Fiter(X,A,dimA,L1,L2);
  stampa(L1);
  stampa(L2);
  cout<<"end"<<endl;
}
