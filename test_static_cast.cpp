#include <iostream>
using std::cout;

class A {
public:
	int a = 1;
	void f() {cout << "1";} const
	virtual void fv() {cout << "1";}
};

class B {
public:
	int a = 5;
	void f() {cout << "5";} const
	virtual void fv() {cout << "5";}
};

class C: public A, public B
{
	void const fv() {cout << "7";}
};



int main()
{
	C c;
	C* pc = &c;
	B* pbc1 = static_cast<B*>(pc);
	B* pbc2 = pc;
	B* pbc3 = (B*)pc;
	B* pbc4 = reinterpret_cast<B*>(pc);
	cout << "inizio\n";
	cout << pc << ' ' << pbc1 << ' ' << pbc2 << ' ' << pbc3 <<  ' ' << pbc4 << '\n'; 
	cout << pbc1->a << ' ' << pbc2->a << ' ' << pbc3->a << ' ' << pbc4->a << '\n'; 
	cout << "fine\n";
	return 0;
}