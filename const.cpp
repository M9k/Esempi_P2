#include <iostream>

using std::cout;
using std::flush;

class pwned
{
	//private:
	//costruttore di default
	int x = 3; //SOLO DA C++ 11
	public:
	int getval() const;
	void setval(const int& x);
	void inutile() {}
	pwned restituisci() const {return *this;}
	pwned qualcosa1(pwned a) { cout << "qualcosa\n"; return a;}
	pwned qualcosa2(pwned& a) { cout << "qualcosa\n"; return a;}
	pwned qualcosa3(const pwned& a) { cout << "qualcosa\n"; return a;}
	pwned qualcosa4(const pwned a) { cout << "qualcosa\n"; return a;}
	//pwned qualcosa5(pwned& const a) { cout << "qualcosa\n"; return a;} //ERRATO ANCHE DICHIARARLO!
	//un alias � SEMPRE costante, non pu� cambiare l'oggetto indicato, semmai punta a qualcosa di variabile o costante
	//TIPS: const agisce sempre sull'elemento a sinistra, se non c'� nulla agisce su quello a destra
};

int pwned::getval() const { return x; }
void pwned::setval(const int& x) { this->x = x;}

int main()
{
	pwned const a, b, c;
	//a.setval(5); //errato! sto chiamando un metodo non const su una istanza const.
	//a.inutile(); //errato! inutile() NON MODIFICA I DATI, ma non � dichiarato const, quindi non posso usarlo.
	pwned x, y, z;
	x.setval(6);
	cout << x.getval() << ' ' << a.getval() << '\n'; //ok
	x.qualcosa1(a); //a viene copiato, quindi non � pi� costante
	
	//x.qualcosa2(a); //a viene passato come alias, ma cos� sarebbe modificabile, errato!
	pwned nuovo = a; //uso il costruttore di copia OPPURE scrivo pwned nuovo; nuovo = a; usando l'operatore di assegnazione, vedere costruttori.cpp
	x.qualcosa2(nuovo); //torno � una COPIA di a, quindi non � pi� const, non vado ad intaccare i valori di a, semmai ne modifico una copia.

	x.qualcosa3(a); //creo un alias ad a passato come parametro, ma il alias punta a qualcosa di costante, quindi il compiatore sa che a non verr� modificato nel metodo
	x.qualcosa4(a); //come qualcosa1, solo che sono certo che non sar� modificato > a questo punto tanto vale usare qualcosa3 e risparmiare memoria, ma comunque corretto
	//x.qualcosa5(a); //vedere sopra
	
	return 0;
}