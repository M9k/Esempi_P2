#include <iostream>
using std::cout;

class A{
public: A() { cout << "A" ;}
};

class B: virtual public A{
public: B() { cout << "B" ;}
};
class C: virtual public A{
public: C(): A() { cout << "C" ;}
};
class D: virtual public B, virtual public C{
public: D(): C(), B() { cout << "D" ;}
};

//----parte di test
// class E: virtual public B{ public: E() { cout << "E" ;}  };
// class F: virtual public E, virtual public C{ public: F() { cout << "F" ;}  };
// A B E C F
//----parte di test
// class E: public B{ public: E() { cout << "E" ;}  };
// class F: virtual public E, virtual public C{ public: F() { cout << "F" ;}  };
// A B E C F
// ----parte di test
// class E: public D { public: E() : B() { cout << "E" ;}  };
// class F: virtual public E { public: F() { cout << "F" ;}  };
// A B C D E F
//----parte di test
// class E: public D { public: E() : B() { cout << "E" ;}  };
// class F: public E { public: F() { cout << "F" ;}  };
// A B C D E F
//----parte di test
// class F:  public B, virtual public C { public: F() { cout << "F" ;}  };
// A C B F
//----parte di test
class E: public B { public: E() { cout << "E" ;}  };
class F: public E, virtual public C { public: F() { cout << "F" ;}  };
// A C B E F
int main()
{
	F f;
	return 0;
}