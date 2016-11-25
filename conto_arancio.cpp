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
	Compilatore: 
	gcc (tdm64-1) 4.9.2, nessun parametro aggiuntivo
*/

#include <iostream>
using std::cout;
//tutti gli unsigned dovrebbero essere short oppure gli int long per evitare out of range

class contobancario
{
	private:
	int saldo; //in centesimi di euro - ignorerò gli arrotondamenti
	//dalle funzioni date nell'esercizio si sottointende che saldo sia richiesto in double, ho però scelto int in quanto mi sembra il più adatto (anche se lontano dunsigned a una soluzione ottimale)
	public:
	contobancario(int i=0): saldo(i) {}
	//copia, assegnazione e distruttore standard
	int getsaldo();
	int deposita(unsigned int);
	int preleva(unsigned int); //accetta saldi negativi
};

int contobancario::getsaldo()
{
	return saldo;
}
int contobancario::deposita(unsigned int s)
{
	return saldo+=s;
}
int contobancario::preleva(unsigned int s)
{
	return saldo-=s;
}

class contocorrente: public contobancario
{
	unsigned int spesa; //suppongo modificabile nel tempo, ogni conto ha la propria, quindi non statica
	public:
	contocorrente(unsigned int s, unsigned int i=0):spesa(s),contobancario(i) {}
	//copia, assegnazione e distruttore standard
	//getsaldo non ridefinito
	int deposita(unsigned int);
	int preleva(unsigned int); //accetta saldi negativi
};
//in caso di spesa static: int contocorrente::spesa = 1234;
int contocorrente::deposita(unsigned int s)
{
	return contobancario::deposita(s-spesa);
}
int contocorrente::preleva(unsigned int s)
{
	return contobancario::preleva(s+spesa);
}

class contodirisparmio: public contobancario
{
	public:
	contodirisparmio(unsigned int i=0):contobancario(i) {} 
	//getsaldo, deposita non ridefinito
	int preleva(int);
};
int contodirisparmio::preleva(int s)
{
	return getsaldo()-s>0 ? contobancario::preleva(s) : getsaldo();
}

class contoarancio: public contodirisparmio
{
	private:
	contocorrente& supporto;
	public:
	contoarancio(contocorrente& c, unsigned int i=0):supporto(c), contodirisparmio(i) {}
	//getsaldo non ridefinito
	int deposita(unsigned int); //sposta da supporto al contoarancio
	int preleva(unsigned int); //sposta dal contoarancio al supporto
};

int contoarancio::preleva(unsigned int i)
{
	if(getsaldo() != contodirisparmio::preleva(i))
		supporto.deposita(i);
	return getsaldo();
}

int contoarancio::deposita(unsigned int i)
{
	supporto.preleva(i);
	return contodirisparmio::deposita(i);
}


int main()
{
	
	return 0;
}