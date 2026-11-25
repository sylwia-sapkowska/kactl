#pragma once
// Compatibility layer for tests ported from acmlib (tonowak).
// The ported file defines void test(); main() runs it repeatedly for ACMLIB_SECONDS.

typedef long long LL;
#define FOR(i, l, r) for(int i = (l); i <= (r); ++i)
#define REP(i, n) FOR(i, 0, (n) - 1)
template<class T> int ssize(const T& x) { return int(x.size()); }
#define debug(...) {}

void test();

mt19937 rng(0);
int rd(int l, int r) {
	return uniform_int_distribution<int>(l, r)(rng);
}
LL rd_ll(LL l, LL r) {
	return uniform_int_distribution<LL>(l, r)(rng);
}

#ifndef ACMLIB_SECONDS
#define ACMLIB_SECONDS 2
#endif
int main() {
	auto start = chrono::steady_clock::now();
	int test_no = 0;
	while(chrono::steady_clock::now() - start < chrono::seconds(ACMLIB_SECONDS)) {
		test();
		++test_no;
	}
	cout << "Tests passed! (" << test_no << ")" << endl;
}
