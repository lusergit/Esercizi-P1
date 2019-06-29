#include<iostream>
#include "code.h"
using namespace std;

//PRE = L, Q strutture rispettive ben formate
void push_l(nodo * L, coda& Q){
	if(Q.inizio){
		Q.fine->next = L;
		Q.fine = ultimo(Q.inizio);
	} else {
		Q.inizio = L;
		Q.fine = ultimo(L);
	}
}
//POST = aggiunge in coda alla coda Q i nodi della lista L

//PRE = L ben formata, P array di dimP elementi definiti
bool match_completo(nodo* L, int * P, int dimP){
	while(L && dimP){
		if(L->info == *P){
			P++; dimP--;
		}
		L = L->next;
	}
	return !dimP;
}
//POST  = ritorna tru sse tutti gli elementi di P sono presenti in ordine in L

//PRE = L ben formata, P array di dimP valori definiti
nodo* match(nodo*&L, int*P, int dimP){
	coda lista_match, resto;
	nodo* current = L;
	if(match_completo(L,P,dimP)){
		while(current && dimP){
			nodo* tmp = current;
			current = current->next;
			tmp->next = 0;
			if(tmp->info == *P){
				push_l(tmp,lista_match);
				P++; dimP--;
			} else {
				push_l(tmp,resto);
			}
		}
		push_l(current,resto);
	} else return 0;
	L = resto.inizio;
	return lista_match.inizio;
}
//POST = se c'è un match completo di P in L ritorna lista formata dai nodi di vL che compongono il match
//		 e L contiene i nodi rimanenti && ritorna 0 e L=vL altrimenti

void stampa(nodo*L){
	while(L){
		cout << L->info;
		if(L->next) cout << " -> ";
		L=L->next;
	}
	cout << endl;
	return;
}

nodo* build(int n){
	coda L;
	for(int i=0; i<n; i++){
		int x; cin >> x;
		push(x,L);
	}
	return L.inizio;
}

int main(){
	int k,n; cin >> k >> n;
	nodo * l = build(k);
	int * A = new int[n];
	for(int i=0; i<n; i++)
		cin >> A[i];
	nodo* lista_match = match(l,A,n);
	if(lista_match){
		cout << "Match trovato:\n\tlista match = ";
		stampa(lista_match);
		cout << "L = ";
		stampa(l);
	} else {
		cout << "Match non trovato:\n\tL = ";
		stampa(l);
	}
}