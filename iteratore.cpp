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
	Esempio di iteratore
*/

#include <iostream>

using std::cout;
using std::flush;

// -- CONTENITORE --
class contenitore
{
	friend class iteratore;
	public:
		class iteratore;
		contenitore();
		contenitore(const contenitore&);
		~contenitore();
		bool operator == (const contenitore&);
		contenitore& operator = (const contenitore&);
		//non sovrascrivo il contenitore, sarà nodo a "cancellarsi" ricorsivamente da solo
		void aggiungi(int); //non costante perchè se primo è 0 verrà modificato
		int somma() const;
		iteratore begin() const;
		iteratore end() const;
		
	private:
		class nodo;
		nodo* primo;
		static nodo* copia(const nodo*);
};

// -- NODO --
class contenitore::nodo
{
	friend class contenitore;
	public:
		nodo(int, nodo*);
		~nodo();
	private:
		int info;
		nodo* next;
};

// -- ITERATORE --
class contenitore::iteratore
{
	public:
		iteratore(nodo* n=0);
		bool operator == (const iteratore&) const;
		bool operator != (const iteratore&) const;
		iteratore& operator ++();
		iteratore operator ++(int);
		nodo& operator *() const;
	private:
		nodo* p;
};

// -- ITERATORE --
contenitore::iteratore::iteratore(nodo* n):p(n){;}

bool contenitore::iteratore::operator == (const iteratore& i) const
{
	return (p == i.p);
}

bool contenitore::iteratore::operator != (const iteratore& i) const
{
	return (p != i.p);
}

contenitore::iteratore& contenitore::iteratore::operator ++()
{
	if(p)
		p = p->next;
	return *this;
}

contenitore::iteratore contenitore::iteratore::operator ++(int)
{
	iteratore rit = *this;
	if(p)
		p = p->next;
	return rit;
}

contenitore::nodo& contenitore::iteratore::operator *() const
{
	return *p;
}

// -- NODO --
contenitore::nodo::nodo(int i, nodo* n = 0): info(i), next(n) {;}

contenitore::nodo::~nodo()
{
	if(next)
		delete next;
	cout << "sto per distruggere il nodo con valore " << info << '\n';
}

contenitore::nodo* contenitore::copia(const nodo* n)
{
	if(n)
		return new contenitore::nodo(n->info, copia(n->next));
	else
		return 0;
}

// -- CONTENITORE -- 
contenitore::contenitore():primo(0){;}

contenitore::contenitore(const contenitore& c):primo(copia(c.primo)) {;}

contenitore::~contenitore()
{
	if(primo)
		delete primo;
	cout << "sto per distruggere il contenitore\n";
}

bool contenitore::operator == (const contenitore& c)
{
	return (primo == c.primo);
}

contenitore& contenitore::operator = (const contenitore& c)
{
	if(*this == c) return *this;
	delete this;
	*this = c;
	return *this;
}

void contenitore::aggiungi(int i)
{
	if(!primo)
	{
		primo = new nodo(i);
		return;
	}
	nodo* p = primo;
	while(p->next)
		p = p->next;
	p->next = new nodo(i);
}

int contenitore::somma() const
{
	int somma = 0;
	for(iteratore i = begin(); i!=end();i++)
		somma += (*i).info; //nodo amico di contenitore
	return somma;
}
contenitore::iteratore contenitore::end() const
{
	return iteratore();
}
contenitore::iteratore contenitore::begin() const
{
	return iteratore(primo);
}


int main()
{
	contenitore c;
	c.aggiungi(1);
	c.aggiungi(2);
	c.aggiungi(3);
	c.aggiungi(4);
	c.aggiungi(5);
	cout << c.somma() << '\n';
	cout << "fine\n";
	
	contenitore c2;
	c2.aggiungi(17);
	c2.aggiungi(4);
	c2.aggiungi(1996);
	
	cout << "fine parte 2\n";
	
	contenitore* c3 = new contenitore();
	c3->aggiungi(1234);
	c3->aggiungi(2341);
	c3->aggiungi(3412);
	c3->aggiungi(4123);
	delete c3;
	
	cout << "Ciao ciao\n";
	return 0;
}