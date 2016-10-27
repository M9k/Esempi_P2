#include <iostream>

using std::cout;

class contenitore
{
	public:
	contenitore(); 
	contenitore(const contenitore&);
	~contenitore();
	void AggiungiInt(int);
	int PrelevaInt(); //non const, se ultimo cambia il primo
	bool Vuoto() {return primo == 0;}
	private:
	class ogg
	{
		public:
		ogg(); //costruttore standard
		ogg(int, ogg*); //costruttore
		//copia standard
		//distruzione standard
		int val; //valore contenuto, int per semplificare
		ogg* next; //il prossimo
		int riferimenti; 
		void operator delete(void* p);
	};
	ogg* primo;
};

// -- OGG --
contenitore::ogg::ogg(): next(0), riferimenti(0) {} //val non inizializzato, oppure lo metto a 0 o NULL, dipende dal tipo

contenitore::ogg::ogg(int v, ogg* n): val(v), next(n), riferimenti(0)
{
	//la copia punta il successivo, incremento il successivo
	if(next) next->riferimenti++;
	//riferimenti a 0, non ho niente per ora che mi punta il nodo che ho creato
}

void contenitore::ogg::operator delete(void* p)
{
	if(p)
	{
		ogg* o = static_cast<ogg*>(p);
		o->riferimenti--; //un riferimento in meno
		if(o->riferimenti == 0) //non più puntato
		{
			delete o->next; //controllo il successivo a cascata
			::delete o; //delete standard su o, lo dealloca
		}
		//se ha ancora riferimenti non lo distruggo
	}
}

// -- CONTENITORE --
contenitore::contenitore():primo(0) {}

contenitore::contenitore(const contenitore& c)
{
	primo = c.primo;
	if(primo) //controllo che c esiste
		primo->riferimenti++; //indico che lo sto puntando
}


contenitore::~contenitore()
{
	if(primo)
		delete(primo);
	//si arrangia a cancellarlo ricorsivamente se necessario
	//se primo ha altri riferimenti non sarà cancellato
}

void contenitore::AggiungiInt(int v)
{
	if(primo)
		primo->riferimenti--; //sposterò il puntatore al'ogg "sopra" nella lista, quindi avrà un riferimento in meno PER ORA
	primo = new ogg(v, primo); //incrementa il vecchio primo, il secondo in scalinata
	primo->riferimenti++; //incrementa il primo in scalinata
	
	/*
		-         0 -> 1
		1 -> 0 -> 1 -> 1
		1 -> 1 -> 1 -> 1
		1 -> 1 -> 1 -> 1
		primo passaggio manuale
		il secondo generato dal costruttore
		il terzo manuale
	*/
}

int contenitore::PrelevaInt()
{
	int rit = primo->val;
	ogg* backup = primo; //costruttore di copia di ogg standard, copia i campi, non fa danni
	primo = primo->next; //ovvio
	if(primo) //mai si sa
		primo->riferimenti++;
	delete backup; //a cascata? NO, cancella al massimo il backup, poi trova il successivo che sto puntando al momento con primo, e quindi si ferma
	return rit;
}

int main()
{
	contenitore a;
	a.AggiungiInt(5);
	a.AggiungiInt(4);
	a.AggiungiInt(3);
	a.AggiungiInt(2);
	a.AggiungiInt(1);
	contenitore b = a;
	b.AggiungiInt(0);
	b.AggiungiInt(-1);
	b.AggiungiInt(-2);
	b.AggiungiInt(-3);
	b.AggiungiInt(-4);
	
	cout << "A = ";
	while(!a.Vuoto())
		cout << a.PrelevaInt() << ' ';
	cout << '\n';
	cout << "B = ";
	while(!b.Vuoto())
		cout << b.PrelevaInt() << ' ';
	cout << '\n';
	
	cout << "fine";
	return 0;
}