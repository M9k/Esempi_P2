#include <iostream>
using std::cout;

class A {
public:
	virtual void m() {cout << " A::m() ";}
	virtual void m(int x) {cout << " A::m(int) ";}
};
class B: public A {
public:
	virtual void m(bool b) {m(3); cout << " B::m(bool) ";}
	void m(int x) {cout << " B::m(int) ";}
};
class C: public A {
public:
	virtual void m(bool b) {cout << " C::m(bool) ";}
};
class D: public B {
public:
	void m() {B::m(false); cout << " D::m() ";}
	void m(int x) {cout << " D::m(int) ";}
};
class E: public D {
public:
	void m(int x) {cout << " E::m(int) ";}
};
int main()
{
	A a; B b; C c; D d; E e;
	// B * pb=&c; pb->m(3); //errore in compilazione
	B * pb1=&e; pb1->m(true); // E::m(int) B::m(bool)
	cout << '\n';
	B * pb2=&e; pb2->m(3); //E::m(int)
	cout << '\n';
	A * pa1=&e; pa1->m(); // E::m(int) B::m(bool) D::m()
	cout << '\n';
	A * pa2=&d; pa2->m(); //D::m(int) B::m(bool) D::m()
	cout << '\n';
	D * pd0=&e; pd0->m(true); //comversione implicita da bool a int -> E::m(int)
	cout << '\n';
	B * pb3=&e; //si
	D * pd1=dynamic_cast<D*>(pb3); pd1->m(true); //E::m(int)
	cout << '\n';
	A * pa3=&b; pa3->m(false); //B::m(int)
	cout << '\n';
	D * pd2=&e; pd2->m(4); //E::m(int)
	cout << '\n';
	B * pb4=&d; pb4->m(true); //D::m(int) B::m(bool)
	cout << '\n';
	B * pb5=&d; pb5->m(5); //D::m(int)
	
	return 0;
}