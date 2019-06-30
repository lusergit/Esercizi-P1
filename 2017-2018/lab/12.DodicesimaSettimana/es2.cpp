#include <iostream>
#include "code.h"
using namespace std;

//PRE = L lista ben formata
int len(nodo* L){
	int count = 0;
	while(L){
		count++;
		L = L->next;
	}
	return count;
}
//POST = ritorna lunghezza della lista


nodo* build(int n){
	coda Q;
	for(int i = 0; i < n; i++){
		int x; cin >> x;
		push(new nodo(x), Q);
	}
	return Q.inizio;
}


nodo* delastk(nodo* &L, int k, int y){

	nodo* current = L;
	int * nodi_y = new int[len(L)];
	int top = 0;
	for(int i = 0; current; i++){
		if(current->info == y){
			nodi_y[top] = i;
			top++;
		}
		current = current->next;
	}

	coda to_return, resto;
	if(top >= k){
		int* da_el = nodi_y+(top-k);
		current = L;
		// dimensione del vettore da_el[] = k;
		for(int i=0; k && current; i++){
			nodo * tmp = current;
			current = current->next;
			tmp->next = 0;
			if(i == *da_el){
				push(tmp, to_return);
				da_el++;
				k--;
			} else {
				push(tmp, resto);
			}
		}
		push(current, resto);
	} else {
		push(L, resto);
	}
	delete[] nodi_y;
	L = resto.inizio;
	return to_return.inizio;
}

void stampa(nodo* L){
	while(L){
		cout << L->info;
		if(L->next) cout << " -> ";
		L=L->next;
	}
	cout << endl;
}

int main(){
	int n, k, y;
	cin >> n >> k >> y;
	nodo* L = build(n);
	nodo* eliminati = delastk(L,k,y);
	if(eliminati){
		cout << "Nodi eliminati: ";
		stampa(eliminati);
		cout << "Resto della lista: ";
		stampa(L);
	} else {
		cout << "Nessun nodo eliminato, lista: ";
		stampa(L);
	}
	return 0;
}