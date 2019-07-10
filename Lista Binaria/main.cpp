#include<iostream>
using namespace std;

struct nodo
{
    int info;
    nodo* next;
    nodo(int a=0, nodo* b=0){
        info = a;
        next = b;
    }
};

nodo* ultimo(nodo*L){
    if(!L) return 0;
    while(L->next) L=L->next;
    return L;
}

struct coda
{
    nodo* inizio, *fine;
    coda(nodo*L =0){
        inizio = fine = L;
        if(L){
            fine = ultimo(L);
        }
    }
};

coda push_end(coda Q, nodo* L){
    if(!L) return Q;
    if(Q.inizio){
        Q.fine->next = L;
        Q.fine = ultimo(Q.inizio);
    } else {
        Q.inizio = L;
        Q.fine = ultimo(L);
    }
    return Q;
}

coda push_beg(coda Q, nodo* L){
    if(!L) return Q;
    if(Q.inizio){
        ultimo(L)->next = Q.inizio;
        Q.inizio = L;
    } else {
        Q.inizio = L;
        Q.fine = ultimo(L);
    }
    return Q;
}

nodo* build(int n){
    coda Q;
    while(n){
        Q = push_beg(Q,new nodo(n%2));
        n -= n%2;
        n = n/2;
    }
    return Q.inizio;
}

void stampa(nodo* L){
    while(L){
        cout << L->info;
        if(L->next) cout << " -> ";
        L=L->next;
    }
    cout << endl;
}

bool somma1(nodo*& L){
    bool overflow = false;
    nodo *current = L, *ultimo = 0;
    while(current){
        if(current->info == 0){
            ultimo = current;
        }
        current = current->next;
    }
    if(!ultimo){
        overflow = true;
        ultimo = push_beg(coda(L),new nodo(0)).inizio;
        L = ultimo;
    }

    ultimo->info = 1;
    ultimo = ultimo->next;
    while(ultimo){
        ultimo->info = 0;
        ultimo = ultimo->next;
    }

    return overflow;
}

int main(){
    int n; cin >> n;
    nodo* L = build(n);
    stampa(L);
    bool overflow = somma1(L);
    if(overflow){
        cout << "andato in overflow" << endl;
        stampa(L);
    } else {
        cout << "overflow non avvenuto" << endl;
        stampa(L);
    }
    return 0;
}  