#ifndef STD
#define STD
#include<stdlib.h>
#include<iostream>
#include<string>
#endif

using std::string;
using std::ostream;

class persona
{
	private:
		string nome;
		string cognome;
		int eta;
		
		static int min;
	
	public:
		explicit persona(int);
		persona();
		persona(string, string, int);
		int get_eta() const;
		void set_eta(int);
		
		static string saluta(); //NO CONST PER I STATIC
		static void decidiMin(int);
		static int incMin();
		
		int operator+(int);
		
		ostream& operator<<(ostream&);
};

persona::persona(string nome, string c, int e=0)
{
	(*this).nome = nome;
	cognome = c;
	eta = e;
}

persona::persona()
{;}

persona::persona(int i) //non ridichiaro esplicito
{
	eta = i;
}

string persona::saluta()
{
	return "Ciao!!\n";
}

int persona::get_eta() const //specifico anche qui che non modifica l'oggetto
{
	return eta;
}

void persona::set_eta(int i)
{
	eta = i;
}

int persona::min = 0; //INIZIALIZZO SEMPRE PRIMA DI USARLA - va benissimo nel cpp
void persona::decidiMin(int i)
{
	min = i;
}
int persona::incMin()
{
	min++;
	return min;
}
int persona::operator+(int i)
{
	return eta + i;
}


using std::ostream;
ostream& persona::operator<<(ostream& o)
{
	return o << nome << ' ' << cognome << '\n';
}
