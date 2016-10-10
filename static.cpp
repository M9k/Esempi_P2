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
	Esercizio 2.7.7 pag 40 (esteso)
*/

#include <iostream>

using std::cout;
using std::flush;

namespace spazio1
{
	class buildme
	{
		private:
		static int c0, c1, cc; //costruttore senza parametri, costruttore con un parametro, costruttore copia
		int x;
		
		public:
		buildme();
		buildme(const int&);
		buildme(const buildme&); //costruttore di copia, non richiesto
		
		//oltre a stampare lo restituiscono, potrebbe essere utile
		static int print_zero_number(); //domanda: ha senso mettere static? la risposta è suggerita dalla riga 63
		static int print_one_number();
		static int print_copy_number();
		
		static buildme niente(buildme a) {return a;}
	};
	
	int buildme::c0 = 0;
	int buildme::c1 = 0;
	int buildme::cc = 0;
	
	buildme::buildme()
	{
		x = 0;
		c0++;
	}
	buildme::buildme(const int& x)
	{
		this->x = x;
		c1++;
	}
	buildme::buildme(const buildme& b)
	{
		x = b.x;
		cc++;
	}
	
	int buildme::print_zero_number()
	{
		cout << "Il numero degli elementi costruiti usando il costruttore senza parametri è " << c0 << '\n'; //domanda: posso stampare anche x? QUALE x se la risposta è si?
		//PS: non posso stampare x, non è un metodo di istanza, non ho nessuna istanza che invoca il metodo print_zero_number
		return c0;
	}
	int buildme::print_one_number()
	{
		cout << "Il numero degli elementi costruiti usando il costruttore con un parametro è " << c1 << '\n';
		return c1;
	}
	int buildme::print_copy_number()
	{
		cout << "Il numero degli elementi costruiti usando il costruttore di copia è " << cc << '\n';
		return cc;
	}
	
}

using spazio1::buildme;


buildme niente2(buildme a) {return a;}

int main()
{
	buildme a, b, c(4), d=6, e(a), f = b;
	//ATTENZIONE: d=6 è ottimizzato e quindi tradotto come d(6), ma in realtà costruisce un oggetto anonimo con il costruttore con parametro intero e poi lo copia in d
	buildme::print_zero_number();
	buildme::print_one_number();
	buildme::print_copy_number();
	
	//i risultati variano in base al compilatori, alcuni ottimizzano in automatico i passaggi per evitare copie inutili, io ho che cc passa da 2 a 5 e poi a 8
	//con -fno-elide-constructors invece assume i valori di 3, 7 e 11. (3 per il motivo spiegato sopra)
	buildme::niente(buildme::niente(c));
	buildme::print_copy_number();
	niente2(niente2(c));
	buildme::print_copy_number();
	
}