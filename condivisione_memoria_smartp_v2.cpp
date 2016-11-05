/*
	`7MMM.     ,MMF'        `7MM      
	  MMMb    dPMM            MM      
	  M YM   ,M MM  .d*"*bg.  MM  ,MP'
	  M  Mb  M' MM 6MP    Mb  MM ;Y   
	  M  YM.P'  MM YMb    MM  MM;Mm   
	  M  `YM'   MM  `MbmmdM9  MM `Mb. 
	.JML. `'  .JMML.     .M'.JMML. YA.
					   .d9            
					 m"'        Mirco Cailotto
-
-				 
	Esempio di smart pointer con togliint, cambiaint e cambiatuttiint
*/
#include <iostream>

using std::cout;

class contenitore
{
	private:
	class ogg;
	class smartp
	{
		public:
		ogg* p;
		smartp(ogg * n = 0); //costruttore di default, con un argomento e conversione da ogg* a smartp
		smartp(const smartp&);						//regola del 3
		~smartp();									//regola del 3
		smartp& operator = (const smartp&);			//regola del 3
		bool operator == (const smartp&) const;
		bool operator != (const smartp&) const;
		ogg& operator *() const;
		ogg* operator ->() const;
		
		
	};
	class ogg
	{
		public:
		int val; //valore contenuto, int per semplificare
		int riferimenti; 
		smartp next; //il prossimo
		
		ogg(); //costruttore standard
		ogg(int, smartp); //costruttore
		//copia standard
		//distruzione standard
		void operator delete(void* p);
	};
	smartp primo;
	
	public:
	contenitore(); 
	contenitore(const contenitore&);
	~contenitore();
	void AggiungiInt(int);
	int PrelevaInt(); //non const perchè modifico il primo
	void TogliInt(int); //toglie la prima istanza dell'intero passato come parametro
	void CambiaInt(int, int); //sostituisce la prima istanza
	void CambiaTuttiInt(int, int); //sostituisci tutte le istanze
	bool Vuoto() {return primo == 0;}
};
// -- SMARTP --
contenitore::smartp::smartp(ogg* n):p(n)
{
	if(p)
		p->riferimenti++;
}

contenitore::smartp::smartp(const smartp& s):p(s.p)
{
	//non dealloco l'oggetto di chiamata, non esiste nemmeno
	if(p)
		p->riferimenti++;
}

contenitore::smartp::~smartp()
{
	if(p)
	{
		p->riferimenti--;
		if(p->riferimenti == 0)
			delete p;
	}
}
contenitore::smartp& contenitore::smartp::operator = (const smartp& s)
{
	if(this != &s)	//confronta gli indirizzi, se uguali so che sto puntando lo stesso oggetto
					//se uso *this != s confronto gli oggetti smartp, quindi gli indirizzi che puntano
	{
		ogg* t = p; //così incremento i riferimenti e evito che si cancelli adesso
		//NON POSSO ELIMINARE ORA P!
		p = s.p;
		//ORA ELIMINO P SE POSSIBILE
		if(p) p->riferimenti++; //nuovo riferimento, me lo segno
		if(t) //se t esiste
		{
			t->riferimenti--; //aggiusto i riferimenti
			if(t->riferimenti == 0)
				delete t; //si cancella a cascata -> elimina il nodo -> che elimina a sua volta smartp e va a loop
		}
	}
	return *this;
}


bool contenitore::smartp::operator == (const smartp& s) const
{
	return p == s.p;
}
bool contenitore::smartp::operator != (const smartp& s) const
{
	return p != s.p;
}
contenitore::ogg& contenitore::smartp::operator *() const
{
	return *p;
}
contenitore::ogg* contenitore::smartp::operator ->() const
{
	return p;
}
		
// -- OGG --
contenitore::ogg::ogg(): next(0), riferimenti(0) {}

contenitore::ogg::ogg(int v, smartp n): val(v), next(n), riferimenti(0) { }

void contenitore::ogg::operator delete(void* p) { }

// -- CONTENITORE --
contenitore::contenitore():primo(0) {}

contenitore::contenitore(const contenitore& c):primo(c.primo) { } //copio puntatori smartp, si arrangia con i riferiemnti

contenitore::~contenitore() { } //si arrangia con i puntatori smartp

