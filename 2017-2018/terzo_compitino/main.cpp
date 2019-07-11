#include<iostream>
using namespace std;
struct nodoA{int info; nodoA* left,*right; nodoA(int a=0, nodoA*b=0,nodoA*c=0){info=a; left=b; right=c;}};
struct nodo{nodoA* info; nodo* next; nodo(nodoA* a=0, nodo*b=0){info=a; next=b;}};

void stampa_l(nodoA *r)
{
  if(r)
    {
      cout<<r->info<<'(';
      stampa_l(r->left);
      cout<<',';
      stampa_l(r->right);
      cout<<')';
    }
  else
    cout<< '_';
}
int conta_n(nodoA*r)
{
   if(!r) return 0;
     else
    return conta_n(r->left)+conta_n(r->right)+1;
}

nodoA* insert(nodoA*r, int y)
{
  if(!r) return new nodoA(y);
   
  if(conta_n(r->left)<=conta_n(r->right))
    r->left=insert(r->left,y);
   else   
    r->right=insert(r->right,y); 
  return r;
}

nodoA* buildtree(nodoA*r, int dim)
{
  if(dim)
   {
    int z;
    cin>>z;
    nodoA*x=insert(r,z);
    return buildtree(x,dim-1);
   }
  return r;
}

void riempi(int*P,int m)
{
  if(m)
    {
      cin>>*P;
      riempi(P+1,m-1);
    }
}
void stampaL(nodo*a)
{
  if(a)
    {
      cout<<a->info->info<<' ';
      stampaL(a->next);      
    }
  else
    cout<<endl;
}

struct elem{
    nodoA* r;
    int mom;
    elem(int m=0, nodoA* rr=0){
        r = rr;
        mom = m;
    }
};

int altezza(nodoA* r){
    if(!r) return 0;
    return 1+max(altezza(r->left),altezza(r->right));
}

//PRE = L ben formata, n nodo singolo
nodo* glue(nodo* L, nodo* n){
    if(!L) return n;
    nodo* current = L;
    while(current->next) current = current->next;
    current->next = n;
    return L;
}

//PRE_B = (albero(r)è ben formato, k>0, 1<=n<=k)
nodo* B(nodoA* r, int k, int& n){
    elem *pila = new elem[altezza(r)+1];
    nodo* to_return = 0;
    int top = 0;
    if(r){
        pila[0] = elem(0,r);
        top++;
    }
    //PRE = r alber ben formato, k, n defniti, pila ha top>=0 elementi al suo interno && PRE_B, vR = r
    while(top)
    /*
    R = top>=0 && all'iterazoine m-esima le prime top poisizioni di pila indicano il cammino percorso dell'albero r in ordine infisso,
        dove ad ogni nodo visitato, se al momento della visita n == 1 il nodo viene inserito in to_return ed n viene riportato al valore k
        se n>1 => n-- && 1<=n<=k
    */ 
    {
        switch(pila[top-1].mom){
            case 0:
                if(!pila[top-1].r){
                    top--;
                } else {
                    pila[top-1].mom++;
                    pila[top] = elem(0,pila[top-1].r->left);
                    top++;
                }
                break;
            
            case 1:
                if(n == 1){
                    //PRE_glue = to_return, n = new nodo(pila[top-1].r liste valide, n formata da nodo singolo), vTo_return = to_return
                    to_return = glue(to_return, new nodo(pila[top-1].r));
                    //POST_glue = to_return = vTo_return@n
                    n = k;
                } else n--;
                pila[top-1].mom++;
                pila[top] = elem(0,pila[top-1].r->right);
                top++;
                break;
                
            case 2:
                top--;
                break;
        }
    }
    //POST = visitati tutti i nodi dell'albero e inseriti in to_return tutti i nodi che al momento della visita avevano n=1 (un nodo ogni k)
    
    return to_return;
}

/*
Dimostrazione:
    PRE => top>=0 (top>0 se radice r valida, 0 altrimenti) && eseguite 0 iterazioni: albero non ancora visitato => R
    
    R && top => essendo top>=0 per PRE, la condizione di guardia (top) è equivanlente a top>0
    eseguite n iterazioni allora eseguo l'n+1-esima:
        
        per come è strutturato lo switch se pila[top-1] esiste ed è nel momento 0 (prima chiamata), viene messo un nuovo elemento in pila in posizione top
        richiamado sul figlio sinistro del nodo puntato da pila[top-1].r, che è proprio ciò in cui consiste il percorrimento infisso
        top-- altrimenti, significa che il nodo pila[top-1].r è vuoto, quindi il padre non ha quel figlio (sinistro o destro che sia)
        
        se pila[top-1] è nel momento 1 la sua esisteza è garantita dal fatto che al momento 0 non sia stato scartato, e a questo punto avviene il controllo di n,
        se n == 1 viene inserito un nuovo nodo (n = new nodo(pila[top-1].r) nella lista to_return e n = k,
        se n>1 => n-- => 1<=n<=k e rispetta l'invarianza
        
        se pila[top-1] è nel momento 2 allora è stato visitato anche il figlio destro di pila[top-1].r e quindi può essere rimosso dalla pila valida con
        top--; (si torna a considerare il padre)
        
    => R
    
    R && top=0 => o vR = 0 => nessun ciclo eseguito, nessun nodo inserito dato che albero vuoto e to_return = 0 => POST
    altrimenti: tutti i cammini validi di r percorsi e inseriti in to_return tutti i nodi nei quali al momento della visita n=1
    => POST
*/


/* Risolvo in modo iterativo dato che mi sto preparando ad affrontare la parte iterativa dell'esame nell'a.a. 2018-2019 */
main()
{
  int  n,m,k;
  cout<<"start"<<endl;
  cin>> n;
  nodoA*R=buildtree(0,n);
  stampa_l(R);
  cout<<endl;
  
  cin>> k;
  m=k;
  nodo*a=B(R,k,m); // da fare 
  cout<<"lista:"<<endl;
  stampaL(a);
  cout<<"n="<<m<<endl;
  cout<<"end"<<endl;
}
