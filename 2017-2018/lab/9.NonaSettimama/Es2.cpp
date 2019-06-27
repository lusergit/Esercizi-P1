#include<iostream>
using namespace std;

struct nodo{
    int info;
    nodo* next;
    nodo(int a = 0, nodo * b = 0){
        info = a;
        next = b;
    }
};

nodo* ultimo(nodo* L){
    if(!L) return 0;
    while(L->next){
        L=L->next;
    }
    return L;
}

struct coda{
    nodo* inizio;
    nodo* fine;
    coda(nodo* L){
        if(L){
            inizio = L;
            fine = ultimo(L);
        } else {
            inizio = fine = 0;
        }
    }
};

//PRE = L lista ben formata e ordinata, x intero
nodo* inserisci(nodo* L, int x){
    if(!L) return new nodo(x);
    cout << "Arrivato qui, L = " << L << endl;
    coda *Q = new coda(L);
    if (x < Q->inizio->info){
        nodo* tmp = Q->inizio;
        Q->inizio = new nodo(x, tmp);
    }
    else if (x > Q->fine->info){
            Q->fine->next = new nodo(x);
            Q->fine = Q->fine->next;
    } else {
       nodo* current = Q->inizio;
        while(current->next->info < x)
            current = current->next;
        current->next = new nodo(x, current->next);
    }
    nodo* tmp = Q->inizio;
    delete Q;
    cout << tmp->info << endl;
    return tmp;
}
//POST = restituisce lista formata dai nodi di L ai quali è stato aggiunto un nodo di campo info = x in modo da manternerla ordinata

nodo* leggi(){
    int x; cin >> x;
    nodo *L = 0;
    while(x != -1){
        L = inserisci(L,x);
        cin >> x;
    }
    return L;
}

void stampa(nodo* L){
    while(L){
        cout << L->info;
        if (L->next) cout << " -> ";
    }
    cout << endl;
}

int main(){
    nodo* L = leggi();
    stampa(L);
    return 0;
}
