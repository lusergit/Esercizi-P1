#include<iostream>
using namespace std;

struct nodo {
    char chiave;
    nodo *next;
    nodo(char c='\0', nodo* n=NULL){
        chiave = c;
        next = n;
    };
};

struct coda {
    nodo *inizio;
    nodo *fine;
    coda(){
        inizio = NULL;
        fine = NULL;
    };
};

bool e_vuota(coda Q){
    return !Q.inizio;
};

void push(char c, coda &Q){
    if(e_vuota(Q)){
        Q.inizio =  new nodo(c);
        Q.fine = Q.inizio;
    } else {
        Q.fine->next = new nodo(c);
        Q.fine=Q.fine->next;
    }
};

char pop(coda &Q){
    if(!Q.inizio) return '\0';
    nodo* tmp = Q.inizio;
    char tmp_c = Q.inizio->chiave;
    Q.inizio = Q.inizio->next;
    if(!Q.inizio) Q.fine = NULL;
    delete tmp;
    return tmp_c;
};

void termina(coda& Q, int k, int m){
    if(!Q.inizio->next) return;
    if(m == 1){
        cout << pop(Q);
        termina(Q,k,k);
    } else {
        push(pop(Q),Q);
        termina(Q,k,m-1);
    }
}

void stampa(nodo* L){
    if(!L){
        cout << endl;
        return;
    }
    cout << L->chiave;
    if(L->next) cout << " -> ";
    stampa(L->next);
}

int main() 
{
    coda Q;
    
    cout << "start" << endl;
    int n, k;
    cin >> n >> k;
    for(int i=0; i<n; i++){
        char x;
        cin >> x;
        push(x,Q);
    }
    cout << "Pushata: ";
    stampa(Q.inizio);
    termina(Q,k,k);
    cout << endl;
    if(Q.inizio == Q.fine){
        cout << "ok, tutto a posto, rimane " << Q.inizio->chiave << endl;
    } else {
        cout << "Fra hai sbagliato, sei scemo" << endl;
    }
    cout << "end" << endl;
}