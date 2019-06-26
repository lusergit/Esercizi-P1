#include<iostream>
using namespace std;

struct nodo{
	int info;
	nodo* left;
	nodo* right;

	nodo(int x=0, nodo* l=0, nodo* r=0){
		info = x;
		left = l;
		right = r;
	}
};

// FUNZIONI AUSILIARIE FORNITE
nodo* buildTree(int arr[], int i, int n)  {

    if (i >= n) {
    	return NULL;
    }
    nodo* root = new nodo(arr[i]);
    // insert left child
    root->left = buildTree(arr, 2 * i + 1, n);
    // insert right child
    root->right = buildTree(arr, 2 * i + 2, n);

    return root;

}

int height(nodo* root) {
	if(!root) {
		return 0;
	}
	return 1 + max(height(root->left), height(root->right));
}

void printGivenLevel(nodo* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
       cout << root->info;
    else if (level > 1)
    {
        printGivenLevel(root->left, level-1);
        printGivenLevel(root->right, level-1);
    }
}

// STAMPA L'ALBERO LIVELLO PER LIVELLO
void printLevelOrder(nodo* root) {
    int h = height(root);
    int i;
    for (i=1; i<=h; i++)
    {
        printGivenLevel(root, i);
        cout << endl;
    }
}


// DA IMPLEMENTARE
// PRE=(albero(root) ben formato e non vuoto)
int cercaFoglia(nodo* root, int key, nodo* &t) {
    if(!root) return -1; // SOSTITUIRE CON LA VOSTRA IMPLEMENTAZIONE
    if(root->info == key){
        t = root;
        return 0;
    }
    int left = cercaFoglia(root->left,key,t);
    if(left != -1) return 1+left;
    int right = cercaFoglia(root->right,key,t);
    if(right!=-1) return 1+right;
    return -1;
}
// POST=(se c'è una foglia con info=x, allora restituisce col return la profondità minima di tale foglia e assegna a t il puntatore ad essa, altrimenti restituisce -1)

// Driver program to test above function
int main() {
    int a[100], n, key;
    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> a[i];
    }
    cin >> key;
    
    nodo* root = NULL;
    root = buildTree(a, 0, n);
    
    //printLevelOrder(root); // decommentare per vedere la stampa dell'albero livello-per-livello
    nodo* tmp = root;
    
    cout << "start" << endl;
    int altezza = cercaFoglia(root, key, tmp);
    if(altezza !=  -1){
        cout << "la foglia si trova ad altezza " << altezza << endl;
    } else cout << "foglia non trovata" << endl;
    cout << "end" << endl;
}
