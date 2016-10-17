#include <iostream>
#include "raz.h"

void raz::prim()
{
	//euclide
	int r;
	int a = num;
	int b = den;
	while(b)
	{
		r = a%b;
		a=b; 
		b=r;
	}
	num/=a;
	den/=a;
	return;
}
		
raz::raz(const int& n, const int& d)
{
	//std::cout << "costruttore con parametri " << n << ' ' << d << '\n';
	//nessun problema a convertire da int a unsigned int
	if(!d)	//se d � 0 sarebbe invalido, setto a 0/1
	{
		num=0;
		den=1;
	}
	else
	{
		if((n>=0 && d>=0) || (n<0 && d<0))
			sign = true;
		else
			sign = false;
		num = n;
		den = d;
		prim();	//li rende primi tra loro
	}
}
raz::raz(const bool& b, const unsigned int& n, const unsigned int& d=1):sign(b), num(n), den(d) {prim();};
raz raz::inverti() const
{
	if(den)
	{
		return raz(sign, den, num);
	}
	else
	{
		return raz(sign, 0, 1);
	}
}
raz raz::operator + (const raz& r) const
{
	int n1, n2;
	if(sign)
		n1 = num;
	else
		n1 = 0-num;
	if(r.sign)
		n2 = r.num;
	else
		n2 = 0-r.num;
	int n = (n2*den)+(r.den*n1);
	int d = den*r.den;
	return raz(n, d); //il costruttore si impegner� a ridurli a numeri primi -> chiamo il costruttore con due int
}
raz raz::operator * (const raz& r) const
{
	if((sign && r.sign) || (!sign && !r.sign))
	{
		int n = num*r.num;
		int d = den*r.den;
		return raz(n,d); //il costruttore si impegner� a ridurli a numeri primi -> chiamo il costruttore con due int
	}
	int n = 0-num*r.num;
	int d = den*r.den;
	return raz(n,d);
}
raz::operator double() const
{
	if(sign)
		return static_cast<double>(num)/static_cast<double>(den);
	else
		return 0-static_cast<double>(num)/static_cast<double>(den);
}
raz& raz::operator++(int)
{
	if(sign)
		num+=den;
	else
	{
		num-=den;
		if(num<0)
		{
			num=0-num;
			sign = true;
		}
	}
	return *this;
}
raz raz::operator++()
{
	if(sign)
		num+=den;
	else
	{
		num-=den;
		if(num<0)
		{
			num=0-num;
			sign = true;
		}
	}
	return *this;
}

std::ostream& raz::operator << (std::ostream& o)
{
	if(sign)
		o << num << '/' << den << '\n';
	else
		o << '-' << num << '/' << den << '\n';
	return o;
}

//se il num � 0 + e - non fa differenza
bool raz::operator==(const raz& r) const
{
	if(num == 0 && r.num == 0)
		if(den == r.den)
			return true;
		else
			return false;
	if(num == r.num && den == r.den && sign == r.sign)
		return true;
	return false;
}