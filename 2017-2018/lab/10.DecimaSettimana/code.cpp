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
void push(char c, coda& Q){
	if(e_vuota(Q)){
		Q.inizio = Q.fine = new nodo(c);
	} else {
		Q.fine->next = new nodo(c);
		Q.fine = Q.fine->next;
	}
}
//POST = aggiunge in fondo alla coda un nodo con campo info = c

//PRE = Q è be formata
char pop(coda& Q){
	if(e_vuota(Q)) return '\0';
	nodo* tmp = Q.inizio;
	Q.inizio = Q.inizio->next;
	char tmpchar = tmp->info;
	delete tmp;
	return tmpchar;
}
//POST = viene rimosso il nodo in testa a Q, e ritorna il carattere del suo campo info