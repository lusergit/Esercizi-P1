#include<iostream>
using namespace std;
#include<fstream>
struct nodo{int info; nodo* next; nodo(int a=0, nodo* b=0){info=a; next=b;}}; // nodo di lista 
struct FIFO{nodo* primo, *ultimo;FIFO(nodo*a=0, nodo*b=0){primo=a; ultimo=b;}};
struct nodot{int info; nodot* left, *right; nodot(int a=0, nodot* b=0, nodot* c=0){info=a; left=b; right=c;}};//nodo di albero

FIFO push_end(FIFO a, nodo*b)
{
  if(!a.primo)
  {a.primo=a.ultimo=b;}
  else
   {a.ultimo->next=b; a.ultimo=b;}
  return a;
}


int conta_n(nodot*r)
{
   if(!r) return 0;
     else
    return conta_n(r->left)+conta_n(r->right)+1;
}

nodot* insert(nodot*r, nodot* y)
{
  if(!r) return y;
   
  if(conta_n(r->left)<=conta_n(r->right))
    r->left=insert(r->left,y);
   else   
    r->right=insert(r->right,y); 
  return r;
}
void stampa_lista(nodo*C)
{
  if(C)
    {cout<<C->info<<' '; stampa_lista(C->next);}
  else
    cout<<endl;
}

nodot* build_tree(nodot*R,int n_el)
{
 if(!n_el) return R;
 int x;
 cin>>x;
 nodot* Q= insert(R,new nodot(x));
 return build_tree(Q,n_el-1);
}
void stampa(nodot *r)
{
  if(r)
    {
      cout<<r->info<<'(';
      stampa(r->left);
      cout<<',';
      stampa(r->right);
      cout<<')';
    }
  else
    cout<< '_';
}

//PRE = SX, DX strutture FIFO ben formate
FIFO conc(FIFO SX, FIFO DX){
  if(!SX.primo) return DX;
  if(!DX.primo) return SX;
  SX.ultimo->next = DX.primo;
  SX.ultimo = DX.ultimo;
  return SX; 
}
//POST ritorna una fifo formata dalla concatenazione delle due (SX@DX)

// PRE=(Tree(R) corretto, 1<= n<=k, k definito, sia vn=n)
FIFO pickric_postfix(nodot* r, int &n, int k){
  FIFO lista;
  if(!r) return lista; //se non c'è nessun nodo ritorna lista vuota
  //ordine postfisso, deve quindi prima richiamare a sinistra
  FIFO SX = pickric_postfix(r->left,n,k);
  //poi a destra
  FIFO DX = pickric_postfix(r->right,n,k);
  //le concatena
  lista = conc(SX,DX);
  //poi guarda la radice
  if(n==k){
    lista = push_end(lista,new nodo(r->info));
    n = 1;
  } else n++;
  return lista;
}
// POST=(restituisce un valore FIFO f tale che L(f.primo) sia una lista L tale che i nodi abbiano i campi info di
// valore uguale ai campi info dei nodi dell'albero Tree(R) che si trovano nella posizione vn, vn+k, vn+2*k,
// eccetera rispetto all'ordine postfisso, inoltre n-1 è il numero di nodi presenti nell'albero che seguono,
// rispetto all'ordine postfisso, il nodo dell'albero in corrispondenza del quale si è creato l'ultimo nodo di L)
/*
Correttezza:
  caso base:
    !r => non ci sono nodi da inserire, ritorna lista vuota ==> POST

    caso ricorsivo;
      r non vuoto:
      //PRE && r non vuoto => PRE_ric = albero(r->left) ben formato, 1<=n<=k, k definito, vn=n
      FIFO SX = pickric_postfix(r->left,n,k);
      //POST=(restituisce un valore FIFO f tale che L(f.primo) sia una lista L tale che i nodi abbiano i campi info di
            valore uguale ai campi info dei nodi dell'albero Tree(R) che si trovano nella posizione vn, vn+k, vn+2*k,
            eccetera rispetto all'ordine postfisso, inoltre n-1 è il numero di nodi presenti nell'albero che seguono,
            rispetto all'ordine postfisso, il nodo dell'albero in corrispondenza del quale si è creato l'ultimo nodo di L)

      stessa cosa per DX solo su r->right (pre vale sempre dato che non sono stati modificati i valori iniziali)

      //PRE_conc = SX,DX FIFO ben formate
      lista = conc(SX,DX);
      //POST = lista contiene una FIFO formata dalla concatenazione di SX con DX (SX@DX)
      if(n==k){
        //se n==k, il nodo corrente va inserito in lista, n va riportato a 1
        lista = push_end(lista,new nodo(r->info));
        n = 1;
      } else n++;
      return lista; ==> POST
*/

bool cerca(nodo*L, int x){
  while(L){
    if(L->info == x) return true;
    L = L->next;
  }
  return false;
}

FIFO tieni_primo(nodo*& L){
  FIFO risp, tolti;
  nodo* current = L;
  //PRE = risp, tolti code ben formate, L lista ben formata, current = L, vL = L
  while(current){
    //R = current lista ben formata && al ciclo n-esimo visitati i primi n nodi di vL
    //    ogni nodo viene inserito nella coda "risp" se all'interno della stessa non è gia presente un 
    //    nodo con lo stesso campo info, e all'interno di tolti altrimenti
    nodo* tmp = current;
    current = current->next;
    tmp->next = 0;
    if(!cerca(risp.primo,tmp->info)){
      risp = push_end(risp,tmp);
    } else {
      tolti = push_end(tolti,tmp);
    }
  }
  //POST = risp è coda formata dai nodi di vL il cui campo info appare per primo in vL stessa,
  //       tolti formata dagli altri nodi
  L = tolti.primo;
  return risp;
}
//POST = ritorna FIFO formata dai nodi di vL il cui campo info appare per primo in vL stessa, lascia in L gli altri nodi tolti

 main()
{
  int test,n_el, k, n=1;
 cin>>test>>n_el>>k;
 
 nodot* R=build_tree(0,n_el);
 cout<<"albero:"<<endl;
 stampa(R);
 FIFO x=pickric_postfix(R,n,k);
 cout<<endl<<"lista creata:"<<endl;
 stampa_lista(x.primo);
 if(test>0)
 {
  FIFO y=tieni_primo(x.primo);
  cout<<"lista dei nodi tolti"<<endl;
  stampa_lista(y.primo);
  cout<<"lista dei nodi che restano"<<endl;
  stampa_lista(x.primo);
 }
 cout<<endl<<"end"<<endl;
}

