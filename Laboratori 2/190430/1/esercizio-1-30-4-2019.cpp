#include<iostream>
using namespace std;

struct nodo{int info; nodo*next; nodo(int a=0, nodo*b=0){info=a; next=b;}};

main()
{
  nodo* L=leggi();
  int n;
  cin>>n;
  cout<<"start"<<endl;
  fai_ricerche(L,n);
  cout<<"end"<<endl;
}
