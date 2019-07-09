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

//PRE = R ben formato e in formato BST, A vettore di n>=0 elementi
bool match(nodo *r, int* A, int n){
    //PRE = PRE_f && vN = n && vA = A
    while(n && r)
    //R = all'iterazione i controllati i primi i nodi del percorso sul quale può trovarsi il match && n>=0 numero di elementi del pattern rimasti
    {
        if(*A == r->info){
            A++; n--;
        }
        if(*A > r->info)
            r = r->right;
        else r = r->left;
    }
    //POST = n=0 sse trovato ogni elemento del pattern in vA
    return !n;
}
//POST = ritorna true sse è il pattern indicato da A è presente in r (anche in maniera non contigua)

/*
Dimostrazione while:
    PRE => 0 iterazioni avvenute && n = numero di elementi di A => 0 nodi controllati dopo 0 iterazioni 
            && (n=vN => ancora vN elementi da trovare) => R

Invarianza:
    R && (n && r) => n>0 && r non vuoto:
        if(*A == r->info){
            A++; n--; // n-- al massimo risulta in n = 0 dato che per la guardia n>0 e intero => n>=0
        }
        if(*A > r->info)
            r = r->right;
        else r = r->left; //Garantisce che si percorra il cammino corretto sull'albero per tentare di trovare il match
                          //proprio per definizione di albero BST

    => controllato l'iesimo nodo dell'unico percorso possibile per il match

    => R

Terminazione:
    2 casi:
        n=0 => match trovato, per invarianza n è diminuito ogni volta che veniva trovato un elemento del pattern
        => ,atch trovato => n=0
    
        n>0 && r=0 => Percorso tutto il possibile cammino dell'albero, ma rimangono ancora elementi del pattern da trovare
        match non trovato => n>0 && n>0 => match trovato

    => n=0 sse trovato match anche non contiguo del pattern in vA

(return !n => ritorna true sse trovato match anche non contiguo del pattern di vA in r)

*/

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
