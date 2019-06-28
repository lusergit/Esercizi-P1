#include<iostream>
#include "code.h"
using namespace std;

nodo* build(int n){
	coda Q;
	for(int i=0; i<n; i++){
		int x; cin >> x;
		push(x,Q);
	}
	return Q.inizio;
}

void leggi(int *A, int dimA){
	for(int i=0; i<dimA; i++){
		cin >> A[i];
	}
}

bool match_completo(nodo* L, int* P, int dimP){
	bool matcha = true;
	for(int i=0; matcha && i<dimP; i++){
		if(L){
			matcha = (L->info == P[i]);
			L = L->next;
		}
		else matcha = false;
	}
	return matcha;
}

//PRE = L lista ben formata, n lista puntata da Q.inizio, vQ
void push_list(coda &Q, nodo* L){
	if(!Q.inizio){
		Q.inizio = L;
		Q.fine = ultimo(L);
	} else {
		Q.fine->next = L;
		Q.fine = ultimo(L);
	}

}
//POST ritorna coda formata da vQ.inizio@L

//PRE = L ben dormata, con almeno n>0 nodi formata da n_nodi@resto
nodo* trim(nodo* L, int n){
	for(int i=0; i<n-1; i++){
		L =L->next;
	}
	nodo* tmp = L->next;
	L->next = 0;
	return tmp;
}
//POST = ritorna puntatore a resto, e mette a zero il puntatore dell'ultimo nodo di n_nodi

//PRE = L lista ben formata, P ha dimP elementi, vL = L
nodo* match(nodo* &L, int *P, int dimP){
	nodo * current = L;
	coda to_return, resto;
	bool trovato = false;
	while(!trovato && current){
		if(match_completo(current,P,dimP)){
			push_list(resto, trim(current,dimP));
			push_list(to_return, current);
			trovato = true;
		} else {
			nodo * tmp = current->next;
			current->next = 0;
			push_list(resto, current);
			current = tmp;
		}
	}
	L = resto.inizio;
	return to_return.inizio;
}
//POST = se in L c'è un match completo di P, la funzione ritorna inodi che compongono il match, chiamiamoli mL
//		 mentre in L rimangono vL-mL (vL alla quale sono stati tolti i nodi di mL)
//		 && se non c'è match ritorna 0 e L=vL

void stampa(nodo* L){
	while(L){
		cout << L->info;
		if(L->next) cout << " -> ";
		L=L->next;
	}
	cout << endl;
}

int main(){
	int n, k; cin >> n >> k;
	nodo *L = build(n);
	int *A = new int[k];
	leggi(A,k);
	nodo* L1 = match(L,A,k);
	stampa(L);
	stampa(L1);
	return 0;
}