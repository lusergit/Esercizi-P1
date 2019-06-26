#include<iostream>
using namespace std;

struct nodo{
    int info;
    nodo *left, *right;
    nodo(int x=0, nodo* y=0, nodo*z=0){
        info = x;
        left = y;
        right = z;
    }
};

nodo* insert(nodo* r, int x){
    if(!r) return new nodo(x);
    if(r->info < x){
        r->right = insert(r->right,x);
    } else {
        r->left = insert(r->left,x);
    }
    return r;
}

nodo* build(nodo *r, int n){
    if(!n) return r;
    int x; cin >> x;
    r = insert(r,x);
    r = build(r,n-1);
    return r;
}

bool match(nodo *r, int* A, int n){
    while(n && r){
        if(*A == r->info){
            A++; n--;
        }
        if(*A > r->info)
            r = r->right;
        else r = r->left;
    }
    return !n;
}

int main(int argc, char *argv[]){
    int n; cin >> n;
    nodo* R = build(0,n);
    cin >> n;
    int *A = new int[n];
    for(int i=0; i<n; i++){
        cin >> A[i];
    }
    if(match(R,A,n)){
        cout << "Pattern trovato" << endl;
    } else {
        cout << "Pattern non trovato" << endl;
    }
    return 0;
}
