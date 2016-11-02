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
	Esempio di smart pointer con iteratori
*/
#include <iostream>

using std::cout;
using std::ostream;

class contenitore
{
	private:
	class ogg;
	class smartp;
	public:
	class iteratore;
	contenitore(); 
	contenitore(const contenitore&);
	~contenitore();
	void AggiungiInt(int);
	int PrelevaInt(); //non const perchè modifico il primo
	bool Vuoto() {return primo == 0;}
	
	private:
	class smartp
	{
		public:
		ogg* p;
		smartp(ogg * n = 0); //costruttore di default, con un argomento e conversione da ogg* a smartp
		smartp(const smartp&);						//regola del 3
		~smartp();									//regola del 3
		smartp& operator = (const smartp&);			//regola del 3
		bool operator == (const smartp&) const;
		bool operator != (const smartp&) const;
		ogg& operator *() const;
		ogg* operator ->() const;
		friend ostream& operator << (ostream& o, smartp p)
		{
			o << (*p).val;
			return o;
		}			
		
	};
	class ogg
	{
		public:
		ogg(); //costruttore standard
		ogg(int, smartp); //costruttore
		//copia standard
		//distruzione standard
		int val; //valore contenuto, int per semplificare
		smartp next; //il prossimo
		int riferimenti; 
		void operator delete(void* p);
	};
	smartp primo;
	public:
	class iteratore
	{
		public:
		iteratore(smartp n=0);
		bool operator == (const iteratore&) const;
		bool operator != (const iteratore&) const;
		iteratore& operator ++();
		iteratore operator ++(int);
		smartp& operator *(); //non più const, il "puntatore" è un oggetto
		
		private:
		smartp p;
	};
	
	iteratore begin() const { return iteratore(primo); }
	iteratore end() const { return iteratore(); }
};
// -- ITERATORE --
contenitore::iteratore::iteratore(smartp n):p(n) {}

bool contenitore::iteratore::operator != (const iteratore& i) const
{
	return p != i.p;
}
bool contenitore::iteratore::operator == (const iteratore& i) const
{
	return p == i.p;
}
contenitore::iteratore& contenitore::iteratore::operator ++() 
{
	if(p != 0)
		p=p->next; //p-> ritorna il nodo che ha un elemento di nome next
	return *this;
}
contenitore::iteratore contenitore::iteratore::operator ++(int) 
{
	iteratore b = *this;
	if(p != 0)
		p=p->next; //p-> ritorna il nodo che ha un elemento di nome next
	return b;
}
contenitore::smartp& contenitore::iteratore::operator *() 
{
	return p;
}

// -- SMARTP --
contenitore::smartp::smartp(ogg* n):p(n)
{
	if(p)
		p->riferimenti++;
}

contenitore::smartp::smartp(const smartp& s):p(s.p)
{
	//non dealloco l'oggetto di chiamata, non esiste nemmeno
	if(p)
		p->riferimenti++;
}

contenitore::smartp::~smartp()
{
	if(p)
	{
		p->riferimenti--;
		if(p->riferimenti == 0)
			delete p;
	}
}
contenitore::smartp& contenitore::smartp::operator = (const smartp& s)
{
	if(this != &s)	//confronta gli indirizzi, se uguali so che sto puntando lo stesso oggetto
					//se uso *this != s confronto gli oggetti smartp, quindi gli indirizzi che puntano
	{
		ogg* t = p; //così incremento i riferimenti e evito che si cancelli adesso
		//NON POSSO ELIMINARE ORA P!
		p = s.p;
		//ORA ELIMINO P SE POSSIBILE
		if(p) p->riferimenti++; //nuovo riferimento, me lo segno
		if(t) //se t esiste
		{
			t->riferimenti--; //aggiusto i riferimenti
			if(t->riferimenti == 0)
				delete t; //si cancella a cascata -> elimina il nodo -> che elimina a sua volta smartp e va a loop
		}
	}
	return *this;
}


bool contenitore::smartp::operator == (const smartp& s) const
{
	return p == s.p;
}
bool contenitore::smartp::operator != (const smartp& s) const
{
	return p != s.p;
}
contenitore::ogg& contenitore::smartp::operator *() const
{
	return *p;
}
contenitore::ogg* contenitore::smartp::operator ->() const
{
	return p;
}
		
// -- OGG --
contenitore::ogg::ogg(): next(0), riferimenti(0) {}

contenitore::ogg::ogg(int v, smartp n): val(v), next(n), riferimenti(0) { }

void contenitore::ogg::operator delete(void* p) { }

// -- CONTENITORE --
contenitore::contenitore():primo(0) {}

contenitore::contenitore(const contenitore& c):primo(c.primo) { } //copio puntatori smartp, si arrangia con i riferiemnti

contenitore::~contenitore() { } //si arrangia con i puntatori smartp

void contenitore::AggiungiInt(int v)
{
	primo = new ogg(v,primo);
}

int contenitore::PrelevaInt()
{
	int r = primo->val; //primo ha l'override di ->, ritorna il puntatore, viene applicato ->val, in pratica primo.p->val;
	primo = primo->next; //si arrangia a deallocare se necessario
	return r;
}

int main()
{
	contenitore a;
	a.AggiungiInt(5);
	a.AggiungiInt(4);
	a.AggiungiInt(3);
	a.AggiungiInt(2);
	a.AggiungiInt(1);
	
	cout << "A = ";
	for(contenitore::iteratore i = a.begin(); i != a.end(); ++i)
		cout << *i << ' ';
	cout << '\n';
	
	contenitore b = a;
	b.AggiungiInt(0);
	b.AggiungiInt(-1);
	b.AggiungiInt(-2);
	contenitore c;
	c.AggiungiInt(10);
	c.AggiungiInt(9);
	c.PrelevaInt(); //scarta
	c = b;
	b.AggiungiInt(-3);
	b.AggiungiInt(-4);
	
	cout << "B = ";
	while(!b.Vuoto())
		cout << b.PrelevaInt() << ' ';
	cout << '\n';
	//PrelevaInt svuota b, quindi adesso sarà vuota
	b.AggiungiInt(12345);
	cout << "B = ";
	for(contenitore::iteratore i = b.begin(); i != b.end(); ++i)
		cout << *i << ' ';
	cout << '\n';
	
	cout << "C = ";
	while(!c.Vuoto())
		cout << c.PrelevaInt() << ' ';
	cout << '\n';
	
	cout << "fine";
	return 0;
}