#include <iostream>
using std::cout;
using std::endl;

/* class A {
public:
virtual void f(int x=0) { cout << "A::f(" << x << ")\n";}
};

class B : public A {
public:
virtual void f(int x=1) { cout << "B::f(" << x << ")\n";}
};
int main() {
	A* p=new A;
	p->f();
	p=new B;
	p->f();
	B* q=new B;
	q->f();
	return 0;
} */

// parte 2

class A {
	public:
	A() { cout << "A ";}
	A(const A&) {cout << "Ac ";}
	virtual ~A() {cout << "~A ";}
};

class B : virtual public A {
	public:
	B() { cout << "B "; }
	~B() { cout << "~B "; }
};

class C : virtual public A {
	public:
	static A x;
	C() { cout << "C "; }
	C(const C&) {cout << "Cc ";}
};

A C::x; //costruttore standard di A -> A()

class D : public B, public C {
	public:
	D() { cout << "D "; }
	D& operator=(const D& d) {cout << "D= "; return *this;}
	~D() {cout << "~D "; }
};

int main() {
	//costruisco C::x
	cout << "START" << endl; //A 
	// costruisco D: A B C D
	D* b=new D(); cout << "UNO" << endl; //A B C D
	// costruisco due d, A B C D A B C D
	D d,e; cout << "DUE" << endl;
	//assegnazione D ridefinita, non fa niente -> D=
	e = d;cout << "TRE" << endl;
	//SE ASSEGNAZIONE STANDARD:
	//assegnazione di A, assegnazione di B, assegnazione di C, assegnazione dei campi di D
	
	//copia A, Ac, copia B, niente, copia C, Cc, copia i campi di D, nessuno -> Ac Cc
	D f(e);
	
	return 0;
}










