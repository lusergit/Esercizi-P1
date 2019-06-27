#include<iostream>
#include"code.h"
using namespace std;

//Problema di giuseppe
coda build(int n){
	coda Q;
	while(n){
		int x;
		cin >> x;
		push(x,Q);
		n--;
	}
	return Q;
}

int main(){
	int n, k;
	cin >> n >> k;
	coda Q = build(n);
	for(int i = 0; i<n-1; i++){
		for(int j=0; j<k-1; j++){
			push(pop(Q),Q);
		}
		cout << "Eliminato: " << pop(Q) << endl;
	}
	cout << "Rimane " << Q.inizio->info << endl;
	return 0;
}