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
using std::ostream;

namespace spazio1
{
	class decimale
	{
		private:
		int intero, virgola; //parte intera del numero e parte dopo la virgola del numero
		/*
			NOTAZIONE SCOMODA IN PRATICAMENTE TUTTI I CONTESTI! Da evitare sempre, non ha senso salvare i numeri in questo modo
		*/
		
		
		public:
		//decimale(); //non serve quello di default, se non specifico nulla viene comunque preso quello sotto grazie ai valori di default
		decimale(const int&, const int&);
		//costruttore di copia -> default va benissimo
		int getIn() const {return intero;}	//TODO: dichiararli sotto e non inline
		void setIn(const int& x) {intero=x;}
		int getVi() const {return virgola;}
		void setVi(const int& x) {virgola=x;}
	};
	
	decimale::decimale(const int& in = 0, const int& vi = 0)
	{
		intero = in;
		virgola = vi;
	}
	
	ostream& operator << (ostream& os, const decimale& d)
	{
		os << "Numero: " << d.getIn() << '.' << d.getVi() << '\n';
		return os;
	}
	
	decimale operator + (const decimale& a, const decimale& b) //ritorno per copia
	{
		//non considero il fatto che 4.5 + 2.10 fa 6.60 e non 6.15, l'esempio non è su questo
		//CODICE LOGICAMENTE ERRATO!
		return decimale(a.getIn()+b.getIn(), a.getVi()+b.getVi());
	}
	
	decimale operator - (const decimale& a, const decimale& b)
	{
		//CODICE LOGICAMENTE ERRATO!
		return decimale(a.getIn()-b.getIn(), a.getVi()-b.getVi());
	}
	bool operator < (const decimale& a, const decimale& b)
	{
		int diff = a.getIn() - b.getIn();
		if(diff > 0)
			return false;
		if(diff < 0)
			return true;
		
		diff = a.getVi() - b.getVi();	//Errato anche qui...
		if(diff > 0)
			return false;
		if(diff < 0)
			return true;
	}
	bool operator == (const decimale& a, const decimale& b)
	{
		if(a.getIn() == b.getIn() && a.getVi() == b.getVi())	//questo è giusto
			return true;
		return false;
	}
	bool operator > (const decimale& a, const decimale& b)
	{
		if(a == b)
			return false;
		return !(a < b);
	}
	bool operator != (const decimale& a, const decimale& b)
	{
		return !(a == b);
	}
	
}

using spazio1::decimale;

int main()
{
	decimale a, b(5), c(7, 10);
	a = 34;
	a.setVi(45);
	cout << a.getIn() << '.' << a.getVi() << '\n';
	cout << b;
	cout << (a+b) << (a+c);
	if(a > b)
		cout << "a e' maggiore di b\n";
	else
		cout << "b e' maggiore o uguale di a\n";
	if(a == a)
		cout << "sorprendentemente a e' uguale ad a\n";
	if(a != b)
		cout << "a e' diverso da b\n";
}