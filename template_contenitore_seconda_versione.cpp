//IN queue.h
#ifndef QUEUE
#define QUEUE

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif
using std::cout;
using std::cerr;
using std::ostream;

template<class T> class queueitem;
template<class T> ostream& operator << (ostream&, const queueitem<T>&);
template<class T> class queue;
template<class T> ostream& operator << (ostream&, const queue<T>&);


template<class T>
class queueitem
{	
	//friend associato (es: <int> amico di <int>)
	friend class queue<T>; //ad esempio queue<int> avrà bisogno di accedere unicamente a queueitem<int>, non ha necessità di accedere ad altre queueitem
	/*
	//friend non associato
	Se volevo l'amicizio per qualsiasi istanza di queueitem:
	template<class Tc>
	friend class queue; //ATTENZIONE! non queue<Tc>
	
	Se volevo l'amicizia con template<class T1, class T2> bool test(C<T1, T2>) scrivevo
	template<class Tc>
	friend bool test<Tc> //Tc "sostituisce" qualsiasi sia il tipo di C<T1, T2>
	
	Se volevo l'amicizia con una funzione di un'altra classe templatizzata
	template<class Tc>
	friend bool classeA<Tc>::funzione();
	*/
	
	private:
	T val;
	queueitem* next;
	queueitem(T, queueitem* n = 0);
	
	friend ostream& operator << <T> (ostream&, const queue<T>&);
	friend ostream& operator << <T> (ostream&, const queueitem<T>&);
};
	
template<class T = int> //default int
class queue
{
	private:
	queueitem<T>* inizio;
	queueitem<T>* fine;
	public:
	queue();
	queue(const queue&);
	void aggiungi(const T&);
	T preleva();
	bool vuoto() const;
	~queue();
	
	friend ostream& operator << <T> (ostream&, const queue<T>&);
};

template<class T>
queueitem<T>::queueitem(T v, queueitem* n): val(v), next(n) {}

template<class T>
queue<T>::queue(): inizio(0), fine(0) {}

template<class T>
queue<T>::queue(const queue& q) : inizio(0), fine(0)
{
	queueitem<T>* p = q.inizio;
	while(p!=0)	//copia profonda di tutti gli elementi di q
	{
		aggiungi(p->val);
		p=p->next;
	}
}

template<class T>
bool queue<T>::vuoto() const
{
	return (inizio == 0);
}

template<class T>
void queue<T>::aggiungi(const T& t)
{
	if(vuoto())
		inizio = fine = new queueitem<T>(t);
	else
	{
		fine->next = new queueitem<T>(t);
		fine = fine->next;
	}
}

template<class T>
T queue<T>::preleva()
{
	if(inizio == 0)
	{
		cerr << "ERRORE! nessun elemento da prelevare!";
		exit(-1);
	}
	T rit = inizio->val;
	queueitem<T>* del = inizio;
	inizio = inizio->next;
	delete del;
	return rit;
}

template<class T>
queue<T>::~queue()
{
	while(!vuoto())
		preleva();
}


template<class T>
ostream& operator <<(ostream& o, const queue<T>& q)
{
	o << "Elementi:\n";
	queueitem<T>* p = q.inizio;
	while(p != 0)
	{
		o << *p;
		p = p->next;
	}
	o << '\n';
	return o;
}

template<class T>
ostream& operator <<(ostream& o, const queueitem<T>& qi)
{
	return o << qi.val << ' ';
}

#endif

//main.cpp
//#include "queue.h"
#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif
using std::cout;
using std::cerr;

int main()
{
	queue<> qint;
	qint.aggiungi(1);
	qint.aggiungi(2);
	qint.aggiungi(3);
	qint.aggiungi(4);
	queue<> qint2 = qint;
	qint.aggiungi(5);
	qint.aggiungi(6);
	qint.aggiungi(7);
	qint.aggiungi(8);
	cout << qint;
	while(!qint.vuoto())
		cout << qint.preleva() << ' ';
	cout << '\n';
	while(!qint2.vuoto())
		cout << qint2.preleva() << ' ';
	cout << '\n';
	queue<double> qd;
	qd.aggiungi(3.32);
	qd.aggiungi(123.2);
	qd.aggiungi(21341234124);
	cout << qd.preleva() << '\n';
	cout << qd.preleva() << '\n';
	cout << qd.preleva() << '\n';
	cout << qd.preleva() << '\n'; //ERRORE!
	
	return 0;
}