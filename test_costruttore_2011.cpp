#include <iostream>
using std::cout;

class A {
	protected:
	int x;
	public:
	A(int k=0) : x(k) {cout << "A(int) ";}
	~A() { cout << "~A ";}
	operator double() const { cout << "operator double() "; return x;}
};

class B : public A
{
	public:
	static A a;		//uno per tutti
	const A &a2;	//alias
	A F(A a=A()) {return a;}
	B(int k=3, const A &a3=0) : A(k), a2(a3) {cout << "B() ";}
	~B() {cout << "~B() ";}
	B(const B &b) : a2(b) { cout << a2 << " ";} // + A()
};

int main()
{
	A a(1); cout << "UNO\n"; //A(int)
	B b; cout << "DUE\n"; //A(int) A(int) B() ~A
	B b2(a); cout << "TRE\n"; //operator double() A(int) A(int) B() ~A
	B b3(a,a); cout << "QUATTRO\n"; //operator double() A(int) B()
	B b4 = b3; cout << "CINQUE\n"; //A(int) operator double() 1
	b.F(); cout << "SEI\n"; //A(int) ~A ~A ~A  ->> A(), assegnazione e copia, ne alloca e distrugge 3
	b.F(2); cout << "SETTE\n"; //A(int) ~A ~A ~A ->> il primo costruito dal main e passato a F
	
	return 0;
}