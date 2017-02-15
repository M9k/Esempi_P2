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
*/

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
	//un alias è SEMPRE costante, non può cambiare l'oggetto indicato, semmai punta a qualcosa di variabile o costante
	//TIPS: const agisce sempre sull'elemento a sinistra, se non c'è nulla agisce su quello a destra
	//ad esempio nella riga 36 agisce su pwned, nella 38 su &.
};

int pwned::getval() const { return x; }
void pwned::setval(const int& x) { this->x = x;}

int main()
{
	pwned const a, b, c;
	//a.setval(5); //errato! sto chiamando un metodo non const su una istanza const.
	//a.inutile(); //errato! inutile() NON MODIFICA I DATI, ma non è dichiarato const, quindi non posso usarlo.
	pwned x, y, z;
	x.setval(6);
	cout << x.getval() << ' ' << a.getval() << '\n'; //ok
	x.qualcosa1(a); //a viene copiato, quindi non è più costante
	
	//x.qualcosa2(a); //a viene passato come alias, ma così sarebbe modificabile, errato!
	pwned nuovo = a; //uso il costruttore di copia OPPURE scrivo pwned nuovo; nuovo = a; usando l'operatore di assegnazione, vedere costruttori.cpp
	x.qualcosa2(nuovo); //torno è una COPIA di a, quindi non è più const, non vado ad intaccare i valori di a, semmai ne modifico una copia.

	x.qualcosa3(a); //creo un alias ad a passato come parametro, ma il alias punta a qualcosa di costante, quindi il compiatore sa che a non verrà modificato nel metodo
	x.qualcosa4(a); //come qualcosa1, solo che sono certo che non sarà modificato > a questo punto tanto vale usare qualcosa3 e risparmiare memoria, ma comunque corretto
	//x.qualcosa5(a); //vedere sopra
	return 0;
}
