# Esercizio
Costruisco una lista (strutture nodo)  
```c++  
struct nodo{  
    int info;
    nodo * next;
}
```
  Con costruttore apposito con campo info 0 oppure 1, in modo che rappresenti un numero in formato binario
  Su questa lista lancerò poi  
  ```c++
  //PRE = L ben formata e in formato binario vL = L
  bool sommma1(nodo*L){
      ...
  }
  //POST = L contiene il numero rappresentato da vL + 1, ritorna true sse è avvenuto overflow (e in tal caso aggiunge un nodo in testa lla lista con campo info 1)
  ```