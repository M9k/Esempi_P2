#include <iostream>
using std::cout;

class Z {
public: Z(int x) {}
};

class A {
public:
	void f(int){cout << "A::f(int) ";}
	virtual void f(bool){cout <<"A::f(bool) ";}
	virtual void f(Z){cout <<"A::f(Z) ";}
};

class B: virtual public A {
public:
	void f(const bool&){cout<< "B::f(const bool&) ";}
	void f(const int&){cout<< "B::f(const int&) ";}
};

class C: virtual public A {
public:
	virtual void f(Z){cout <<"C::f(Z) ";}
};

class D: public B, public C {
public:
	virtual void f(int*){cout<< "D::f(int * ) ";}
	void f(int&){cout <<"D::f(int&) ";}
};

class E: public D {
public:
	void f(Z){cout <<"E::f(Z) ";}
};

int main()
{
	B* pb=new B;
	C* pc=new C;
	D* pd=new D;
	E* pe=new E;
	A *pa1=pb, *pa2=pc, *pa3=pd, *pa4=pe;
	C* pc1=pe;

	(dynamic_cast<B*>(pa1))->f(1); //B::f(const int&)
	(dynamic_cast<B*>(pa1))->f(true); //B::f(const bool&) non prende il virtual di A perchè la signatura è diversa e la nuova funzione in B nasconde la virtuale
	pa1->f(true); //A::f(bool) 
	cout << '\n';
	pa2->f(1); //A::f(int) statico
	(dynamic_cast<C*>(pa2))->f(1); //C::f(Z) C eredita f(int) da A, ma viene nascosto da f(Z), Z ha un costruttore che fa da convertitore di tipo
	//(dynamic_cast<E*>(pa2))->f(1); //stamperebbe E::f(Z), ma il dynamic cast fallisce e si chiama una funzione su un oggetto nullo, quindi crasha
	cout << '\n';
	(dynamic_cast<C*>(pa3))->f(0); //C::f(Z) 
	(dynamic_cast<D*>(pa3))->f(0); //D::f(int * ), non a intero perchè non const
	pa4->f(1); //"A::f(int) statico
	cout << '\n';
	(dynamic_cast<C*>(pa4))->f(1); //E::f(Z)
	pc1->f(1); //E::f(Z) 
	(static_cast<E*>(pc1))->f(1); //E::f(Z)
	cout << '\n';
	(static_cast<A*>(pc1))->f(1); //A::f(int) 
	
	return 0;
}