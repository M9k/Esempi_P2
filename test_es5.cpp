#include <iostream>
using std::cout;

class X
{
	public:
	int a;
	X(int x=0) : a(x)
	{
		cout << "creato un X\n";
	}
	operator int()
	{
		return a;
	}
	X& operator = (const X& x)
	{
		a = x.a;
		cout << "assegnato un X\n";
	}
};

class A{
	public:
	A(int x=0):a(x) {};
	virtual ~A(){};
	X a;
};

class B : public virtual A{
	public:
	virtual ~B() = 0;
};
B::~B() {}

class C : public B { };

class D : public virtual A{
	public:
	virtual ~D() = 0;
};
D::~D() {}

class E: public C, public D
{
	public:
	E(int x): A(x) {};
	E& operator = (const E& e)
	{
		if(this != &e)
		{
			A::operator = (e);
			C::operator = (e);
			D::operator = (e);
			//nessun campo extra
		}
		return *this;
	}
};

int main()
{
	E e1(5);
	E e2(10);
	cout << e1.a << ' ' << &e1.a <<'\n';
	cout << e2.a << ' ' << &e2.a <<'\n';
	cout << "assegno\n";
	e2 = e1;
	cout << e1.a << ' ' << &e1.a <<'\n';
	cout << e2.a << ' ' << &e2.a <<'\n';
}