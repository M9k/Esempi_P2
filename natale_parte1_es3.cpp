#include <iostream>
#include <typeinfo>
using std::cout;

/*
        _
_    /- B <-\
A <--        --- D <-- E <-- F         
     \- C <-/
  
  //ASCII ART TIME!
*/
class A
{
public:
	virtual void m() =0;
};
class B: virtual public A {};
class C: virtual public A
{
public:
	virtual void m() {}
};
class D: public B, public C
{
public:
	virtual void m() {}
};
class E: public D {};
class F: public E {};

char G(A * p, B& r){
	C * pc = dynamic_cast<E*>(&r);
	if(pc && typeid(*p)==typeid(r))
		return 'G';
	if(!dynamic_cast<E*>(&r) && dynamic_cast<D*>(p))
		return 'Z';
	if(!dynamic_cast<F*>(pc))
		return 'A';
	else
		if(typeid(*p)==typeid(E))
			return 'S';
	return 'E';
}

int main()
{
	cout
	//       p         r
	<< G(new E(), *new F())  //S - *p di tipo E, &r non deve essere E, non deve castare ad E, deve castare a F
	<< G(new C(), *new E())  //A - &r deve castare a E ma non ad F quindi E, *p non deve essere E , A e B astratte, basta sia C, D o F
	<< G(new E(), *new E())  //G r casta a E, r = E o F, p uguale, E o F
	<< G(new F(), *new F())  //G 
	<< G(new C(), *new F())  //E - p,r diversi, r deve essere F o stampa A, p diverso da F, D e F, rimane C
	<< G(new E(), *new D())  //Z r non casta ad E e p casta a D
	<< G(new F(), *new D())  //Z
	<< G(new D(), *new E())  //A 
	<< G(new F(), *new E()); //A - altra combinazione per A
	return 0;
}