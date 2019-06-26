#include<iostream>
#include "BST.h"
using namespace std;
main()
{
  nodo* r=new nodo(15, new nodo(7), new nodo(19));
  r->left->right=new nodo (9, new nodo(8));
  r->right->right=new nodo(25, new nodo(22));
  
  bool stop=false;
  while(!stop){

      int x; cin >> x;
      switch (x)
      {
      case 0:
        stop = true;
        break;
      
      case 1:
        stampa_l(r);
        break;
      
      case 2:
        int y; cin >> y;
        r = insert(r,y);
        break;
      
      case 3:
        int y; cin >> y;
        cout << "valore " << y;
        if(search(r,y)){
          cout << " presente" << endl;
        } else cout << " non presente" << endl;
        break;

      case 4:
        int witch; cin >> witch;
        if(witch == 1){
          cout << "Massimo: " << max(r)->info << endl;
        } else cout << "Minimo: " << min(r)->info << endl;
        break;
      
      case 5:
        cout << "Altezza: " << altezza(r) << endl;
        break;

      case 6:
        cout << "Altezza minima: " << altMin(r) << endl;
      }
    }
}
