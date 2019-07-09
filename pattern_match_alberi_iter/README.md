# Soluzione iterativa
fortunatamente essendo gli albero considerati in formato BST un pattern match è facilmente realizzabile e dimostrabile.  
Data la struttura considerata il pattern può apparire in un unico percorso (indicato dal pattern e dall'albero stessi), e quindi è facile realizzare una soluzione iterativa

  Un'eventuale soluzione ricorsiva consisterebbe in una ricorsione terminale dato che la funzione andrebbe richiamata su uno solo dei sottoalberi figli della radice a seconda del pattern da trovare.