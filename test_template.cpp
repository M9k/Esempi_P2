#include <iostream>
#include <string>

using std::cout;
using std::string;

template<class T>
T somma(T t1, T t2)
{
	return t1 + t2;
}
int main()
{
	int a=5,b=3,c=7;
	double d=5.5,e=3.3,f=7.7;
	cout << somma(a,b) << '\n';
	cout << somma(c,b) << '\n';
	cout << somma(e,d) << '\n';
	cout << somma<int>(e,d) << '\n';
	cout << somma<int>(a,d) << '\n';
	cout << somma<double>(a,d) << '\n';
	
	string s="asd", x="gef";
	cout << somma(s,x);
	return 0;
}

/*
somma<int>

push rbp
mov rbp,rsp
mov dword ptr ss:[rbp+10],ecx
mov dword ptr ss:[rbp+18],edx
mov edx,dword ptr ss:[rbp+10]
mov eax,dword ptr ss:[rbp+18]
add eax,edx
pop rbp
ret 


somma<double>

push rbp
mov rbp,rsp
movsd qword ptr ss:[rbp+10],xmm0
movsd qword ptr ss:[rbp+18],xmm1
movsd xmm0,qword ptr ss:[rbp+10]
addsd xmm0,qword ptr ss:[rbp+18]
pop rbp
ret 

*/