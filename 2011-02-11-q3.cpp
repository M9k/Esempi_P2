namespace ns {
	class C {
	public:
		C(int n=0) : x(n) {}
	private:
		friend int f(); // -> int ns::f()
		int x;
	};
}

int f() {
	ns::C c;
	return c.x;
}

int main() {
	f();
	return 0;
}