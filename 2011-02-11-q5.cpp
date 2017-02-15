#include <iostream>
using namespace std;

class C {
public:
	C(int x=0,int y=1) {a[0]=x; a[1]=y; cout << "C(" << a[0] << "," << a[1] << ") ";}
	C(const C&) {cout << "Cc ";}
	int a[2];
};

class D {
public:
	D(): c2(&c1),cr(c1) { cout << "D() ";}
	D(const D& d) : cr(c1) { cout << "Dc ";}
	~D() { cout << "~D ";}
private:
	C c1;
	C* c2;
	C& cr;
};

class E {
public:
	static C cs;
};

C E::cs=1;

int main() {
	C c; cout << "UNO" << endl;
	C x(c); cout << x.a[0] << " " << x.a[1] << " DUE" << endl;
	D d=D(); cout << "TRE" << endl;
	E e;cout << "QUATTRO" << endl;
	return 0;
}
// C(1, 1) Cc C(0,1) UNO
// Cc VALCAS VALCAS DUE
// C(0,1) D() C(0,1) Dc ~D TRE
// QUATTRO
// ~D