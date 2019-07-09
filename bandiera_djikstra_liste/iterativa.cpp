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
    bool match = true;
    while(match && dimP){
        match = n->info == *P;
        P++; dimP--; n=n->next;
    }
    return match;
}
//POST = ritorna true sse i primi dimP elementi di L(n) coincidono con l'array P

nodo* glue(nodo* L1, nodo* L2){
    if(L1){
        nodo* current = L1;
        while(current->next)
            current = current->next;
        current->next = L2;
        return L1;
    } else return L2;
}

//PRE = L(n) ben formata, con almeno dim elementi
nodo* trim(nodo*&n, int dim){
    if(dim && n){
        nodo* to_return = 0;
        nodo* current = n;
        while(dim && n){
            nodo* tmp = n;
            n = n->next;
            tmp->next = 0;
            to_return = glue(to_return, tmp);
            dim--;
        }
        return to_return;
    } else return 0;
}
//POST = restituisce il puntatore nodo di indice dim
//       && nodo di indice dim-1 avrà campo next=NULL;

//PRE = L(n) ben formata, P ha dimP elementi, vL(n)=L(n)
nodo* match(nodo*& n, int* P, int dimP){
    nodo* buoni = 0;
    nodo* da_elim = 0;
    bool trovato = false;
    while(n){
        if(!trovato && prova(n,P,dimP)){
            da_elim = glue(da_elim,trim(n,dimP));
            trovato = true;
        } else {
            nodo* tmp = n;
            n = n->next;
            tmp->next = 0;
            buoni = glue(buoni,tmp);
        }
    }

    n = buoni;
    return da_elim;
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