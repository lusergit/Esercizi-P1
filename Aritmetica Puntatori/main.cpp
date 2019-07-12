#include<iostream>
using namespace std;

int V_ele(int n_ele, int lim3){
  return (n_ele*lim3);
}

int compatta_match(int* X, int n_el, int lim3, int*& P, int& dimP){
    int buoni = 0;
    for(int i=0; dimP && i<n_el-dimP+1; i++){
        if(X[V_ele(i,lim3)] != *P){
            X[V_ele(buoni,lim3)] = X[V_ele(i,lim3)];
            buoni++;
        } else {
            P++;
            dimP--;
        }
    }
    return buoni;
}

int main(){
    int X[400], el, lim1, lim2, lim3;
    cin >> el >> lim1 >> lim2 >> lim3;
    if(el > lim1*lim2*lim3) el = lim1*lim2*lim3;
    for(int i=0; i<el; i++){
        cin >> X[i];
    }
    int dimP; cin >> dimP;
    int *P = new int[dimP];
    for(int i=0; i<dimP; i++){
        cin >> P[i];
    }
    int vf; cin >> vf;
    int *pvf = X+vf;
    int sp = el/(lim2*lim3), eus = el - (sp*lim2*lim3), rpus = eus/lim3, eur = eus - (rpus*lim3);
    int n_el = lim3*sp;
    if(vf < rpus) n_el += lim3;
    if(vf == rpus) n_el += eur;
    
    n_el = compatta_match(pvf,n_el,lim3,P,dimP);

    if(dimP){
        cout << "Pattern non esaurito, rimane: ";
        for(int i=0; i<dimP; i++){
            cout << P[i] << ' ';
        }
    } else {
        cout << "Pattern consumato tutto";
    }
    cout << endl;

    cout << "V-Fetta rimanente:\n\t";
    for(int i=0; i<n_el; i++){
        cout << pvf[V_ele(i,lim3)] << " ";
    }
    cout << endl;
}