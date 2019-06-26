#include<iostream>
using namespace std;

struct nodo{
    int info; 
    nodo* left,*right; 
    nodo(int a=0, nodo* b=0, nodo*c=0){
        info=a; left=b; right=c;
    }
};

//PRE = r albero ben formato
int n_nodi(nodo* r){
  if(!r) return 0;
  return 1 + n_nodi(r->left) + n_nodi(r->right);
}
//POST = restituisce il numero di nodi dell'albero r

//PRE = r albero ben formato, x intero
nodo* insert(nodo* r, int x){
  if(!r) return new nodo(x);
  if(n_nodi(r->right) < n_nodi(r->left))
    r->right = insert(r->right,x);
  else r->left = insert(r->left,x);
  return r;
}
//POST = inserisce un nodo con campo info = x in modo che l'albero r sia bilanciato

//PRE = r albero ben formato
nodo* buildtree(nodo* r, int dim){
  if(!dim) return r;
  int x; cin >> x;
  r = insert(r,x);
  r = buildtree(r,dim-1);
  return r;
}
//POST = inserisce in r dim nodi con campo info definito da stdin in modo da formare un albero bilanciato

//PRE = r albero ben formato
void stampa_l(nodo* r){
  if(!r){
    cout << '_';
    return;
  }
  cout << r->info << '('; stampa_l(r->left); cout << ','; stampa_l(r->right); cout <<')';
}
//POST = stampa r in formato lineare

//PRE=(albero(r) è ben formato, k>0, 1<=n<=k)
int stampa_a_salti(nodo* r, int k, int n){
  if(!r) return n;
  int left;
  if(n == 1){
    cout << r->info << ' ';
    left = stampa_a_salti(r->left,k,k);
  } else left = stampa_a_salti(r->left,k,n-1);
  int right = stampa_a_salti(r->right,k,left);
  return right;
}
// POST = (percorre i nodi di albero(r) in ordine prefisso stampando i
//        campi info di alcuni di essi nel modo seguente: salta i primi n-1,
//        stampa il campo info del nodo n-esimo, poi ne salta k-1 e stampa
//        quello successivo e così via fino a visitare tutti i nodi di
//        albero(r)) && (restituisce un intero m (1<=m<=k) che indica che
//        si dovranno saltare m-1 nodi prima di stampare il prossimo)



int main()
{
  int dim,k;
  cin>>dim;
  nodo* R = buildtree(0,dim);
  cout<<"start"<<endl;
  stampa_l(R);
  cin>>k;
  int b=stampa_a_salti(R,k,k);
  cout<<"valore restituito="<<b<<endl;
  cout<<"end"<<endl;
  return 0;
}


/*
Correttezza stampa_a_salti:
  caso base:
    !r -> non c'è nessun nodo da stampare, bisogna saltare ancora n nodi prima di stamparne uno
    return n ==> POST

  caso ricorsivo:
    1:
      n==1
      //allora bisogna stampare il nodo corrente
      cout << r->info << ' '
      //e richiamare stampa a salti con valore di n resettato
      // dato che !r passato: r albero non vuoto, ha almeno la radice
      // => r->left && r->right sono alberi ben formati, k>0 per ipotesi
      //PRE_ric1 = r->left ben formato, k>0, 1<=k<=k
      left = stampa_a_salti(r->left,k,k);
      //POST_ric1 = ritorna un intero 1<=<=km che indica che si dovranno ancora stampare m-1 nodi prima di stampare il prossimo
    2:
      n!=1 => n>1
      //PRE_ric1 = r->left ben formato, k>0, 1<=n-1<=k
      left = stampa_a_salti(r->left,k,n-1);
      //POST_ric1 = ritorna un intero 1<=<=km che indica che si dovranno ancora stampare m-1 nodi prima di stampare il prossimo
    
    //PRE_ric2 = r->right ben formato, k>0, per POST_ric1 1<=left<=k
    right = stampa_a_salti(r->left,k,left);
    //POST_ric1 = ritorna un intero 1<=<=km che indica che si dovranno ancora stampare m-1 nodi prima di stampare il prossimo
    //            && stampati i nodi dei due sottoalberi correttamente

    return right => POST
*/
