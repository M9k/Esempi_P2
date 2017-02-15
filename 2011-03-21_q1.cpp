#include <iostream>
using std::cout;
using std::endl;

class A {
public:
	virtual void f(int x=0) { cout << "A::f(" << x << ")" << endl;}
};

class B : public A {
public:
	virtual void f(int x=1) { cout << "B::f(" << x << ")" << endl;}
};

int main() {
	A* p=new A;
	p->f(); //A::f(0)
	p=new B;
	p->f(); //B::f(0)
	B* q=new B;
	q->f(); //B::f(1)
	return 0;
}