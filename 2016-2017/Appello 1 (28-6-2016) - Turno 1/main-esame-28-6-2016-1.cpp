#include<iostream>
using namespace std;
#include<fstream>
struct nodo{int info; nodo* next; nodo(int a=0, nodo* b=0){info=a; next=b;}}; // nodo di lista 
struct FIFO{nodo* primo, *ultimo; FIFO(nodo*a=0, nodo*b=0){primo=a; ultimo=b;}};
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
//POST = restituisce SX@DX

// PRE=(Tree(R) corretto, 1<=n<=k, k definito, sia vn=n)
FIFO pickric_infix(nodot* r, int &n, int k){
  FIFO lista;
  if(!r) return lista;
  FIFO SX = pickric_infix(r->left,n,k);
  if(n==k){
      SX = push_end(SX, new nodo(r->info));
      n=1;
  } else n++;
  FIFO DX = pickric_infix(r->right,n,k);
  return conc(SX,DX);
}
// POST=(restituisce un valore FIFO f tale che f.primo sia una lista L tale che i nodi abbiano i campi info di
//      valore uguale ai campi info dei nodi dell'albero Tree(R) che si trovano nella posizione vn, vn+k, vn+2*k,
//      eccetera rispetto all'ordine infisso, inoltre n-1 è il numero di nodi presenti nell'albero che seguono, rispetto
//      all'ordine infisso, il nodo dell'albero in corrispondenza del quale si è creato l'ultimo nodo di L)

/*
correttezza pickric_infix:
  caso base:
    !r => albero vuoto, non ci sono nodi, restituisce lista vuota => POST

  caso ricorsivo:

    //PRE && !(!r) => PRE_ric = r->left albero ben formato, 1<=n<=k, k bendefinito
    FIFO SX = pickric_infix(r->left,n,k);
    //POST_ric = ritorna fifo dei nodi in posizione vn+hk di r->left rispetto l'ordine infisso, n consistente
    
    se n==k, r va inserito in SX, altrimenti n va aumentato

    //PRE && !(!r) => PRE_ric = r->right albero ben formato, 1<=n<=k, k bendefinito
    FIFO DX = pickric_infix(r->right,n,k);
    //POST_ric = DX contiene FIFO dei nodi in posizione n+hk di r->right, n consistente
    
    return conc(SX,DX) ==> POST
*/

bool cerca(FIFO C, int y){
  nodo* p = C.primo;
  while(p){
    if(p->info == y) return true;
    p = p->next;
  }
  return false;
}
//ritorna se in C c'è un nodo con campo info == y

FIFO tieni_primo(nodo*& L){
  FIFO risp, tolti;
  nodo *current = L;
  while(current){
    nodo* tmp = current;
    current = current->next;
    tmp->next = 0;
    if(cerca(risp,tmp->info)){
      tolti = push_end(tolti,tmp);
    } else {
      risp = push_end(risp,tmp);
    }
  }
  L=risp.primo;
  return tolti;
}

 main()
{
  int test,n_el, k, n=1;
 cin>>test>>n_el>>k;
 
 nodot* R=build_tree(0,n_el);
 cout<<"albero:"<<endl;
 stampa(R);
 FIFO x=pickric_infix(R,n,k);
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
