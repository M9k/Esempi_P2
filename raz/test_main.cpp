#include <iostream>
#include "raz.h"

using std::cout;

int main()
{
	raz a(34,6);
	cout << a << '\n'; //convertito a double
	raz b(1,3);
	b = b + raz(5,3);
	cout << b << '\n';
	b = b*raz(2,1);
	cout << b << '\n';
	raz d(4,4);
	cout << d << '\n';
	d = d * b * a;
	cout << d << '\n';	
	d << cout << '\n';
	
	
	return 0;
}