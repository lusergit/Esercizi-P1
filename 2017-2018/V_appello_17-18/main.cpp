#include<iostream>
using namespace std;

struct nodo{
    int info;
    nodo* next;
    nodo(int x=0, nodo* y=0){
        info = x;
        next = y;
    }
};

struct nodoL{
    nodo* info;
    nodoL* next;
    nodoL(nodo* L=0, nodoL*N=0){
        info = L;
        next = N;
    }
};

//PRE = nL ben formata, k intero non negativo, vL = L
nodo* trim(nodo*&L, int k){
    if(!k || !L) return NULL;
    nodo* start = L;
    while(L && k-1){
        k--;
        L = L->next;
    }
    if(L){
        nodo *tmp = L->next;
        L->next = 0;
        L = tmp;
    }
    return start;
}
//POST = ritorna lista formata dai primi k nodi di L, L contiene il resto della lista;



//PRE = (lista(L) corretta, dimA >=0 e A contiene dimA interi non negativi
//      (quindi è possibile anche il valore 0), vL= valore iniziale di L)
nodoL* affettaiter(nodo*&L, int*A, int dimA){
    nodo* nL = L;
    nodoL *risp=0, *current=0;
    //PRE = PRE_affettaiter && risp = 0, current = 0 && nL = L
    for(int i=0; nL && i<dimA; i++){
    //R = 0<=i<=dimA, nL lista ben definita && all'iterazione i-esima eliminati i primi i segmenti definiti dalla i-esima posizione di A
        
        //PRE = nL ben formata && non vuota (per la guardia), A[i] intero non negativo, vnL = nL
        nodo* tmp = trim(nL, A[i]);
        //POST = ritorna lista formata dai primi A[i] nodi di vnL, nL contiene ora il resto della lista

        if(!risp){
            risp = new nodoL(tmp);
            current = risp;
        } else {
            current->next = new nodoL(tmp);
            current = current->next;
        }
    }
    //POST = tagliata la lista secondo A, oppure Lista esaurita prima di finire le posizioni di A
    //       && nL contiene i nodi rimanenti nel caso in cui la lista non sia stat esaurita
    //       && risp lista ben formata da puntatore a liste di lunghezza definta dai primi i elementi di A
    L = nL; 
    return risp;
}
//POST = (restituisce una lista di nodi di tipo nodoL che puntano alle fette di vL secondo quanto 
//        descritto nell’esempio precedente, L è quello che resta di vL una volta tolte le fette)
/*
Correttezza ciclo interno:
    condizione iniziale:
    PRE => all'iterazione 0, 0<=i<=dimA vera dato che dimA>=0 => R

    invarianza:
    R && nL!=0 && i<dimA ==> 0<=i<=dimA && (nL!=0 => nL ben formata) && eliminati i primi i segmenti definiti dalle corrispondenti posizioni di A ==> R

    terminazione:
    R && !(nL!=0 && i<dimA):
        caso 1:
            esaurita la lista: allora formata correttamente la lista ris per invarianza, che verrà ritornata, L=nL=>L=0, che è corretto secondo le specifiche della post
            ==> POST
        caso 2:
            i==dimA, esaurito il vettore A,
            allora risp formata correttamente per invarianza e in nL sono presenti i nodi che rimangono della lista di partenza
            L = nL ==> POST in toto
 */
nodo* build(int n){
    if(!n) return NULL;
    int x; cin >> x;
    nodo* L = new nodo(x);
    L->next = build(n-1);
    return L;
}

void stampa(nodo* L){
    while(L){
        cout << L->info;
        if(L->next) cout << "->";
        L = L->next;
    }
    cout << endl;
}

void stampaL(nodoL* L){
    while (L)
    {
        stampa(L->info);
        L = L->next;
    }
}

int main(int argc, char *argv[]){
    int x; cin >> x;
    nodo*L = build(x);
    cin >> x;
    int *A = new int[x];
    for(int i=0; i<x; i++){
        cin >> A[i];
    }

    nodoL* qlo = affettaiter(L,A,x);
    cout << "zio" << endl;
    stampaL(qlo);
    if(L){nodo* current = L;
        cout << "Lista non finita, rimane" << endl;
        stampa(L);
    }
    return 0;
}
