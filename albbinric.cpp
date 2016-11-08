#include <iostream>
using std::cout;
using std::ostream;

template<class T> class albbinric;
template<class T> class nodo;
template<class T> ostream& operator<< (ostream&, nodo<T>*);
template<class T> ostream& operator<< (ostream&, const albbinric<T>&);

template<class T>
class nodo
{
    friend class albbinric<T>;
    friend ostream& operator<< <T> (ostream&, nodo<T>*);
    private:
    T info;
    nodo *padre, *sinistro, *destro;
    nodo(const T& v, nodo *p = 0, nodo *s = 0, nodo *d = 0) : info(v), padre(p), sinistro(s), destro(d) {}
};

template<class T>
ostream& operator<< (ostream& o, nodo<T>* n)
{
    if(!n) o << '@';
    else
        o << '(' << n->info << ',' << n->sinistro << ',' << n->destro << ')'; //ricorsivo
    return o;
}

template<class T>
class albbinric
{
    friend ostream& operator<< <T> (ostream&, const albbinric<T>&);
    private:
    nodo<T>* root;
    static nodo<T>* findric(nodo<T>*, T);
    static nodo<T>* minric(nodo<T>*);
    static nodo<T>* maxric(nodo<T>*);
    static void insertric(nodo<T>*, T);
    public:
    albbinric(): root(0) {}
    nodo<T>* find(T) const;
    nodo<T>* min() const;
    nodo<T>* max() const;
    nodo<T>* succ(nodo<T>*) const;
    nodo<T>* prec(nodo<T>*) const;
    void insert(T);
    static T valore(nodo<T>* p) {return p->info;}
};

template<class T>
ostream& operator<< (ostream& o, const albbinric<T>& a)
{
    return o << a.root << '\n';
}

template<class T>
nodo<T>* albbinric<T>::find(T t) const {return findric(root, t);}
template<class T>
nodo<T>* albbinric<T>::min() const { if(!root) return 0; return minric(root);}
template<class T>
nodo<T>* albbinric<T>::max() const { if(!root) return 0; return maxric(root);}
template<class T>
void albbinric<T>::insert(T t)
{
    if(!root)
        root = new nodo<T>(t);
    else
        insertric(root, t);
}


template<class T>
nodo<T>* albbinric<T>::findric(nodo<T>* n, T t)
{
    if(!n)
        return 0; //nodo invalido, non c'è
    if(n->info == t)
        return n;
    if(n->info > t)
        return findric(n->sinistro, t);
    else
        return findric(n->destro, t);
}

template<class T>
nodo<T>* albbinric<T>::minric(nodo<T>* n)
{
    if(n->sinistro)
        return minric(n->sinistro);
    else
        return n;
}
template<class T>
nodo<T>* albbinric<T>::maxric(nodo<T>* n)
{
    if(n->destro)
        return maxric(n->destro);
    else
        return n;
}
template<class T>
void albbinric<T>::insertric(nodo<T>* n, T t)
{
    if(t < n->info)
        if(n->sinistro == 0)
            n->sinistro = new nodo<T>(t, n);
        else
            insertric(n->sinistro, t);
    else
        if(n->destro == 0)
            n->destro = new nodo<T>(t, n);
        else
            insertric(n->destro, t);
}

template<class T>
nodo<T>* albbinric<T>::succ(nodo<T>* n) const
{
    if(!n)
        return 0;
    if (n->destro)
        return minric(n->destro);
    //non ho il destro, devo risalire finchè non trovo un padre che abbia l'elemento attuale
    //come figlio sinistro
    while(n->padre && n->padre->destro == n)
        n = n->padre;
    //n->padre->sinistro != n, quindi n è il figlio destro e non sinistro
    return n->padre;

}
template<class T>
nodo<T>* albbinric<T>::prec(nodo<T>* n) const
{

    if(!n)
        return 0;
    if (n->sinistro)
        return maxric(n->sinistro);
    while(n->padre && n->padre->sinistro == n)
        n = n->padre;
    return n->padre;
}

int main()
{
    albbinric<int> a;
    a.insert(3);
    a.insert(2);
    a.insert(3);
    a.insert(1);
    a.insert(6);
    a.insert(5);
    cout << a;

    cout << "minimo: " << albbinric<int>::valore(a.min()) << '\n';
    cout << "massimo: " << albbinric<int>::valore(a.max()) << '\n';
    cout << "minimo seguente: " << albbinric<int>::valore(a.succ(a.min())) << '\n';
    if(a.find(2) == 0)
        cout << "non c'e' il numero 2\n";
    else
        cout << "c'e' il numero 2\n";
    return 0;
}
