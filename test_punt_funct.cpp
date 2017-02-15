#include<stdio.h>
#include<iostream>

using namespace std;

int f1(double d, int  y = 5)
{
	int i;
	cin >> i;
	i++;
	i--;
	i++;
	i--;
	cout << "F1 " << d << '\n'; 
	return y + 1;
}

int f2(char i)
{
	cout << "F2" << i << '\n';
	return 0;
}

int main()
{
	int (*pf2)(char) = &f2;
	int (*pf1)(double, int) = &f1; //dichiaro SEMPRE anche i parametri opzionali
	
	int i;
	cin >> i;
	i++;
	i--;
	i++;
	i--;
	
	cout << "posizione di F1 in memoria: " << pf1 << '\n';
	cout << "posizione di F2 in memoria: " << pf2 << '\n';
	
	cin >> i;
	i++;
	i--;
	i++;
	i--;
	(*pf2)(3);
	
	return 0;
}