#include<iostream>
using namespace std;

struct nodo{
    int info;
    nodo* left, *right;
    nodo(int x=0, nodo* y=0, nodo* z=0){
        info = x;
        left = y;
        right = z;
    }
};

//costruisce albero con n livelli
nodo* buildTree(int n){
    if(!n) return NULL;
    int x; cin >> x;
    return new nodo(x,buildTree(n-1),buildTree(n-1));
}

int altezza(nodo* r){
    if(!r) return 0;
    return 1+altezza(r->left)+altezza(r->right);
}

struct elem{
    int momento;
    nodo* N;
    elem(int a=0, nodo*b=0){
        momento = a;
        N=b;
    }
};

//PRE = r albeo ben formato
void stampa(nodo* r){
    elem *pila = new elem[altezza(r)+1];
    int top = 0;
    if(r){
        pila[top] = elem(0,r);  //inizializza, mette r come primo elemento della radice
        top++;                  //ora c'è un elemento nella pila
    }
    while(top){
        switch (pila[top-1].momento)
        {
        case 0:
            //caso 0: stampa "r->info(" e poi mette un nodo con il nodo sinistro
            if(!pila[top-1].N){//Se punta a 0
                cout << '_';
                top --;
            } else {
                cout << pila[top-1].N->info << "(";
                pila[top-1].momento++;
                pila[top] = elem(0,pila[top-1].N->left);
                top++;
            }
            break;
        
        case 1:
            //caso 1: ha ritornato da sinistra, stampa ',' e richiama a destra
            // POSSO ASSUMERE CHE CI SIA R PERCHE altrimenti non avrebbe richiamato a sinistra
            cout << ',';
            pila[top] = elem(0,pila[top-1].N->right);
            pila[top-1].momento++;
            top++;
            break;

        case 2:
            cout << ")";
            top--;
            break;
        }
    }
}
//POST = stampa r in formato lineare

int main(int argc, char *argv[]){
    int n; cin >> n;
    nodo* r = buildTree(n);
    stampa(r);
    cout << endl;
    return 0;
}
