# Non completato

L'eliminazione di un nodo da un albero in formato BST è un processo la cui soluzione ricorsiva è facilmente dimostrabile, a livello
iterativo invece è molto più complicato dato che bisognerebbe tenere traccia del padre più che del nodo corrente; bisognerebbe quindi 
trattare casi come l'eliminazione della radice a parte.  
In pratica Questo main si è trasformato più in un esercizio volto a capire meglio come percorrere un albero con la struttura ausiliaria 
  ```c++
elem{
    int momento;
    nodo* r;
    elem(..){
      ..
    }
};
```
  Descitta in clsse, tramite una pila `elem pila[] = new elem[altezza(r)+1]` è facile percorrere un albero binaro qualsiasi simulando 
  le chiamate ricorsive di una funzione ricorsiva
