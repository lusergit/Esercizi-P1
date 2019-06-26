#include<iostream>
using namespace std;

struct nodo
{
    int info;
    nodo* next;
    nodo(int x, nodo* n){
        info = x;
        next = n;
    }
};

nodo* buildList(){
    int x;
    cin >> x;
    if(x == -1) return NULL;
    return new nodo(x,buildList());
}

//PRE = n lista ben formata, P array di dimensione dimP
bool prova(nodo* n, int* P, int dimP){
    if(!dimP) return true;
    if(n && n->info == *P) return prova(n->next,P+1,dimP-1);
    return false;
}
//POST = ritorna true sse i primi dimP elementi di L(n) coincidono con l'array P

//PRE = L(n) ben formata, con almeno dim elementi
nodo* next(nodo*&n, int dim){
    if(!dim) {
        nodo* tmp = n;
        n = NULL;
        return tmp;
    }
    return next(n->next,dim-1);
}
//POST = restituisce il puntatore nodo di indice dim
//       && nodo di indice dim-1 avrà campo next=NULL;

//PRE = L(n) ben formata, P ha dimP elementi, vL(n)=L(n)
nodo* match(nodo*& n, int* P, int dimP){
    if(!n) return NULL;
    bool trovato = prova(n,P,dimP);
    if(trovato){
        nodo* tmp = n;
        n = next(n,dimP);
        return tmp;
    }
    return match(n->next, P, dimP);
}
//POST = se in L(n) c'è un match completo di P, allora la funzione restituisce col return il match e 
//       salva in n per riferimento resto_match(vL(n),P[0,..,dimP-1])

void stampa_l(nodo* L){
    if(!L) return;
    cout << L->info << " ";
    stampa_l(L->next);
}

int main(){
    nodo* L = buildList();
    int nP;
    cin >> nP;
    int* pattern = new int[nP];
    for(int i=0; i<nP; i++){
        cin >> pattern[i];
    }
    nodo *L1 = match(L, pattern, nP);
    if(L1){
        cout << "L1 > ";
        stampa_l(L1);
        cout << endl;

        cout << "L > ";
        stampa_l(L);
        cout << endl;
    } else {
        cout << "no match found" << endl;
    }
}