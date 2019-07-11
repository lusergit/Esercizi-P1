#include<iostream>
using namespace std;

struct nodo{int info; nodo* next; nodo(int a=0, nodo* b=0){info=a; next=b;}}; // nodo di lista 
struct FIFO{nodo* primo, *ultimo;FIFO(nodo*a=0, nodo*b=0){primo=a; ultimo=b;}};
struct nodot{int info; nodot* left, *right; nodot(int a=0, nodot* b=0, nodot* c=0){info=a; left=b; right=c;}};//nodo di albero

FIFO push_end(FIFO a, nodo*b)
{
  if(!a.primo)
  {a.primo=a.ultimo=b;}
  else
   {a.ultimo->next=b; a.ultimo=b;}
  return a;
}


int conta_n(nodot*r)
{
   if(!r) return 0;
     else
    return conta_n(r->left)+conta_n(r->right)+1;
}

nodot* insert(nodot*r, nodot* y)
{
  if(!r) return y;
   
  if(conta_n(r->left)<=conta_n(r->right))
    r->left=insert(r->left,y);
   else   
    r->right=insert(r->right,y); 
  return r;
}
void stampa_lista(nodo*C)
{
  if(C)
    {cout<<C->info<<' '; stampa_lista(C->next);}
  else
    cout<<endl;
}

nodot* build_tree(nodot*R,int n_el)
{
 if(!n_el) return R;
 int x;
 cin>>x;
 nodot* Q= insert(R,new nodot(x));
 return build_tree(Q,n_el-1);
}
void stampa(nodot *r)
{
  if(r)
    {
      cout<<r->info<<'(';
      stampa(r->left);
      cout<<',';
      stampa(r->right);
      cout<<')';
    }
  else
    cout<< '_';
}

FIFO concF(FIFO a, FIFO b){
    if (!a.primo) return b;
    if (!b.primo) return a;
    a.ultimo->next = b.primo;
    a.ultimo = b.ultimo;
    return a;
}

/* Farò tutti iterativo perchè mi sto preparando per la parte iterativa dell'appello nell'a.a. 2018-2019 */
struct elem{
  nodot* r;
  int mom;
  elem(int a=0, nodot* b=0){
      r = b;
      mom = a;
  }
};

int altezza(nodot* r){
    if(!r) return 0;
    return 1+max(altezza(r->left),altezza(r->right));
}

FIFO pickiter_infix(nodot* R, int& n, int k){
    FIFO to_return;
    elem *pila = new elem[altezza(R)+1];
    int top = 0;
    if(R){
        pila[top] = elem(0,R);
        top++;
    }
    while(top){
        switch(pila[top-1].mom){
            case 0:
                if(!pila[top-1].r){
                    top--;
                } else {
                    pila[top-1].mom++;
                    pila[top] = elem(0,pila[top-1].r->left);
                    top++;
                }
                break;
                
            case 1:
                if(n == k){
                    to_return = push_end(to_return, new nodo(pila[top-1].r->info));
                    n = 1;
                } else n++;
                pila[top-1].mom++;
                pila[top] = elem(0,pila[top-1].r->right);
                top++;
                break;
                
            case 2:
                top--;
                break;
        }
    }
    
    return to_return;
}

/*
//Funzione non necessaria davvero
bool presente(nodo* L, int n){
    bool pres = false;
    while(L && !pres){
        if(L->info == n) pres = true;
        L = L->next;
    }
    return pres;
}
*/

FIFO tieni_primo(nodo*& Q){
    
    FIFO ripetuti, primi;
    while(Q){
        nodo* current = Q;
        Q = Q->next;
        current->next = 0;
        primi = push_end(primi, current);
        FIFO uguali, resto;
        while(Q){
            current = Q;
            Q = Q->next;
            current->next = 0;
            if(current->info == primi.ultimo->info){
                uguali = push_end(uguali,current);
            } else resto = push_end(resto, current);
        }
        ripetuti = concF(ripetuti,uguali);
        Q = resto.primo;
    }
    
    Q = primi.primo;
    return ripetuti;
}

 main()
{
  int test,n_el, k, n=1;
 cin>>test>>n_el>>k;
 
 nodot* R=build_tree(0,n_el);
 cout<<"albero:"<<endl;
 stampa(R);
 FIFO x=pickiter_infix(R,n,k);
 cout<<endl<<"lista creata:"<<endl;
 stampa_lista(x.primo);
 if(test>0)
 {
  FIFO y=tieni_primo(x.primo);
  cout<<"lista dei nodi tolti"<<endl;
  stampa_lista(y.primo);
  cout<<"lista dei nodi che restano"<<endl;
  stampa_lista(x.primo);
 }

 cout<<endl<<"end"<<endl;
 
}
