#include<iostream>
#include<fstream>
using namespace std;
struct nodo{int info; nodo* next; nodo(int a=0, nodo* b=0){info=a; next=b;}}; // nodo di lista
struct FIFO{
	nodo* primo, *ultimo;
	FIFO(nodo*a=0){
		primo=a;
		ultimo=a;
	}
};

FIFO push_end(FIFO a, nodo*b)
{
  if(!a.primo)
  {a.primo=a.ultimo=b;}
  else
   {a.ultimo->next=b; a.ultimo=b;}
  return a;
}


struct nodoF {FIFO fi; nodoF* next;nodoF(FIFO a=FIFO(),nodoF*b=0){fi=a; next=b;}};

//funzioni ausiliarie

  void stampa_L(nodo*L)
{
 if(L)
  {cout<<L->info<<' '; stampa_L(L->next);}
 else
   cout<<endl;

}
 void stampa_F(nodoF* a)
{
  if(a)
   {stampa_L(a->fi.primo);
    cout<<endl;
    stampa_F(a->next);
   }
  else
   cout<<endl;
}

nodo* costruisci(int dim)
{
 if(dim)
   {int x; cin>>x; return new nodo(x,costruisci(dim-1));}
 return 0;
}

//PRE=(W è una lista corretta di nodoF, a è un nodo con campo next=0, vW=W)

nodoF* inserisci (nodoF*W, nodo*a){

	if(!W){
		//caso base 1: la lista dei nodoF e' vuota
		FIFO *b= new FIFO(a);
		return  new nodoF(*b,0);
	}
	if(a->info == W->fi.primo->info){
		//caso base 2: il nodo da inserire ha info == al fifo contenuto dal nodoF corrente.
		W->fi= push_end(W->fi,a);
		return W;
	}else if( W->fi.primo->info > a->info ){
		//caso base 3: nella W non e'  presente il valore a->info inoltre il valore info del FIFO di W attuale e' > del nodo ->info, il che vuol dire che
		// L(W) non contiene un fifo che abbiamo il valore == a->info, percio' devo creare una nodoF nuova e inserirlo.
		nodoF* f= new nodoF(*new FIFO(a),0);
		f->next=W;
		return f;
	}else{
		//caso ricorsivo: il nodo a->info non e' <= al valore di valore dei nodi contenuti nel fifo del  nodof W corrente, quindi
		// devo l'operazione di inserisci sul nodo successivo di L(W).
		//PRE_ric: (W->next è una lista corretta di nodoF, a è un nodo con campo next=0, vW->next=W->next)

		W->next=inserisci(W->next,a);
		//POST_ric:(restituisce una lista di nodoF ottenuta da vW->next aggiungendo ad esso  il nodo a) questa asserzione richiede maggiori spiegazioni.
		//i) se in vW->next c'è già un nodoF che gestisce una sottolista con nodi con campo info=a->info, allora a andrà aggiunto in fondo a questa sottolista.
		//ii) se (i) non si applica allora sarà necessario aggiungere un nuovo nodoF a vW->next che gestisca la sottolista composta solo dal nodo a e questo
		//nuovo nodoF andrà inserito nel posto di vW->next tale che prima di lui ci siano le sottoliste con campo info minori di a->info e dopo di lui quelle
		//con info maggiore di a->info
		return W;
	}
/***************************************DIMOSTRAZIONE DI CORRETTEZZA*************************************
 *
 * caso base 1:
 * 	!W: il nodo corrente di W e' nullo, quindi devo creare un nodoF con un fifo che gestisce il nodo a e restituirlo;
 *
 * 	caso base 2:  a->info == W->fi.primo->info
 * 	e' stato trovato una struttura FIFO che gestisce dei valori uguali al valore info contenuto nel nodo da inserire,
 * 	quindi inserisco il nodo nella FIFO attraverso la funzione push_end e risultato lo riassegno alla struttura FIFO di W corrente, quindi lo restituisco.
 *
 *
 * 	caso base 3: W->fi.primo->info > a->info
 *
 * 	se si arriva a questo punto dell'esecuzione, allora W non contiene un fifo che gestisce dei valori pari a quello contenuto in a, allora controllo se e'
 * 	> del valore in a, se si, vuol dire che dobbiamo creare un nodoF nuovo, poiche' la W e' ordinata.
 * 	Quindi creo un nodo nuovo, assegno come il valore di next il valore di W, e restituisco f.
 *
 * 	caso ricorsivo:
 *
 * 	la chiamata ricorsiva avviene sse i primi 3 casi basi non avvengono, quindi continuo la ricerca della posizione corretta della L(W) per
 * 	inserire il nodo a.
 *
 * Dal PRE, possiamo affermare che il PRE_ric sia corretta, poiche' se si arriva alla chiamata ricorsiva, vuol dire che non e' stato effettuato nessun operazione
 * sulla lista, e sul nodo a.
 * Quindi assegno il valore restituito dalla chiamata ricorsiva al W->next, e con il return dei chiamate ricorsive precedenti, si forma la L(W).
 *
 * Per il passo induttivo, possiamo affermare che anche il  POST_ric e' vera, distinguendo due casi:
 * i: nel L(vW->next) esiste gia una struttura FIFO che gestisce quel valore, allora il nodo a viene semplicemente inserito. (caso base 2)
 * ii: nel L(vW->next) non esiste gia' una struttura FIFO che gestisce quel valore, quindi si distinguono in ulteriori due casi:
 * 		1: la W e' nulla, quindi semplicemente si crea un nodoF con un FIFO che contiene il nodo a; (caso base 1)
 * 		2: la W NON e' nulla, quindi si deve creare un nodoF con un FIFO che contiene il nodo a, e lo si deve inserire nella L(vW) modificando
 * 			i puntatori (caso base 3)
 * Cosi' con il ritorno delle chiamate ricorsive si forma una lista corretta, perche' nella costruzione dei nodoF nuovi, il valore next e'= 0, che contiene
 * Allora il POST e' soddisfatto.
 *
 *
 */

}
//POST=(restituisce una lista di nodoF ottenuta da vW aggiungendo ad esso  il nodo a) questa asserzione richiede maggiori spiegazioni.
//i) se in vW c'è già un nodoF che gestisec una sottolista con nodi con campo info=a->info, allora a andrà aggiunto in fondo a questa sottolista.
//ii) se (i) non si applica allora sarà necessario aggiungere un nuovo nodoF a vW che gestisca la sottolista composta solo dal nodo a e questo
//nuovo nodoF andrà inserito nel posto di vW tale che prima di lui ci siano le sottoliste con campo info minori di a->info e dopo di lui quelle
//con info maggiore di a->info


