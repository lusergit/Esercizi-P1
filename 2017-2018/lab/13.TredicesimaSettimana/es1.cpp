#include<iostream>
using namespace std;

struct nodo
{
    int info;
    nodo* left, *right;
    nodo(int a = 0, nodo * b = 0, nodo * c = 0){
        info = a;
        left = b;
        right = c;
    }
};

struct elem{
    int momento;
    nodo* info;
    elem(nodo * a = 0, int mom = 0){
        info = a;
        momento = mom;
    }
};

int n_nodi(nodo* r){
    if(!r) return 0;
    return 1 + n_nodi(r->left) + n_nodi(r->right);
}

nodo* insert(nodo* r, int x){
    if (!r) return new nodo(x);
    if(n_nodi(r->right) < n_nodi(r->left))
        r->right = insert(r->right,x);
    else r->left = insert(r->left,x);
    return r;
}

nodo* build(){
    int x; cin >> x;
    nodo * R;
    while(x != -1){
        R = insert(R, x);
        cin >> x;
    }
}

int altezza(nodo* r){
    if(!r) return 0;
    return 1 + max(altezza(r->left) , altezza(r->right));
}

void stampa_a_salti(nodo* r, int k){
    elem *al = new elem[altezza(r)+1];
}

int main(){
    int k;
    nodo* R = build();
    cin >> k;
    stampa_a_salti(R,k);
}