#include "../utilities/template.h"

#include "../../content/various/TernarySearch.h"

mt19937 gen(1234);
int rd(int l, int r) { return uniform_int_distribution<int>(l, r)(gen); }

int main() {
	rep(it,0,200000) {
		// f strictly increasing up to some peak, then non-increasing
		int n = rd(1, it < 1000 ? 2000 : 30), peak = rd(0, n - 1);
		vi f(n);
		f[peak] = rd(-5, 5);
		for (int i = peak - 1; i >= 0; --i) f[i] = f[i + 1] - rd(1, 3);
		rep(i,peak + 1,n) f[i] = f[i - 1] - rd(0, 2);
		int a = rd(0, n - 1), b = rd(a, n - 1);
		int expected = a;
		rep(i,a,b + 1) if (f[i] > f[expected]) expected = i;
		int calls = 0;
		int got = ternSearch(a, b, [&](int i) { ++calls; assert(a <= i && i <= b); return f[i]; });
		assert(got == expected);
		if (b - a >= 100) assert(calls <= 100);
	}
	cout << "Tests passed!" << endl;
}
