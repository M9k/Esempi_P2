#include <iostream>
#include <vector>
#include <cstdint>

using std::cout;
using std::vector;

int main()
{
	cout << "inizio\n";
	vector<int> z(vector<int>::size_type(100), -1);
	vector<int> a(vector<int>::size_type(15), 1);
	vector<int> b(vector<int>::size_type(50), 5);
	cout << z.capacity() << ' ' << a.capacity() << ' ' << b.capacity() << '\n';
	cout << &(z[0]) << ' ' << &(a[0]) << ' ' << &(b[0]) << '\n';
	int i;
	std::uintptr_t prec = reinterpret_cast<uintptr_t>(&(a[0]));
	for(i=0; i<10000; i++)
	{
		a.push_back(i);
		if(prec != reinterpret_cast<uintptr_t>(&(a[0])))
		{
			prec = reinterpret_cast<uintptr_t>(&(a[0]));
			cout  << &(a[0]) << " inserendo il " << i << " elemento\n";
		}
	}
	cout << "1000 elemento si trova in " << &(a[10000]) << " - con una differenza dalla base di: " << (int)(&(a[10000])-&(a[0])) << '\n';
	cout << &(z[0]) << ' ' << &(a[0]) << ' ' << &(b[0]) << '\n';
	cout << "fine";
	return 0;
}