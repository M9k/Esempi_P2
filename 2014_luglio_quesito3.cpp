#include <iostream>

class Empty {};

template <class T = double>
class Coda
{
private:
	class nodo
	{
	public:
		T t;
		nodo* prec;
		nodo(const T& oggetto, nodo* precNodo = 0) : t(oggetto), prec(precNodo) {}
	};
	
	nodo* testa = 0;	// testa è dove inserisco/prelievo, ho usato una concezzione contraria a quella del professore
						// inserisco/prelievo ----> <----- |testa| | | | | | | | |coda| (il fondo)

	void insert_coda(const T& t)
	{
		nodo* ultimo = testa;
		while(ultimo)
			ultimo = ultimo->prec;
		ultimo = new nodo(t);
	}
	
public:
	void insert(const T& t)
	{
		testa = new nodo(t, testa);
	}
	T removeNext()
	{
		if(!testa)
			throw Empty();
		T bkt = testa->t;
		nodo* bk = testa->prec;
		delete testa;
		testa =bk;
		return bkt;
	}
	T* getNext()
	{
		if(!testa)
			return nullptr;
		return &(testa->t);
	}
	void svuota()
	{
		nodo* testa;
		while(testa!=0)
		{
			nodo* bk = testa;
			testa = testa->prec;
			delete bk;
		}
	}
	Coda() {} //testa già a zero per dafault, C++11
	Coda(int k, const T& t)
	{
		if(k>=0)
			for(int i=0;i<k; i++)
				insert(t);
	}
	Coda(const Coda& c)
	{
		nodo* i = c.testa;
		while(i!=0)
		{
			insert_coda((i)->t);
			i = i->prec;
		}
	}
	
	~Coda()
	{
		svuota();
	}
	
	Coda& operator = (const Coda& c)
	{
		if(this != &c)
		{
			svuota();
			nodo* i = c.testa;
			while(i!=0)
			{
				insert_coda((i)->t);
				i = i->prec;
			}
		}
		return *this;
	}
	bool operator != (const Coda& c) const
	{
		bool uguali = true;
		nodo* i=testa, j=c.testa;
		while(uguali && i && j)
		{
			if(i->t != j->t)
				uguali = false;
			i = i->prec;
			j = j->prec;
		}
		if(i || j)
			return false;
		return uguali;
	}
	
	Coda& operator + (const Coda& c)
	{
		nodo* ultimo = testa;
		while(ultimo->prec)
			ultimo = ultimo->prec;
		nodo* i = c.testa;
		while(i)
		{
			ultimo->prec = new nodo(i->t);
			ultimo = ultimo->prec;
			i = i->prec;
		}
		return *this;
	}
	
	class const_iterator
	{
		private:
			nodo* p;
		public:
			const_iterator(nodo* n=0) : p(n) {}
			const T operator *() const {return p->t;}
			const_iterator operator ++(int) {const_iterator bk = p; p=p->prec;return bk;}
			const_iterator& operator ++() {p=p->prec; return *this;}
			bool operator == (const const_iterator& c) const { return p == c.p;}
			bool operator != (const const_iterator& c) const { return !operator==(c);}
	};
	const_iterator End() const {return 0;}
	const_iterator Begin() const {return testa;}
};

int main()
{
	Coda<> a;
	Coda<char> b(10, 'b');
	Coda<char> c(3, 'c');
	c.insert('b');
	c.insert('a');
	Coda<char>::const_iterator i = b.Begin();
	while(i != b.End())
	{
		std::cout << *i << ' ';
		i++;
	}
	std::cout << '\n';
	b = b + c;
	i = b.Begin();
	while(i != b.End())
	{
		std::cout << *i << ' ';
		i++;
	}
	
	std::cout << "fine\n";
	return 0;
}