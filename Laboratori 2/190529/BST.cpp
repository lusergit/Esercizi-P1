#include "BST.h"
#include<iostream>
using namespace std;

//PRE = albero(n) ben formato
void stampa_l(nodo* n){
    if(!n){
        cout << '_';
        return;
    }
    cout << n->info << '(';
    stampa_l(n->left);
    cout << ',';
    stampa_l(n->right);
    cout << ')';
}
//POST = stampa in formato lineare albero(n)
/*
correttezza:
    caso base !n:
        albero vuoto, stampa '_' ==> POST
    caso ricorsivo:
        n albero be formato, allora esiste n->info && n->left e n->right alberi ben formati
        allora
        PRE_ric = n->left albero ben formato
        stampa(n->left)
        POST_ric = stampato in formato lineare n->left

        analogo per n->right
        in entrambi i casi verificata la post condizione 
*/

//PRE = albero(r) ben formato e in formato BST, x intero
nodo* insert(nodo* BST, int x){
    if(!BST) return new nodo(x);
    if(x > BST->info){
        BST->right = insert(BST->right,x);
    } else {
        BST->left = insert(BST->left, x);
    }
    return BST;
}
//POST = inserito un nodo con info=x nell'albero in modo da mantenere il formato BST
/*
Correttezza:
    caso base: !r
        alloca un nodo con campo info=x e ne ritorna il puntatore ==> POST
    
    caso ricorsivo:
        !!r ==> r albero non vuoto,
        // per mantenere il formato BST
        // PRE_ric = essendo r non vuoto e ben formato, allora sia r->left che r->right sono alberi ben formati e in formato BST
        //           (dato che sottoalberi di un BST)
        if(x > r->info) r->right = insert(r->right,x);
        else r->left = insert(r->left,x);
        // POST = nodo con info=x inserito nel sottoalbero desto o sinistro in maniera da conservare il formato BST

        return r ==> POST
*/

//PRE = r ben formato
bool search(nodo* r, int x){
    if(!r) return false;
    if(x == r->info) return true;
    return search(r->left,x) || search(r->right,x);
}
//POST = ritorna true sse r contiene un nodo con campo info = x
/*
Correttezza:
    caso base 1: 
        !r ==> r albero vuoto, non ha un campo info
        ritorna falso ==> POST
    caso base 2:
        r non vuoto && r->info == x
        ritorna true ==> POST
    caso ricorsivo:
        !!r ==> r non è vuoto
        ==> r->left e r-> right sono alberi ben formati
        && r->info diverso da x
        //PRE_ric = r->left e r->right alberi ben formati
        return search(r->left,x) || search(r->right,x);
        //POST_ric = ritorna true sse r->left o r->right contengono un nodo con campo info = x
        ==> POST 
*/

//PRE = r benf formato e in formato BST
nodo* max(nodo*r){
    if(!r) return NULL;
    if(r->right) return max(r->right);
    return r;
}
//POST = ritorna puntatore al nodo con campo info massimo all'interno di r, altrimenti ritorna NULL
/*
Correttezza:    
    caso base 1:
        !r => r = albero r vuoto, non ha nodi
        return NULL ==> POST
    caso base 2:
        r non vuoto, r->right = NULL;
        allora essendo albero in formato BST, la funzione è stata richiamata sul nodo
        più a destra dell'albero.

        return r ==> POST
    caso ricorsivo:

    if(r->right)
        //PRE_ric = albero r->right ben formato e in formato BST
        return max(r->right);
        //POST_ric = ritorna puntatore al nodo con campo info massimo di r->right
        return max(r->right) ==> POST;
*/

//PRE = r benf formato e in formato BST e non vuoto
nodo*& min(nodo*&r){
    //if(!r) return NULL;
    if(r->left) return min(r->left);
    return r;
}
//POST = ritorna puntatore del padre al nodo con campo info minimo all'interno di r per riferimento
/*
Correttezza:    
    caso base 1:
        !r => r = albero r vuoto, non ha nodi
        return NULL ==> POST
    caso base 2:
        r non vuoto, r->left = NULL;
        allora essendo albero in formato BST, la funzione è stata richiamata sul nodo
        più a sinistra dell'albero.

        return r ==> POST
    caso ricorsivo:

    if(r->left)
        //PRE_ric = albero r->left ben formato e in formato BST
        return min(r->left);
        //POST_ric = ritorna puntatore al nodo con campo info minimo di r->left
        return max(r->left) ==> POST;
*/

