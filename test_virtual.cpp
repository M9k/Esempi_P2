#include <iostream>
using std::cout;

class B {
	public:
	virtual ~B() = 0; //fake, indico che B è astratta
	//virtual per non creare memory leak con D
};
B::~B() {} //uso distruttore standard
class D: public B {};

class A
{
	//si suppone che i metodi senza signatura const fanno side effect (anche se non è vero)
	public:
	virtual int F() const
	{
		cout << "A\n";
	}
	virtual B* F(int x) const
	{
		cout << "A con intero\n";
		return new D;
	}
	virtual void G()
	{
		cout << "G\n";
	}
	virtual void S(int x=0)
	{
		cout << "X uguale a " << x << '\n';
	}
	virtual ~A() {} //distruttore virtuale, per non avere memory leak
};

class C: public A
{
	public:
	virtual int F()		//senza const, signatura diversa, non polimorfico con A
	{
		cout << "C\n";
	}
	/*virtual*/ D* F(int x) const		//covariante
	{
		cout << "C con intero\n";
		return new D;
	}
	/*virtual*/ void S(int x) //se mettevo un valore di default a x veniva ignorato, perchè segue la signatura di S presente in A
	{
		cout << "X in C uguale a " << x << '\n';
	}
};

int main()
{
	A *p;
	p = new A();
	p->F();
	p->F(5);
	delete p;
	p = new C();
	p->F();	//chiama sempre A::F(), perchè C lo eredita e ne dichiara un secondo con signatura diversa
	p->F(5);
	(*p).F(5);	//va anche così
	A aogg = *p;
	aogg.F(5); //così ovviamente no, non late binding
	
	const C x;
	//x.F(); //errore, vuole un F() const, lo erediterebbe da A, ma poi c'è l'overloading e viene sovrascritto
	const A* px  = &x;
	px->F(); //così riesco a chiamare A::F()
	
	//eredita il metodo virtuale
	A* p2 = new C();
	p2->G();
	
	//anche con alias oltre che puntatori
	C cx;
	A& a3 = cx;
	a3.F(123);
	
	//D* dp = a3.F(123);	//impossibile! il tipo di ritorno statico è un B*, il tipo dinamico sarà D*
	B* bp = a3.F(123);
	
	A* p5 = new A;
	p5->S();
	p5->S(321);
	delete p5;
	p5 = new C;
	p5->S();
	p5->S(321);
	B* pb = new D;
	//B* pb2 = new B; //non possibile, B astratta
	
	return 0;
}