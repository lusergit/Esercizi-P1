#include<iostream>
#include "code.h"
using namespace std;

//PRE = L lista ben formata
nodo* ultimo(nodo* L){
	if (L) {
		while(L->next){
			L=L->next;
		}
	}
	return L;
}
//POST = ritorna puntatore all'ultimo nodo della lista, se è vuota ritorna NULL

//PRE = coda Q ben formata
bool e_vuota(coda Q){
	return !Q.inizio;
}
//POST = ritorna true sse Q è vuota

//PRE = Coda Q ben formata, c definito
void push(nodo* L, coda& Q){
	if(e_vuota(Q)){
		if(L){
			Q.inizio = L;
			Q.fine = ultimo(L);
		} else {
			Q.inizio = Q.fine = L;
		}
	} else {
		Q.fine->next = L;
		Q.fine = ultimo(Q.inizio);
	}
}
//POST = aggiunge in fondo alla coda un nodo con campo info = c

//PRE = Q è be formata
int pop(coda& Q){
	if(e_vuota(Q)) return '\0';
	nodo* tmp = Q.inizio;
	Q.inizio = Q.inizio->next;
	int tmpinfo = tmp->info;
	delete tmp;
	return tmpinfo;
}
//POST = viene rimosso il nodo in testa a Q, e ritorna il carattere del suo campo info