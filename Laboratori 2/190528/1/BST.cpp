#include<iostream>
#include "BST.h"
using namespace std;

//PRE = albero(r) ben formato
void stampa_l(nodo*r){
    if(!r){
        cout << '_';
        return;
    }
    cout << r->info << '(';
    stampa_l(r->left);
    cout << ',';
    stampa_l(r->right);
    cout << ')';
}
//POST = stampa r in formato lineare

//PRE = albero(r) ben formato in formato BST, x intero da inserire
nodo* insert(nodo*r, int x){
    if(!r) return new nodo(x);
    if(x > r->info){
        r->right = insert(r->right,x);
    } else {
        r->left = insert(r->left,x);
    }
    return r;
}
//POST = inserisce una foglia in r in modo da mantenere il formato BST

//PRE = albero r ben formato e in formato BST, x intero qualsiasi
bool search (nodo* r, int x){
    if(!r) return false;
    if(x > r->info) return search(r->right,x);
    else return search(r->left,x);
}
//POST = restituisce true sse eisite in r un nodo con campo info = x

//PRE = albero r ben formato e in formato BST
nodo* max(nodo* r){
    if(!r) return NULL;
    if(r->right) return max(r->right);
    return r;
}
//POST = restituisce puntatore al nodo di campo info massimo

//PRE = albero r ben formato e in formato BST
nodo* min(nodo* r){
    if(!r) return NULL;
    if(r->left) return max(r->left);
    return r;
}
//POST = restituisce puntatore al nodo di campo info minore in r

//PRE = albero r ben formato
int altezza(nodo*r){
    if(!r) return 0;
    return 1 + max(altezza(r->left), altezza(r->right));
}
//POST restituisce la lunghezza del cammino più lungosull'albero, ovvero l'altezza di r

//PRE = albero r ben formato
int altMin(nodo*r){
    if(!r) return 0;
    return 1 + min(altMin(r->left),altMin(r->right));
}
//POST = restituisce lunghezza del cammino minimo dalla radice a una foglia