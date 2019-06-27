#include<iostream> 
using namespace std;

struct nodo
{
	int info;
	nodo* next;
	nodo(int a=0, nodo* b=0){
		info = a;
		next = b;
	}
};

//PRE = cin contiene n valori interi con n>=0
nodo* leggi(){
	int x; cin >> x;
	nodo* L;
	if(x != -1){
		L = new nodo(x);
		nodo* current = L;
		cin >> x;
		while(x != -1){
			current->next = new nodo(x);
			current = current->next;
			cin >> x;
		}
	}
	return L;
}
//POST = restituisce lista concatenata formata da nodi il cui campo info è definito dai valori letti in input
//		 (se vengono letti x1, x2 e così via la lista sarà formamta da x1,x2 e così via)

//PRE = L ben formata
int fai_ricerca(nodo* L, int x){
    int i=0; 
    bool trovato = false;
    while(L && !trovato){
        if(L->info == x)
            trovato = true;
        else{
            L = L->next;
            i++;
        }
    }
    if(trovato) return i;
    return -1;
}
//POST = ritorna la posizione in lista dell'elemento con info = x se questo è presente, -1 altrimenti

//PRE = L lista ben formata, cin contiene n valori
void fai_ricerche(nodo* L, int n){
    int *A = new int[n];
    for(int i=0; i<n; i++){
        cin >> A[i];
    }
    
    for(int i=0; i<n; i++){
        int posizione = fai_ricerca(L,A[i]);
        if(posizione == -1){
            cout << "Nessun nodo con campo info = " << A[i] << endl;
        }
        else {
            cout << "Nodo con campo info = " << A[i] << " in posizione " << posizione << endl;
        }
    }
    
    return;
}
//POST = stampa in stdout se i valori contenuti in cin stdin sono presenti o meno in L e in che posizione


int main(){
	nodo* L = leggi();
    int n; cin >> n;
    fai_ricerche(L,n);
	return 0;
}
