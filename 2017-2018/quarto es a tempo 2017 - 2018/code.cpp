#include<iostream>
#include "code.h"

nodo::nodo(char c, nodo* n)
{
	info = c;
	next = n;
}

coda::coda()
{
	inizio = NULL;
	fine = NULL;
}

//PRE_push=(c è una lettera, Q è una coda, eventualmente vuota)

void push(nodo*n, coda &Q)
{
  n->next=0;
	if (Q.fine)
	{
		Q.fine->next = n;
		Q.fine = Q.fine->next;
	}
	else
	{
		Q.inizio = n;
		Q.fine = Q.inizio;
	}
}

//POST_push=(a Q è stato aggiunto un nodo terminale, di chiave c)

//NB: se inizo==fine, allora fine->next==NULL, e quando faccio inizio=inizio->next, inizio diventa NULL, quindi ottengo la lista vuota
//PRE_pop=(Q è una coda non vuota)

nodo* pop(coda &Q)
{
	nodo *x = Q.inizio;
	Q.inizio = x->next;

	if (Q.inizio == NULL)
		Q.fine = NULL;

	return x;
}

//POST_pop=(a Q è stato rimosso il nodo iniziale, e pop ritorna la chiave del nodo rimosso)

//PRE_e_vuota=(Q è una coda, eventualmente vuota)

bool e_vuota(coda Q)
{
	return Q.inizio == NULL;
}

//POST_e_vuota=(e_vuota ritorna true sse Q è vuota)

//PRE = L lista ben formata e non vuota
nodo* ultimo(nodo* L){
	if(!L->next) return L;
	return ultimo(L->next);
}
//POST = restituisce puntatore allúltimo nodo di L

//PRE = Lista L ben formata && Q coda ben formata
void push_list(nodo*L,coda &Q){
	if(!L) return;
	if(e_vuota(Q)){
		Q.inizio = L;
		Q.fine = ultimo(L);
		return;
	}
	Q.fine->next = L;
	Q.fine = ultimo(L);
}
//POST = inserisce L in coda alla lista gestita da Q