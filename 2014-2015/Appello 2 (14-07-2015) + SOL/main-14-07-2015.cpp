#include<iostream>
#include<fstream>
using namespace std;

struct nodo{int info; nodo* next; nodo(int a=0, nodo* b=0){info=a; next=b;}};
struct nodoT{int info; nodoT* left,* right; nodoT(int a=0, nodoT* b=0, nodoT* c=0){info=a; left=b;right=c;}};

void F0(nodo*L, bool & b)
{
  if(!L)
    b=false;
  else
  {
  F0(L->next,b);
  if(!b)// se b=true non fa niente !
  {
   if(L->info==0)
     {L->info=1; b=true;} //lavoro fatto !
   else
     L->info=0;
  }
 }
  
}

//PRE=(alt>=0)
nodo* costruisci_L(int alt)
{
  nodo* r=0;
  while(alt)
   {
    r=new nodo(0,r);
    alt--;
   }
  return r;

}
//POST=(restituisce una lista con alt nodi con info=0)

nodoT*buildt()
{
  nodoT* f1=new nodoT(10);
  nodoT* f2=new nodoT(20);
  nodoT*I=new nodoT(15,f1,f2);
  nodoT*R=new nodoT(2,I, new nodoT(23));
  return R;
}
//restituisce un albero per provare la vostra F1
//stampa gli alberi in forma lineare
void stampa_l(nodoT *r, ofstream & OUT)
{
  if(r)
    {
      OUT<<r->info<<'(';
      stampa_l(r->left,OUT);
      OUT<<',';
      stampa_l(r->right, OUT);
      OUT<<')';
    }
  else
    OUT<< '_';
}

//stampa lista 
void stampa_L(nodo* x,ofstream& OUT)
{
  if(x)
  {OUT<<x->info<<' '; stampa_L(x->next,OUT);}
  else
   OUT<<endl;
}

struct elem{
  int momento;
  nodoT* vert;
  elem(int m, nodoT* v){
    momento = m;
    vert = v;
  }
};

void inserisci(nodoT*& r, nodo* cammino, ifstream & in){
  if(!r){
    int x; in >> x;
    r = new nodoT(x);
  }
  nodoT* current = r;
  while(cammino){
    if(cammino->info){// se 1 guarda a destra
      if(!current->right){
        int x; in >> x;
        current->right = new nodoT(x);
      }
      current = current->right;
      cammino = cammino->next;
    } else {
      if(!current->left){
        int x; in >> x;
        current->left = new nodoT(x);
      }
      current = current->left;
      cammino = cammino->next;
    }
  }
}

// PRE=( albero(R)corretto, 0<prof, INP ifstream definito, R=vR, INP contiene (almeno) 2(alt+1) -1 valori )
nodoT * F1(nodoT* R, int alt, ifstream & INP){
  //if(!alt) return 0; // non serve dato che prof>0
  nodo* cammino = costruisci_L(alt);
  bool b = true;
  while(b){
    inserisci(R,cammino,INP);
    F0(cammino,b);
  }
}
// POST=(albero(R) è ottenuto da albero(vR) aggiungendo tutti i nodi non già presenti in albero(vR) di tutti i
// cammini di lunghezza alt, i campi info dei nodi sono letti da INP. I cammini vanno considerati partendo dal
// cammino con soli 0, poi applicando F0 ripetutamente )


main()
{
  ifstream IN("input");
  ofstream OUT("output");
  if(IN && OUT) 
  { 
   int alt;
   
   IN>>alt;
   nodo*L=costruisci_L(alt);//data
   bool b=true;
   while(b)
    {
      stampa_L(L,OUT); 
      F0(L,b); //da fare
      
   }
    nodoT*R=F1(0,alt,IN); //da fare
    stampa_l(R,OUT);
    OUT<<endl;
    nodoT*K=buildt();//data
    stampa_l(K,OUT);//data
    OUT<<endl;
    K=F1(K,alt,IN);
    stampa_l(K,OUT);
     IN.close(); OUT.close(); 

  }
  else
   cout<<"errore con i files";
 }

