#include<iostream>
#include<fstream>
using namespace std;
struct nodo{int info; nodo* next; nodo(int a=0, nodo* b=0){info=a; next=b;}}; // nodo di lista 
struct FIFOX{nodo* primo, *ultimo; int valp, valu,nele; FIFOX(nodo*a=0, int b=0, int c=0, int d=0){primo=a; ultimo=a;valp=b;valu=c;nele=d;}};

ostream & operator<<(ostream & OUT, FIFOX& a)
{
  OUT<< '['<<"nele="<<a.nele<<" valp="<<a.valp<<" valu="<<a.valu<<']'<<endl; 
  int x=0;
  nodo*z=a.primo;
  while(x<a.nele)
  {OUT<<z->info<<' ';z=z->next; x++;}
  OUT<<endl;
  return OUT;
}

bool operator!=(FIFOX a, FIFOX b){
  if(a.nele == b.nele && a.primo == b.primo && a.ultimo == b.ultimo && a.valp == b.valp && a.valu == b.valu)
    return false;
  return true;
}

FIFOX push_iter(FIFOX A, nodo* n){
  if(!A.primo){
    A.primo = A.ultimo = n;
    A.nele = 1;
    A.valp = n->info;
    A.valu = n->info;
    return A;
  }
  if(A.primo->info > n->info){
    n->next = A.primo;
    A.primo = n;
    A.valp = n->info;
    A.nele++;
    return A;
  }
  if(A.ultimo->info < n->info){
    n->next = 0;
    A.ultimo->next = n;
    A.ultimo = n;
    A.valu = n->info;
    A.nele++;
    return A;
  }
  nodo* current = A.primo;
  while(current->next && current->next->info < n->info){
    current = current->next;
  }
  n->next = current->next;
  current->next = n;
  A.nele++;
  return A;
}

nodo* aux(nodo*&L, int x){
  if(!L) return NULL;
  if(L->info == x){
    nodo* tmp = L;
    L=L->next;
    
  }
}

FIFOX deleteX(FIFOX a, int z){
  if(z<a.valp || z>a.valu) return a;
  if(z == a.valp){
    nodo* tmp = a.primo;
    a.primo = a.primo->next;
    a.valp = a.primo->info;
    a.nele--;
    return a;
  } else {
    a.ultimo = aux(a.primo,z);
    a.nele--;
  }
}

main()
{
   int dim1,dim2, x;
   
   cin>>dim1>>dim2;
   FIFOX a;
   while(dim1)
   {
   
   cin>>x;
   a=push_iter(a,new nodo(x));
   dim1--;
  }
   cout<< a;

   while(dim2)
   {
     cin>>x;
     a=deleteX(a,x);
     dim2--;
   }
   cout<<a;

   cout<<"end"<<endl;  
}
