/*
	`7MMM.     ,MMF'        `7MM      
	  MMMb    dPMM            MM      
	  M YM   ,M MM  .d*"*bg.  MM  ,MP'
	  M  Mb  M' MM 6MP    Mb  MM ;Y   
	  M  YM.P'  MM YMb    MM  MM;Mm   
	  M  `YM'   MM  `MbmmdM9  MM `Mb. 
	.JML. `'  .JMML.     .M'.JMML. YA.
					   .d9            
					 m"'        Mirco Cailotto
-
-				 
	Esercizio: 
	parte A: trovo l'elemento più presente (in caso di parità, prendo quello più a sinistra)
	parte B: rimuovo tutte le istanze dell'elemento del punto A
	fatto tutto in modo iterattivo
*/

#include <iostream>
using namespace std;

void popola(int*a, int d)
{
	int i;
	for(i=0;i<d;i++)
		cin >> *(a+i);
}

int popolare(int*a, int d)
{
	//trova l'elemento più popolare (che appare più volte) in a array lungo d
	//varie soluzioni possibili, questa è quella logicamente più facile, ottimizzabile in vari modi
	int val = 0;
	int max = 0;
	int i, j;
	for(i=0;i<d;i++)
	{
		int cont = 0;
		for(j=i;j<d;j++)
			if(*(a+i) == *(a+j))
				cont++;
		if(cont > max)	//MAGGIORE NON UGUALE, altrimenti prendo il valore più a destra
		{
			max = cont;
			val = *(a+i);
		}
	}
	//debug
	//cout << "valore piu' popolare: " << val << " con " << max << " istanze\n";
	return val;
}

void rimuovi(int*a, int &d, int r)
{
	int i;
	for(i=0;i<d;i++)
		if(*(a+i) == r)
		{
			d--;
			//shift
			int j;
			for(j=i;j<d;j++)
				*(a+j) = *(a+j+1);
		}
	//MEMORY LEAK! a è stato dichiarato di d elementi, se ne uso meno ne spreco alcuni, trascurabile per ora
}
void stampa(int*a, int d)
{
	int i;
	for(i=0;i<d;i++)
		cout << *(a+i) << ' ';
	cout << '\n';
}

int main()
{
	int d;
	cin >> d;
	int a[d];
	popola(a,d);
	//PARTE A
	int pop = popolare(a, d); //se coglio anche il numero di istanze mi devo passare un puntatore a un intero e assegnarlo nella funzione
	cout << "valore piu' popolare: " << pop << '\n';
	//PARTE B
	rimuovi(a, d, pop);
	stampa(a, d);
	
	return 0;
}
