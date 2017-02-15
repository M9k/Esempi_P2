#include<stdlib.h>
#include<iostream>
#include<string>

using namespace std;

class prova
{
	private:
		static const double x = 10;
		int a, b;
		static int cont;

	public:
		prova();
		prova(const int&);
		prova(const int&, const int&);
		int getsomma() const;
};

prova::prova(): a(0), b(0) {};

//prova::prova(const double& v1): x(v1) {};

prova::prova(const int& v1): a(v1) {};

//LI CHIAMA SEMPRE IN BASE ALL'ORDINE NELLA CLASSE, SE VUOTO CHIAMA QUELLO DI DEFAULT
prova::prova(const int& v1, const int& v2): a(v1), b(v2) {};
//costruisce x, a, b e cont, per x e cont usa costrtuttore di default

//COSTANTI NON STATICHE - DEVONO essere presenti in ogni costruttore, visto che non hanno il costruttore di default e non possono essere vuote
//AKA le dichiaro sempre in quello di default e apposto

int prova::getsomma() const
{
	return a + b;
}

using namespace std;

int main()
{
	prova ciao;
	prova a(6), b(8,9);
	cout << a.getsomma() << " " << b.getsomma();
	
	return 0;
}