#include <iostream>
using std::cout;

class B {
public:
	int x;
	B(int z=1): x(z) {}
};

class D: public B {
public:
	int y;
	D(int z=5): B(z-2), y(z) {}
};

void fun(B* a, int size) {
	for(int i=0; i<size; ++i) cout << (*(a+i)).x << " ";
}

int main() {
	fun(new D[4],4); cout << "**1\n"; //B 3 e D 5, 4 copie, stampa 3 5 3 5, incremento errato
	B* b = new D[4]; fun(b,4); cout << "**2\n"; //come sopra
	b[0] = D(6); b[1] = D(9); fun(b,4); cout << "**3\n"; //B 4 e D 6, B 7 e D 9, stampa 4 7 3 5, converte di tipo assegnando e ne assegna solo la prima parte della classe
	b = new B[4]; b[0] = D(6); b[1] = D(9); fun(b,4); cout << "**4\n"; // 1 1 1 1, poi 4 1 1 1 e 4 7 1 1
}