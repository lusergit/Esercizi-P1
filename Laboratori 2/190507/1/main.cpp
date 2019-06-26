#include<iostream>
using namespace std;

struct nodo {
    char chiave;
    nodo *next;
    nodo(char c='\0', nodo* n=NULL)
    {
        chiave = c;
        next = n;
    };
};

struct coda {
    nodo *inizio;
    nodo *fine;
    coda(){
        inizio = 0;
        fine = 0;
    };
};

bool e_vuota(coda Q){
    return Q.inizio == NULL;
};
void push(char c, coda &Q){
    if(e_vuota(Q)){
        Q.inizio=Q.fine=new nodo(c);
        return;
    }
    Q.fine->next = new nodo(c);
    Q.fine = Q.fine->next;
};
char pop(coda &Q){
    if(!Q.inizio) return '\0';
    char tmp = Q.inizio->chiave;
    nodo* nodoTmp = Q.inizio;
    Q.inizio = Q.inizio->next;
    delete nodoTmp;
    return tmp;
};

// IMPLEMENTARE I METODI DELLA LIBRERIA `coda`

void input(coda &Q,char x){
    if(x >= 'A' && x <= 'Z'){
        push(x,Q);
    } else if(x == '*'){
        if(e_vuota(Q)) cout << "vuota";
        else cout << pop(Q);
        cout << ' ';
    } else if(x == '.') return;
    cin >> x;
    input(Q,x);
}

int main() 
{
    coda Q;
    
    cout << "start" << endl;
    // IMPLEMENTARE LA SOLUZIONE DELL'ESERCIZIO UTILIZZANDO LE FUNZIONI ESPOSTE DALLA LIBRERIA `coda`
    char x; cin >> x;
    input(Q,x);
    cout << "end" << endl;
}