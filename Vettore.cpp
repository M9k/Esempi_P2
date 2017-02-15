/*
Definire una classe Vettore i cui oggetti rappresentano array di interi. 
Vettore deve includere un costruttore di default, l'overloading dell'uguaglianza, 
dell'operatore di output e dell'operatore di indicizzazione.  Deve inoltre 
includere il costruttore di copia profonda, l'assegnazione profonda e la 
distruzione profonda.
*/

#include<iostream>

class Vettore {
private:
  int* ar;
  unsigned int _size;

  //duplica l'array in uno della stessa dimensione
  int* copia() const {
    int* tmp = new int[_size];
    for(unsigned int i=0; i<_size; ++i)
		tmp[i]=ar[i]; 
    return tmp;
  }
public:
//costruttore, dimensione e numero da usare dimensione volte, mette l'array nel heap
  Vettore(unsigned int s=0, int init=0): ar(new int[s]), _size(s) {
    for(unsigned int i=0; i<_size; ++i) ar[i]=init; 
  }
  
//controlla tutti gli elementi
  bool operator==(const Vettore& v) const {
    if(_size != v._size) return false;
    for(int i=0; i<_size; ++i) 
      if(ar[i] != v.ar[i]) return false;
    return true;
  }

//operatore di indicizzazione, restituisce l'elemento, const perchè non si modificherà mai l'indice
//PS: qualche controllo che i<_size?
  int& operator[](unsigned int i) const {
    return ar[i];
  }

  //cstruttore di copia -> REGOLA DEL 3
  Vettore(const Vettore& v): ar(v.copia()), _size(v._size) {}
 //REGOLA DEL 3
  Vettore& operator=(const Vettore& v) {
    if(this != &v) {
      delete[] ar;
      ar = v.copia(); 
      _size = v._size;
    }
    return *this;
  }
   //REGOLA DEL 3
  ~Vettore() {
    delete[] ar;
  }
//può essere utili, ha senso
  unsigned int size() const {return _size;}
};

//non amica, usa solo l'interfaccia (dimensione e indicizzazione)
std::ostream& operator<<(std::ostream& os,const Vettore& v) {
  for(unsigned int i=0; i<v.size(); ++i) os << v[i] << " ";
  return os;
}
