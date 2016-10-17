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
	Esercizio sui numeri razionali
*/
#ifndef N_RAZ
#define N_RAZ
#include <iostream>

class raz
{
	private:
		unsigned int num, den;
		bool sign;
		void prim(); //modifica il numeratore e il denominatore perchè siano primi tra loro
		//il nome va bene non intuitivo se sono solamente io che sviluppo la classe, visto che non fa parte dell'interfaccia
	public:
		raz(const int&, const int&);
		raz(const bool&, const unsigned int&, const unsigned int&);
		raz inverti() const;
		raz operator + (const raz&) const;
		raz operator * (const raz&) const;
		operator double() const;
		raz& operator++(int);
		raz operator++();
		bool operator==(const raz&) const;
		std::ostream& operator << (std::ostream&);
};

	
#endif