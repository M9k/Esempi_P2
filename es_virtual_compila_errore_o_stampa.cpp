#include <iostream>
using std::cout;

class A {
	private:
	void h() { cout << " A::h ";}
	public:
	virtual void g() {cout << " A::g ";}
	virtual void f() {cout << " A::f "; g(); h();}
	void m() {cout << " A::m "; g(); h();}
	virtual void k() {cout << " A::k "; g(); h(); m();}
	virtual ~A() {}
	A* n() {cout << " A::n "; return this;}
};

class B: public A {
	private:
	void h() { cout << " B::h ";}
	public:
	virtual void g() {cout << " B::g ";}
	void m() {cout << " B::m "; g(); h();}
	/*virtual*/ void k() {cout << " B::k "; g(); h(); m();}
	//eredita da A:
	//virtual void f() {cout << " A::f "; g(); h();}
	B* n() {cout << " B::n "; return this;}
};

int main()
{
	B* b = new B();
	A* a = new B();
	
	b->f(); //f polimorfico, A::f, this->g() con late binding, B::g, h() non late binding, A::h
	cout << '\n';
	b->m();	//m non polimorfico, B::m, g polimorfico B::g, h non polimorfico, B::h
	cout << '\n';
	b->k(); //B::k, B::g, B::h, B::m, B::g, B::h
	cout << '\n';
	a->f(); //A::f, B::g, A::h
	cout << '\n';
	a->m(); //A::m, B::g, A::h
	cout << '\n';
	a->k(); //B::k, B::g, B::h, B::m, B::g, B::h
	cout << '\n';
	(b->n())->g(); //B::n, B::g
	cout << '\n';
	(b->n())->n()->g(); //B::n, B::n, B::g
	cout << '\n';
	(a->n())->g(); //A::n, B::g
	cout << '\n';
	(a->n())->m(); //A::n, A::m, B::g, A::h
	cout << '\n';
	return 0;
}

