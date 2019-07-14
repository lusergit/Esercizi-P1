# Esercizio inventato
Dato un albero binario e un array di interi si tratta di restituire una lista concatenata di nodi il cui campo info sia un puntatore ai nodi dell'albero che verificano il match  
Costruire quindi una funzione iterativa  
```c++
//PRE = r radice di un albero ben formato, P array di dimP interi definiti
nodo* trova(nodoA* r, int* P, int dimP);
//POST = ritorna lista concatenata di nodi il cui campo info è un puntatore ai nodi dell'albero r che partecipano al match se questo avviene anche in maniera non continua ma completa, ritorna 0 altrimenti
```
La soluzione che ho adottato usa anche una a funzione ausiliaria `nodo* build_L(elem*,int)` che nel caso di match data la pila (Quindi il percorso nell'albero) restituisce la lista concatenata di nodi che puntano ai nodi dell'albero che contribuiscono al match.