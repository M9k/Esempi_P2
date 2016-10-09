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
	Note:
	Con "nell'indirizzo" si intende l'indirizzo dove il costruttore "opera", cioè l'allocazione in memoria dell'istanza della classe,
	notare se l'indirizzo cresce o decresce per capire in che segmento di memoria operiamo.
	Il file è mio, i nomi li scelgo io (si, non voglio usare pippo e pluto o foo e bar).
*/

#include <iostream>

using std::cout;
using std::flush;
using std::ostream;

namespace GlaDOS
{
	class shodan
	{
		private: //potevo sottointenderlo
		int x;
		
		public:
		shodan(); //altrimenti di default
		shodan(int); //explicit per impedire l'utilizzo nella riga 115
		shodan& operator = (const shodan&); //i tipi const & saranno spiegati più avanti
		int getval() const; //const verrà spiegato più avanti
		shodan(const shodan&); //altrimenti di default
		
		operator int();
		//VALIDO RICAMBIARE SPECIFICATORE D'ACCESSO
		//private:
		//char y;
	};

	int shodan::getval() const
	{
		return x;
	}

	shodan::shodan()
	{
		x = 0;
		cout << "usato costruttore di default nell'indirizzo " << this << '\n';
	};
	shodan::shodan(int a)
	{
		x = a;
		cout << "usato costruttore con parametro nell'indirizzo " << this << '\n';
	};

	//OPERATORE DI ASSEGNAZIONE
	shodan& shodan::operator = (const shodan& sender)
	{
		cout << "usato operatore di copia dall'oggetto con valore " << sender.getval() << " a " << this << '\n';
		x = sender.x;
		return *this; //NE HO DAVVERO BISOGNO? NO, tanto quallo che ritorno non lo uso in questo caso
		//potrei persino ritornare un booleano o qualsiasi altra cosa, ma per convenzione si titorna l'oggetto
		//per permettere operazioni a cascata
		//leggere https://stackoverflow.com/questions/15292892/what-is-return-type-of-assignment-operator
	};

	//COSTRUTTORE DI COPIA
	shodan::shodan(const shodan& sender)
	{
		cout << "usato costruttore di copia dall'oggetto con valore " << sender.getval() << " a " << this << '\n';
		x = sender.x;
		//ritorno? NO, è un costruttore, i costruttori non hanno ritorno, e non ha senso usare "costruttori in cascata"
	}
	
	shodan::operator int() //NON specifico il ritorno, è sottointeso che è int
	{
		return x;
	}
	
	class terminalreality
	{
		private:
		;
		public:
		
		terminalreality(int a)
		{
			;	//l'apoteosi dell'utilità...
		}
		
		friend ostream& operator << (ostream& in, const terminalreality& ogg) //definizione inline perchè sarà usato una volta sola
		{
			in << "complimenti, hai stampato una classe vuota. *clap clap* \n";
			return in;
		}
	};
}

using GlaDOS::shodan;
using GlaDOS::terminalreality;

int main()
{
	cout << "a1:\n";
	shodan a1;
	cout << "Valore di a5 = " << a1.getval() << '\n';
	//ERRATO -> il compilatore pensa di dover dichiarare una funziona che ritorna un oggetto shodan
	//shodan a2();
	cout << "a3:\n";
	shodan a3 = 3; //POSSO IMPEDIRE QUESTO USO - uso explicit shodan(int) come costruttore
	cout << "Valore di a3 = " << a3.getval() << '\n';
	cout << "a4:\n";
	shodan a4(5);
	cout << "Valore di a4 = " << a4.getval() << '\n';
	cout << "a5:\n";
	shodan a5;
	a5 = a3;
	cout << "Valore di a5 = " << a5.getval() << '\n';
	cout << "a6:\n";
	shodan a6(a5);
	cout << "Valore di a6 = " << a6.getval() << '\n';
	cout << "Valore di a6 = " << a6 << '\n'; //ho definito un operatore di casting ad int, quindi va
	
	
	//terminalreality t; //ERRATO! ridefinire un costruttore elimina quello senza parametri di default
	terminalreality t(5);
	cout << t;
}