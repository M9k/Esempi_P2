#include <iostream>
using std::cout;

class X
{
	public:
	int a; //per il test
	X(int x=0) : a(x) { cout << "creato un X\n";}
	X& operator = (const X& x)
	{
		a = x.a;
		cout << "assegnato un X\n";
		return *this;
	}
	X(const X& x) : a(x.a){cout << "costruttore di copia di X\n";}
};

class B : virtual public X{};

class D : virtual public X{};

class E: public B, public D
{
	public:
	E(int x): X(x) {};
	E& operator = (const E& e)
	{
		X::operator = (e);
		B::operator = (e);
		D::operator = (e);
		//nessun campo extra
		return *this;
	}
};

int main()
{
	E e1(5);
	E e2(10);
	e2 = e1;
	cout << e1.a << ' ' << &e1.a <<'\n';
	cout << e2.a << ' ' << &e2.a <<'\n';
}