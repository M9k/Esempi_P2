#include <iostream>
using std::cout;

template <class T>
class Array
{
private:
	unsigned int elementi;
	unsigned int dimensione;
	T* lista;

public:	
	void pushBack(const T& t)
	{
		if(elementi < dimensione)
		{
			*(lista+elementi) = t;
			elementi++;
		}
		else
		{
			T* clone = new T[dimensione*2];
			for(int i=0; i<dimensione;i++)
				*(clone+i) = *(lista+i);
			dimensione *= 2;
			*(clone+elementi) = t;
			elementi++;
			delete[] lista;
			lista = clone;
		}
	}
	T popBack()
	{
		//non richiede di ridimensionare
		if(elementi)
		{
			T rit = *(lista+(elementi-1));
			elementi--;
			return rit;
		}
		else
			; //eccezione - TODO
	}
	
	Array(int k=0, const T& t = T()) : dimensione(1), elementi(0), lista(new T[dimensione])
	{
		for(int i=0;i<k;i++)
			pushBack(t);
	}
	
	const T& operator = (const Array<T>& a)
	{
		if(a != this)
		{	
			if(elementi != 0)
				delete[] lista;
			for(int i=0; i<a.elementi; i++)
				pushBack(*(a.lista+i));
			
			elementi = a.elementi;
			dimensione = a.dimensione;
		}
		return *this;
	}
	
	Array(const Array& a) : elementi(0), dimensione(a.dimensione), lista(new T[dimensione])
	{
		for(int i=0; i<a.elementi; i++)
		{
			pushBack(*(a.lista+i));
		}
	}
	
	~Array()
	{
		delete[] lista;
	}
	
	bool operator == (const Array& a)
	{
		if(elementi != a.elementi)
			return false;
		bool uguali = true;
		for(int i=0; i<elementi && uguali; i++)
			if(*(lista+i) != *(a.lista+i))
				uguali = false;
		return uguali;
	}
	bool operator != (const Array& a)
	{
		return !operator==(a);
	}
	
	friend std::ostream& operator << (std::ostream& os, const Array &a)
	{
		os << "Lista: ";
		for(int i=0; i< a.elementi; i++)
			os << *(a.lista+i) << ' ';
		os << '\n';
		return os;
	}
};

int main()
{
	Array<int> a(5,7), b(a);
	if(a == b)
		cout <<"uguali\n";
	else
		cout <<"diversi\n";
	b.pushBack(6);
	b.pushBack(7);
	if(a == b)
		cout <<"uguali\n";
	else
		cout <<"diversi\n";
	b.popBack();
	b.popBack();
	if(a == b)
		cout <<"uguali\n";
	else
		cout <<"diversi\n";
	b.pushBack(8);
	b.pushBack(9);
	cout << b;
	b.pushBack(10);
	b.pushBack(11);
	cout << b;
	cout << a;
	int x = b.popBack();
	cout << x  << '\n';
	x = b.popBack();
	cout << x  << '\n';
	x = b.popBack();
	cout << x  << '\n';
	x = b.popBack();
	cout << x  << '\n';
	x = a.popBack();
	cout << x  << '\n';
	x = a.popBack();
	cout << x  << '\n';
	x = a.popBack();
	cout << x  << '\n';
	x = a.popBack();
	cout << x  << '\n';
	
	return 0;
}