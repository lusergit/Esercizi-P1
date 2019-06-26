#include<iostream>
using namespace std;

struct nodo{
    int info;
    nodo* next;
    nodo(int x=0, nodo* y=0){
        info = x;
        next = y;
    }
};

void leggi(int*& A, int dim){
    A = new int[dim];
    for(int i=0; i<dim; i++){
        cin >> A[i];
    }
}

void scambia(int* A, int a, int b){
    int c = A[a];
    A[a] = A[b];
    A[b] = c;
}

void djikstra(int* A, int dim){
    int zeri=0,due=dim;
    for(int i=0; i<due; i++){
        if(A[i] == 2){
            scambia(A,i,due-1);
            due--;
        }
        if(A[i] == 0){
            scambia(A,i,zeri);
            zeri++;
        }
    }
}

void stampa(int* A, int dim){
    for(int i=0; i<dim; i++){
        cout << A[i];
        if(dim-1-i) cout << ", ";
        else cout << endl;
    }
}

int main(int argc, char *argv[]){
    int* A, N; cin >> N;
    leggi(A,N);
    djikstra(A,N);
    stampa(A,N);
    return 0;
}
