#include<iostream>
using namespace std;

//qualche funzione ausiliaria
int H_ele(int n_ele, int lim2, int lim3){
  return ((n_ele%lim3) + (n_ele/lim3)*lim2*lim3);
}

void stampa_fetta(int *hf, int n_ele, int lim2, int lim3) {
  for (int i=0; i<n_ele; i++){
    cout << hf[H_ele(i,lim2,lim3)];
    if(i<n_ele-1) cout << ", ";
  }
  cout << endl;
  return;
} 

int main()
{
  int X[400], P[20], n_ele, nP, lim1, lim2,lim3;
  cin >> n_ele;
  for(int i=0; i<n_ele; i++)
    cin >> X[i];
  cin >> lim1 >> lim2 >> lim3;
  if(lim1*lim2*lim3 < n_ele)
    n_ele=lim1*lim2*lim3;
  cin >> nP;
  for(int i=0; i<nP; i++)
    cin >> P[i];
  int nsp= n_ele/(lim2*lim3), eus= n_ele%(lim2*lim3), rpus= eus/lim3, ur= eus%lim3;
  cout<<"start"<<endl;
  int hf;
  cin >> hf;
  int lung = nsp*lim3;
  if(hf < rpus) lung+=lim3;
  if(hf == rpus) lung += ur;
  int* phf = X+(hf*lim3), *p=P, vnP = nP;
  int buoni = 0;

  for(int j=0; j < lung && nP > 0; j++)
	{
    if(phf[H_ele(j,lim2,lim3)] != *p){
      phf[H_ele(buoni,lim2,lim3)] = phf[H_ele(j,lim2,lim3)];
      buoni ++;
    } else {
      p++;
      nP--;
    }
	}
  
  if(nP){
    cout << "Pattern rimasto: ";
    for(int i=0; i<nP; i++){
      cout << *(p+i) << " ";
    }
    cout << endl;
  } else { cout << "Pattern consumato tutto" << endl; }

  cout<<"la H-fetta "<<hf<<" e' diventata:"<<endl;
  stampa_fetta(phf,buoni,lim2,lim3);
  cout<<"end"<<endl;

  return 0;
}
