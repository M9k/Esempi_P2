#include <iostream>
using std::cout;
using std::endl;


class B {
	public:
void m(int x) { cout<<"B::m(int)";}
void m(int x, int y) { cout<<"B::m(int,int)";}
};

class D: public B {
	public:
void m(int x) { cout<<"D::m(int)";}
void m() { cout<<"D::m()";}
using B::m; //anche dopo, non importa, gli override in D rimangono quelli
};

int main() {
D d; d.m(3,5);
d.m(5);
}