#include<iostream>
using namespace std;
struct nodo{int info; nodo* next; nodo(int a=0, nodo*b=0){info=a; next=b;}};
struct nodoD{int lascia,togli; nodoD* next; nodoD(int a=0, int b=0,  nodoD*c=0){lascia=a; togli=b;  next=c;}};
struct doppioN{nodo*  La, *To; doppioN(nodo*a=0,nodo*b=0){La=a; To=b;}};
 
nodo* build(int n)
{
  if(n)
    {
      int x;
      cin>>x;
      return new nodo(x,build(n-1));
    }
  return 0;
}
nodoD* buildD(int n)
{
  if(n)
    {
      int x,y;
      cin>>x>>y;
      return new nodoD(x,y,buildD(n-1));
    }
  return 0;
}
 
void stampaL(nodo*L)
{
  if(L)
    {
      cout<<L->info<<' ';
      stampaL(L->next);
    }
  else
    cout<<endl;
}
void stampaD(nodoD*L)
{
  if(L)
    {
      cout<<'['<<L->lascia<<','<<L->togli<<']'<<' ';
      stampaD(L->next);
    }
  else
    cout<<endl;
}
 
nodo* concric(nodo* L1, nodo* L2){
    if(!L1) return L2;
    if(!L2) return L1;
    L1->next = concric(L1->next,L2);
    return L1;
}

nodo* tagliaric(nodo*& L, int n){ //ricorsiva
    if(!n || !L) return 0;
    nodo* temp = L;
    L = L->next;
    temp->next = 0;
    nodo* d = 0;
    d = tagliaric(L,n-1);
    return concric(temp,d);
}

nodo* conc(nodo* L1, nodo* L2){
  if(L1){
    nodo* current = L1;
    while(current->next) current = current->next;
    current->next = L2;
    return L1;
  } else return L2;
}

nodo* trim(nodo*&L, int k){
  if(!k) return 0;
  nodo* start = L;
  for(int i=0; i<k-1 && L->next; i++){
    L=L->next;
  }
  nodo* tmp = L;
  L=L->next;
  tmp->next = 0;
  return start;
}

void Fiter(nodo*L, nodoD* D, nodo*& lasciati, nodo*& tolti){ //iterattiva
    while(L){
      if(D){
        lasciati = conc(lasciati,trim(L,D->lascia));
        tolti = conc(tolti,trim(L,D->togli));
        D = D->next;
      } else {
        lasciati = conc(lasciati,L);
        L=0;
      }
    }
}

doppioN Fric(nodo* L,nodoD*D){
    doppioN doppialista = 0;
    if(!D){
        doppialista.La = conc(doppialista.La,L);
        return doppialista;
    }
    nodo* l = tagliaric(L,D->lascia);
    nodo* t = tagliaric(L,D->togli);
    doppialista = Fric(L,D->next);
    doppialista.La = concric(l,doppialista.La);
    doppialista.To = concric(t,doppialista.To);
    return doppialista;
}
 
nodo*clone(nodo*L)
{
  if(!L) return 0;
  return new nodo(L->info,clone(L->next));
}
 
main()
{
  int dimL, dimD;
  cin>> dimL>>dimD;
  nodo* L= build(dimL);//data
  nodoD* D=buildD(dimD);//data
  nodo*L1=clone(L);//data
  cout<<"start"<<endl;
  stampaL(L); //data
  stampaD(D);//data
  nodo* lasciati=0, *tolti=0;
  Fiter(L,D, lasciati, tolti); //da fare
  stampaL(lasciati);
  stampaL(tolti);
  doppioN y=Fric(L1,D); //da fare
  stampaL(y.La);
  stampaL(y.To);
  cout<<"end"<<endl;
}