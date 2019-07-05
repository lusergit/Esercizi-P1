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
 
nodo* conc(nodo*L1, nodo*L2)
{
  if(!L1) return L2;
  if(!L2) return L1;
  nodo* x=L1;
  while(x->next)
    x=x->next;
  x->next=L2;
  return L1;
}
 
nodo* concric(nodo* L1, nodo* L2){
    if(!L1) return L2;
    if(!L2) return L1;
    L1->next = concric(L1->next,L2);
    return L1;
}
            //* METODO DEL PROF *//
/*nodo* taglia(nodo*&L, int n){
    if(!L || !n) return 0;
    nodo* inizio=L;
    while(n>1 && inizio->next){
        inizio=inizio->next;
        n=n-1;
    }
    if(!inizio->next){
        nodo*x=L;
        L=0;
        return x;
    }
    else{
        nodo*x=inizio->next;
        inizio->next=0;
        nodo*y=L;
        L=x;
        return y;
    }
}*/
 
nodo* taglia(nodo*&L, int n){ //iterattiva 
    if(!L || !n) return 0;
    nodo* d = 0;
    while(n>0 && L){
        nodo* c = L;
        L = L->next;
        c->next = 0;
        d = conc(d,c);
        n--;
    }
    return d;
}
            //* METODO DEL PROF *//
/*nodo* tagliaric(nodo*& L, int n){ 
    if(!L || !n) return 0;
    if(n==1){
        nodo*x=L;
        L=L->next;
        x->next=0;
        return x;
    }
    else{ //qui n è maggiore di 1
        nodo*y=tagliaric(L->next,n-1);
        nodo*z=L;
        L=L->next;
        z->next=y;
        return z;
    }
}*/

            
nodo* tagliaric(nodo*& L, int n){ //ricorsiva
    if(!n || !L) return 0;
    nodo* temp = L;
    L = L->next;
    temp->next = 0;
    nodo* d = 0;
    d = tagliaric(L,n-1);
    return concric(temp,d);
}
            //* METODO DEL PROF *//

/*void Fiter(nodo*L, nodoD* D, nodo*& lasciati, nodo*& tolti){
    lasciati=0, tolti=0;
    while(L && D){
        nodo*x=taglia(L, D->lascia);
        nodo*y=taglia(L, D->tolti);
        lasciati=conc(lasciati,x);
        tolti=conc(tolti,y);
        D=D->next;
    }
    lasciati=conc(lasciati,L);
}*/

void Fiter(nodo*L, nodoD* D, nodo*& lasciati, nodo*& tolti){ //iterattiva
    while(L && D){
        lasciati = conc(lasciati,taglia(L,D->lascia));
        tolti = conc(tolti,taglia(L,D->togli));
        D = D->next;
    }
    lasciati = conc(lasciati,L);
}

            //* METODO DEL PROF *//
            
/*doppioN Fric(nodo* L,nodoD*D){
    if(!L || !D) return doppioN(L);
    else{
        nodo*l=tagliaric(L,D->lascia);
        nodo*t=tagliaric(L,D->togli);
        doppioN z=Fric(L,D->next);
        return doppioN(concric(l,z.La), concric(t.z.To));
    }
}*/
 
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