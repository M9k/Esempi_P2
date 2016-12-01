#include <iostream>
#include <vector>
using std::cout;
using std::vector;

class car	//astratta
{
	private:
	unsigned int cavalli;
	static const unsigned int tassa_cv = 500;	//in centesimi
	public:
	car(unsigned int cv) : cavalli(cv) {}
	virtual ~car() = 0;	//impone l'astrazione
	virtual unsigned int tassa() const; //in centesimi
};
class diesel: public car
{
	private:
	static const unsigned int tassa_fisso = 10000;
	public:
	diesel(unsigned int cv):car(cv) {}
	unsigned int tassa() const; //astratta
};
class benzina: public car
{
	private:
	const bool euro5;
	static const unsigned int tassa_detrazione = 5000;
	public:
	benzina(unsigned int cv, bool e5): car(cv), euro5(e5) {}
	unsigned int tassa() const; //astratta
};

class ACI
{
	private:
	//array di puntatori di auto? implemento con vector
	vector<car*> lista;
	public:
	//distruttore, copia e assegnazione standard perfetti
	void aggiungi(car*);
	unsigned int incassaBolli() const;
};

// -- car --
car::~car() {}
unsigned int car::tassa() const
{
	return tassa_cv*cavalli;
}
// -- diesel --
unsigned int diesel::tassa() const
{
	return car::tassa()+tassa_fisso;	//secondo la logica che è la tassa di una auto con 100€ extra
}

// -- benzina --
unsigned int benzina::tassa() const
{
	return euro5 ? car::tassa()-tassa_detrazione : car::tassa();
}
// -- ACI --
void ACI::aggiungi(car* c)
{
	lista.push_back(c);
}
unsigned int ACI::incassaBolli() const
{
	unsigned int somma = 0;
	//iteratore costante perchè non vado a modificare le auto
	for(vector<car*>::const_iterator i=lista.begin(); i!=lista.end(); i++)
		somma += (*i)->tassa();
	return somma;
}
int main()
{
	ACI a1;
	car* c1 = new diesel(5);			//12500
	car* c2 = new benzina(10, true);	//0
	car* c3 = new benzina(10, false);	//5000
	diesel c4(4);						//12000
	benzina c5(20, true);				//5000
	benzina c6(20, false);				//10000
	diesel c7(10);						//15000
	a1.aggiungi(c1);
	a1.aggiungi(c2);
	a1.aggiungi(c3);
	a1.aggiungi(&c4);
	a1.aggiungi(&c5);
	a1.aggiungi(&c6);
	a1.aggiungi(&c7);
	
	//tot 59500
	cout << a1.incassaBolli() << '\n';
	
	delete c1;
	delete c2;
	delete c3;
	
	return 0;
}