template <class T> class C
{
	public:
	class D
	{
		public:
		T x;
	};
	
	template <class U> class E
	{
		public:
		T x;
		void fun1() {return 1;}
		template<class X> class F
		{
			public:
			int i;
		};
	};
	
	template <class U> void fun2()
	{
		T x;
		return;
	}
	
	template <class U> void fun3()
	{
		return;
	}
};

template <class T>
void templateFun(typename C<T>::D d)
{
	//indico con typename e template tutto quello che può "variare" in base a T
	
	C<T> c;
	C<int> ci;
	typename C<T>::D d1; //d1 dipende da C<T>, D non è templarizzata
	C<int>::D d2;
	typename C<T>::template E<T> e; //e dipende da E<T> che a sua volta dipende da C<T>
	
	C<int>::E<int> e2; //e2 non dipende da nulla, usa E<int> contenuta in C<int>
	typename C<int>::template E<int> e4; //ok anche specificare, ma non necessario 
	
	typename C<T>::template E<double> e3; //e3 dipende da E<double> che a sua volta dipende da C<T>, E<double> non posso determinarlo senza conoscere T
	C<double>::template E<T> e5; //e5 dipende solo da E<T>
	e.fun1();
	e2.fun1();
	e3.fun1();
	
	c.template fun2<T>();
	c.template fun2<int>(); //fun2 dipende dal tipo T essendo contenuta in C<T>, in base a come è inizializzato c può essere diversa
	
	c.template fun3<int>; //non importa se fun3 usa o no T di C<T>, è dentro a C<T> quindi non so quale istanza verrà usata finchè non so T
	/*
		typename per i tipi
		template per funzioni e classi
	*/
	
	typename C<T>::template E<T>::template F<T> k1;
	typename C<int>::E<T>::template F<T> k2; //E<T> adesso non dipende più da T di C<T> essendo C<int>
	typename C<int>::E<double>::F<T> k3;
	C<int>::E<double>::F<char> k4;
	// il primo typename/template si riferisce al membro "finale", gli altri al successivo
	//ovviamente il primo non dipende da nulla
	
	
	//dal primo T che trovo o dal primo oggetto istanziato secondo il tipo T devo iniziare a specificare typename e template
}



int main()
{
	return 0;
}