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

//PRE = L lista ben formata e ordinata, x intero
nodo* inserisci(nodo* L, int x){
    if(!L) return new nodo(x);
    //cout << "Arrivato qui, L = " << L << endl;
    //coda *Q = new coda(L);
    if (x < L->info){
        L = new nodo(x,L);
    }
    else{
        if (x > ultimo(L)->info){
            ultimo(L)->next = new nodo(x);
        } else {
            nodo* current = L;
            while(current->next->info < x)
                current = current->next;
            current->next = new nodo(x, current->next);
        }
    }

    return L;
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
        L=L->next;
    }
    cout << endl;
}

int main(){
    nodo* L = leggi();
    stampa(L);
    return 0;
}
