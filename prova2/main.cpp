#ifndef STD
#define STD
#include<stdlib.h>
#include<iostream>
#include<string>
#endif

#include "classe.h"

using namespace std;

int main()
{
	prova ciao;
	prova a(6), b(8,9);
	cout << a.getsomma() << " " << b.getsomma();
	
	return 0;
}