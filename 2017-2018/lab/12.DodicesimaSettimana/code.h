#ifndef CODE_H
#define CODE_H

struct nodo{
	//char info;
	//Servono char o int in base all'esercizio
	int info;
	nodo* next;
	nodo(int a = 0, nodo * b = 0){
		info = a;
		next = b;
	}
};

nodo* ultimo(nodo*);

struct coda
{
	nodo* inizio;
	nodo* fine;
	coda(nodo*L = 0){
		if(L){
			inizio = L;
			fine = ultimo(L);
		} else {
			inizio = fine = 0;
		}
	}
};

void push(nodo*, coda&);
int pop(coda&);
bool e_vuota(coda);
nodo* build(nodo*);
#endif