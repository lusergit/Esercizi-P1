#include<iostream>
using namespace std;

struct nodo{int info; nodo* next;nodo(int a=0, nodo* b=0){info=a; next=b;}};
struct coda{nodo* primo,*ultimo;coda(nodo*a=0){primo=a; ultimo=a;}};

coda push_end(coda x, nodo*p)
{
  p->next=0;
  if(!x.primo)
    x.primo=x.ultimo=p;
     else
    {
      x.ultimo->next=p;
      x.ultimo=p;
    }
  return x;
}

nodo* faiLista()
{
  int x;
  cin>> x;
  if(x==-1) return 0;
  return new nodo(x, faiLista());
}

void stampaL(nodo*L)
 {
   if(L)
     {
       cout<<L->info<<' ';
       stampaL(L->next);
     } else cout<<endl;

 }

//PRE_preleva = L lista ben formata, A ha nA elementi strettamente crescenti, vL = L
coda preleva(nodo*&L, int* A, int nA){
    coda to_return, resto;
    nodo* current = L;
    //PRE_for = PRE_preleva && to_return, resto code ben formate e vuote, current punta al primo nodo di L, nA>=0
    for(int i=0; current && nA; i++)
    //R_for = L(current) lista ben formata && A ha ancora nA elementi che indicano quali nodi eliminare && to_return contiene i nodi orelevati, resto contiene quelli non prelevati
    {
        nodo* tmp = current;
        current = current->next;
        tmp->next = 0;
        if(i == *A){
            to_return = push_end(to_return, tmp);
            A++;
            nA--;
        } else {
            resto = push_end(resto, tmp);
        }
    }
    //POST_for = se L consumata tutta to_return coda contenente i nodi di vL da prelevare (Quelli con indice definito da A), resto contiene gli altri nodi
    //           se ci sono ancora elementi in L(current) tutti gli elementi definiti da A sono stati prelevati e messi in to_return
    
    //PRE_while = L(current) ben formata, vResto = resto
    while(current)
    //R_while = all'iterazione n-esima prelevati i primi n elementi di L(current) e inseriti in resto && L(current) ben formata
    {
        nodo* tmp = current;
        current = current->next;
        tmp->next = 0;
        resto = push_end(resto, tmp);
    }
    //POST_while = resto formata da L(vResto.primo)@L(current)
    
    L = resto.primo;
    return to_return;
}
//POST = restituisce col return una coda con i nodi di vL che corrispondo agli indici di A, L è vL a cui sono stati tolti i nodi col return

/*
Dimostrazione for della funzione preleva:
    
    Condizione iniziale: 
        PRE_preleva => L(current) ben formata, A ha nA elementi defniti && to_return vuota prima di inziare, così
        come resto, dato che non è ancora stato fatto nulla => R
    
    invarianza:
        R && (current && nA) => current lista non vuota, nA>0 => 
            current = current->next // essendo current non vuota, anche current->next è ben formata
            
            if(i == *A){
                ...
                nA--;
            }           => essendo nA > 0 per la guardia, nA-- al massimo rende nA=0 che rispetta comunque l'invarianza
            else {
                ...
            }           => Qui nA non viene modificatom quindi nA>0 => nA>=0
        
        => R && guardia => R
        
    uscita:
        R && !guardia => 2 condizioni di uscita
        nA == 0 => tutti i nodi di indice definito da A sono stati prelevati e inseriti in to_return, current punta ad una lista ancora ben formata
        
        current == 0 => current ancora lista ben formata(vuota), tutti i nodi di vL di indice definito da A sono stati inseriti in to_return
                        e gli altri in resto
        
        in entrambi i casi R && (!(current && nA)) => POST_for

*/
main()
{
  cout<<"start"<<endl;
  nodo*K=faiLista();
  int nA;
  cin >>nA;
  int * A= new int[nA];
  for(int i=0; i<nA;i++)
    cin >>A[i];
  coda X=preleva(K,A,nA);
  cout<<"lista prelevata:"<<endl;
  stampaL(X.primo);
  cout<<"lista rimasta:"<<endl;
   stampaL(K);  
    cout<<"end"<<endl;
}
