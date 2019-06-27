#include<iostream>
#include "code.h"
using namespace std;

int main(){
	char x; cin >> x;
	coda Q;
	while(x != '.'){
		if(x <= 'z' && x >= 'a')
			push(x,Q);
		else if(x == '*')
			cout << pop(Q);

		cin >> x;
	}
	cout << endl;
	return 0;
}