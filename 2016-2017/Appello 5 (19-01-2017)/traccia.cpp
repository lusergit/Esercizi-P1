#include<iostream>
using namespace std;
//-------------------strutture dati------osservare costruttore di FIFOX-----------------------
struct nodo {
int info;
nodo *next; 
nodo(int a=0, nodo*b=0){info=a; next=b;}
};

//trova ultimo nodo di lista non vuota
nodo* ult(nodo*n){if(!n->next) return n; return ult(n->next);}
//calcola lungheza di lista
int length(nodo*n){if(!n) return 0; return 1 + length(n->next);}

struct FIFOX {
nodo *primo, *ultimo;
int val_p, val_u, n_ele;
FIFOX(nodo*a,nodo*b, int c=0, int d=0, int e=0) 
 {
      primo=a;
      ultimo=b;
      val_p=c;
      val_u=d;
      n_ele=e;
  }
FIFOX(nodo*L){
  primo = L;
  if(primo){
    ultimo = ult(L);
    val_p = L->info;
    val_u = ultimo->info;
    n_ele = length(L);
  } else {
    ultimo = primo;
    val_p = 0;
    val_u = 0;
    n_ele = 0;
  }
}
};

struct nodo_x{
FIFOX* fix;
nodo_x *next;
nodo_x(FIFOX * a=0, nodo_x*b=0){fix=a; next=b;} //CREO UN COSTRUTTORE PER NODO_X POICHE' MANCANTE (CONSENTITOMI DAL PROF. DI PIETRO)
nodo_x(nodo*L, nodo_x*b=0){
  fix = new FIFOX(L);
  next = b;
}
};
//-------------------------------------funzioni date----------------------------


nodo* build(int n)//costruisce lista di n nodi
{
  if(n>0)
   {
     int x;
     cin >> x;
     return new nodo(x, build(n-1));
   }
 return 0;

}

nodo_x* fai()//costruisce la lista nodo_x su cui far girare partiziona
{
  
       nodo_x*m1=new nodo_x;
       int n;
       cin >> n;
       nodo*x1=build(n);
       m1->fix=new FIFOX(x1);
       return m1;
}
  

void stampaL(nodo* L)
{
  if(L)
   {cout<<L->info<<' '; stampaL(L->next);}
  else
    cout<<endl;
}
 void stampaT(nodo_x* x,int n)
 {
   if(x)
    {
      cout<<"nodo_x n."<<n<<" primo="<<x->fix->val_p<<" ultimo="<<x->fix->val_u<<':'<<"lista=";
      stampaL(x->fix->primo);
      stampaT(x->next,n+1);
    }
 }
nodo* cloneL(nodo*a)//fa copia di lista di tipo nodo
{
  if(a)
    return new nodo(a->info, cloneL(a->next));
  return 0;
}
nodo_x* clone(nodo_x* a)//fa copia di lista di tipo nodo_x
{
  FIFOX *b= a->fix;
  nodo*c=cloneL(b->primo);
  nodo_x* d=new nodo_x;
  d->fix=new FIFOX(c,ult(c),b->val_p, b->val_u,b->n_ele);
  return d;
}

void init(nodo_x* & N){
  N->fix->ultimo = ult(N->fix->primo);
  N->fix->n_ele = length(N->fix->primo);
  N->fix->val_p = N->fix->primo->info;
  N->fix->val_u = N->fix->ultimo->info;
}

nodo* trim(nodo* L, int k){
  while(k-1){
    L=L->next;
    k--;
    if(!L) return NULL;
  }
  nodo* tmp = L->next;
  L->next = 0;
  return tmp;
}

void partiziona_it(nodo_x* N, int k){
  nodo* tmp = trim(N->fix->primo,k);
  while(tmp){
    N->next = new nodo_x(tmp);
    init(N);
    N=N->next;
    tmp = trim(N->fix->primo,k);
  }
}

nodo* trim_l(nodo*& L, int k){
  if(!L) return NULL;
  if(!k){
    nodo* tmp = L;
    L=0;
    return tmp;
  }
  return trim_l(L->next,k-1);
}

// PRE = N gestisce uana lista corretta di nodi di tipo nodo
void partiziona_ric(nodo_x* N, int k){
  if(!N) return;
  nodo* tmp = trim_l(N->fix->primo,k);
  if(tmp){
    init(N);
    N->next = new nodo_x(tmp);
  }
  else N->next = 0;
  partiziona_ric(N->next,k);
}
//POST = N nodo inziale di una lista di nodo_xtale che i nodi di questa lista gestiscano le sottoliste 
//       di L di lunghezza k

main()
{
 cout<<"start"<<endl;
 nodo_x* T1=fai(), *T2=clone(T1);
 int k;
 cin >> k;
 stampaT(T1,0);
 cout << endl << "Partiziona iterativa:" << endl;
 partiziona_it(T1,k);
 stampaT(T1,0);
 cout << endl << "Partiziona ricorsiva:" << endl;
 partiziona_ric(T2,k);
 stampaT(T2,0);
 cout<<"end"<<endl;
}
