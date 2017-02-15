#ifndef STD
#define STD
#include<stdlib.h>
#include<iostream>
#include<string>
#endif

#include "classe.h"

using namespace std;

prova::prova()
{
	a = 0;
	b = 0;
}

prova::prova(int a)
{
	(*this).a = a;
	b = 0;
}

prova::prova(int a, int x)
{
	(*this).a = a;
	b = x;
}

int prova::getsomma() const
{
	return a + b;
}