//PRE = r albero ben formato
int altezza(nodo* r){
    if(!r) return 0;
    return 1 + max(altezza(r->left),altezza(r->right));
}
//POST = ritorna l'altezza dell'albero (inteso come il cammino più lungo dalla radice a una foglia)
/*
Correttezza:
    caso base:
        !r ==> r vuoto: ha altezza 0;
        return 0 ==> POST
    
    caso ricorsivo:
        //PRE_ric = r->left && r->right sono alberi ben formati
        1+max(altezza(r->left),altezza(r->right))
        //POST_ric = altezza(left) e altezza(right) ritornano l'altezza dei sottoalberi sinsstro e destro rispettivamente
        //l'espressione ritornata avrà valore 1+massima altezza dei due sottoalberi
        ==> POST
*/
//forse poco chiara come dimostrazione

//PRE = r albero ben formato
int altMin(nodo* r){
    if(!r) return 0;
    return 1 + min(altMin(r->left),altMin(r->right));
}
//POST = ritorna l'altezza minima dell'albero (inteso come il cammino più corto dalla radice a una foglia)
/*
Correttezza:
    caso base:
        !r ==> r vuoto: ha altezza 0;
        return 0 ==> POST
    
    caso ricorsivo:
        //PRE_ric = r->left && r->right sono alberi ben formati
        1+max(altMin(r->left),altMin(r->right))
        //POST_ric = altMin(left) e altMin(right) ritornano l'altezza minima dei sottoalberi sinsstro e destro rispettivamente
        //l'espressione ritornata avrà valore 1+altezza minima dei due sottoalberi
        ==> POST
*/
//PRE = r albero ben formato e in formato BST
void elim(nodo*& r, int x){
    if(!r) return;
    if(r->info == x){
        if(!r->left && !r->right){
            delete r;
            r=NULL;
            return;
        } else if(r->left){
            if(r->right){
                nodo* tmp = min(r->right);
                min(r->right) = min(r->right)->right;
                r->info = tmp->info;
                delete tmp;
            } else {
                nodo* tmp = r;
                r = r->left;
                delete tmp;
            }
        } else {
            nodo* tmp = r;
            r = r->right;
            delete tmp;
        }
    } else {
        if(x > r->info) 
            elim(r->right, x);
        else elim(r->left, x);
    }
}
//POST = modifica r in modo da eliminare tutti i nodi con campo info=x
/*
Correttezza:
    caso base 1:
        !r -> r vuoto, non ha nodi da eliminare
        return ==> POST
    caso base 2:
        r non vuoto && r->info == x:
        3 sottocasi:
        1)
            r foglia (!r->left && !r->right)
            delete r
            r=NULL;
            return ==> POST
            dato che r passato per riferimento, r in realtà è il puntatore del padre al nodo,
            elminando dall'Heap r e settando a 0 la memoria viene liberata e il padre non punta più
            ad alvun nodo

        2)
            r ha 2 figli:
        if(r->right) // r->right albero ben formato e NON VUOTO
            //tmp punta al nodo con campo info minore di r->right, quello che più si avvicina ad r
            //PRE_ric = r->right ben formato e non vuoto 
            nodo* tmp = min(r->right);
            //POST_ric = tmp punta al nodo con campo info minore in r->right
            min(r->right) = min(r->right)->right; // min(r->right) scollegato dall'albero
            r->info = tmp->info;
            delete tmp; // eliminato
            ==> POST

        3)
            r ha 1 figlio
            in questi casi r (puntatore del padre) viene modificato per puntare al figlio esistente
            e il nodo da eliminare viene eliminato
            ==> POST

    caso ricorsivo:
        r->info diverso da x
        //PRE_ric = r->left e r->right ben formati
        if(x > r->info) 
            elim(r->right, x);
        else elim(r->left, x);
        //POST_ric = eliminati i nodi con campo info=x nel sottoalbero nel quale possono trovarsi
        ==> POST
*/

nodo* elim1(nodo* r, int x){

}
