#include <iostream>
#include <vector>

using std::cout;
using std::vector;

int main()
{
	vector<int> a; //primo parametro = dimensione = default 0
	cout << "Dimensione: " << a.size() << "\nDimensione massima: " << a.max_size() << "\nCapacita': " << a.capacity() << '\n';
	
	a.push_back(123456); //inserisco uno alla fine
	//lo allungo a 60, costruttore di default per ogni campo (a 0 per gli int)
	a.resize(60);
	
	//ne riempio un pò a caso
	for(int i=5; i<25; ++i)
	{
		a[i] = i;
	}
	for(int i=22; i<35; ++i)
	{
		a.at(i) = i*3;
	}
	
	//tolgo gli zero finali
	for(int i=a.size()-1; i>=0; --i)
		if(!a[i])
			a.resize(a.size()-1);
		else
			break; //poco elegante
	
	a.shrink_to_fit();
	 
	for(int n : a)
        std::cout << n << '\n';
	cout << "Dimensione: " << a.size() << "\nDimensione massima: " << a.max_size() << "\nCapacita': " << a.capacity() << '\n';
	//tengo solo i primi 15 elementi
	a.resize(15);
	//altri 15 a 0
	a.resize(30);
	
	//a.at(1000) = 0; -> lancia una eccezzione out of range
	a.reserve(123);
	//123 sarà la capacità, non la size, non posso scrivere sul 100° elemento, out_of_range
	a.resize(12);
	//di 123 elementi ne uso 12
	a[6] = 2132131231;
	a.at(7) = 66225;
	for(int n : a)
        std::cout << n << '\n';
	cout << "Dimensione: " << a.size() << "\nDimensione massima: " << a.max_size() << "\nCapacita': " << a.capacity() << '\n';
	vector<int>::iterator i;
	vector<int>::const_iterator ci;
	for(i = a.begin(); i!=a.end(); i++)
		*i = 123;
	a.pop_back();
	a.pop_back();
	a.pop_back();
	a.pop_back();
	//cout << a.pop_back(); elimina solo, non preleva
	if(!a.empty())
		cout << "array non vuoto\n";
	//ci costante, non potrei modificarlo
	for(ci = a.end()-1; ci!=a.begin()-1; --ci)
		cout << *ci << ' ';
	return 0;
}