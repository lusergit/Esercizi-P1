#include<iostream>
using namespace std;

struct nodoA{
    int info;
    nodoA* left;
    nodoA* right;
    nodoA(int a=0, nodoA *b = 0, nodoA * c=0){
        info = a; left=b; right=c;
    }
};

struct nodo{
    nodoA* info;
    nodo* next;
    nodo(nodoA* a=0, nodo* b=0){
        info = a;
        next = b;
    }
};

//PRE = L, M liste ben formate
nodo* glue(nodo* L, nodo* M){
    if(!L) return M;
    nodo* current = L;
    while(current->next) current = current->next;
    current->next = M;
    return L;
}
//POST = ritorna L@M

int n_nodi(nodoA* r){
    if(!r) return 0;
    return 1+n_nodi(r->left)+n_nodi(r->right);
}

nodoA* build(nodoA* r, int n){
    if(n){
        int x; cin >> x;
        r = new nodoA(x);
        r->left = build(r->left,n-1);
        r->right = build(r->right,n-1);
        return r;
    } else return 0;
}

struct elem{
    nodoA* r;
    int mom, pm;
    elem(int a=0, int c = 0, nodoA* b=0){
        mom = a;
        r = b;
        pm = c;
    }
};

int altezza(nodoA* r){
    if(!r) return 0;
    return 1+max(altezza(r->left), altezza(r->right));
}

nodo* build_L(elem *pila, int dimP){
    int el_match = 0;
    nodo* to_return = 0;
    for(int i=0; i<dimP; i++){
        if(pila[i].pm > el_match){
            to_return = glue(to_return, new nodo(pila[i].r));
            el_match++;
        }
    }
    return to_return;
}

//PRE = r radice di un albero ben formato, P array di dimP interi definiti
nodo* trova(nodoA* r, int* P, int dimP){
    elem *pila = new elem[altezza(r)+1];
    int top = 0;
    if(r){
        pila[top++] = elem(0,0,r);
    }
    bool trovato = false;
    while(top && !trovato){
        switch(pila[top-1].mom){
            case 0:
                if(pila[top-1].pm == dimP)
                    trovato = true;
                else {
                    if(!pila[top-1].r)
                        top--;
                    else {
                        if(pila[top-1].r->info == P[pila[top-1].pm])
                            (pila[top-1].pm)++;
                        pila[top-1].mom++;
                        pila[top++] = elem(0,pila[top-1].pm, pila[top-1].r->left);
                    }
                }
                break;

            case 1:
                pila[top-1].mom++;
                pila[top++] = elem(0,pila[top-1].pm, pila[top-1].r->right);
                break;

            case 2:
                top--;
                break;
        }
    }
    if(trovato){
        return build_L(pila, top);
    } else return 0;
}
/*POST = ritorna lista concatenata di nodi il cui campo info è un puntatore ai nodi dell'albero r 
         che partecipano al match se questo avviene anche in maniera non continua ma completa, 
         ritorna 0 altrimenti */

void stampa(nodo* L){
    while(L){
        cout << L->info->info;
        if(L->next) cout << "->";
        L = L->next;
    }
    cout << endl;
}

int main()
{
    int n, k; cin >> n >> k;
    nodoA* r = build(r,n);
    //cout << "Fatto" << endl;
    int *P = new int[k];
    for(int i=0; i<k; i++){
        cin >> P[i];
    }
    //cout << "inseriti" << endl;
    nodo* found = trova(r,P,k);
    if(found){
        cout << "Match trovato" << endl;
        stampa(found);
    } else cout << "Match non trovato" << endl;
}
