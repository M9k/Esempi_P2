#include <iostream>
using std::cout;

class B {
	public:
	virtual void f() {int i=0;}
	virtual void g() {int i=1;}
	virtual void h() {int i=2;}
	virtual void i() {int i=3;}
};
class D: public B {
	public:
	void f() {int i=4;}
	void g() {int i=5;}
	void h() {int i=6;}
	void i() {int i=7;}
};

int main()
{
	B* p = new D;
	int i;
	cout << "start\n";
	for(i=0; i<50; i++) p->f();
	cout << "end\n";
	return 0;
}