//PRE=(Q è lista corretta di nodo)
nodoF*smembra(nodo* Q){
	nodoF* daRest=0;

	while(Q){
		/* Invariante:
		 *
		 * daRest e' una lista di FIFO, dove ogni fifo gestisce una coda di valore omogenei, mentre tra le FIFO i valore sono diverse, &&
		 *  se daRest != 0, allora daRest->info->primo->info < daRest->next->info->primo->info
		 *  Q contiene i nodi rimanenti da inserire nella lista nodoF  daRest puo' anche essere nulla, ovvero quando i nodi da inserire sono finiti.
		 *
		 */
		nodo* temp=Q;
		Q=Q->next;
		temp->next=0;
		daRest=inserisci(daRest,temp);
	}

	return daRest;
}
//POST=(restituisce  una lista concatenata di nodoF che contiene le sottoliste di Q come mostrato nell'esempio 2, cioè in ordine di campo info crescenti)

nodo* concatenaFifo(FIFO a, nodo* b){
	if(!a.primo) return b;
	if(!b) return a.primo;

	a.ultimo->next=b;
	return a.primo;
}


//PRE=(W è lista corretta di nodoF, vW=W)
nodo* LO(nodoF* W) {
	if(!W) return 0;
	 nodo* temp = LO(W->next);
	 temp= concatenaFifo(W->fi,temp);

	 return temp;
}
//POST=(produce una lista di tipo nodo composta concatenando le sottoliste gestite dai campi info dei nodi di vW nell'ordine in cui sono in vW;
//		i nodoF di vW sono tutti deallocati)


int main()
{
   int dim;

   cin>>dim;
   nodo*C=costruisci(dim);

   cout<<"Lista costruita"<<endl;
   stampa_L(C);
   nodoF* a=smembra(C);
   cout<<"Liste uniformi:"<<endl;
   stampa_F(a);

   nodo* b=LO(a);
   cout<<"Lista ordinata"<<endl;
   stampa_L(b);
   cout<<"end";
}