void contenitore::AggiungiInt(int v)
{
	primo = new ogg(v,primo);
}

int contenitore::PrelevaInt()
{
	int r = primo->val; //primo ha l'override di ->, ritorna il puntatore, viene applicato ->val, in pratica primo.p->val;
	primo = primo->next; //si arrangia a deallocare se necessario
	return r;
}

void contenitore::TogliInt(int i)
{
	smartp t = primo, copia, prec; //=0 di default, posso ometterlo
	smartp backup = primo;
	primo = 0;
	while(t != 0 && (t->val != i))
	{
		copia = new ogg(t->val, t->next); //duplico il t attuale, sotto accodo a primo
		if(prec==0)
			primo = copia;	//se sono al primo ciclo mi segno che primo punterà la copia
							//la testa della copia rimane puntata da primo
		else
			prec->next = copia;	//metto copia nella nuova lista
								//prec scorre la nuova lista
		//sposto in avanti
		prec = copia;
		t = t->next;
	}
	if(t == 0) //non ho trovato i
		primo = backup; //risistemo
	else
		if (prec==0) //ho trovato i, è in testa
			primo = t->next;
		else //ho trovato i, non è in testa, "salto" t collegando prec->next a t->next
			prec->next = t->next;
}

void contenitore::CambiaInt(int i, int x)
{
	smartp t = primo, copia, prec; //=0 di default, posso ometterlo
	smartp backup = primo;
	primo = 0;
	while(t != 0 && (t->val != i))
	{
		copia = new ogg(t->val, t->next); //duplico il t attuale, sotto accodo a primo
		if(prec==0)
			primo = copia;	//se sono al primo ciclo mi segno che primo punterà la copia
							//la testa della copia rimane puntata da primo
		else
			prec->next = copia;	//metto copia nella nuova lista
								//prec scorre la nuova lista
		//sposto in avanti
		prec = copia;
		t = t->next;
	}
	if(t == 0) //non ho trovato i
		primo = backup; //risistemo
	else
		if (prec==0) //ho trovato i, è in testa
			primo = new ogg(x, backup->next);
		else //ho trovato i, non è in testa, "salto" t collegando prec->next a t->next
			prec->next = new ogg(x, t->next);
}

void contenitore::CambiaTuttiInt(int i, int x)
{
	smartp t = primo, copia, prec; //=0 di default, posso ometterlo
	
	int n = 0; //conto quanti sono presenti
	for(;t != 0;t=t->next)
		if(t->val == i)
			n++;
	
	if(n == 0)
		return; //niente da togliere 
	
	t = primo; //reiposto t per scorrere nuovamente la lista
	while(n != 0)
	{
		if(t->val == i)
		{
			copia = new ogg(x, t->next);
			n--;
		}
		else
			copia = new ogg(t->val, t->next); 
		
		if(prec==0)
			primo = copia;	//se sono al primo ciclo mi segno che primo punterà la copia
							//la testa della copia rimane puntata da primo
		else
			prec->next = copia;	//metto copia nella nuova lista
								//prec scorre la nuova lista
		//sposto in avanti
		prec = copia;
		t = t->next;
	}
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
	b.AggiungiInt(3);
	b.AggiungiInt(4);
	b.AggiungiInt(4);
	b.AggiungiInt(4);
	b.AggiungiInt(3);
	b.AggiungiInt(-2);
	contenitore c;
	c.AggiungiInt(10);
	c.AggiungiInt(9);
	c.PrelevaInt(); //scarta
	c = b;
	b.AggiungiInt(-3);
	b.AggiungiInt(-4);
	
	cout << "A = ";
	while(!a.Vuoto())
		cout << a.PrelevaInt() << ' ';
	cout << '\n';
	b.TogliInt(2);
	b.TogliInt(-2);
	b.CambiaInt(3, 12);
	b.CambiaInt(-4, 4);
	b.CambiaTuttiInt(3, 333);
	cout << "B = ";
	while(!b.Vuoto())
		cout << b.PrelevaInt() << ' ';
	cout << '\n';
	cout << "C = ";
	while(!c.Vuoto())
		cout << c.PrelevaInt() << ' ';
	cout << '\n';
	
	cout << "fine";
	return 0;
}