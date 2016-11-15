#include <iostream>
using std::cout;

class B
{
	private:
	int a;
	public:
	int geta() const {return a;}
	void seta(int na) {a = na;}
	B(int a=0):a(a) { cout << "costruito B, a:" << a << "\n";}
	B(const B& b) { a = b.a; cout << "costruttore copia di B, a:" << a << "\n";}
	B& operator = (const B& b) {a = b.a; cout << "operatore di copia di B, a:" << a << "\n";}
	~B() {cout << "distruttore di B, a:" << a << "\n";}
};
class D: public B
{
	private:
	int b;
	public:
	int getb() const {return b;}
	void setb(int nb) {b = nb;}
	//int geta_ofb() const {return B::geta(a);}
	
	D(int a=0, int b=0):b(b), B(a) { cout << "costruito D, a:" << geta() << ", b:" << b << "\n";} //se non specifico B(int) chiamerà B()
	
	//D(const D& d) {} //a e b saranno posti a zero, richiamerà B() per costruire B
	
	//D(const D& d) { seta(d.geta()); b = d.b; cout << "costruttore copia di D, a:" << geta() << ", b:" << b << "\n";} //uso linterfaccia di B, a è privato
	//chiama B() e poi copia il dato, funziona ma poco elegante e errato, senza un seta sono fregato
	
	D(const D& d):B(d.geta()) {b = d.b; cout << "costruttore copia di D, a:" << geta() << ", b:" << b << "\n";}
	//migliore, chiama B(int) e poi copia il dato di D
	
	// se non inserisco il costruttore di copia di D farà la copia di B usando il suo costruttore di copia, QUINDI VEDE I PRIVATI, non ho nessun problema!
	// e poi copia uno a uno i campi usando il loro costruttore di copia
	
	
	//D& operator = (const D& d){}
	//non esegue nessuna operazione, non richiama l'operator = di B
	
	//D& operator = (const D& d) {seta(d.geta()); b = d.b; cout << "operatore di copia di D, a:" << geta() << ", b:" << b << "\n";}
	D& operator = (const D& d) {((B&)*this) = ((B&)d); b = d.b; cout << "operatore di copia di D, a:" << geta() << ", b:" << b << "\n";} //in pratica è il comportamento standard
	//AAA cercasi modo elegante per scriverlo, e magari che non rischia un crash in esecuzione...
	// se non inserisco l'operatore di uguaglianza utilizza quello di B, stesso discorso di prima per le visibilità, e poi copia uno a uno tutti i campi
	//in pratica se faccio una catena di classi e in nessuna ridefinisco la copia, quando andrò a copiare la classe derivata per ultima copierà unicamente tutti i campi
	
	//operatore standard: invoca la copia di B, poi copia ogni valore usando il loro operatore di copia
	~D() {cout << "distruttore di D, a:" << geta() << ", b:" << b << "\n";}
};

int main()
{
	B b(5);
	B c(b);
	B d;
	d = b;
	cout << "--------------\n";
	D x(1,2);
	cout << x.geta() << ' ' <<  x.getb() <<'\n';
	D z(x);
	cout << z.geta() << ' ' <<  z.getb() <<'\n';
	D k;
	k = x;
	cout << k.geta() << ' ' <<  k.getb() <<'\n';
	cout << "--------------\n";
	return 0;
}