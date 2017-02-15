#include <string>
#include <iostream>
#include <vector>
#include <typeinfo>
using std::string;
using std::cout;
using std::ostream;
using std::vector;

class PaccoBase {
protected:
	string mittente;
	string destinatario;
	double peso;
	static double tariffa;
public:
	PaccoBase(string mitt, string dest, double pes) : mittente(mitt), destinatario(dest), peso(pes) {}
	virtual double costo() const {return peso * tariffa;}
	virtual ~PaccoBase();
	string getDestinatario() const {return destinatario;}
	string getMittente() const {return mittente;}
	double getPeso() const {return peso;}
};
double PaccoBase::tariffa = 10;

class PaccoDue : public PaccoBase
{
private:
	static double aggiunta;
public:
	PaccoDue(string mittente, string destinatario, double peso) : PaccoBase(mittente, destinatario, peso) {}
	double costo() const {return PaccoDue::costo() + aggiunta;}	
	double getExtra() const  {return aggiunta;}
};
double PaccoDue::aggiunta = 2;

class PaccoFast : public PaccoBase
{
private:
	bool overnight;
	static double costoovernight;
	static double aggiunta;
public:
	PaccoFast(string mittente, string destinatario, double peso, bool on=false) : PaccoBase(mittente, destinatario, peso), overnight(on) {}
	double costo() const {return overnight ? PaccoBase::costo() + aggiunta + (costoovernight*peso) : PaccoBase::costo() + aggiunta;}
	bool isOvernight() const {return overnight;}
	double getExtra() const {return overnight ? aggiunta + (costoovernight*peso) : aggiunta;}
};
double PaccoFast::costoovernight = 5;
double PaccoFast::aggiunta = 7;

class AgenziaEDS
{
private:
	vector<PaccoBase*> p;
public:
	friend ostream& operator << (ostream& o, AgenziaEDS a)
	{
		double costotot=0;
		for(vector<PaccoBase*>::const_iterator i = a.p.begin(); i!= a.p.end(); ++i)
		{
			costotot += (*i)->costo();
			if(PaccoDue* pk=dynamic_cast<PaccoDue*>(*i))
				o << "pacco due, prezzo " << (*i)->costo() << ", extra " << pk->getExtra() << '\n';
			else
			{
				if(PaccoFast* pk=dynamic_cast<PaccoFast*>(*i))
				{
					o << "pacco fast, ";
					if(pk->isOvernight())
						o<<"overnight";
					else
						o<<"non overnight";
					o<<", prezzo " << (*i)->costo() << ", extra " << pk->getExtra() << '\n';
				}
				else
					o << "pacco base, prezzo " << (*i)->costo() << ", no extra\n";
			}
		}
		o << "\ncosto totale: " << costotot << '\n';
	}
	
	vector<PaccoBase*> cerca(string dest, double pe) const
	{
		vector<PaccoBase*> rit;
		for(vector<PaccoBase*>::const_iterator i = p.begin(); i!=p.end(); ++i)
			if(dest == (*i)->getDestinatario() && pe >= (*i)->getPeso())
				rit.push_back(*i);
		return rit;
	}
	
	void modifica(string mittente)
	{
		for(auto i=p.begin(); i!=p.end(); ++i)
			if((*i)->getMittente() == mittente && typeid(*(*i)) == typeid(PaccoBase))
			{
				p.push_back(new PaccoFast(mittente, (*i)->getDestinatario(), (*i)->getPeso(), true)); 
				delete (*i);
				p.erase(i);
			}
	}
};


