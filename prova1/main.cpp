#ifndef STD
#define STD
#include<stdlib.h>
#include<iostream>
#include<string>
#endif

#include "classe1.cpp"

using namespace std;

int main()
{
	persona io("Mirco", "Cailotto"), john("John","Smith",-1);
	io.set_eta(20);
	cout << io.get_eta() << '\n';
	persona x(5);
	//persona y = 6; //ERRORE! costruttore esplicito
	persona io2 = io; //copia tutti i valori
	
	cout << persona::saluta();
	cout << io.saluta();
	
	cout << "fine\n";
	return 0;
}