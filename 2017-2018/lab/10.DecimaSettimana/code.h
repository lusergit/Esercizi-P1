#ifndef CODE_H
#define CODE_H

struct nodo{
	char info;
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

void push(char, coda&);
char pop(coda&);
bool e_vuota(coda);

#endif