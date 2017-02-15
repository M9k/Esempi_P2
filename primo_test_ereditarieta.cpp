#include <iostream>
using std::cout;

class C
{
	public:
	int a;
	void fC() {a = 2;}
};

class D: public C
{
	public:
	double a;
	void fD() {a = 3.14; C::a=4;}
};

class E: public D
{
	public:
	char a;
	void fE() { a='x'; C::a=5; D::a=6.28;}
};

int main()
{
	C c; D d; E e;
	c.fC(); d.fD(); e.fE();
	D* pd = &d; E& pe = e;
	
	cout << pd->a << ' ' << pe.a << '\n';
	cout << pd->a << ' ' << pd->D::a << ' ' << pd->C::a << '\n';
	cout << d.a << ' ' << d.D::a << ' ' << d.C::a << '\n';
	cout << pe.a << ' ' << pe.D::a << ' ' << pe.C::a << '\n';
	cout << e.a << ' ' << e.D::a << ' ' << e.C::a << '\n';
	
	return 0;
}