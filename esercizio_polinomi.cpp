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
*/
#include <iostream>

using std::cout;
using std::ostream;

//esponente -1 -> 0
class polinomio
{
	private:
	class monomio;
	class smartp
	{
		public:
		monomio* punt;
		smartp(monomio* n = 0); //convertitore
		//regola del 3
		smartp(const smartp&);
		~smartp();
		smartp& operator = (const smartp&);
		monomio* operator -> () const;
		monomio& operator *();
		bool operator == (const smartp&) const;
		bool operator != (const smartp&) const;
	};
	class monomio
	{
		public:
		int coefficente, esponente, riferimenti;
		smartp next;
		monomio();
		monomio(const int& c, const int& e, const smartp& n=0);
	};
	smartp first;
	
	public:
	polinomio();
	polinomio(const int& c, const int& e=0);
	int espmax() const;
	int coeff(int esp) const;
	friend polinomio operator + (const polinomio& p1, const polinomio& p2);
	friend ostream& operator << (ostream& o, const polinomio& p);
};
// -- MONOMIO --
polinomio::monomio::monomio(): coefficente(0), esponente(-1), riferimenti(0), next(0) {}
polinomio::monomio::monomio(const int& c, const int& e, const smartp& n): coefficente(c), esponente(e), riferimenti(0), next(n) {if (esponente< -1) {esponente = -1; coefficente=0;} }

// -- SMARTP --
polinomio::smartp::smartp(monomio* n):punt(n)
{
	if(n)
		n->riferimenti++;
}
polinomio::smartp::smartp(const smartp& s) : punt(s.punt)
{
	if(punt)
		punt->riferimenti++;
}
polinomio::smartp::~smartp()
{
	if(punt)
	{
		punt->riferimenti--;
		if(punt->riferimenti == 0)
			delete punt; //punt � un monimio, far� un delete next che � un smartp, agir� in cascata
	}
}
polinomio::smartp& polinomio::smartp::operator = (const smartp& s)
{
	if(this != &s)
	{
		monomio* t = punt;
		punt = s.punt;
		if(t)
		{
			t->riferimenti--;
			if(t->riferimenti == 0)
				delete t;
		}
	}
	return *this;
}
polinomio::monomio* polinomio::smartp::operator -> () const
{
	return punt;
}
polinomio::monomio& polinomio::smartp::operator *()
{
	return *punt;
}
bool polinomio::smartp::operator == (const smartp& s) const
{
	return punt == s.punt;
}
bool polinomio::smartp::operator != (const smartp& s) const
{
	return punt != s.punt;
}
		
// -- POLINOMIO --
polinomio::polinomio():first() {};
polinomio::polinomio(const int& c, const int& e):first(new monomio(c, e)) {};

int polinomio::espmax() const
{
	int emax = -1;
	smartp t = first;
	while(t != 0)
	{
		if(t->esponente > emax)
			emax = t->esponente;
		t = t->next;
	}
	//distruzione automatica di t
	return emax;
}
int polinomio::coeff(int esp) const
{
	smartp t = first;
	while(t != 0)
	{
		if(t->esponente == esp)
			return t->coefficente;
		t = t->next;
	}
	return 0;
}

polinomio operator + (const polinomio& p1, const polinomio& p2)
{
	int max = p1.espmax();
	if(max < p2.espmax())
		max = p2.espmax();
	polinomio rit;
	int i;
	for(i=0; i<=max; i++)
		if(p1.coeff(i)!=0 || p2.coeff(i)!=0)
			rit.first = new polinomio::monomio(p1.coeff(i) + p2.coeff(i),i,rit.first);
	return rit;
}
	
ostream& operator << (ostream& o, const polinomio& p)
{	
	int i=p.espmax();
	if(i == -1)
		return o << 0;
	for(; i>-1; i--)
		if(p.coeff(i) != 0)
			if(i != 1)
				if(i != 1)
					o << p.coeff(i) << 'x' << '^' << i;
				else
					o << p.coeff(i) << 'x';
			else
				if(i != 1)
					o << 'x' << '^' << i;
				else
					o << 'x';
	return o;
}

int main()
{
	polinomio x(1,1);
	cout << "x = " << x << '\n'; //stampa x = x
	polinomio z(3,4);
	cout << "z = " << z << '\n'; //stampa z = 3x^4
	polinomio t(x+z);
	cout << "t = " << t << '\n';
	/*
	polinomio q = 3*x+2*x*x-x*x*x+7/(x^4);
	cout << "q = " << q << '\n'; //7x^4-x^3-2x^2+3x
	cout << q/t << " " << q%t;
	if(q == p(3))
		cout "q uguale p(3)\n";
	else
		cout "q diverso p(3)\n";
		
	
	*/
	
	
	return 0;
}