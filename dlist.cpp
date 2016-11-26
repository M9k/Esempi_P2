#include <iostream>
using std::cout;

template<class T>
class dlist
{
    private:
    class nodo
    {
        public:
        T info;
        nodo* prec;
        nodo* succ;
        nodo(T i, nodo* p=0, nodo* s=0): info(i), prec(p), succ(s) {}
        //distruttore, assegnazione e costruttore di copia di default
        T getinfo() const {return info;}
    };
    nodo* primo;
    nodo* ultimo;
    public:
    dlist(): primo(0), ultimo(0) {}
    void insertFront(T ogg);
    void insertBack(T ogg);
    dlist(const T&, unsigned int);
    //copia profonda!
    dlist(const dlist& d2);
    //distruzione! ->metodo ricorsivo
    void distruggi();
    ~dlist() {distruggi();}
    //assegnazione! ->metodo copia ricorsivo sopra
    const dlist& operator = (const dlist&);
    class constiterator
    {
        private:
        const nodo* n;
        public:
        constiterator(const nodo* p=0): n(p) {}
        bool operator == (const constiterator&) const;
        bool operator != (const constiterator&) const;
        constiterator& operator ++(); //prefisso
        constiterator operator ++(int); //postfisso
        constiterator& operator --(); //prefisso
        constiterator operator --(int); //postfisso
        const nodo& operator *() const;
        const nodo* operator ->() const;
    };
    constiterator begin() const;
    constiterator last() const; //dopo l'ultimo
    //al contrario
    constiterator end() const;
    constiterator frontbegin() const; //prima del primo
};

// --- metodi per iterare ---
template<class T>
typename dlist<T>::constiterator dlist<T>::begin() const {return primo;} //conversione implicita
template<class T>
typename dlist<T>::constiterator dlist<T>::end() const {return 0;}
template<class T>
typename dlist<T>::constiterator dlist<T>::last() const {return ultimo;}
template<class T>
typename dlist<T>::constiterator dlist<T>::frontbegin() const {return 0;}

// --- constiterator ---
template<class T>
bool dlist<T>::constiterator::operator == (const constiterator& it2) const
{
    return n == it2.n;
}
template<class T>
bool dlist<T>::constiterator::operator != (const constiterator& it2) const
{
    return n != it2.n;
}
template<class T>
typename dlist<T>::constiterator& dlist<T>::constiterator::operator ++()
{
    n = n->succ;
    return *this;
}
template<class T>
typename dlist<T>::constiterator dlist<T>::constiterator::operator ++(int)
{
    constiterator bk = n;
    n = n->succ;
    return bk;
}
template<class T>
typename dlist<T>::constiterator& dlist<T>::constiterator::operator --()
{
    n = n->prec;
    return *this;
}
template<class T>
typename dlist<T>::constiterator dlist<T>::constiterator::operator --(int)
{
    constiterator bk = n;
    n = n->prec;
    return bk;
}
template<class T>
const typename dlist<T>::nodo& dlist<T>::constiterator::operator *() const
{
    return *n;
}
template<class T>
const typename dlist<T>::nodo* dlist<T>::constiterator::operator ->() const
{
    return n;
}

// --- dlist ---
template<class T>
void dlist<T>::insertFront(T ogg)
{
    primo = new nodo(ogg, 0, primo);
    if(primo->succ)
        primo->succ->prec = primo;
    if(!ultimo)
        ultimo = primo;
}
template<class T>
void dlist<T>::insertBack(T ogg)
{
    ultimo = new nodo(ogg, ultimo, 0);
    if(ultimo->prec)
        ultimo->prec->succ = ultimo;
    if(!primo)
        primo = ultimo;
}
template<class T>
dlist<T>::dlist(const T& ogg, unsigned int i)
{
    primo = 0;
    ultimo = 0;
    unsigned int x;
    for(x=0; x<i; x++)
        insertBack(ogg);
}
template<class T>
dlist<T>::dlist(const dlist& da)
{
    primo = ultimo = 0;
    nodo* t = da.primo;
    while(t!= da.ultimo)
    {
        insertBack(t->info);
        t = t->succ;
    }
    insertBack(t->info);
}
template<class T>
void dlist<T>::distruggi()
{
    nodo* t = primo;
    nodo* p;
    while(t)
    {
        p = t;
        t = t->succ;
        delete p;
    }
}
template<class T>
const dlist<T>& dlist<T>::operator = (const dlist& d2)
{
    //controllo non sia una assegnazione a = a
    if(this == &d2)
        return *this;
    //distruggo this -> NO MEMORIA CONDIVISA, non ho problemi in caso di ->next
    distruggi();
    //assegno copiando
    primo = ultimo = 0;
    nodo* t = d2.primo;
    while(t!= d2.ultimo)
    {
        insertBack(t->info);
        t = t->succ;
    }
    insertBack(t->info);
    return *this;
}

int main()
{
    dlist<int> a;
    a.insertFront(123);
    a.insertFront(567);
    a.insertBack(321);
    dlist<char> b('x', 5);
    dlist<int> c(a);
    a = c;

    a.insertFront(56677);
    a.insertBack(3431);
    a.insertFront(7);
    a.insertBack(3661);
    a.insertFront(56);
    a.insertBack(37);

    for(dlist<int>::constiterator c = a.last(); c != a.frontbegin(); --c)
        cout << (*c).getinfo() << ' ';
    cout << '\n';
    for(dlist<int>::constiterator c = a.begin(); c != a.end(); ++c)
        cout << (*c).getinfo() << ' ';
    cout << '\n';
    for(dlist<int>::constiterator c = a.begin(); c != a.end(); c++)
        cout << (*c).getinfo() << ' ';
    cout << '\n';

    cout << "fine\n";
    return 0;
}
