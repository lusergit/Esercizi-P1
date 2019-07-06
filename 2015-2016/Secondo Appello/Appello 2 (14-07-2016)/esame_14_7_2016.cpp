#include<iostream>
using namespace std;
#include<fstream>
struct nodo { int info; nodo* next; nodo(int a = 0, nodo * b = 0) { info = a; next = b; } }; // nodo di lista 
struct FIFO { nodo* primo, * ultimo; FIFO(nodo* a = 0, nodo * b = 0) { primo = a; ultimo = b; } };
struct nodot { int info; nodot* left, * right; nodot(int a = 0, nodot * b = 0, nodot * c = 0) { info = a; left = b; right = c; } };//nodo di albero




FIFO push_end(FIFO a, nodo* b)
{
	if (!a.primo)
	{
		a.primo = a.ultimo = b;
	}
	else
	{
		a.ultimo->next = b; a.ultimo = b;
	}
	return a;
}

void stampa_L(nodo* L)
{
	if (L)
	{
		cout << L->info << ' '; stampa_L(L->next);
	}
	else
		cout << endl;

}
nodo* costruisci(int dim)
{
	if (dim)
	{
		int x; cin >> x; return new nodo(x, costruisci(dim - 1));
	}
	return 0;
}
nodo* clone(nodo* a)
{
	if (a)
	{
		return new nodo(a->info, clone(a->next));
	}
	return 0;
}

//*****************************************

FIFO  push_begin(FIFO x, nodo* b) {
	if (x.primo == 0 && x.ultimo == 0) {
		x.primo = b;
		x.ultimo = b;
	}
	else {
		b->next = x.primo;
		x.primo = b;
	}
	return x;
}

nodo* presente(nodo* n, int y) {
	if (n == 0) {
		return 0;
	}
	else {
		if (n->info == y) {
			return n;
		}
		else {
			return presente(n->next, y);
		}
	}
}

bool presente_iter(nodo* n, int y) {
	bool b = false;
	while (n && !b) {
		if (n->info == y) {
			b = true;
		}
		n = n->next;
	}
	return b;
}

//PRE=(L(Q) � una lista corretta e vL(Q)=L(Q))
FIFO tieni_ultimo_ric(nodo*& Q) {
	FIFO r;
	//caso base la lista e' vuota
	if (Q == 0) {//CB1
		return FIFO();//la lista dei nodi ripetuti su una lista vuota e' anche essa vuota
	}
	else {
		//caso ricorsivo
		r = tieni_ultimo_ric(Q->next);
		nodo* p = presente(Q->next, Q->info);//CR1
		if (p != 0) {//allora q e' un duplicato
			nodo* a = Q;
			Q = Q->next;
			a->next = 0;
			r = push_begin(r, a);

		}
		//r=push_end(r,0);
		return r;
	}
}
/*
POST=(L(Q) è ottenuta da vL(Q) eliminando i nodi con info ripetuto mantenendo solo l'ultimo
nodo per ciascun campo info e mantenendo l'ordine relativo che questi nodi hanno in vL(Q).
Inoltre restituisce un valore FIFO f tale che f.primo è la lista dei nodi eliminati
nello stesso ordine relativo che essi hanno in vL(Q))
*/

/*
PROVA INDUTTIVA
CB1) se la lista e' vuota di duplicati di una lista vuota non ce ne sono
CR1) se il nodo non e' vuoto effettuo la ricorsione
pre-ric=(L(Q->next) è una lista corretta e vL(Q->next)=L(Q->next))
POST-ric=(L(Q->next) è ottenuta da vL(Q->next) eliminando i nodi con info ripetuto mantenendo solo l'ultimo
nodo per ciascun campo info e mantenendo l'ordine relativo che questi nodi hanno in vL(Q->next).
Inoltre restituisce un valore FIFO f tale che f.primo � la lista dei nodi eliminati
nello stesso ordine relativo che essi hanno in vL(Q->next))
*/

//PRE=(L(Q) è una lista corretta e vL(Q)=L(Q))
FIFO tieni_ultimo_iter(nodo*& Q) 
//R = L(current) ben formata && all'n-esimo ciclo staccato l'n-esimo nodo di vL(Q) e inserito in resto se questo è l'ultimo col proprio campo info
//    Inserito in to_return altrimenti
{
	FIFO to_return, resto;
	while (Q) {
		nodo* tmp = Q;
		Q = Q->next;
		tmp->next = 0;
		if (presente_iter(Q, tmp->info)) {
			resto = push_end(resto, tmp);
		}
		else {
			to_return = push_end(to_return, tmp);
		}
	}

	Q = resto.primo;
	return to_return;
}
/*
POST=(L(Q) � ottenuta da vL(Q) eliminando i nodi con info ripetuto mantenendo solo l'ultimo
nodo per ciascun campo info e mantenendo l'ordine relativo che questi nodi hanno in vL(Q).
Inoltre restituisce un valore FIFO f tale che f.primo � la lista dei nodi eliminati
nello stesso ordine relativo che essi hanno in vL(Q))
*/

/*
Dim tieni_ultimo_iter:
PRE_while = PRE_f && to_return, resto code ben formate e vuote, L(current) = L(Q)
PRE_while =>  L(Q) ben formata && eseguiti 0 cicli => R

invarinaza:
	L(Q) && Q => Q non vuota => Q->next ben formata
	nell'esecuzione del ciclo:
	//viene staccato il primo nodo di L(Q) e viene puntato da tmp, Q=Q->next ben formata per guardia
	//PRE_presente = Q ben formata, tmp->info definito
	if(presente(Q,tmp->info))
	//POST_presente = ritorna 0 sse tmp->info non è presente in nessun altro nodo successivo a quello appena staccato in vL(Q)
	{ //inserisce tmp in resto, dato che in Q è presente un altro nodo con campo info = tmp->info }
	else //inserisce tmp in to_return
	=> nel ciclo eseguito eseguite le operazioni defnite nell'invariante
	=> R && guardia => R
	
terminazione:
	R && !current => percorsa tutta la lista => POST_while
	
	POST_while && Q=resto.primo, return to_return.primo => POST_f
*/

/*
ESERCIZIO TEORIA
PRE=(l' albero che ricevo e' corretto e non vuoto)
POST=(restituisce il numeo di nodi con un solo figlio successivi al nodo radice dato)
*/

//*****************************************

int main()
{

	int dim;

	cin >> dim;
	nodo* C = costruisci(dim);
	nodo* D = clone(C);
	cout << "Lista costruita" << endl;
	stampa_L(C);
	FIFO a = tieni_ultimo_ric(C);
	cout << "soluzione ricorsiva" << endl << "nodi tolti:" << endl;

	stampa_L(a.primo);
	cout << "lista rimanente:" << endl;
	stampa_L(C);
	FIFO b = tieni_ultimo_iter(D);
	cout << "soluzione iterativa" << endl << "nodi tolti:" << endl;
	stampa_L(b.primo);
	cout << "lista rimanente:" << endl;
	stampa_L(D);
	cout << "end";

	return 0;
}
