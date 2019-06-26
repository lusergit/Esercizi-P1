#include<iostream>
using namespace std;

struct nodo{
    int info;
    nodo* next;
    nodo(int a=0, nodo* b=0){
        info = a;
        next = b;
    }
};

nodo* buildList(){
    int x;
    cin >> x;
    if(x==-1) return NULL;
    return new nodo(x,buildList());
}

nodo* buildList_iter(){
    int x;
    cin >> x;
    if(x==-1) return NULL;
    nodo* L = new nodo(x);
    nodo* start = L;
    bool primo = true;
    while(x!=-1){
        if(!primo){
            L->next = new nodo(x);
            L = L->next;
        } else primo = false;
        cin >> x;
    }
    return start;
}

bool compare(nodo*L1, nodo*L2){
    if(!L1 || !L2){
        if(!L1 && !L2) return true;
        return false;
    }
    return compare(L1->next,L2->next);
}

void stampa(nodo* L){
    if(!L) return;
    cout << L->info << ' ';
    if(L->next) cout << " -> ";
    else cout << endl;
    stampa(L->next);
}

int nodi(nodo* L){
    if(!L) return 0;
    return 1+nodi(L->next);
}

//STAMPA LISTA L DALL'ULTIMO NODO AL PRIMO 
//PRE = Lista L ben formata
void stampaC_ric(nodo* L){
    const int n = nodi(L);
    nodo **stack = new nodo[1][n];
    //struisce stack che suerà come LIFO
    for(int i=n-1; i>0; i--){
        stack[0][i] = L;
        L=L->next;
    }
    //Stampa dallo stack
    for(int i=1; i<n-1; i++){
        cout << stack[i]->info;
        if(i!=n-1) cout << " -> ";
        else cout << endl;
    }
}
//POST = stampaLista L dall'ultimo nodo al primo

int main(){
    nodo* L = buildList();
    cout << "passo a L1" << endl;
    nodo* L1 = buildList_iter();
    bool uguali = compare(L,L1);
    if(uguali) cout << "L1 e L2 sono uguali" << endl;
    else{
        cout << "Fra hai sbagliato qualcosa, ti mostro: " << endl;
        stampa(L);
        stampa(L1);
    }
    cout << "ricorsiva: " << endl;
    stampaC_ric(L);
    stampaC_ric(L1);
    return 0;
}