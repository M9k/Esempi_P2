#include <iostream>
#include <exception>
#include <typeinfo>
using namespace std;

// ES 1
/*
void fun(const wxWindows& w)
{
	if(wxPasswordEntryDialog* ped = dynamic_cast<wxPasswordEntryDialog*>(&w))
		ped->SetValue("password");
	if(xwFileDialog* fd = dynamic_cast<wxFileDialog*>(&w))
		fd->SetFilename("Default File");
	if(w.IsShown())
		w.setSize(100,50);
}
*/

/*  ES 2 - PARTE COMUNE   */
// class B {
// protected:
// int i;
// public:
// B(int x = 5): i(x) {}
// int f() const {return i;}
// int f(double x) {return i - static_cast<int>(x);}
// virtual int m(int x) const {return i+x;}
// };

//A
// class D: public B {
// private: 
// int k;
// public:
// D(int x = 3): B(x), k(x) {}
// int m(B b) {return k + b.i;} //non compila, b privato
// };
// int main()
// {
// D d; B b; cout << d.m(b);
// return 0;
// }

// B
// class D: public B {
// private: int k;
// public:
// D(int x = 3): B(x), k(x) {}
// int m(D d) { B::m(4); return k+d.i;}
// };
// int main()
// {
// D d1, d2; cout << d1.m(d2); //stampa 6
// return 0;
// }

// C
// class D: public B {
// private: int k;
// public:
// D(int x = 3): B(x), k(x) {}
// int m(int x) const {return m(x);} //LOOP
// };
// int main()
// {
// D d; B* p=&d; cout<< p->m(6);
// return 0;
// }

// D
// class D: public B {
// private: int k;
// public:
// D(int x = 3): B(x), k(x) {}
// int f(int x) {return x + i;}
// };
// int main()
// {
// D d; B* p=&d; cout << p->f(2); //1
// return 0;
// }

// E
// class D: public B {
// private: int k;
// public:
// D(int x = 3): B(x), k(x) {}
// double f(int x) {f(); return k+x;}
// };
// int main()
// {
// D d; cout << d.f(); //non compila
// return 0;
// }

// F
// class D: public B {
// private: int k;
// public:
// D(int x = 3): B(x), k(x) {}
// int f(int x) {return B::f();}
// };
// int main()
// {
// D d; B* p=&d; cout << p->f(5.4); //-2
// return 0;
// }

// G
// class D: public B {
// private: int k;
// public:
// D(int x = 3): B(x), k(x) {}
// int f() {B b(4); return m(b.i);}
// };
// int main()
// {
// D d; cout << d.f(); //non compila
// return 0;
// }

// H
// class D: public B {
// private: int k;
// public:
// D(int x = 3): B(x), k(x) {}
// double f(int x) {D d(4); return m(d.i);}
// };
// int main()
// {
// D d; cout << d.f(2); //7
// return 0;
// }

// I
// class D: public B {
// private: int k;
// public:
// D(int x = 3): B(x), k(x) {}
// int m(int x) const {const B* p =static_cast<const B*>(this); return p->m(x);}
// };
// int main()
// {
// D d; B* p=&d; cout << p->m(8); //errore run time
// return 0;
// }

// L
// class D: public B {
// private: int k;
// public:
// D(int x = 3): B(x), k(x) {}
// int m(int x) const {return f(x);} //f(x) usa un this const, ma f(x) non è const
// };
// int main()
// {
// D d; B* p=&d; cout << p->m(5); //errore in compilazione
// return 0;
// }



/*       ES 3      */
// class Z {
// public:
// Z(int i=0) {}
// int operator ++() {return 1;}
// int operator ++(int) {return 1;}
// operator int() {return 0;}
// };
// template <class T1, class T2=Z>
// class C {
// public:
// T1 x; //Z o int
// T2* p;
// };
// template<class T1,class T2>
// void fun(C<T1,T2>* q)
// {
// ++(q->p); //sempre ok, puntatore
// if(true == false) //niente -O, devo eseguire
// cout << ++(q->x); 
// else
// cout << q->p;
// (q->x)++;
// if(*(q->p) == q->x) //puntatore con ritorno -> ritorno int
// *(q->p) = q->x;
// T1* ptr = &(q->x);
// T2 t2 = q->x;
// }
// main(){
// C<Z> c1;
// fun(&c1);
// C<int> c2;
// fun(&c2);
// }




/*       ES 4      */
class A { public: virtual ~A(){} };
class B: public A {};
class C: public A {};
class D: virtual public B {};
class E: virtual public B {};
class F: public D, public E {};
void f(A* p) throw(E*) {
	if(!dynamic_cast<D* >(p)) throw new E();
}
char fun(A* p, B& r) {
	if(typeid(*p)==typeid(r)) return '1';
	try{
		f(&r);
	}
	catch(B*) {return '2';}
	//il primo a,c,d,f, il secondo b,d,e,f, diversi
	E* punt = dynamic_cast<F*>(&r);
	try{
		B& ref = dynamic_cast<B&>(*p);
	}
	catch(bad_cast) {
		if(!punt)
			return '3';
		return '4';
	}
	//il primo d,f, il secondo b,d,e,f
	if(punt)
		return '5';
	return '6';
}

int main()
{
	A a; B b; C c; D d; E e; F f;
		//	1			2		     3			 4			 5			 6
	cout << fun(&b,b) <<fun(&e, b) <<fun(&a,d) <<fun(&a,f) <<fun(&d,f) <<fun(&b,d);
	return 0;
}