#include <iostream>
using namespace std;

class C {
	public:
	C(int n=1) : number(n) { cout << "C(" << number << ") "; }
	~C() { cout << "~C(" << number << ") "; }
	C& operator=(const C& c) { number=c.number; cout << "operator=(" << number << ") "; }
	int number;
};

int F(C c) {return c.number;}

int main() {
	C* c=new C; cout << "UNO" << endl;
	C d; d= *c; cout << "DUE" << endl;
	int x=F(d); cout << "TRE" << endl; //1
	int y=F(F(d)); cout << "QUATTRO" << endl;
	return 0;
}

// C(1) UNO
// C(1) operator=(1) DUE 
// ~C(1) TRE
// C(1) ~C(1) ~C(1) ~C(1) QUATTRO
// ~C(1)