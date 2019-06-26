struct nodo{int info; nodo*left, *right; nodo(int a =0, nodo*b=0, nodo*c=0){info=a; left=b; right=c;}};

void stampa_l(nodo*);
nodo* insert(nodo*, int);
bool search (nodo*, int);
nodo* max(nodo*);
nodo*& min(nodo*&);
int altezza(nodo*);
int altMin(nodo*);
void elim(nodo*&,int);
nodo*elim1(nodo*,int);

