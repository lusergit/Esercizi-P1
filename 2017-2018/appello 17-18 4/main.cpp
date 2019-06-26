 
#include<iostream>
using namespace std;

struct nodo
{
    int info;
    nodo *next;
    nodo(int a=0, nodo *b=0){
        info = a;
        next = b;
    }
};

struct nodoL
{
    nodo* info;
    nodoL *next;
    nodoL(nodo* a=NULL, nodoL* b=NULL){
        info = a;
        next = b;
    }
};

nodo* buildList(int n){
    if(n == 0) return NULL;
    int x; cin >> x;
    return new nodo(x,buildList(n-1));
}

nodo* trim(nodo* &L, int x){
    if(!L) return NULL;
    if(L->info < x){       
        nodo* tmp = L;
        L= NULL;
        return tmp;
    }
    return trim(L->next,L->info);
}

//PRE = L lista ben formata
nodoL* Gric(nodo* L){
    if(!L) return NULL; //NULLa da fare qui
    nodoL* tmp = new nodoL(L);
    nodo* prossimo = trim(L,L->info);
    tmp->next = Gric(prossimo);
    return tmp;
}
//POST = restituisce lista concatenata LL di nodi di tipo nodoL con tanti nodi quanti sono
//       i pezzi CeNA di L e tale che il primo nodo di LL ha campo p che punta al primo pezzo
//       CeNA di L, il secondo nodo punta al secondo pezzo CeNA e così via. I pezzi CeNA puntati
//       da LL sono trasformati in liste ben formate mettendo a 0 il campo next del loro ultimo nodo)

void stampaL(nodo* L){
    if(!L) {
        cout << endl;
        return;
    }
    cout << L->info;
    if(L->next) cout << " -> ";
    stampaL(L->next);
}

void stampaLL(nodoL* G){
    if(!G) return;
    stampaL(G->info);
    stampaLL(G->next);
}

int n_nodi(nodo*L){
    int count = 0;
    while(L){
        count++;
        L=L->next;
    }
    return count;
}

nodoL* insert(nodoL* ord, nodoL* L){
    nodoL* current = ord, *padre = ord;
    if(!ord) return L;
    if (n_nodi(current->info) > n_nodi(L->info))
    {
        L->next = current;
        return L;
    }
    //non nel primo nodo
    while(current && n_nodi(current->info) <= n_nodi(L->info)){
        padre = current;
        current = current->next;
    }
    L->next = current;
    padre->next = L;
    return ord;
}

nodoL* ordina(nodoL* LL){
    nodoL* ordinata;
    while(LL){
        nodoL* tmp = LL;
        LL=LL->next;
        tmp->next = 0;
        ordinata = insert(ordinata, tmp);
    }
    return ordinata;
}

int main(){
    int n;
    cin >> n;
    nodo* L = buildList(n);
    stampaL(L);
    nodoL* y = Gric(L);
    stampaLL(y);
    nodoL* ordinata = ordina(y);
    cout << endl;
    stampaLL(ordinata);
    return 0;
}

