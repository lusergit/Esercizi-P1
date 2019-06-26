#include<iostream>
using namespace std;

//albero
struct nodo
{
    char info;
    int n;
    nodo *left, *right;
    nodo(char a='\0', nodo* b=0, nodo*c=0){
        info = a;
        left = b;
        right = c;
        n = 1;
    }
};

nodo* insert(nodo* r, char x){
    if(!r) return new nodo(x);
    if(r->info < x){
        r->right = insert(r->right,x);
    } else {
        r->left = insert(r->left,x);
    }
    return r;
}

void buildtree(nodo* &r){
    char x;
    cin >> x;
    if(x == 'q') return;
    r = insert(r,x);
    buildtree(r);
}

void stampa(nodo* r){
    if(!r){
        cout << '_';
        return;
    }
    cout << r->info << '(';
    stampa(r->left);
    cout << ',';
    stampa(r->right);
    cout << ')';
}

int n_nodi(nodo* r){
    if(!r) return 0;
    return 1 + n_nodi(r->left) + n_nodi(r->right);
}

nodo* cerca_infix(nodo* r, int &k, int*C){
    if(!r) return NULL;
    *C = 0;
    nodo* left = cerca_infix(r->left,k,C+1);
    if(left) return left;
    *C=-1;
    if(k == 1) return r;
    k=k-1;
    *C=1;
    nodo* right = cerca_infix(r->right,k,C+1);
    if(right) return right;
    return NULL;
}

void stampa_path(int* C){
    if(*C == -1){
        cout << *C << " ]" << endl;
        return;
    }

    cout << *C << ' ';
    stampa_path(C+1);
}

void completa(nodo*&r){
    if(!r) return;
    completa(r->left);
    completa(r->right);
    int n = 1;
    if(r->left) n += r->left->n;
    if(r->right) n += r->right->n;
    r->n = n;
}

void stampa_completa(nodo* r){
    if(!r){
        cout << '_';
        return;
    }
    cout << r->n << '(';
    stampa_completa(r->left);
    cout << ',';
    stampa_completa(r->right);
    cout << ')';
}

int main(){
    nodo* root = NULL;
    buildtree(root);   
    stampa(root);
    cout << endl;
    int k = n_nodi(root), x;
    int* C = new int[k];
    cin >> x;
    int y=x;
    nodo* trovato = cerca_infix(root,x,C);
    if(trovato){
        cout << "nodo " << y << " trovato:" << endl;
        cout << "valore: " << trovato->info << "\tPath: [ ";
        stampa_path(C);
    } else {
        cout << "Valore non trovato";
    }
    completa(root);
    stampa_completa(root);
    cout << endl;
}