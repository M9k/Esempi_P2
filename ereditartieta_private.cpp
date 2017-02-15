#include <iostream>
using std::cout;

class B
{
	private:
	int x;
	protected:
	int funzpro() { cout << "asd\n";} //<-----
	public:
	int a;
	void  funz1() const { cout << "C\n";}
};

class D: private B
{
	public:
	int x;
	void funz2(B b2, D d)
	{
		d.x = 123;
		x = 123;
		b2.a = 123;
		//funzpro la eredito in D, posso usarla all'interno di D
		funzpro();
		d.funzpro();
		//MA NON HO L'AMICIZIA CON B!!
		//b.funzpro();
	}
};

void funz3(B)
{
	cout << "funz3\n";
}

int main()
{
	B b;
	b.a = 34;
	funz3(b);
	D d;
	//d.a = 234;	// ereditato da B, era pubblico, è diventato privato
	//funz3(d);		// D non è polimorfico visto che l'interfaccia di B è stata resta privata, cioè non accessibile dall'esterno
	d.x = 54;
	d.funz2(b, d);
	
	return 0;
}